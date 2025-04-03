#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include "Linked List.h"

enum class Direction
{
	Up,
	Down,
	Left,
	Right,
	None
};

class Collectable;
class Wall;
class Water;

class Snake
{
private:
	int m_controlType{ 0 }; // Used to determine a player 1 and 2, and their control scheme
	bool m_isAlive{ true };

	LinkedList<sf::Vector2f> m_segmentList;
	int m_startingSegments{ 4 };
	int m_growAmount{ 0 };
	int m_breath{ 50 };

	Direction m_direction{ Direction::Right };
	Direction m_previousDirection{ Direction::Right };

	bool m_atBottom{ false };
	bool m_deadLoop{ false };
public:
	inline static float segmentSize = 30.0f;

	Snake(int type, sf::Vector2f headPosition);

	void Draw(sf::RenderWindow& window); // Defines and displays the snake
	void MovementInput(); // Handles the input for movement
	void Update(); // Handles the snake's movement

	void Drowning(const Water& water);

	void CollectableCollision(std::vector<Collectable*>& collectableVector);
	void BoundsCollision(sf::RenderWindow& window, const Wall& tankWalls);
	void OtherSnakeCollision(Snake* other);
	void RemoveSegment(int index);
	void SelfCollision();

	void GrowAmount(int amount);

	void isDead(sf::RenderWindow& window, const Wall& tankWalls);

	const LinkedList<sf::Vector2f>& getSegmentList() const;
	const bool& getIsAlive() const;
	void setToDead(bool isAlive);
};