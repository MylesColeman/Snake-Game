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
	int m_controlType{ 0 }; // Used to determine a player 1 and 2, and their control scheme

	sf::Vector2f m_headPosition{ 395.0f, 1125.0f };

	Direction m_direction{ Direction::Right };
	Direction m_previousDirection{ Direction::Right };
public:
	inline static float segmentSize = 30.0f;

	Snake(int type);

	void Display(sf::RenderWindow &window); // Defines and displays the snake
	void MovementInput(); // Handles the input for movement
	void Update(); // Handles the snake's movement
};