#pragma once
#include <SFML/Graphics.hpp>

enum class Direction
{
	Up,
	Down,
	Left,
	Right
};

class Snake
{
private:
	float segmentSize = 30.0f;
	sf::Vector2f m_headPosition{ 395.0f, 1125.0f };

	sf::Clock clock;

	Direction m_direction{ Direction::Right };

public:
	void Display(sf::RenderWindow &window); // Defines and displays the snake
	void Update(); // Handles snake movement and other updates
};