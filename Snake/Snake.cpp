#include "Snake.h"

void Snake::Display(sf::RenderWindow &window)
{
	sf::RectangleShape snakeHead({ (20.0f), (20.0f) });
	snakeHead.setFillColor(sf::Color::Green);
	snakeHead.setOutlineThickness(-3.0f);
	snakeHead.setOutlineColor(sf::Color::Cyan);
	snakeHead.setOrigin({ (10.0f), (10.0f) });
	snakeHead.setPosition({ (20.0f), (20.0f) });

	window.draw(snakeHead);
}