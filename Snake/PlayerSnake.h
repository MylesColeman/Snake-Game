#pragma once
#include "Snake.h"
#include "IReceivesInput.h"

class Game;

class PlayerSnake : public Snake, public IReceivesInput
{
private:
	int m_controlType{ 0 }; // Used to determine a player 1 and 2, and their control scheme
public:
	PlayerSnake(int type, sf::Vector2f headPosition);

	// Required by IReceivesInput
	void HandleInput(Actions action) override;

	void Update(GameData& m_gameData) override;

	SnakeType getType() const override { return SnakeType::Player; }
};