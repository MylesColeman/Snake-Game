#include "Game.h"
#include <iostream>

const float simulationTimer = 0.2f;

sf::Vector2f GetRandomFreePosition(int screenWidth, int screenHeight, Wall tankWalls, std::vector<Snake*> snakeVector, std::vector<Collectable*> collectableVector, Water water)
{
	int xPosBuffer = 300;
	int yPosBuffer = 300;

	if (water.getPredictedNextWaterPosition() >= (screenHeight - (int)tankWalls.getSurfaceHeight() - (int)tankWalls.getWallWidth() - yPosBuffer))
		yPosBuffer = 0;

	int rangeX = screenWidth - (int)tankWalls.getLeftWallPos() - (int)tankWalls.getWallWidth() - xPosBuffer;
	int rangeY = screenHeight - (int)tankWalls.getSurfaceHeight() - (int)tankWalls.getWallWidth() - (int)water.getPredictedNextWaterPosition() - yPosBuffer;

	if (rangeY <= 0)
		rangeY = (int)Snake::segmentSize;

	int randomX = (rand() % (rangeX / (int)Snake::segmentSize) * (int)Snake::segmentSize) + ((int)Snake::segmentSize / 2) + (int)tankWalls.getLeftWallPos() + (int)Snake::segmentSize + (xPosBuffer / 2);
	int randomY = (rand() % (rangeY / (int)Snake::segmentSize) * (int)Snake::segmentSize) + ((int)Snake::segmentSize / 2) + (int)water.getPredictedNextWaterPosition() + (yPosBuffer / 2);
	sf::Vector2f randomVector = { (float)randomX, (float)randomY };

	// Ensures the position is free, checking off the snake
	for (Snake* snake : snakeVector)
	{
		Node<sf::Vector2f>* current = snake->getSegmentList().head;
		while (current != nullptr)
		{
			if (randomVector == current->data)
				return GetRandomFreePosition(screenWidth, screenHeight, tankWalls, snakeVector, collectableVector, water);

			current = current->next;
		}
	}

	// Ensures the position is free, checking off the collectabkes x value. - As only one fruit can grow in each collumn
	for (Collectable* collectable : collectableVector)
	{
		if (randomVector.x == collectable->getCollectablePosition().x)
			return GetRandomFreePosition(screenWidth, screenHeight, tankWalls, snakeVector, collectableVector, water);
	}

	return randomVector;
}

void Game::SwitchState(GameState newState)
{
	// On exit from state
	switch (m_state)
	{
	case GameState::FrontEnd:
		m_simulationClock.restart();
		break;
	case GameState::InGame:
		m_simulationClock.stop();
		m_gameClock.stop();
		break;
	case GameState::EndGame:
		break;
	default:
		break;
	}

	m_state = newState;

	// On entry to state
	switch (m_state)
	{
	case GameState::FrontEnd:
		break;
	case GameState::InGame:
		m_gameClock.restart();
		break;
	case GameState::EndGame:
		break;
	default:
		break;
	}
}

// Before game - start screen
void Game::FrontEndState(sf::RenderWindow& window, bool showText, sf::Font mainFont)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		SwitchState(GameState::InGame);

	// Yellow
	sf::Text title(mainFont);
	title.setCharacterSize(72);
	title.setFillColor({ (212), (202), (19) }); 
	title.setOutlineThickness(-3.0f);
	title.setOutlineColor({ (103), (99), (14) });
	title.setStyle(sf::Text::Bold);
	title.setString("Sea Snake");
	title.setOrigin(title.getGlobalBounds().getCenter());
	title.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 6.0f });

	sf::Text inputText(mainFont);
	inputText.setCharacterSize(36);
	inputText.setOutlineThickness(-3.0f);
	inputText.setString("Press Space to Play");
	inputText.setOrigin(inputText.getGlobalBounds().getCenter());
	inputText.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });

	// Flashes the text
	if (m_simulationClock.getElapsedTime().asSeconds() >= 0.8)
	{
		m_showText = !m_showText;
		m_simulationClock.restart();
	}

	if (showText)
	{
		// White
		inputText.setFillColor({ (203), (203), (196) }); 
		inputText.setOutlineColor({ (64), (64), (58) });
	}
	else
	{
		// Invisible
		inputText.setFillColor({ (0), (0), (0), (0) });
		inputText.setOutlineColor({ (0), (0), (0), (0) });
	}

	m_window.clear({ (188), (180), (178) }); // Resets the window for use

	window.draw(title);
	window.draw(inputText);

	m_window.display(); // Displays the windows contents
}

