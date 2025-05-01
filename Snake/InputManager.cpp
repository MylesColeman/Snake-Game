#include "InputManager.h"

void InputManager::AddListener(IReceivesInput* listener)
{
	m_listeners.push_back(listener);
}

void InputManager::Update()
{
	Actions action;
	PreviousActions previousAction;

	// Checks for keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && previousAction != PreviousActions::eMoveDown1)
		action = Actions::eMoveUp1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A) && previousAction != PreviousActions::eMoveRight1)
		action = Actions::eMoveLeft1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) && previousAction != PreviousActions::eMoveUp1)
		action = Actions::eMoveDown1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D) && previousAction != PreviousActions::eMoveLeft1)
		action = Actions::eMoveRight1;

	for (IReceivesInput* listeners : m_listeners)
		listeners->HandleInput(action);
}