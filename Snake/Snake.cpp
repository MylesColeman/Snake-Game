#include "Snake.h"
#include "Collectable.h"
#include "Wall.h"
#include <iostream>

Snake::Snake(int type, sf::Vector2f headPosition) : m_controlType(type)
{
	for (int i = 1; i <= m_startingSegments; i++)
	{
		m_segmentList.push_back({ headPosition.x - (i * segmentSize), headPosition.y});
	}
}

void Snake::Draw(sf::RenderWindow &window)
{
	for (sf::Vector2f segment : m_segmentList)
	{
		sf::RectangleShape snakeSegment({ (segmentSize), (segmentSize) });
		snakeSegment.setOutlineThickness(-3.0f);
		snakeSegment.setOrigin({ (segmentSize / 2), (segmentSize / 2) });
		snakeSegment.setPosition(segment);

		if (m_controlType == 0)
		{
			snakeSegment.setFillColor({ (212), (202), (19) });
			snakeSegment.setOutlineColor({ (103), (99), (14) });
		}
		else if (m_controlType == 1)
		{
			snakeSegment.setFillColor({ (203), (203), (196) });
			snakeSegment.setOutlineColor({ (64), (64), (58) });
		}


		window.draw(snakeSegment);
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
		m_segmentList.push_front({ m_segmentList.front().x - segmentSize, m_segmentList.front().y});
		m_previousDirection = Direction::Left;
		break;
	case Direction::Right:
		m_segmentList.push_front({ m_segmentList.front().x + segmentSize, m_segmentList.front().y });
		m_previousDirection = Direction::Right;
		break;
	case Direction::None:
		break;
	default:
		std::cout << "Error - Unknown Direction" << std::endl;
		break;
	}

	// Only removes the last item from the list if the snake isn't currently growing
	if (m_growAmount == 0 || !m_atBottom)
	{
		m_segmentList.pop_back();
	}
	else if (m_growAmount != 0)
	{
		m_growAmount--;
	}
}

void Snake::CollectableCollision(std::vector<Collectable*>& collectableVector)
{
	// Loops through the collectables vector only incrementing if a collision isn't detected
	for (auto it = collectableVector.begin(); it != collectableVector.end();)
	{
		if (m_segmentList.front() == (*it)->getCollectablePosition())
		{
			GrowAmount((*it)->getCollectableValue());
			delete* it;
			it = collectableVector.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void Snake::BoundsCollision(sf::RenderWindow& window, Wall tankWalls)
{
	if (m_segmentList.front().x < tankWalls.getLeftWallPos() - (tankWalls.getWallWidth() / 2) || m_segmentList.front().x > window.getSize().x - tankWalls.getWallWidth() || m_segmentList.front().y < 0 || m_segmentList.front().y > window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight())
	{	
		m_isAlive = false;
	}
}

void Snake::OtherSnakeCollision(Snake* other)
{
	assert(other);

	if (m_segmentList.front() == other->getSegmentList().front())
	{
		m_isAlive = false;
		other->setToDead(m_isAlive);
	}
	for (const auto& segment : m_segmentList)
	{
		if (segment == other->getSegmentList().front())
		{
			other->setToDead(m_isAlive);
		}
	}
}

void Snake::SelfCollision()
{
	// Starts the check from the second position, skipping the head
	auto it = m_segmentList.begin();
	++it; 

	for (; it != m_segmentList.end(); ++it)
	{
		if (m_segmentList.front() == *it)
		{
			m_isAlive = false;
		}
	}
}

void Snake::GrowAmount(int amount)
{
	m_growAmount += amount;
}

void Snake::isDead(sf::RenderWindow& window, Wall tankWalls)
{
	// Checks if dead
	if (!m_isAlive)
	{
		// Checks if the snake's corpse has fallen to the bottom of the tank
		if (!m_atBottom)
		{
			for (auto& segment : m_segmentList)
			{
				// Checks whether the snake is at the bottom
				if (segment.y + segmentSize >= window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight() - segmentSize)
				{
					m_atBottom = true;
					break;
				}
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
					// Extra movements to fix death on ground level
					m_segmentList.pop_front();
					m_segmentList.push_back({ m_segmentList.back().x, m_segmentList.back().y - segmentSize });
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

			// Sets direction to down, so the snake moves to the floor upon death
			m_direction = Direction::Down;
		}
		else
		{
			// Stops movement and ensures the snake is the correct size
			m_growAmount++;
			m_direction = Direction::None;
		}
	}
}

const std::list<sf::Vector2f>& Snake::getSegmentList() const
{
	return m_segmentList;
}

void Snake::setToDead(bool m_isAlive)
{
	m_isAlive = false;
}