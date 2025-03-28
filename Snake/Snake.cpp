#include "Snake.h"
#include "Collectable.h"
#include "Wall.h"
#include <iostream>

Snake::Snake(int type, sf::Vector2f headPosition) : m_controlType(type)
{
	for (int i = 1; i <= m_startingSegments; i++)
		m_segmentList.push_back({ headPosition.x - (i * segmentSize), headPosition.y });
}

void Snake::Draw(sf::RenderWindow& window)
{
	Node<sf::Vector2f>* current = m_segmentList.head;
	while (current != nullptr)
	{
		sf::RectangleShape snakeSegment({ (segmentSize), (segmentSize) });
		snakeSegment.setOutlineThickness(-3.0f);
		snakeSegment.setOrigin({ (segmentSize / 2), (segmentSize / 2) });
		snakeSegment.setPosition(current->data);

		if (m_controlType == 0) // Yellow Snake
		{
			snakeSegment.setFillColor({ (212), (202), (19) });
			snakeSegment.setOutlineColor({ (103), (99), (14) });
		}
		else if (m_controlType == 1) // White Snake
		{
			snakeSegment.setFillColor({ (203), (203), (196) });
			snakeSegment.setOutlineColor({ (64), (64), (58) });
		}


		window.draw(snakeSegment);
		current = current->next;
	}
}

void Snake::MovementInput()
{
	// Only allows keyboard input if the snake is alive
	if (m_isAlive)
	{
		// The control scheme for both players
		if (m_controlType == 0)
		{
			// Checks for keyboard input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && m_previousDirection != Direction::Down)
			{
				m_direction = Direction::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && m_previousDirection != Direction::Up)
			{
				m_direction = Direction::Down;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && m_previousDirection != Direction::Right)
			{
				m_direction = Direction::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && m_previousDirection != Direction::Left)
			{
				m_direction = Direction::Right;
			}
		}
		else if (m_controlType == 1)
		{
			// Checks for keyboard input
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && m_previousDirection != Direction::Down)
			{
				m_direction = Direction::Up;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && m_previousDirection != Direction::Up)
			{
				m_direction = Direction::Down;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && m_previousDirection != Direction::Right)
			{
				m_direction = Direction::Left;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && m_previousDirection != Direction::Left)
			{
				m_direction = Direction::Right;
			}
		}
	}
}

void Snake::Update()
{
	// Causes the snake to move
	switch (m_direction)
	{
	case Direction::Up:
		m_segmentList.push_front({ m_segmentList.front().x, m_segmentList.front().y - segmentSize });
		m_previousDirection = Direction::Up;
		break;
	case Direction::Down:
		m_segmentList.push_front({ m_segmentList.front().x, m_segmentList.front().y + segmentSize });
		m_previousDirection = Direction::Down;
		break;
	case Direction::Left:
		m_segmentList.push_front({ m_segmentList.front().x - segmentSize, m_segmentList.front().y });
		m_previousDirection = Direction::Left;
		break;
	case Direction::Right:
		m_segmentList.push_front({ m_segmentList.front().x + segmentSize, m_segmentList.front().y });
		m_previousDirection = Direction::Right;
		break;
	case Direction::None:
		m_previousDirection = Direction::None;
		break;
	default:
		std::cout << "Error - Unknown Direction" << std::endl;
		break;
	}

	// Only removes the last item from the list if the snake isn't currently growing
	if (m_growAmount == 0)
		m_segmentList.pop_back();
	else
		m_growAmount--;
}

void Snake::CollectableCollision(std::vector<Collectable*>& collectableVector)
{
	// Loops through the collectables vector only incrementing if a collision isn't detected
	for (auto it = collectableVector.begin(); it != collectableVector.end();)
	{
		if (m_segmentList.front() == (*it)->getCollectablePosition() && (*it)->getCollectableAliveStatus())
		{
			GrowAmount((*it)->getCollectableValue());
			(*it)->setToDead(false);
		}
		else
			++it;
	}
}

void Snake::BoundsCollision(sf::RenderWindow& window, const Wall& tankWalls)
{
	if (m_segmentList.front().x < tankWalls.getLeftWallPos() - (tankWalls.getWallWidth() / 2) || m_segmentList.front().x > window.getSize().x - tankWalls.getWallWidth() || m_segmentList.front().y < 0 || m_segmentList.front().y > window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight())
		m_isAlive = false;
}

