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
	std::vector<Snake*> m_snakeVector;
	std::vector<Collectable*> m_collectableVector;
public: 
	void Run();
};