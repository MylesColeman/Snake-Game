#include "Game.h"
#include <iostream>

const float simulationTimer = 0.2f;

sf::Vector2f GetRandomFreePosition(int screenWidth, int screenHeight)
{
    int rangeX = screenWidth - 150;
    int rangeY = screenHeight - 60;

    int randomX = rand() % (rangeX / (int)Snake::segmentSize) * (int)Snake::segmentSize;
    int randomY = rand() % (rangeY / (int)Snake::segmentSize) * (int)Snake::segmentSize;

    return sf::Vector2f((float)randomX + 155, (float)randomY + 15);
}

void Game::Run()
{
    srand((unsigned int)time(0));

    sf::RenderWindow window(sf::VideoMode({ 1920, 1200 }), "GSE - Snake Game - E4109732", sf::State::Fullscreen);

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
            {
                snake->Update();
                
                // Loops through the collectables vector only incrementing if a collision isn't detected
                for (auto it = m_collectableVector.begin(); it != m_collectableVector.end();)
                {
                    if (snake->getSegmentList().front() == (*it)->getCollectablePosition())
                    {
                        snake->GrowAmount((*it)->getCollectableValue());
                        delete* it;
                        it = m_collectableVector.erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }
            }
                
            // Rolls a dice 1 to 20, and if 1 lands checks whether a new collectable can be created (limit of 5)
            if (rand() % 20 == 0)
            {
                if (m_collectableVector.size() < 5)
                {
                    m_collectableVector.push_back(new Collectable(rand() % 3 + 1, GetRandomFreePosition(window.getSize().x, window.getSize().y)));
                }
            }

            simulationClock.restart();
        }

        window.clear(); // Resets the window for use

        m_tankWalls.Draw(window);

        for (Snake* snake : m_snakeVector)
        {
            snake->Draw(window);
            snake->MovementInput();
        }

        for (Collectable* collectable : m_collectableVector)
        {
            collectable->Draw(window);
        }

        window.display();
    }

    for (Snake* snake : m_snakeVector)
        delete snake;

    for (Collectable* collectable : m_collectableVector)
        delete collectable;
}