#include "Game.h"

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
		m_inputCooldownTimer.restart();
		break;
	case GameState::InGame:
		m_simulationClock.stop();
		m_gameClock.stop();
		m_water.reset(m_window, m_tankWalls);
		m_inputCooldownTimer.restart();
		break;
	case GameState::EndGame:
		m_inputCooldownTimer.restart();
		break;
	default:
		break;
	}

	m_state = newState;

	// On entry to state
	switch (m_state)
	{
	case GameState::FrontEnd:
		for (Snake* snake : m_snakeVector)
		{
			snake->setToDead(false);
			snake->resetDeadLoop();
			delete snake;
		}
		m_snakeVector.clear();
		INPUT_MAN.ClearListeners();
		for (int i = 0; i < 1; i++)
		{
			PlayerSnake* playerSnake = new PlayerSnake(i, GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water));
			m_snakeVector.push_back(playerSnake);
			INPUT_MAN.AddListener(playerSnake);
			
		}
		for (int i = 0; i < 1; i++)
		{
			AISnake* aiSnake = new AISnake(i, GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water));
			m_snakeVector.push_back(aiSnake);
		}
		for (Collectable* collectable : m_collectableVector)
			delete collectable;
		m_collectableVector.clear();
		for (int i = 0; i < 5; i++)
			m_collectableVector.push_back(new Collectable(GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water)));
		m_gameOver = false;
		m_winningSnakeVector.clear();
		m_highestCurrentSurvivalTime = sf::Time::Zero;
		m_highestCurrentScore = 0;
		m_simulationClock.restart();
		break;
	case GameState::InGame:
		m_gameClock.restart();
		break;
	case GameState::EndGame:
		AddNewHighScore(m_highestCurrentScore); // Adds the highest current score here, to ensure its not updated
		m_simulationClock.restart();
		break;
	default:
		break;
	}
}

// Before game - start screen
void Game::FrontEndState(sf::RenderWindow& window, bool showText, sf::Font mainFont)
{
	if (m_inputCooldownTimer.getElapsedTime().asSeconds() > 0.2f && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		SwitchState(GameState::InGame);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		window.close();

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

	// White
	sf::Text highscoreText(mainFont);
	highscoreText.setCharacterSize(42);
	highscoreText.setFillColor({ 203, 203, 196 });
	highscoreText.setOutlineThickness(-3.0f);
	highscoreText.setOutlineColor({ 64, 64, 58 });
	highscoreText.setString("Highscores:");
	highscoreText.setOrigin(highscoreText.getGlobalBounds().getCenter());
	highscoreText.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 4.0f });

	// Yellow
	sf::Text scoreText(mainFont);
	scoreText.setCharacterSize(18);
	scoreText.setFillColor({ (212), (202), (19) });
	scoreText.setOutlineThickness(-3.0f);
	scoreText.setOutlineColor({ (103), (99), (14) });
	scoreText.setOrigin(scoreText.getGlobalBounds().getCenter());

	sf::Text inputText(mainFont);
	inputText.setCharacterSize(36);
	inputText.setOutlineThickness(-3.0f);
	inputText.setString("Press Space to Play - Esc to Exit");
	inputText.setOrigin(inputText.getGlobalBounds().getCenter());
	inputText.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 1.2f });

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
	window.draw(highscoreText);

	for (size_t i = 0; i < m_highScores.size(); i++)
	{
		scoreText.setString(std::to_string(m_highScores[i]));
		scoreText.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 3.8f + (i + 1) * 40 });

		window.draw(scoreText);

		if (i >= 9) // Only display top 10
			break;
	}

	window.draw(inputText);

	m_window.display(); // Displays the windows contents
}

