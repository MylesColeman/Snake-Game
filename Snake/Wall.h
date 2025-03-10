#pragma once
#include <SFML/Graphics.hpp>

class Wall
{
private: 
	float wallWidth{ 10.0f };
	float leftWallPos{ 140 };
	float surfaceHeight{ 50 };
public: 
	void Draw(sf::RenderWindow& window);

	const float& getWallWidth() const;
	const float& getLeftWallPos() const;
	const float& getSurfaceHeight() const;
};