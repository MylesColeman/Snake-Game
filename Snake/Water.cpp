#include "Water.h"
#include "Wall.h"
#include "Snake.h"

Water::Water(const sf::RenderWindow& window, const Wall& tankWalls)
{
	waterLevel = (((float)window.getSize().y - tankWalls.getSurfaceHeight() - tankWalls.getWallWidth()) / 2); // Sets the starting water level
}

void Water::Draw(sf::RenderWindow& window, const Wall& tankWalls)
{
	sf::RectangleShape water({ (float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth(), (float)window.getSize().y - tankWalls.getSurfaceHeight() - tankWalls.getWallWidth() });
	water.setFillColor(sf::Color(12, 56, 133, 90));
	water.setOrigin({ ((float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth()) / 2, ((float)window.getSize().y - tankWalls.getSurfaceHeight() - tankWalls.getWallWidth()) / 2 });
	water.setPosition({ (((float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth()) / 2) + tankWalls.getLeftWallPos(), waterLevel });

	window.draw(water);
}

void Water::Update()
{
	waterLevel += Snake::segmentSize; // Lowers the water by one snake segment
}