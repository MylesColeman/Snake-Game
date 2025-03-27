#pragma once
#include <SFML/Graphics.hpp>

class Wall;

class Water
{
private:
	float m_waterLevel{ 570 };
	float m_waterRatio{ 0 };
public:
	Water(const sf::RenderWindow& window, const Wall& tankWalls);
	void Draw(sf::RenderWindow& window, const Wall& tankWalls);
	void Update(const sf::Time& time); // Handles the water level sinking
};