#pragma once
#include <SFML/Graphics.hpp>

class Wall;

class Water
{
private:
	float waterLevel{ 570 };
public:
	Water(const sf::RenderWindow& window, const Wall& tankWalls);
	void Draw(sf::RenderWindow& window, const Wall& tankWalls);
	void Update(); // Handles the water level sinking
};