// Actual game
void Game::InGameState(sf::RenderWindow& window)
{
	if (m_simulationClock.getElapsedTime().asSeconds() >= simulationTimer)
	{
		for (size_t i = 0; i < m_snakeVector.size(); i++)
		{
			for (size_t j = i + 1; j < m_snakeVector.size(); j++)
				m_snakeVector[i]->OtherSnakeCollision(m_snakeVector[j]);
		}

		for (Snake* snake : m_snakeVector)
		{
			snake->CollectableCollision(m_collectableVector);
			snake->BoundsCollision(m_window, m_tankWalls);
			snake->SelfCollision();

			snake->isDead(m_window, m_tankWalls);

			snake->Update();

			snake->Drowning(m_water);
		}

		// Rolls a dice 1 to 20, and if 1 lands checks whether any of the collectables are dead - if so, creates a collectable
		if (rand() % 10 == 0)
		{
			for (auto* collectable : m_collectableVector)
			{
				if (!collectable->getCollectableAliveStatus())
				{
					collectable->Spawn(GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water));
					break;
				}
			}
		}

		m_water.Update(m_gameClock.getElapsedTime(), m_gameTime);
		for (auto* collectable : m_collectableVector)
		{
			if (collectable->getCollectableAliveStatus())
				collectable->Update(m_water);
		}

		m_simulationClock.restart();
	}

	// End of game - Winner Declaration
	if (m_gameClock.getElapsedTime() >= m_gameTime)
		SwitchState(GameState::EndGame);

	bool allSnakesDead = true;
	for (Snake* snake : m_snakeVector)
	{
		if (snake->getIsAlive())
		{
			allSnakesDead = false;
			break;
		}
	}
	if (allSnakesDead)
		SwitchState(GameState::EndGame);

	m_window.clear({ (188), (180), (178) }); // Resets the window for use

	for (Collectable* collectable : m_collectableVector)
		collectable->Draw(m_window);

	for (Snake* snake : m_snakeVector)
	{
		snake->DrawSnake(m_window);
		snake->MovementInput();
	}

	m_water.Draw(m_window, m_tankWalls);
	m_tankWalls.Draw(m_window);

	for (Snake* snake : m_snakeVector)
		snake->DrawUI(m_window, m_tankWalls, m_mainFont);

	m_window.display(); // Displays the windows contents
}

// Post Game - Winner
void Game::EndGameState(sf::RenderWindow& window, sf::Font mainFont)
{
	sf::Text gameOver(mainFont);
	gameOver.setCharacterSize(72);
	gameOver.setFillColor({ (212), (202), (19) });
	gameOver.setOutlineThickness(-3.0f);
	gameOver.setOutlineColor({ (103), (99), (14) });
	gameOver.setStyle(sf::Text::Bold);
	gameOver.setString("Game Over!");
	gameOver.setOrigin(gameOver.getGlobalBounds().getCenter());
	gameOver.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 6.0f });

	m_window.clear({ (188), (180), (178) }); // Resets the window for use

	window.draw(gameOver);

	m_window.display(); // Displays the windows contents
}

Game::Game() : m_window(sf::VideoMode({ 1920, 1200 }), "GSE - Snake Game - E4109732", sf::State::Fullscreen), m_water(m_window, m_tankWalls)
{
	if (!m_mainFont.openFromFile("data\\Snake Chan.ttf"))
		std::cerr << "Error loading font" << std::endl;

	// Creates the snakes
	for (int i = 0; i < 2; i++)
		m_snakeVector.push_back(new Snake(i, GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water)));

	for (int i = 0; i < 5; i++)
		m_collectableVector.push_back(new Collectable(GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water)));
}

void Game::Run()
{
	srand((unsigned int)time(0));

	// Loops whilst the window is open
	while (m_window.isOpen())
	{
		// Checks if the window has been closed
		while (const std::optional event = m_window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				m_window.close();
		}

		// Allows the switching of states
		switch (m_state)
		{
		case GameState::FrontEnd:
			FrontEndState(m_window, m_showText, m_mainFont);
			break;
		case GameState::InGame:
			InGameState(m_window);
			break;
		case GameState::EndGame:
			EndGameState(m_window, m_mainFont);
			break;
		default:
			break;
		}
	}

	for (Snake* snake : m_snakeVector)
		delete snake;

	for (Collectable* collectable : m_collectableVector)
		delete collectable;
}