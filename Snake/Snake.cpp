#include "Snake.h"
#include <iostream>

void Snake::Display(sf::RenderWindow &window)
{
	sf::RectangleShape snakeHead({ (20.0f), (20.0f) });
	snakeHead.setFillColor(sf::Color::Green);
	snakeHead.setOutlineThickness(-3.0f);
	snakeHead.setOutlineColor(sf::Color::Cyan);
	snakeHead.setOrigin({ (10.0f), (10.0f) });
	snakeHead.setPosition({ (headPosX), (headPosY) });

	window.draw(snakeHead);
}

void Snake::Update()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	{
		m_direction = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	{
		m_direction = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		m_direction = Direction::Up;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		m_direction = Direction::Up;
	}

	switch (m_direction)
	{
	case Snake::Direction::Up:
		headPosY -= 20;
		break;
	case Snake::Direction::Down:
		headPosY += 20;
		break;
	case Snake::Direction::Left:
		headPosX -= 20;
		break;
	case Snake::Direction::Right:
		headPosX += 20;
		break;
	}

	std::cout << headPosX << std::endl;
}