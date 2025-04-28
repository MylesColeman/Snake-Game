#pragma once
#include <SFML/Graphics.hpp>
#include "Linked List.h"

class Collectable;
class Wall;

class Vine
{
private:
	sf::Texture m_vineTexture;

	LinkedList<sf::Vector2f> m_vineList;
	float m_vinePosition{ -100.0f };

	sf::Clock m_growthClock;
	float m_fullyGrownTime{ 3.0f };
	float m_growTime{ };

	bool m_vineIsFullyGrown{ false };
public:
	Vine(sf::Vector2f fruitPosition);

	void Draw(sf::RenderWindow& window, const Collectable* collectable);
	void Update(sf::RenderWindow& window, const Wall& tankWalls, const Collectable* collectable);

	void outOfWater(const Collectable* collectable);

	const bool& getVineIsFullyGrown() const;
};