// Actual game
void Game::InGameState(sf::RenderWindow& window)
{
	INPUT_MAN.Update();

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

			snake->Update(m_gameData);

			snake->Drowning(m_water);
		}

		// Rolls a dice 1 to 20, and if 1 lands checks whether any of the collectables are dead - if so, creates a collectable
		if (rand() % 10 == 0)
		{
			for (auto* collectable : m_collectableVector)
			{
				if (!collectable->getCollectableAliveStatus())
				{
					collectable->Spawn(GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water), m_window, m_tankWalls);
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
		m_waterLeak.Update(m_simulationClock.getElapsedTime());

		m_simulationClock.restart();
	}

	// End of game - Winner Declaration
	// Game Over
	// Ends the game after the set time
	if (m_gameClock.getElapsedTime() >= m_gameTime)
	{
		// Stops all snakes survival times
		for (Snake* snake : m_snakeVector)
			snake->stopSurvivalClock();

		m_gameOver = true;
	}

	// Checks if all snakes are dead
	bool allSnakesDead = true;
	for (Snake* snake : m_snakeVector)
	{
		if (snake->getIsAlive())
		{
			allSnakesDead = false;
			break;
		}
	}
	// Ends the game if all snakes are dead
	if (allSnakesDead)
		m_gameOver = true;

	// Winner Declaration
	if (m_gameOver)
	{
		//  Finds the highest survival time
		for (Snake* snake : m_snakeVector)
		{
			if (m_highestCurrentSurvivalTime < snake->getSurvivalTime())
				m_highestCurrentSurvivalTime = snake->getSurvivalTime();
		}

		// Adds all snakes who surivived the longest to the winners vector
		for (Snake* snake : m_snakeVector)
		{
			if (snake->getSurvivalTime() >= m_highestCurrentSurvivalTime)
				m_winningSnakeVector.push_back(snake);
		}

		// If more than one snake survived the longest (last snakes died at same time or survived till the end)
		if (m_winningSnakeVector.size() > 1)
		{
			// Finds the highest score amongst the snakes who survived the longest
			for (Snake* snake : m_winningSnakeVector)
			{
				if (m_highestCurrentScore < snake->getScore())
					m_highestCurrentScore = snake->getScore();
			}

			// Creates a vector for the survivors with the highest score, adds those snakes to it. Then sets the winning snake vector to equal this one
			std::vector<Snake*> survivorsWithHighestScore;
			for (Snake* snake : m_winningSnakeVector)
			{
				if (snake->getScore() == m_highestCurrentScore)
				{
					survivorsWithHighestScore.push_back(snake);
				}
			}
			m_winningSnakeVector = survivorsWithHighestScore;
		}
		else // If only one snake survived, sets the highest score to its
			m_highestCurrentScore = m_winningSnakeVector[0]->getScore();

		SwitchState(GameState::EndGame);
	}

	m_window.clear({ (188), (180), (178) }); // Resets the window for use

	for (Collectable* collectable : m_collectableVector)
		collectable->Draw(m_window);

	for (auto it = m_snakeVector.rbegin(); it != m_snakeVector.rend(); ++it)
		(*it)->DrawSnake(m_window);

	m_water.Draw(m_window, m_tankWalls);
	m_tankWalls.Draw(m_window);

	m_waterLeak.Draw(m_window);

	for (Snake* snake : m_snakeVector)
		snake->DrawUI(m_window, m_tankWalls, m_mainFont);

	m_window.display(); // Displays the windows contents
}

