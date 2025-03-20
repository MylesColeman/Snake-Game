#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Wall.h"
#include "Snake.h"
#include "Collectable.h"

enum class GameState
{
	FrontEnd,
	InGame,
	Pause,
	EndGame
};

class Game
{
private:
	GameState m_state{ GameState::FrontEnd };
	void SwitchState(GameState newState);
	void FrontEndState(sf::RenderWindow& window, bool showText, sf::Font mainFont);
	void InGameState(sf::RenderWindow& window);
	void Pause(sf::RenderWindow& window);
	void EndGameState(sf::RenderWindow& window);
	
	sf::RenderWindow m_window;
	sf::Clock simulationClock;

	sf::Font m_mainFont;

	bool m_showText = true;

	Wall m_tankWalls;
	std::vector<Snake*> m_snakeVector;
	std::vector<Collectable*> m_collectableVector;
public: 
	void Run();
};