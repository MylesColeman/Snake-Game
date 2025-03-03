#include "Game.h"
#include "Snake.h"

const float simulationTimer = 0.2f;

sf::Vector2f GetRandomFreePosition(int screenWidth, int screenHeight)
{
    int rangeX = screenWidth - 150;
    int rangeY = screenHeight - 60;

    int randomX = rand() % (rangeX / (int)Snake::segmentSize) * Snake::segmentSize;
    int randomY = rand() % (rangeY / (int)Snake::segmentSize) * Snake::segmentSize;

    return sf::Vector2f((float)randomX + 155, (float)randomY + 15);
}

void Game::Run()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode({ 1920,1200 }), "GSE - Snake Game - E4109732");

    sf::Clock simulationClock;

    for (int i = 0; i < 2; i++)
        m_snakeVector.push_back(new Snake(i, GetRandomFreePosition(window.getSize().x, window.getSize().y)));

    // Loops whilst the window is open
    while (window.isOpen())
    {
        // Checks if the window has been closed
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        if (simulationClock.getElapsedTime().asSeconds() >= simulationTimer)
        {
            
            for (Snake* snake : m_snakeVector)
                snake->Update();
            simulationClock.restart();
        }

        window.clear(); // Resets the window for use

        m_tankWalls.Draw(window);

        for (Snake* snake : m_snakeVector)
        {
            snake->Display(window);
            snake->MovementInput();
        }

        window.display();
    }

    for (Snake* snake : m_snakeVector)
        delete snake;
}