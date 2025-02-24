#pragma once
#include <SFML/Graphics.hpp>

class Snake
{
private:
	float headPosX = 20.0f, headPosY = 20.0f;
	enum class Direction { Up, Down, Left, Right };
	Direction m_direction = Direction::Right;

public:
	void Display(sf::RenderWindow &window); // Defines and displays the snake
	void Update(); // Handles snake movement and other updates
};