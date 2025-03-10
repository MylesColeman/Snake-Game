#include "Game.h"
#include <iostream>

const float simulationTimer = 0.2f;

sf::Vector2f GetRandomFreePosition(int screenWidth, int screenHeight, Wall tankWalls, std::vector<Snake*> snakeVector, std::vector<Collectable*> collectableVector)
{
    int posBuffer = 300;

    int rangeX = screenWidth - (int)tankWalls.getLeftWallPos() - (int)tankWalls.getWallWidth() - posBuffer;
    int rangeY = screenHeight - (int)tankWalls.getSurfaceHeight() - (int)tankWalls.getWallWidth() - posBuffer;

    int randomX = (rand() % (rangeX / (int)Snake::segmentSize) * (int)Snake::segmentSize) + ((int)Snake::segmentSize / 2) +(int)tankWalls.getLeftWallPos() + (int)Snake::segmentSize + (posBuffer / 2);
    int randomY = (rand() % (rangeY / (int)Snake::segmentSize) * (int)Snake::segmentSize) + ((int)Snake::segmentSize / 2) + (posBuffer / 2);
    sf::Vector2f randomVector = { (float)randomX, (float)randomY };

    // Ensures the position is free, checking off the snake
    for (Snake* snake : snakeVector)
    {
        for (const auto& segment : snake->getSegmentList())
        {
            if (randomVector == segment)
            {
                return GetRandomFreePosition(screenWidth, screenHeight, tankWalls, snakeVector, collectableVector);
            }
        }
    }

    // Ensures the position is free, checking off the collectabkes x value. - As only one fruit can grow in each collumn
    for (Collectable* collectable : collectableVector)
    {
        if (randomVector.x == collectable->getCollectablePosition().x)
        {
            return GetRandomFreePosition(screenWidth, screenHeight, tankWalls, snakeVector, collectableVector);
        }
    }

    return randomVector;
}

void Game::Run()
{
    srand((unsigned int)time(0));

    sf::RenderWindow window(sf::VideoMode({ 1920, 1200 }), "GSE - Snake Game - E4109732", sf::State::Fullscreen);

    sf::Clock simulationClock;

    for (int i = 0; i < 2; i++)
        m_snakeVector.push_back(new Snake(i, GetRandomFreePosition(window.getSize().x, window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector)));

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

                if (snake->getSegmentList().front().x < m_tankWalls.getLeftWallPos() - (m_tankWalls.getWallWidth() / 2) || snake->getSegmentList().front().x > window.getSize().x - m_tankWalls.getWallWidth() || snake->getSegmentList().front().y < 0)
                {
                    std::cout << "Outside Bounds" << std::endl;
                }
                else if (snake->getSegmentList().front().y > window.getSize().y - m_tankWalls.getWallWidth() - m_tankWalls.getSurfaceHeight())
                {
                    std::cout << "Hit Floor" << std::endl;
                }
            }
                
            // Rolls a dice 1 to 20, and if 1 lands checks whether a new collectable can be created (limit of 5)
            if (rand() % 20 == 0)
            {
                if (m_collectableVector.size() < 5)
                {
                    m_collectableVector.push_back(new Collectable(rand() % 3 + 1, GetRandomFreePosition(window.getSize().x, window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector))); // Creates a collectable and assigns it a random value
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