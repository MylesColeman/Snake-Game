#include "Wall.h"

void Wall::Draw(sf::RenderWindow& window)
{
	sf::RectangleShape leftTankWall({ (10.0f), (1200.0f) });
	leftTankWall.setFillColor(sf::Color(90, 60, 11));
	leftTankWall.setOutlineThickness(-3.0f);
	leftTankWall.setOutlineColor(sf::Color(136, 91, 19));
	leftTankWall.setOrigin({ (5.0f), (600.0f) });
	leftTankWall.setPosition({ (135.0f), (600.0f) });

	sf::RectangleShape rightTankWall({ (10.0f), (1200.0f) });
	rightTankWall.setFillColor(sf::Color(90, 60, 11));
	rightTankWall.setOutlineThickness(-3.0f);
	rightTankWall.setOutlineColor(sf::Color(136, 91, 19));
	rightTankWall.setOrigin({ (5.0f), (600.0f) });
	rightTankWall.setPosition({ (1915.0f), (600.0f) });

	sf::RectangleShape tankFloor({ (1770.0f), (10.0f) });
	tankFloor.setFillColor(sf::Color(90, 60, 11));
	tankFloor.setOutlineThickness(-3.0f);
	tankFloor.setOutlineColor(sf::Color(136, 91, 19));
	tankFloor.setOrigin({ (885.0f), (5.0f) });
	tankFloor.setPosition({ (1025.0f), (1195.0f) });

	sf::RectangleShape tankSurface({ (1770.0f),(50.0f) });
	tankSurface.setFillColor(sf::Color(223, 212, 133));
	tankSurface.setOutlineThickness(-3.0f);
	tankSurface.setOutlineColor(sf::Color(204, 194, 112));
	tankSurface.setOrigin({ (885.0f), (25.0f) });
	tankSurface.setPosition({ (1025.0f), (1165.0f) });

	window.draw(leftTankWall);
	window.draw(rightTankWall);
	window.draw(tankFloor);
	window.draw(tankSurface);
}