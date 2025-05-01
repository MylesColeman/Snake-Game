#include "PlayerSnake.h"

void PlayerSnake::HandleInput(Actions action)
{
	switch (action)
	{
	case Actions::eMoveUp1:
		break;
	case Actions::eMoveUp2:
		break;
	case Actions::eMoveLeft1:
		break;
	case Actions::eMoveLeft2:
		break;
	case Actions::eMoveDown1:
		break;
	case Actions::eMoveDown2:
		break;
	case Actions::eMoveRight1:
		break;
	case Actions::eMoveRight2:
		break;
	default:
		break;
	}

	// Only allows keyboard input if the snake is alive
	if (m_isAlive)
	{
		// The control scheme for both players
		if (m_controlType == 0)
		{

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

void PlayerSnake::Update()
{
	Move();
}