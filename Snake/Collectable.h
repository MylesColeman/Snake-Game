#pragma once
#include <SFML/Graphics.hpp>

class Collectable
{
private:
	bool m_isAlive{ true };

	int m_collectableValue{ 1 };

	sf::Vector2f m_fruitPosition{ 395.0f, 900.0f };
public:
	Collectable(int value, sf::Vector2f fruitPosition);
	void Draw(sf::RenderWindow& window);

	const bool& getCollectableAliveStatus() const;
	void setToDead(bool isAlive);

	const sf::Vector2f& getCollectablePosition() const;
	const int& getCollectableValue() const;
};