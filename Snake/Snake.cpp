#include "Snake.h"
#include "Collectable.h"
#include "Wall.h"
#include "Water.h"
#include "InputManager.h"
#include <iostream>

Snake::Snake(sf::Vector2f headPosition)
{
	for (int i = 1; i <= m_startingSegments; i++)
		m_segmentList.push_back({ headPosition.x - (i * segmentSize), headPosition.y });

	m_survivalClock.restart();
}

void Snake::DrawSnake(sf::RenderWindow& window)
{
	Node<sf::Vector2f>* current = m_segmentList.head;
	while (current != nullptr)
	{
		sf::RectangleShape snakeSegment({ (segmentSize), (segmentSize) });
		snakeSegment.setOutlineThickness(-3.0f);
		snakeSegment.setOrigin({ snakeSegment.getGlobalBounds().getCenter() });
		snakeSegment.setPosition(current->data);

		if (getType() == SnakeType::Player) // Yellow Snake
		{
			snakeSegment.setFillColor({ (212), (202), (19) });
			snakeSegment.setOutlineColor({ (103), (99), (14) });
		}
		else if (getType() == SnakeType::AI) // White Snake
		{
			snakeSegment.setFillColor({ (203), (203), (196) });
			snakeSegment.setOutlineColor({ (64), (64), (58) });
		}


		window.draw(snakeSegment);
		current = current->next;
	}
}

void Snake::DrawUI(sf::RenderWindow& window, const Wall& tankWalls, sf::Font mainFont)
{
	float outlineDepth = 3.0f;

	sf::RectangleShape breathBlock({ segmentSize * 10, tankWalls.getSurfaceHeight() / 2 });
	breathBlock.setOutlineThickness(-outlineDepth);
	breathBlock.setFillColor({ (82), (86), (87) }); // Grey
	breathBlock.setOutlineColor({ (61), (63), (64) }); // Darker Grey

	sf::RectangleShape breathRemaining({ (segmentSize * 10) - outlineDepth * 2, ((tankWalls.getSurfaceHeight() / 2) - outlineDepth * 2) });
	breathRemaining.setFillColor({ (12), (56), (133) }); // Blue

	sf::Text score(mainFont);
	score.setCharacterSize(28);
	score.setOutlineThickness(-outlineDepth);

	if (getType() == SnakeType::Player)
	{
		breathBlock.setOrigin({ (0), (tankWalls.getSurfaceHeight() / 2) / 2 });
		breathBlock.setPosition({ (tankWalls.getWallWidth() + tankWalls.getLeftWallPos()), (window.getSize().y - tankWalls.getWallWidth() - (tankWalls.getSurfaceHeight() / 2)) });

		breathRemaining.setOrigin({ (0 - outlineDepth), (breathRemaining.getGlobalBounds().getCenter().y) });
		breathRemaining.setPosition({ breathBlock.getPosition() });

		// Decreases the breath bar - dependent on breath
		breathRemaining.setScale({ ((float)m_breath / (float)m_maxBreath), (breathRemaining.getScale().y) });

		// Yellow
		score.setFillColor({ (212), (202), (19) });
		score.setOutlineColor({ (103), (99), (14) });
		score.setString(std::to_string(m_score));
		score.setOrigin(score.getGlobalBounds().getCenter());
		score.setPosition({ breathBlock.getPosition().x + breathBlock.getSize().x + segmentSize, breathBlock.getPosition().y });
	}
	else if (getType() == SnakeType::AI)
	{
		breathBlock.setOrigin({ (segmentSize * 10), (tankWalls.getSurfaceHeight() / 2) / 2 });
		breathBlock.setPosition({ (window.getSize().x - (tankWalls.getWallWidth() * 2)), (window.getSize().y - tankWalls.getWallWidth() - (tankWalls.getSurfaceHeight() / 2)) });

		breathRemaining.setOrigin({ ((segmentSize * 10) - outlineDepth), (breathRemaining.getGlobalBounds().getCenter().y) });
		breathRemaining.setPosition({ breathBlock.getPosition() });

		// Decreases the breath bar - dependent on breath
		breathRemaining.setScale({ ((float)m_breath / (float)m_maxBreath), (breathRemaining.getScale().y) });

		// White
		score.setFillColor({ (203), (203), (196) });
		score.setOutlineColor({ (64), (64), (58) });
		score.setString(std::to_string(m_score));
		score.setOrigin(score.getGlobalBounds().getCenter());
		score.setPosition({ breathBlock.getPosition().x - breathBlock.getSize().x - segmentSize, breathBlock.getPosition().y });
	}

	window.draw(breathBlock);
	window.draw(breathRemaining);

	window.draw(score);
}

void Snake::Move()
{
	if (!m_segmentList.empty())
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
		case Direction::None: // For when the snake is dead
			m_previousDirection = Direction::None;
			break;
		default:
			std::cout << "Error - Unknown Direction" << std::endl;
			break;
		}
	}
	
	// Only removes the last item from the list if the snake isn't currently growing
	if (m_growAmount == 0 && !m_segmentList.empty())
		m_segmentList.pop_back();
	else
		m_growAmount--;

	if (m_segmentList.size() <= 0)
		m_isAlive = false;
}

