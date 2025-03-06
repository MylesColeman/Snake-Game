#pragma once
#include <SFML/Graphics.hpp>
#include <list>

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

	std::list<sf::Vector2f> m_segmentList;
	int m_startingSegments{ 4 };
	int m_growAmount{ 0 };

	Direction m_direction{ Direction::Right };
	Direction m_previousDirection{ Direction::Right };
public:
	inline static float segmentSize = 30.0f;

	Snake(int type, sf::Vector2f headPosition);

	void Draw(sf::RenderWindow &window); // Defines and displays the snake
	void MovementInput(); // Handles the input for movement
	void Update(); // Handles the snake's movement
};