#pragma once
#include <SFML/Graphics.hpp>
#include "Linked List.h"
#include "GameData.h"

enum class Direction
{
	Up,
	Down,
	Left,
	Right,
	None
};

enum class SnakeType
{
	Player,
	AI
};

class Collectable;
class Wall;
class Water;

class Snake
{
private:
	LinkedList<sf::Vector2f> m_segmentList;
	int m_startingSegments{ 4 };
	int m_growAmount{ 0 };

	int m_maxBreath{ 50 };

	sf::Clock m_survivalClock;
	int m_score{ 0 };

	bool m_atBottom{ false };
	bool m_deadLoop{ false };
protected:
	int m_breath{ 50 };

	bool m_isAlive{ true };
	Direction m_direction{ Direction::Right };
	Direction m_previousDirection{ Direction::Right };

	void Move();
public:
	inline static float segmentSize = 30.0f;

	Snake(sf::Vector2f headPosition);

	virtual SnakeType getType() const = 0;

	void DrawSnake(sf::RenderWindow& window); // Defines and displays the snake
	void DrawUI(sf::RenderWindow& window, const Wall& tankWalls, sf::Font mainFont); // Draws the UI

	virtual void Update(GameData& m_gameData) = 0; // Handles the snake's movement
	
	void Drowning(const Water& water);

	void CollectableCollision(std::vector<Collectable*>& collectableVector);
	void BoundsCollision(sf::RenderWindow& window, const Wall& tankWalls);
	void OtherSnakeCollision(Snake* other);
	void RemoveSegment(int index);
	void SelfCollision();

	void GrowAmount(int amount);

	void stopSurvivalClock();

	void isDead(sf::RenderWindow& window, const Wall& tankWalls);

	const LinkedList<sf::Vector2f>& getSegmentList() const;
	const bool& getIsAlive() const;
	const sf::Time& getSurvivalTime() const;
	const int& getScore() const;
	void setToDead(bool isAlive);

	void resetDeadLoop();
};