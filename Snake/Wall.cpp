#include "Wall.h"

void Wall::Draw(sf::RenderWindow& window)
{
	sf::RectangleShape leftTankWall({ (10.0f), (1200.0f) });
	leftTankWall.setFillColor(sf::Color(90, 60, 11));
	leftTankWall.setOutlineThickness(-3.0f);
	leftTankWall.setOutlineColor(sf::Color(136, 91, 19));
	leftTankWall.setOrigin({ (5.0f), (600.0f) });
	leftTankWall.setPosition({ (150.0f), (600.0f) });

	sf::RectangleShape rightTankWall({ (10.0f), (1200.0f) });
	rightTankWall.setFillColor(sf::Color(90, 60, 11));
	rightTankWall.setOutlineThickness(-3.0f);
	rightTankWall.setOutlineColor(sf::Color(136, 91, 19));
	rightTankWall.setOrigin({ (5.0f), (600.0f) });
	rightTankWall.setPosition({ (1915.0f), (600.0f) });

	sf::RectangleShape tankFloor({ (1755.0f), (10.0f) });
	tankFloor.setFillColor(sf::Color(90, 60, 11));
	tankFloor.setOutlineThickness(-3.0f);
	tankFloor.setOutlineColor(sf::Color(136, 91, 19));
	tankFloor.setOrigin({ (877.5f), (5.0f) });
	tankFloor.setPosition({ (1032.5f), (1195.0f) });

	sf::RectangleShape tankSurface({ (1755.0f),(40.0f) });
	tankSurface.setFillColor(sf::Color(223, 212, 133));
	tankSurface.setOutlineThickness(-3.0f);
	tankSurface.setOutlineColor(sf::Color(204, 194, 112));
	tankSurface.setOrigin({ (877.5f), (20.0f) });
	tankSurface.setPosition({ (1032.5f), (1170.0f) });

	window.draw(leftTankWall);
	window.draw(rightTankWall);
	window.draw(tankFloor);
	window.draw(tankSurface);
}