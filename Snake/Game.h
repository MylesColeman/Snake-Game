#pragma once
#include <SFML/Graphics.hpp>
#include "Snake.h"

class Game
{
private:
	Snake m_snake;
public: 
	void Run();
};