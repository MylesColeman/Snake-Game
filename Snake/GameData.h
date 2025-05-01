#pragma once
#include <vector>

class Snake;
class Collectable;
class Wall;
class Water;

struct GameData
{
	std::vector<Snake*>* m_snakeVector{ nullptr };
	std::vector<Collectable*>* m_collectableVector{ nullptr };
	Wall* m_tankWalls{ nullptr };
	Water* m_water{ nullptr };
	sf::RenderWindow* m_window{ nullptr };
};