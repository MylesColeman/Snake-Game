#pragma once
#include <SFML/Graphics.hpp>
#include "Wall.h"
#include "Snake.h"
#include "Collectable.h"

class Game
{
private:
	Wall m_tankWalls;
	Snake m_playerSnake;
public: 
	void Run();
};