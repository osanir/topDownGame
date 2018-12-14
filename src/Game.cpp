#include "../include/Game.h"

Game::Game() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Top Down"){
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(true);
}

void Game::run(){
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
                handlePlayerInput(false);
                break;
            case Event::KeyPressed:
                handlePlayerInput(true);
                break;
            default:
                break;
        }
        if(Mouse::isButtonPressed(Mouse::Button::Left))
            player.fire();
    }
}

void Game::update(){
    player.update(&window);
    player.collision(map.getSolidObjets());
    camera.update(player.getBody().getPosition());
}

void Game::render()
{
    window.clear(Color::White);
    map.drawTile(window);
    window.setView(camera.getView());
    
    window.draw(player.getBody());
    window.draw(player.getGun());
    

    list<Bullet> bullets = player.getBullets();
    list<Bullet>::iterator iter = bullets.begin();
    while( iter != bullets.end() ){
        window.draw(iter->body);
        iter++;
    }

/*     for(auto iter : map.getSolidObjets() ){
        window.draw(*iter);
    }
 */    window.display();
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
