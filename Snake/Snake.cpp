#include "Snake.h"
#include <iostream>

void Snake::Display(sf::RenderWindow &window)
{
	sf::RectangleShape snakeSegment({ (segmentSize), (segmentSize) });
	snakeSegment.setFillColor(sf::Color::Green);
	snakeSegment.setOutlineThickness(-3.0f);
	snakeSegment.setOutlineColor(sf::Color::Cyan);
	snakeSegment.setOrigin({ (segmentSize / 2), (segmentSize / 2) });
	snakeSegment.setPosition(m_headPosition);

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
		case Direction::Up:
			m_headPosition.y -= segmentSize;
			break;
		case Direction::Down:
			m_headPosition.y += segmentSize;
			break;
		case Direction::Left:
			m_headPosition.x -= segmentSize;
			break;
		case Direction::Right:
			m_headPosition.x += segmentSize;
			break;
		default:
			std::cout << "Error - Unknown Direction" << std::endl;
		}

		clock.restart();
	}
}