#include "Game.h"

const float simulationTimer = 0.2f;

void Game::Run()
{
    sf::RenderWindow window(sf::VideoMode({ 1920,1200 }), "GSE - Snake Game - E4109732");

    sf::Clock simulationClock;

    for (int i = 0; i < 2; i++)
        m_snakeVector.push_back(new Snake(i));

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

        for (Snake* snake : m_snakeVector)
            snake->Display(window);

        m_playerSnake.MovementInput();

        if (simulationClock.getElapsedTime().asSeconds() >= simulationTimer)
        {
            for(Snake* snake: m_snakeVector)
                snake->Update();
            simulationClock.restart();
        }

        window.display();
    }

    for (Snake* snake : m_snakeVector)
        delete snake;
}