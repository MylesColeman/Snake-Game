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
		m_previousDirection = Direction::None;
		break;
	default:
		std::cout << "Error - Unknown Direction" << std::endl;
		break;
	}

	// Only removes the last item from the list if the snake isn't currently growing
	if (m_growAmount == 0 && m_isAlive)
	{
		m_segmentList.pop_back();
	}
	else if (m_growAmount != 0 && m_isAlive)
	{
		m_growAmount--;
	}
}

void Snake::CollectableCollision(std::vector<Collectable*>& collectableVector)
{
	// Loops through the collectables vector only incrementing if a collision isn't detected
	for (auto it = collectableVector.begin(); it != collectableVector.end();)
	{
		if (getSegmentList().front() == (*it)->getCollectablePosition())
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
	if (getSegmentList().front().x < tankWalls.getLeftWallPos() - (tankWalls.getWallWidth() / 2) || getSegmentList().front().x > window.getSize().x - tankWalls.getWallWidth() || getSegmentList().front().y < 0 || getSegmentList().front().y > window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight())
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
		
		m_isAlive = false;
	}
}

void Snake::OtherSnakeCollision()
{

}

void Snake::SelfCollision()
{

}

void Snake::GrowAmount(int amount)
{
	m_growAmount += amount;
}

void Snake::isDead(sf::RenderWindow& window, Wall tankWalls)
{
	if (!m_isAlive)
	{
		m_direction = Direction::None;

		if (!atBottom)
		{
			for (auto& segment : m_segmentList)
			{
				segment.y += 30;

				std::cout << segment.y << std::endl;
				if (segment.y >= window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight() - segmentSize)
				{
					atBottom = true;
				}
			}
		}
	}
}

const std::list<sf::Vector2f>& Snake::getSegmentList() const
{
	return m_segmentList;
}