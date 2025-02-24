#include "Game.h"

void Game::Run()
{
    sf::RenderWindow window(sf::VideoMode({ 1024,800 }), "GSE - Snake Game - E4109732");

    // Loops whilst the window is open
    while (window.isOpen())
    {
        // Checks if the window has been closed
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear(); // Resets the window for use

        m_snake.Display(window);
        m_snake.Update();

        window.display();
    }
}