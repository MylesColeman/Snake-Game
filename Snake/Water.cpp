#include "Water.h"
#include "Wall.h"
#include "Snake.h"

Water::Water(const sf::RenderWindow& window, const Wall& tankWalls)
{
	m_waterLevel = ((float)window.getSize().y - tankWalls.getSurfaceHeight() - tankWalls.getWallWidth()); // Sets the starting water level
}

void Water::Draw(sf::RenderWindow& window, const Wall& tankWalls)
{
	sf::RectangleShape water({ (float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth(), m_waterLevel });
	water.setFillColor(sf::Color(12, 56, 133, 90)); // Dark Blue
	water.setOrigin({ ((float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth()) / 2, m_waterLevel / 2 });
	water.setPosition({ (((float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth()) / 2) + tankWalls.getLeftWallPos(), (m_waterLevel / 2) * m_waterRatio });

	window.draw(water);
}

void Water::Update(const sf::Time& time)
{
	m_waterRatio = time.asSeconds() / 90.0f;
}