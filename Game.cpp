<<<<<<< HEAD
alşsdkfşlksşdfg
=======
#include "Game.h"

Game::Game() : window(sf::VideoMode(WIDTH, HEIGHT), "Name of Application")
{
    window.setFramerateLimit(60);
}

void Game::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Game::processEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        }
    }
}

void Game::update()
{
}

void Game::render()
{
    window.clear();

    //draw()

    window.display();
}
>>>>>>> 19667e71e64f5d9d46b2e87080cdcb222d9247ed
