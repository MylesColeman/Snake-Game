#pragma once
#include <SFML/Graphics.hpp>
#include "Linked List.h"

class Wall;
class Collectable;

class Vine
{
private:
	LinkedList<sf::Vector2f> m_vineList;
	float m_vinePosition{ -100.0f };
public:
	void Draw(sf::RenderWindow& window, std::vector<Collectable*>& collectableVector);
	void Update(sf::RenderWindow& window, const Wall& tankWalls, std::vector<Collectable*>& collectableVector);
};