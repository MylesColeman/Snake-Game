#pragma once
#include "Snake.h"
class AISnake : public Snake
{
private:

public:
	AISnake(int type, sf::Vector2f headPosition);

	void Update() override;
	SnakeType getType() const override { return SnakeType::AI; }
};