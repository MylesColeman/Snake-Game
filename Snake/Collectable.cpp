#include "Collectable.h"
#include "Snake.h"
#include "Water.h"
#include "Wall.h"
#include "Vine.h"

Collectable::Collectable(sf::Vector2f fruitPosition) : m_fruitPosition(fruitPosition), m_vine(fruitPosition) {}

void Collectable::Draw(sf::RenderWindow& window)
{
	m_vine.Draw(window, this); // Draws the vine

	if (m_vine.getVineIsFullyGrown())
	{
		sf::CircleShape collectableFruit(Snake::segmentSize / 2);
		collectableFruit.setOutlineThickness(-3.0f);
		collectableFruit.setOrigin(collectableFruit.getGlobalBounds().getCenter());
		collectableFruit.setPosition(m_fruitPosition);

		if (m_collectableValue == 1) // Red
		{
			collectableFruit.setFillColor({ (233), (26), (26) });
			collectableFruit.setOutlineColor({ (168), (21), (21) });
		}
		else if (m_collectableValue == 2) // Green
		{
			collectableFruit.setFillColor({ (66), (222), (23) });
			collectableFruit.setOutlineColor({ (50), (155), (21) });
		}
		else if (m_collectableValue == 3) // Blue
		{
			collectableFruit.setFillColor({ (17), (48), (224) });
			collectableFruit.setOutlineColor({ (15), (34), (142) });
		}

		if (!m_isAlive) // Turns collectable transparent, if collectable is dead
		{
			collectableFruit.setFillColor({ (0), (0), (0), (0) });
			collectableFruit.setOutlineColor({ (0),(0),(0),(0) });
		}

		window.draw(collectableFruit);
	}
}

// Sets default collectable variables for spawning
void Collectable::Spawn(sf::Vector2f pos, sf::RenderWindow& window, const Wall& tankWalls)
{
	m_fruitPosition = pos;

	m_isAlive = true;
	m_collectableValue = rand() % 3 + 1;

	m_vine.Update(window, tankWalls, this); // Sets the vine's nodes up
}

void Collectable::Update(const Water& water)
{
	if (m_fruitPosition.y < water.getPredictedNextWaterPosition() - Snake::segmentSize)
		m_fruitPosition.y += Snake::segmentSize;

	m_vine.outOfWater(this);
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

// Necessary so the snake only eats fully grown fruit
const bool& Collectable::getIsVineFullyGrown() const
{
	return m_vine.getVineIsFullyGrown();
}
