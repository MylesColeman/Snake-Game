#include "Snake.h"
#include <iostream>

Snake::Snake(int type)
{
	m_controlType = type;
}

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

void Snake::MovementInput()
{
	// The control scheme for both players
	if (m_controlType == 0)
	{
		// Checks for keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && m_previousDirection != Direction::Down)
		{
			m_direction = Direction::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && m_previousDirection != Direction::Up)
		{
			m_direction = Direction::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && m_previousDirection != Direction::Right)
		{
			m_direction = Direction::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && m_previousDirection != Direction::Left)
		{
			m_direction = Direction::Right;
		}
	}
	else if (m_controlType == 1)
	{
		// Checks for keyboard input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_previousDirection != Direction::Down)
		{
			m_direction = Direction::Up;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_previousDirection != Direction::Up)
		{
			m_direction = Direction::Down;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && m_previousDirection != Direction::Right)
		{
			m_direction = Direction::Left;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && m_previousDirection != Direction::Left)
		{
			m_direction = Direction::Right;
		}
	}
}

void Snake::Update()
{
	std::cout << m_headPosition.x << " and " << m_headPosition.y << std::endl;
	// Causes the snake to move
	switch (m_direction)
	{
	case Direction::Up:
		m_headPosition.y -= segmentSize;
		m_previousDirection = Direction::Up;
		break;
	case Direction::Down:
		m_headPosition.y += segmentSize;
		m_previousDirection = Direction::Down;
		break;
	case Direction::Left:
		m_headPosition.x -= segmentSize;
		m_previousDirection = Direction::Left;
		break;
	case Direction::Right:
		m_headPosition.x += segmentSize;
		m_previousDirection = Direction::Right;
		break;
	default:
		std::cout << "Error - Unknown Direction" << std::endl;
		break;
	}
}