#pragma once
#include "Snake.h"
#include "IReceivesInput.h"

class PlayerSnake : public Snake, public IReceivesInput
{
private:
	int m_controlType{ 0 }; // Used to determine a player 1 and 2, and their control scheme
public:
	// Required by IReceivesInput
	void HandleInput(Actions action) override;

	void Update() override;
};