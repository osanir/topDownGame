#include "Game.h"

Game::Game() : window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Top Down"){
    window.setFramerateLimit(60);
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
        }
    }
}

void Game::update(){
    player.move( {1, 1} );
}

void Game::render()
{
    window.clear(Color::White);

    window.draw(player.getBody());

    window.display();
}

