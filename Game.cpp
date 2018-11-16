#include "Game.h"

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
                if( event.key.code == Keyboard::A )
                    player.setDirection('A', false);
                if( event.key.code == Keyboard::D )
                    player.setDirection('D', false);
                if( event.key.code == Keyboard::W )
                    player.setDirection('W', false);
                if( event.key.code == Keyboard::S )
                    player.setDirection('S', false);
                break;
            case Event::KeyPressed:
                if(Keyboard::isKeyPressed(Keyboard::A) )
                    player.setDirection('A', true);
                if(Keyboard::isKeyPressed(Keyboard::D) )
                    player.setDirection('D', true);
                if(Keyboard::isKeyPressed(Keyboard::W) )
                    player.setDirection('W', true);
                if(Keyboard::isKeyPressed(Keyboard::S) )
                    player.setDirection('S', true);                
                break;
        }
    }
}

void Game::update(){
    player.update(&window);
}

void Game::render()
{
    window.clear(Color::White);

    window.draw(player.getBody());
    window.draw(player.getGun());

    window.display();
}

void Game::handlePlayerInput(bool isPressed){

}
