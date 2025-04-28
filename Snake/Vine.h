#pragma once
#include <SFML/Graphics.hpp>
#include "Linked List.h"

class Collectable;
class Wall;

class Vine
{
private:
	LinkedList<sf::Vector2f> m_vineList;
	float m_vinePosition{ -100.0f };
public:
	void Draw(sf::RenderWindow& window, const Collectable* collectable) const;
	void Update(sf::RenderWindow& window, const Wall& tankWalls, const Collectable* collectable);
};