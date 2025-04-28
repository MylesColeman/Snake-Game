#include "Vine.h"
#include "Snake.h"
#include "Wall.h"
#include "Collectable.h"

void Vine::Draw(sf::RenderWindow& window, std::vector<Collectable*>& collectableVector)
{
	Node<sf::Vector2f>* current = m_vineList.head;
	while (current != nullptr)
	{
		sf::RectangleShape fruitVine({ Snake::segmentSize, Snake::segmentSize });
		fruitVine.setFillColor(sf::Color::Green);
		fruitVine.setOrigin(fruitVine.getGlobalBounds().getCenter());
		fruitVine.setPosition(current->data);

		if (!collectable.getCollectableAliveStatus())
		{
			fruitVine.setFillColor({ (0), (0), (0), (0) });
			fruitVine.setOutlineColor({ (0),(0),(0),(0) });
		}

		window.draw(fruitVine);
		current = current->next;
	}
}

void Vine::Update(sf::RenderWindow& window, const Wall& tankWalls, std::vector<Collectable*>& collectableVector)
{
	bool m_atBottom = false;
	m_vineList.Clear();

	while (!m_atBottom)
	{
		if (m_vineList.empty())
			m_vinePosition = collectable.getCollectablePosition().y + Snake::segmentSize;
		else
			m_vinePosition += Snake::segmentSize;

		m_vineList.push_back({ collectable.getCollectablePosition().x, m_vinePosition });

		if (m_vinePosition >= window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight() - (Snake::segmentSize / 2))
			m_atBottom = true;
	}
}