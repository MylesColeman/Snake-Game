#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include "Wall.h"
#include "PlayerSnake.h"
#include "AISnake.h"
#include "Water.h"
#include "Collectable.h"
#include "WaterLeak.h"
#include "InputManager.h"
#include "GameData.h"

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
	void EndGameState(sf::RenderWindow& window, sf::Font mainFont, bool showText);

	sf::RenderWindow m_window;
	sf::Clock m_simulationClock;
	sf::Clock m_gameClock;
	sf::Clock m_inputCooldownTimer; // Necessary so end game state doesn't immediately switch to ingame state

	sf::Time m_gameTime = sf::seconds(90);
	bool m_gameOver{ false };
	std::vector<Snake*> m_winningSnakeVector;
	sf::Time m_highestCurrentSurvivalTime = sf::seconds(-1);
	int m_highestCurrentScore{ -1 };

	sf::Font m_mainFont;

	bool m_showText = true;

	GameData m_gameData;

	Wall m_tankWalls;

	std::vector<Snake*> m_snakeVector;

	Water m_water;
	std::vector<Collectable*> m_collectableVector;

	WaterLeak m_waterLeak;

	// Highscore Table
	std::vector<int> m_highScores;
	std::string m_highScoreFileName = "data\\highscores.txt"; // Name of the high score file

	void LoadHighScores();
	void SaveHighScores();
	void AddNewHighScore(int score);
	void SortHighScores();
public:
	Game();
	void Run();
};