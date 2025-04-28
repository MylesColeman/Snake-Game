#pragma once
#include <SFML/Graphics.hpp>
#include "Linked List.h"
#include "Vine.h"

class Water;
class Wall;

class Collectable
{
private:
	bool m_isAlive{ false };

	int m_collectableValue{ 1 };

	sf::Vector2f m_fruitPosition{ 395.0f, 900.0f };

	Vine m_vine;
public:
	Collectable(sf::Vector2f fruitPosition);
	void Draw(sf::RenderWindow& window);
	void Spawn(sf::Vector2f pos, sf::RenderWindow& window, const Wall& tankWalls);
	void Update(const Water& water);

	const bool& getCollectableAliveStatus() const;
	void setToDead(bool isAlive);

	const sf::Vector2f& getCollectablePosition() const;
	const int& getCollectableValue() const;

	const bool& getIsVineFullyGrown() const;
};