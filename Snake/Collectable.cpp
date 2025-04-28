#include "Collectable.h"
#include "Snake.h"
#include "Water.h"
#include "Wall.h"

Collectable::Collectable(sf::Vector2f fruitPosition) : m_fruitPosition(fruitPosition) {}

void Collectable::Draw(sf::RenderWindow& window)
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

	/*Node<sf::Vector2f>* current = m_vineList.head;
	while (current != nullptr)
	{
		sf::RectangleShape fruitVine({ Snake::segmentSize, Snake::segmentSize });
		fruitVine.setFillColor(sf::Color::Green);
		fruitVine.setOrigin(fruitVine.getGlobalBounds().getCenter());
		fruitVine.setPosition( current->data );

		if (!m_isAlive)
		{
			fruitVine.setFillColor({ (0), (0), (0), (0) });
			fruitVine.setOutlineColor({ (0),(0),(0),(0) });
		}

		window.draw(fruitVine);
		current = current->next;
	}*/
	
	if (!m_isAlive) // Turns collectable transparent, if collectable is dead
	{
		collectableFruit.setFillColor({ (0), (0), (0), (0) });
		collectableFruit.setOutlineColor({ (0),(0),(0),(0) });
	}

	
	window.draw(collectableFruit);
}

// Sets default collectable variables for spawning
void Collectable::Spawn(sf::Vector2f pos, sf::RenderWindow& window, const Wall& tankWalls)
{
	/*bool m_atBottom = false;
	m_vineList.Clear();*/
	m_fruitPosition = pos;

	/*while (!m_atBottom)
	{
		if (m_vineList.empty())
			m_vinePosition = m_fruitPosition.y + Snake::segmentSize;
		else
			m_vinePosition += Snake::segmentSize;

		m_vineList.push_back({ m_fruitPosition.x, m_vinePosition });

		if (m_vinePosition >= window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight() - (Snake::segmentSize / 2))
			m_atBottom = true;
	}*/

	m_isAlive = true;
	m_collectableValue = rand() % 3 + 1;
}

void Collectable::Update(const Water& water)
{
	if (m_fruitPosition.y < water.getPredictedNextWaterPosition())
		m_fruitPosition.y += Snake::segmentSize;
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

const bool& Collectable::getCollectableAliveStatus() const
{
	return m_isAlive;
}