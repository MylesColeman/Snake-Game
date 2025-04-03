#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Wall.h"
#include "Snake.h"
#include "Water.h"
#include "Collectable.h"

enum class GameState
{
	FrontEnd,
	InGame,
	EndGame
};

class Game
{
private:
	GameState m_state{ GameState::FrontEnd };
	void SwitchState(GameState newState);
	void FrontEndState(sf::RenderWindow& window, bool showText, sf::Font mainFont);
	void InGameState(sf::RenderWindow& window);
	void EndGameState(sf::RenderWindow& window, sf::Font mainFont);

	sf::RenderWindow m_window;
	sf::Clock m_simulationClock;
	sf::Clock m_gameClock;

	sf::Time m_gameTime = sf::seconds(90);
	bool m_gameOver{ false };
	std::vector<Snake*> m_winningSnakeVector;
	int m_highestCurrentScore{ 0 };

	sf::Font m_mainFont;

	bool m_showText = true;

	Wall m_tankWalls;
	std::vector<Snake*> m_snakeVector;
	Water m_water;
	std::vector<Collectable*> m_collectableVector;
public:
	Game();
	void Run();
};