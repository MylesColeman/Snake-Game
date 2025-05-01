#pragma once

enum class Actions
{
	eMoveUp1,
	eMoveUp2,
	eMoveLeft1,
	eMoveLeft2,
	eMoveDown1,
	eMoveDown2,
	eMoveRight1,
	eMoveRight2
};

enum class PreviousActions
{
	eMoveUp1,
	eMoveUp2,
	eMoveLeft1,
	eMoveLeft2,
	eMoveDown1,
	eMoveDown2,
	eMoveRight1,
	eMoveRight2
};

class IReceivesInput
{
public:
	virtual void HandleInput(Actions action) = 0;
};