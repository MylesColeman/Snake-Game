#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Wall.h"
#include "Snake.h"
#include "Collectable.h"

class Game
{
private:
	Wall m_tankWalls;
	Snake m_playerSnake;
	std::vector<Snake*> m_snakeVector;
public: 
	void Run();
};