#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
private: 
	float wallWidth{ 10.0f };
	float leftWallPos{ 140 };
public: 
	void Draw(sf::RenderWindow& window);
};