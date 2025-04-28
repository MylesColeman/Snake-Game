#pragma once
#include <SFML/Graphics.hpp>

class Wall;

class Water
{
private:
	sf::RectangleShape m_water;

	float m_waterLevel{ 570 };
	float m_waterRatio{ 0 };
	float m_predictedNextWaterPosition{ 0 };
public:
	Water(const sf::RenderWindow& window, const Wall& tankWalls);
	void Draw(sf::RenderWindow& window, const Wall& tankWalls);
	void Update(const sf::Time& gameTimer, const sf::Time& gameTime); // Handles the water level sinking

	void reset(const sf::RenderWindow& window, const Wall& tankWalls);

	const float& getPredictedNextWaterPosition() const;
};