void Snake::OtherSnakeCollision(Snake* other)
{
	// Check for head-on collision
	if (m_segmentList.front() == other->getSegmentList().front())
	{
		if (m_isAlive && other->getIsAlive())
		{
			m_isAlive = false;
			other->setToDead(false);
		}
		else if (m_isAlive && !other->getIsAlive())
		{
			other->removeSegment(0);
			m_growAmount++;
		}
		else if (!m_isAlive && other->getIsAlive())
		{
			removeSegment(0);
			other->GrowAmount(1);
		}
	}

	// Check if this snake's head collides with the other snake's body
	Node<sf::Vector2f>* currentOther = other->getSegmentList().head;
	if (currentOther != nullptr)
		currentOther = currentOther->next;
	int thisSegmentCounter = 0;
	while (currentOther != nullptr)
	{
		if (m_segmentList.front() == currentOther->data)
		{
			if (other->getIsAlive())
			{
				m_isAlive = false;
				break;
			}
			else
			{
				other->removeSegment(thisSegmentCounter);
				m_growAmount++;
				break;
			}
		}
		thisSegmentCounter++;
		currentOther = currentOther->next;
	}

	// Check if the other snake's head collides with this snake's body
	Node<sf::Vector2f>* currentThis = m_segmentList.head;
	if (currentThis != nullptr)
		currentThis = currentThis->next;
	int otherSegmentCounter = 0;
	while (currentThis != nullptr)
	{
		if (other->getSegmentList().front() == currentThis->data)
		{
			if (m_isAlive)
			{
				other->setToDead(false);
				break;
			}
			else
			{
				removeSegment(otherSegmentCounter);
				other->GrowAmount(1);
				break;
			}
		}
		otherSegmentCounter++;
		currentThis = currentThis->next;
	}
}

void Snake::removeSegment(int index)
{
	m_segmentList.Erase(index);
}

void Snake::SelfCollision()
{
	// Starts the check from the second position, skipping the head
	Node<sf::Vector2f>* current = m_segmentList.head;
	if (current != nullptr)
	{
		current = current->next; // Skip the head
	}

	while (current != nullptr)
	{
		if (m_segmentList.front() == current->data)
		{
			m_isAlive = false;
			break;
		}
		current = current->next;
	}
}

void Snake::GrowAmount(int amount)
{
	m_growAmount += amount;
}

void Snake::isDead(sf::RenderWindow& window, const Wall& tankWalls)
{
	// Checks if dead
	if (!m_isAlive)
	{
		Node<sf::Vector2f>* current = m_segmentList.head;
		while (current->next != nullptr)
		{
			// Checks whether the snake is at the bottom
			if (current->data.y >= window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight() - segmentSize)
			{
				m_atBottom = true;
				break;
			}
			current = current->next;
		}

		// Ensures the resizing is only done once
		if (!m_deadLoop)
		{
			m_segmentList.pop_front();

			if (m_direction == Direction::Up)
			{
				m_segmentList.push_back({ m_segmentList.back().x, m_segmentList.back().y + segmentSize });
			}
			else if (m_direction == Direction::Down)
			{
				m_segmentList.push_back({ m_segmentList.back().x, m_segmentList.back().y - segmentSize });
			}
			else if (m_direction == Direction::Left)
			{
				m_segmentList.push_back({ m_segmentList.back().x + segmentSize, m_segmentList.back().y });
			}
			else if (m_direction == Direction::Right)
			{
				m_segmentList.push_back({ m_segmentList.back().x - segmentSize, m_segmentList.back().y });
			}

			m_deadLoop = true;
		}

		// Checks if the snake's corpse has fallen to the bottom of the tank
		if (!m_atBottom)
			m_direction = Direction::Down; // Sets direction to down, so the snake moves to the floor upon death
		else
		{
			// Stops movement and ensures the snake is the correct size
			m_growAmount++;
			m_direction = Direction::None;
		}
	}
}

const LinkedList<sf::Vector2f>& Snake::getSegmentList() const
{
	return m_segmentList;
}

const bool& Snake::getIsAlive() const
{
	return m_isAlive;
}

void Snake::setToDead(bool isAlive)
{
	m_isAlive = isAlive;
}