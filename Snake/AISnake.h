#pragma once
#include "Snake.h"
#include "Collectable.h"


class Game;

class AISnake : public Snake
{
private:
	bool FindClosestFood(GameData& m_gameData);
	Collectable* m_closestCollectable{ nullptr };

	// Reward System
	float CalculateRewardForDirection(Direction direction, GameData& m_gameData);
	float GetWallProximityReward(sf::Vector2f predictedPos, const Wall& tankWalls, sf::RenderWindow* m_window);
	float GetWaterProximityReward(sf::Vector2f predictedPos, const Water& water);
	float GetFoodProximityReward(sf::Vector2f predictedPos, sf::Vector2f foodPos);
public:
	AISnake(int type, sf::Vector2f headPosition);

	void Update(GameData& m_gameData) override;
	SnakeType getType() const override { return SnakeType::AI; }
};