#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "IReceivesInput.h"

class InputManager
{
private:
	std::vector<IReceivesInput*> m_listeners;
public:
	static InputManager& GetInstance()
	{
		static InputManager manager;

		return manager;
	}

	void AddListener(IReceivesInput* listener);
	void ClearListeners(); // For game cycle
	void Update();
};

#define INPUT_MAN	InputManager::GetInstance()