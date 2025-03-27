#include "Wall.h"

void Wall::Draw(sf::RenderWindow& window)
{
	sf::RectangleShape leftTankWall({ wallWidth, (float)window.getSize().y });
	leftTankWall.setFillColor(sf::Color(90, 60, 11));
	leftTankWall.setOutlineThickness(-3.0f);
	leftTankWall.setOutlineColor(sf::Color(136, 91, 19));
	leftTankWall.setOrigin({ wallWidth / 2, (float)window.getSize().y / 2 });
	leftTankWall.setPosition({ leftWallPos - (wallWidth / 2), (float)window.getSize().y / 2 });

	sf::RectangleShape rightTankWall({ wallWidth, (float)window.getSize().y });
	rightTankWall.setFillColor(sf::Color(90, 60, 11));
	rightTankWall.setOutlineThickness(-3.0f);
	rightTankWall.setOutlineColor(sf::Color(136, 91, 19));
	rightTankWall.setOrigin({ wallWidth / 2, (float)window.getSize().y / 2 });
	rightTankWall.setPosition({ (float)window.getSize().x - (wallWidth / 2), (float)window.getSize().y / 2 });

	sf::RectangleShape tankFloor({ (float)window.getSize().x - leftWallPos - wallWidth, wallWidth });
	tankFloor.setFillColor(sf::Color(90, 60, 11));
	tankFloor.setOutlineThickness(-3.0f);
	tankFloor.setOutlineColor(sf::Color(136, 91, 19));
	tankFloor.setOrigin({ ((float)window.getSize().x - leftWallPos - wallWidth) / 2, wallWidth / 2 });
	tankFloor.setPosition({ (((float)window.getSize().x - leftWallPos - wallWidth) / 2) + leftWallPos, (float)window.getSize().y - (wallWidth / 2) });

	sf::RectangleShape tankSurface({ (float)window.getSize().x - leftWallPos - wallWidth, surfaceHeight });
	tankSurface.setFillColor(sf::Color(223, 212, 133));
	tankSurface.setOutlineThickness(-3.0f);
	tankSurface.setOutlineColor(sf::Color(204, 194, 112));
	tankSurface.setOrigin({ ((float)window.getSize().x - leftWallPos - wallWidth) / 2, surfaceHeight / 2 });
	tankSurface.setPosition({ (((float)window.getSize().x - leftWallPos - wallWidth) / 2) + leftWallPos, (float)window.getSize().y - wallWidth - (surfaceHeight / 2) });

	window.draw(leftTankWall);
	window.draw(rightTankWall);
	window.draw(tankFloor);
	window.draw(tankSurface);
}

const float& Wall::getWallWidth() const
{
	return wallWidth;
}

const float& Wall::getLeftWallPos() const
{
	return leftWallPos;
}

const float& Wall::getSurfaceHeight() const
{
	return surfaceHeight;
}