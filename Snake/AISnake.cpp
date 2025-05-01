#include "AISnake.h"

AISnake::AISnake(int type, sf::Vector2f headPosition) : Snake(headPosition) {}

void AISnake::Update()
{
	Move();
}