void Snake::Drowning(const Water& water)
{
	if (m_isAlive)
	{
		if (!m_segmentList.empty())
		{
			if (m_breath <= 0) // Snake is drowning
			{
				m_segmentList.pop_back();
				if (m_score > 0)
					m_score--;
			}

			if (m_segmentList.front().y < water.getPredictedNextWaterPosition() - segmentSize)
			{
				m_breath = m_maxBreath;

				// Snake is drying out
				if (m_segmentList.front().y < water.getPredictedNextWaterPosition() - (segmentSize * 2))
				{
					m_segmentList.pop_back();
					if (m_score > 0)
						m_score--;
				}

			}
			else
			{
				if (m_breath > 0)
					m_breath--;
			}
		}
	}
	else
	{
		m_breath = 0;
	}
}

void Snake::CollectableCollision(std::vector<Collectable*>& collectableVector)
{
	if (m_isAlive)
	{
		// Loops through the collectables vector only incrementing if a collision isn't detected
		if (!m_segmentList.empty())
		{
			for (auto it = collectableVector.begin(); it != collectableVector.end();)
			{
				if (m_segmentList.front() == (*it)->getCollectablePosition() && (*it)->getCollectableAliveStatus() && (*it)->getIsVineFullyGrown())
				{
					GrowAmount((*it)->getCollectableValue());
					m_score += (*it)->getCollectableValue();
					(*it)->setToDead(false);
				}
				else
					++it;
			}
		}
	}
}

void Snake::BoundsCollision(sf::RenderWindow& window, const Wall& tankWalls)
{
	if (m_isAlive)
	{
		if (!m_segmentList.empty())
		{
			if (m_segmentList.front().x < tankWalls.getLeftWallPos() - (tankWalls.getWallWidth() / 2) || m_segmentList.front().x > window.getSize().x - tankWalls.getWallWidth() || m_segmentList.front().y < 0 || m_segmentList.front().y > window.getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight())
				m_isAlive = false;
		}
	}
}

void Snake::OtherSnakeCollision(Snake* other)
{
	if (m_isAlive && other->getIsAlive() && !m_segmentList.empty() && !other->getSegmentList().empty())
	{
		// Check for head-on collision
		if (m_segmentList.front() == other->getSegmentList().front())
		{
			m_isAlive = false;
			other->setToDead(false);
		}

		// Check if this snake's head collides with the other snake's body
		Node<sf::Vector2f>* currentOther = other->getSegmentList().head;
		while (currentOther != nullptr)
		{
			if (m_segmentList.front() == currentOther->data)
			{
				m_isAlive = false;
				break;
			}
			currentOther = currentOther->next;
		}

		// Check if the other snake's head collides with this snake's body
		Node<sf::Vector2f>* currentThis = m_segmentList.head;
		while (currentThis != nullptr)
		{
			if (other->getSegmentList().front() == currentThis->data)
			{
				other->setToDead(false);
				break;
			}
			currentThis = currentThis->next;
		}
	}
	else
	{
		// Check if this snake's head collides with the other snake's body
		Node<sf::Vector2f>* currentOther = other->getSegmentList().head;
		int thisSegmentCounter = 0;
		while (currentOther != nullptr)
		{
			if (!m_segmentList.empty())
			{
				if (m_segmentList.front() == currentOther->data)
				{
					// Needed if one snake is dead and the other is alive
					if (!other->getIsAlive())
					{
						other->RemoveSegment(thisSegmentCounter);
						m_growAmount++;
						break;
					}
					else
					{
						m_isAlive = false;
						break;
					}

				}
				thisSegmentCounter++;
				currentOther = currentOther->next;
			}
			else
				break;
		}

		// Check if the other snake's head collides with this snake's body
		Node<sf::Vector2f>* currentThis = m_segmentList.head;
		int otherSegmentCounter = 0;
		while (currentThis != nullptr)
		{
			if (!other->getSegmentList().empty())
			{
				if (other->getSegmentList().front() == currentThis->data)
				{
					// Needed if one snake is dead and the other is alive
					if (!m_isAlive)
					{
						RemoveSegment(otherSegmentCounter);
						other->GrowAmount(1);
						break;
					}
					else
					{
						other->setToDead(false);
						break;
					}

				}
				otherSegmentCounter++;
				currentThis = currentThis->next;
			}
			else
				break;
		}
	}
}

void Snake::RemoveSegment(int index)
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
		if (!m_segmentList.empty())
		{
			if (m_segmentList.front() == current->data)
			{
				m_isAlive = false;
				break;
			}
			current = current->next;
		}
	}
}

void Snake::GrowAmount(int amount)
{
	m_growAmount += amount;
}

void Snake::stopSurvivalClock()
{
	m_survivalClock.stop();
}

void Snake::isDead(sf::RenderWindow& window, const Wall& tankWalls)
{
	// Checks if dead
	if (!m_isAlive)
	{
		m_survivalClock.stop();
		Node<sf::Vector2f>* current = m_segmentList.head;
		if (current != nullptr)
		{
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
			if (!m_deadLoop && !m_segmentList.empty())
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

const sf::Time& Snake::getSurvivalTime() const
{
	return m_survivalClock.getElapsedTime();
}

const int& Snake::getScore() const
{
	return m_score;
}

void Snake::setToDead(bool isAlive)
{
	m_isAlive = isAlive;
}

void Snake::resetDeadLoop()
{
	m_deadLoop = false;
}
