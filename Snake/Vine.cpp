#include "Vine.h"
#include "Snake.h"
#include "Wall.h"
#include "Collectable.h"

Vine::Vine(sf::Vector2f fruitPosition) : m_vinePosition(fruitPosition.y + Snake::segmentSize), m_growTime(0)
{
	if (!m_vineTexture.loadFromFile("data\\Vine Sprite.png"))
		std::cerr << "Error loading vine texture!" << std::endl;
}

// Draws the vine itself, iterating through the linked list
void Vine::Draw(sf::RenderWindow& window, const Collectable* collectable)
{
	// Doesn't draw the vine, if theres no vine to be drawn
	if (m_vineList.empty())
	{
		m_vineIsFullyGrown = false;
		return;
	}

	float elapsed = m_growthClock.getElapsedTime().asSeconds();
	int segmentsToDraw = static_cast<int>(elapsed / m_growTime);

	Node<sf::Vector2f>* current = m_vineList.head;
	int drawnCount = 0;
	// Loops through whilst not at the end of list, and whilst there's still segments to draw
	while (current != nullptr && drawnCount < segmentsToDraw)
	{
		// If the growth time has passed, grows a vine
		if (m_growthClock.getElapsedTime().asSeconds() >= m_growTime)
		{
			sf::RectangleShape fruitVine({ Snake::segmentSize, Snake::segmentSize });
			fruitVine.setTexture(&m_vineTexture);

			fruitVine.setOrigin(fruitVine.getGlobalBounds().getCenter());
			fruitVine.setPosition(current->data);

			// Makes vine invisible if dead
			if (!collectable->getCollectableAliveStatus())
			{
				fruitVine.setFillColor({ (0), (0), (0), (0) });
				fruitVine.setOutlineColor({ (0),(0),(0),(0) });
			}

			window.draw(fruitVine);
			current = current->next;
			drawnCount++;
		}
	}

	// Checks whether the entire list has been drawn
	if (drawnCount >= m_vineList.size())
	{
		m_vineIsFullyGrown = true;
	}
	else
	{
		m_vineIsFullyGrown = false;
	}
}

// Populates the vine linked list with vine segments, built from the surface to the collectable
void Vine::Update(sf::RenderWindow& window, const Wall& tankWalls, const Collectable* collectable)
{
	bool m_atCollectable = false;
	m_vineList.Clear();

	// For each snake sized segment from the surface to a collectable, adds to the vine list
	while (!m_atCollectable)
	{
		if (m_vineList.empty())
			m_vinePosition = window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight() - (Snake::segmentSize / 2);
		else
			m_vinePosition -= Snake::segmentSize;

		m_vineList.push_back({ collectable->getCollectablePosition().x, m_vinePosition });

		if (m_vinePosition <= collectable->getCollectablePosition().y + Snake::segmentSize)
			m_atCollectable = true;
	}

	// As long as the vine list isn't empty, calculates how many intervals to divide the growth amongst three seconds
	if (!m_vineList.empty())
		m_growTime = m_fullyGrownTime / static_cast<float>(m_vineList.size());

	m_growthClock.restart();
	m_vineIsFullyGrown = false;
}

// Checks whether the vine is at or above the collectable (as its been moved down due to water), then pops the back vine
void Vine::outOfWater(const Collectable* collectable)
{
	if (m_vineList.back().y <= collectable->getCollectablePosition().y)
		m_vineList.pop_back();
}

const bool& Vine::getVineIsFullyGrown() const
{
	return m_vineIsFullyGrown;
}