// Post Game - Winner
void Game::EndGameState(sf::RenderWindow& window, sf::Font mainFont, bool showText)
{
	if (m_inputCooldownTimer.getElapsedTime().asSeconds() > 0.2f && sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space))
		SwitchState(GameState::FrontEnd);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
		window.close();

	// Yellow
	sf::Text gameOver(mainFont);
	gameOver.setCharacterSize(72);
	gameOver.setFillColor({ (212), (202), (19) });
	gameOver.setOutlineThickness(-3.0f);
	gameOver.setOutlineColor({ (103), (99), (14) });
	gameOver.setStyle(sf::Text::Bold);
	gameOver.setString("Game Over!");
	gameOver.setOrigin(gameOver.getGlobalBounds().getCenter());
	gameOver.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 6.0f });

	// White
	sf::Text winners(mainFont);
	winners.setCharacterSize(48);
	winners.setOutlineThickness(-3.0f);
	winners.setFillColor({ (203), (203), (196) });
	winners.setOutlineColor({ (64), (64), (58) });
	winners.setStyle(sf::Text::Bold);

	for (size_t i = 0; i < m_winningSnakeVector.size(); i++)
	{
		if (i == m_winningSnakeVector.size() - 1 && m_winningSnakeVector[i]->getType() == SnakeType::Player)
			winners.setString("The Player Wins!");
		else if (i == m_winningSnakeVector.size() - 1 && m_winningSnakeVector[i]->getType() == SnakeType::AI)
			winners.setString("The AI Wins!");
		else
			winners.setString("It's a Draw!");
	}

	winners.setOrigin(winners.getGlobalBounds().getCenter());
	winners.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 3.0f });

	// Yellow
	sf::Text score(mainFont);
	score.setCharacterSize(36);
	score.setFillColor({ (212), (202), (19) });
	score.setOutlineThickness(-3.0f);
	score.setOutlineColor({ (103), (99), (14) });
	score.setString("With a Score of: " + std::to_string(m_highestCurrentScore));
	score.setOrigin(score.getGlobalBounds().getCenter());
	score.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 2.0f });

	sf::Text inputText(mainFont);
	inputText.setCharacterSize(36);
	inputText.setOutlineThickness(-3.0f);
	inputText.setString("Press Space to Play Again - Esc to Exit");
	inputText.setOrigin(inputText.getGlobalBounds().getCenter());
	inputText.setPosition({ window.getSize().x / 2.0f, window.getSize().y / 1.4f });

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

	window.draw(gameOver);
	window.draw(winners);
	window.draw(score);
	window.draw(inputText);

	m_window.display(); // Displays the windows contents
}

void Game::LoadHighScores()
{
	std::ifstream inputFile(m_highScoreFileName);
	if (inputFile.is_open())
	{
		int score;
		while (inputFile >> score)
		{
			m_highScores.push_back(score);
		}
		inputFile.close();
	}
	else
	{
		std::cerr << "Error opening high score file for loading." << std::endl;
	}
	SortHighScores();
}

void Game::SaveHighScores()
{
	std::ofstream outputFile(m_highScoreFileName);
	if (outputFile.is_open())
	{
		for (int score : m_highScores)
		{
			outputFile << score << std::endl;
		}
		outputFile.close();
	}
	else
	{
		std::cerr << "Error opening high score file for saving." << std::endl;
	}
}

void Game::AddNewHighScore(int score)
{
	m_highScores.push_back(score); // Adds the highest current score from the game
	SortHighScores();
	if (m_highScores.size() > 10)
	{
		m_highScores.resize(10);
	}
	SaveHighScores();
}

void Game::SortHighScores()
{
	std::sort(m_highScores.rbegin(), m_highScores.rend()); // Sorts the highscores, highest to lowest
}

Game::Game() : m_window(sf::VideoMode({ 1920, 1200 }), "GSE - Snake Game - E4109732", sf::State::Fullscreen), m_water(m_window, m_tankWalls), m_waterLeak({ m_tankWalls.getLeftWallPos() - m_tankWalls.getWallWidth(), m_window.getSize().y - m_tankWalls.getSurfaceHeight() - m_tankWalls.getWallWidth() }, 150)
{
	if (!m_mainFont.openFromFile("data\\Snake Chan.ttf"))
		std::cerr << "Error loading font" << std::endl;

	LoadHighScores();
	SortHighScores();

	// Creates the snakes
	for (int i = 0; i < 1; i++)
	{
		PlayerSnake* playerSnake = new PlayerSnake(i, GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water));
		m_snakeVector.push_back(playerSnake);
		INPUT_MAN.AddListener(playerSnake);
	}
	for (int i = 0; i < 1; i++)
	{
		AISnake* aiSnake = new AISnake(i, GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water));
		m_snakeVector.push_back(aiSnake);
	}

	for (int i = 0; i < 5; i++)
		m_collectableVector.push_back(new Collectable(GetRandomFreePosition(m_window.getSize().x, m_window.getSize().y, m_tankWalls, m_snakeVector, m_collectableVector, m_water)));
}

void Game::Run()
{
	srand((unsigned int)time(0));

	m_gameData.m_collectableVector = &m_collectableVector;
	m_gameData.m_snakeVector = &m_snakeVector;
	m_gameData.m_tankWalls = &m_tankWalls;
	m_gameData.m_water = &m_water;
	m_gameData.m_window = &m_window;

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
			EndGameState(m_window, m_mainFont, m_showText);
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