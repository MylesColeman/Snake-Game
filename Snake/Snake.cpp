#include "Snake.h"

void Snake::Display(sf::RenderWindow &window)
{
	sf::RectangleShape snakeSegment({ (segmentSize), (segmentSize) });
	snakeSegment.setFillColor(sf::Color::Green);
	snakeSegment.setOutlineThickness(-3.0f);
	snakeSegment.setOutlineColor(sf::Color::Cyan);
	snakeSegment.setOrigin({ (10.0f), (10.0f) });
	snakeSegment.setPosition({ (headPosX), (headPosY) });

	window.draw(snakeSegment);
}

void Snake::Update()
{
	// Checks for keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && m_direction != Direction::Down)
	{
		m_direction = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && m_direction != Direction::Up)
	{
		m_direction = Direction::Down;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && m_direction != Direction::Right)
	{
		m_direction = Direction::Left;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && m_direction != Direction::Left)
	{
		m_direction = Direction::Right;
	}

	// Causes the snake to move every 0.2 seconds
	sf::Time elapstedTime = clock.getElapsedTime();
	if (elapstedTime.asSeconds() >= 0.2f)
	{
		switch (m_direction)
		{
		case Snake::Direction::Up:
			headPosY -= segmentSize;
			break;
		case Snake::Direction::Down:
			headPosY += segmentSize;
			break;
		case Snake::Direction::Left:
			headPosX -= segmentSize;
			break;
		case Snake::Direction::Right:
			headPosX += segmentSize;
			break;
		}

		clock.restart();
	}
}