#include "Collectable.h"
#include "Snake.h"
#include <iostream>

Collectable::Collectable(int value, sf::Vector2f fruitPosition) : m_collectableValue(value), m_fruitPosition(fruitPosition)
{

}

void Collectable::Draw(sf::RenderWindow& window)
{
	sf::CircleShape collectableFruit(Snake::segmentSize / 2);
	collectableFruit.setOutlineThickness(-3.0f);
	collectableFruit.setOrigin({ (Snake::segmentSize / 2), (Snake::segmentSize / 2) });
	collectableFruit.setPosition(m_fruitPosition);

	if (m_collectableValue == 1) // Red
	{
		collectableFruit.setFillColor({ (233), (26), (26) });
		collectableFruit.setOutlineColor({ (168), (21), (21) });
	}
	else if (m_collectableValue == 2)
	{
		collectableFruit.setFillColor({ (66), (222), (23) }); // Green
		collectableFruit.setOutlineColor({ (50), (155), (21) });
	}
	else if (m_collectableValue == 3)
	{
		collectableFruit.setFillColor({ (17), (48), (224) }); // Blue
		collectableFruit.setOutlineColor({ (15), (34), (142) });
	}

	if (!m_isAlive)
	{
		collectableFruit.setFillColor({ (0), (0), (0), (0) });
		collectableFruit.setOutlineColor({ (0),(0),(0),(0) });
	}

	window.draw(collectableFruit);
}

const bool& Collectable::getCollectableAliveStatus() const
{
	return m_isAlive;
}

void Collectable::setToDead(bool isAlive)
{
	m_isAlive = isAlive;
}

const sf::Vector2f& Collectable::getCollectablePosition() const
{
	return m_fruitPosition;
}

const int& Collectable::getCollectableValue() const
{
	return m_collectableValue;
}