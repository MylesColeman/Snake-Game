#pragma once
#include <SFML/Graphics.hpp>

class Snake
{
private:
	float segmentSize = 30.0f;
	float headPosX = 395.0f, headPosY = 1125.0f;

	sf::Clock clock;

	enum class Direction { Up, Down, Left, Right, Error};
	Direction m_direction = Direction::Error;

public:
	void Display(sf::RenderWindow &window); // Defines and displays the snake
	void Update(); // Handles snake movement and other updates
};