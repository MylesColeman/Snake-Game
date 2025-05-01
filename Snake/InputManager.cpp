#include "InputManager.h"

void InputManager::AddListener(IReceivesInput* listener)
{
	m_listeners.push_back(listener);
}

void InputManager::ClearListeners()
{
	m_listeners.clear();
}

void InputManager::Update()
{
	Actions action{ Actions::eNone };

	// Checks for keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		action = Actions::eMoveUp1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		action = Actions::eMoveLeft1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		action = Actions::eMoveDown1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		action = Actions::eMoveRight1;

	// Not currently implemented
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		action = Actions::eMoveUp2;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		action = Actions::eMoveLeft2;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
		action = Actions::eMoveDown2;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		action = Actions::eMoveRight2;*/

	for (IReceivesInput* listeners : m_listeners)
		listeners->HandleInput(action);
}