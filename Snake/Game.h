#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Collectable.h"

class Game
{
private:
	Snake m_playerSnake;
public: 
	void Run();
};