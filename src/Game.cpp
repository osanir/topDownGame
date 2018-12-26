#include "../include/Game.h"

Game::Game() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Top Down"){
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);

    menuMusic.setMusicFile("res/TimeMachine.ogg");
    menuMusic.playMusic();
    menuButtonSound.setSoundFile("res/button.wav");
}

void Game::run(){
    // If its server, it creates 50 zombies. Client side just receive zombies;
    if( multiplayer.getConnectionType() == 's')
        enemies.createEnemy(50);
    
    while (window.isOpen()){
        processEvents();
        update();
        render();
    }
}


void Game::processEvents(){
    sf::Event event;
    while (window.pollEvent(event)){
        switch (event.type){
            case sf::Event::Closed:
                window.close();
                break;
            case Event::KeyReleased:
                if(menu.getMenuState()){
                    switch(event.key.code){
                        case Keyboard::Up:
                            menu.MoveUp();
                            menuButtonSound.playSound();
                            break;
                        case Keyboard::Down:
                            menuButtonSound.playSound();
                            menu.MoveDown();
                            break;
                        case Keyboard::Return:
                            switch(menu.getPressedItem()){
                                case 0:
                                    //start the game
                                    menu.setMenuState(false);
                                    break;
                                case 1:
                                    cout<<"Coming soon..."<<endl;
                                case 2:
                                    window.close();
                                default:
                                    break;
                            }
                        default:
                            break;
                    }
                }
                else{
                    handlePlayerInput(false);
                    break;
                }

            case Event::KeyPressed:
                handlePlayerInput(true);
                break;
            case Event::GainedFocus:
                gameFocus = true;
                multiplayer.setUpdateStatus(true);
                break;
            case Event::LostFocus:
                gameFocus = false;
                multiplayer.setUpdateStatus(false);
                break;
            default:
                break;
        }
        
        if(Mouse::isButtonPressed(Mouse::Button::Left) && gameFocus)
            player.setFireStatement( true );
        else 
            player.setFireStatement( false );
    }
}

void Game::update(){
    player.update(&window, camera.getView());
    player.collision(map.getSolidObjects());
    camera.update(player.getBody().getPosition(), map.getLayoutSize());
    window.setView(camera.getView());

    multiplayer.update(player, player2);
    for( auto enemy : enemies.getEnemies() )
        enemy->update(map.getSolidObjects());

    Packet packet;
    if( multiplayer.getConnectionType() == 's' ){   // if its server
        packet << 2;    // flag byte, 2 for zombies
        for( auto enemy : enemies.getEnemies() ){
            packet << enemy->getBody().getPosition().x << enemy->getBody().getPosition().y << enemy->getSprite().getRotation();
        }
        multiplayer.socket.send(packet);
    }
    else if( multiplayer.getConnectionType() == 'c' ){ // if its client
        multiplayer.socket.receive(packet);
        otherEnemies.clear();
        int type;
        packet >> type;
        if( type == 2 ){    // if packet keeps zombies positions
            while( !packet.endOfPacket() ){
                EnemySpr *enemy = new EnemySpr;
                float x, y, rot;
                packet >> x >> y >> rot;
                enemy->sprite.setPosition({x,y});
                enemy->sprite.setRotation(rot);
                otherEnemies.push_back(enemy);
            }
        }
    }

    // Destroying bullets or enemies
    for( list<Bullet>::iterator bullet = player.bullets.begin(); bullet != player.bullets.end(); bullet++ ){
        for( auto object : map.getSolidObjects() ){
            if( bullet->body.getGlobalBounds().intersects(object->getGlobalBounds()) ){
                player.bullets.erase(bullet);
                return;
            }
        }
        for( list<Enemy*>::iterator enemy = enemies.enemies.begin(); enemy != enemies.enemies.end(); enemy++ ){
            if( bullet->body.getGlobalBounds().intersects((*enemy)->getBody().getGlobalBounds()) ){
                player.bullets.erase(bullet);
                enemies.enemies.erase(enemy);                
                return;
            }
        }
    }

    // Destroying bullets or enemies for both side (server-client)
    for( list<Bullet>::iterator bullet = player2.bullets.begin(); bullet != player2.bullets.end(); bullet++ ){
        for( auto object : map.getSolidObjects() ){
            if( bullet->body.getGlobalBounds().intersects(object->getGlobalBounds()) ){
                player2.bullets.erase(bullet);
                return;
            }
        }
        for( list<Enemy*>::iterator enemy = enemies.enemies.begin(); enemy != enemies.enemies.end(); enemy++ ){
            if( bullet->body.getGlobalBounds().intersects((*enemy)->getBody().getGlobalBounds()) ){
                player2.bullets.erase(bullet);
                enemies.enemies.erase(enemy);                
                return;
            }
        }
    }
}

void Game::render()
{
    window.clear(Color::Black);
    if(menu.getMenuState()){
        menu.drawMenu(window);
    }
    else{
    menuMusic.pauseMusic();
    map.drawTile(window);
    
//    window.draw(player.getBody());
//    window.draw(player.getGun());
    window.draw(player.getSprite());
    window.draw(player2.playerSprite);
    
    // Drawing bullets
    for( auto &bullet : player.getBullets() ){
        window.draw(bullet.body);
    }

    // Drawing bullets which came from server
    for( auto &bullet : player2.bullets){
        window.draw(bullet.body);
    }

    // Drawing zombies
    for( auto enemy : enemies.getEnemies() )
        window.draw(enemy->getSprite());
    
    // Drawing that receiving zombie positions from server
    for( auto enemy : otherEnemies )
        window.draw(enemy->getSprite() );
    
    }

    window.display();
}

void Game::handlePlayerInput(bool keyIsPressed){


    if( !keyIsPressed ){
        if( !Keyboard::isKeyPressed(Keyboard::A) )
            player.setDirection('A', false);
        if( !Keyboard::isKeyPressed(Keyboard::D) )
            player.setDirection('D', false);
        if( !Keyboard::isKeyPressed(Keyboard::W) )
            player.setDirection('W', false);
        if( !Keyboard::isKeyPressed(Keyboard::S) )
            player.setDirection('S', false);
    }

    if( keyIsPressed ){
        if( Keyboard::isKeyPressed(Keyboard::A) )
            player.setDirection('A', true);
        if( Keyboard::isKeyPressed(Keyboard::D) )
            player.setDirection('D', true);
        if( Keyboard::isKeyPressed(Keyboard::W) )
            player.setDirection('W', true);
        if( Keyboard::isKeyPressed(Keyboard::S) )
            player.setDirection('S', true);                
    }
}
