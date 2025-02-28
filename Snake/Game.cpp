#include "Game.h"

const float simulationTimer = 0.2f;

void Game::Run()
{
    sf::RenderWindow window(sf::VideoMode({ 1920,1200 }), "GSE - Snake Game - E4109732");

    sf::Clock simulationClock;

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

        m_tankWalls.Draw(window);

        m_playerSnake.Display(window);
        m_playerSnake.MovementInput();

        if (simulationClock.getElapsedTime().asSeconds() >= simulationTimer)
        {
            m_playerSnake.Update();
            simulationClock.restart();
        }

        window.display();
    }
}