#include "PlayerSnake.h"
#include "GameData.h"

PlayerSnake::PlayerSnake(int type, sf::Vector2f headPosition) : Snake(headPosition), m_controlType(type) {}

void PlayerSnake::HandleInput(Actions action)
{
	// Only allows keyboard input if the snake is alive
	if (m_isAlive)
	{
		if (m_controlType == 0) // Player 1 controls
		{
			switch (action)
			{
			case Actions::eMoveUp1:
				if (m_previousDirection != Direction::Down)
					m_direction = Direction::Up;
				break;
			case Actions::eMoveLeft1:
				if (m_previousDirection != Direction::Right)
					m_direction = Direction::Left;
				break;
			case Actions::eMoveDown1:
				if (m_previousDirection != Direction::Up)
					m_direction = Direction::Down;
				break;
			case Actions::eMoveRight1:
				if (m_previousDirection != Direction::Left)
					m_direction = Direction::Right;
				break;
			default:
				break;
			}
		}
		else if (m_controlType == 1) // Player 2 controls (currently not used)
		{
			switch (action)
			{
			case Actions::eMoveUp2:
				if (m_previousDirection != Direction::Down)
					m_direction = Direction::Up;
				break;
			case Actions::eMoveLeft2:
				if (m_previousDirection != Direction::Right)
					m_direction = Direction::Left;
				break;
			case Actions::eMoveDown2:
				if (m_previousDirection != Direction::Up)
					m_direction = Direction::Down;
				break;
			case Actions::eMoveRight2:
				if (m_previousDirection != Direction::Left)
					m_direction = Direction::Right;
				break;
			default:
				break;
			}
		}
	}
}

void PlayerSnake::Update(GameData& m_gameData)
{
	Move();
}