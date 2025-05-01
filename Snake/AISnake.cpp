#include "AISnake.h"
#include "GameData.h"
#include "Wall.h"
#include "Water.h"
#include <limits>
#include <algorithm>

float AISnake::CalculateRewardForDirection(Direction direction, GameData& m_gameData)
{
	float reward = 0.0f;

	// Checks next grid space along
	sf::Vector2f predictedNextPos{ 0.0f, 0.0f };
	if (direction == Direction::Up)
		predictedNextPos = { getSegmentList().front().x, getSegmentList().front().y - segmentSize };
	else if (direction == Direction::Left)
		predictedNextPos = { getSegmentList().front().x - segmentSize, getSegmentList().front().y };
	else if (direction == Direction::Down)
		predictedNextPos = { getSegmentList().front().x, getSegmentList().front().y + segmentSize };
	else if (direction == Direction::Right)
		predictedNextPos = { getSegmentList().front().x + segmentSize, getSegmentList().front().y };
	else
		std::cerr << "Unknown Direction - Error" << std::endl;

	reward += GetWallProximityReward(predictedNextPos, *m_gameData.m_tankWalls, m_gameData.m_window);

	// Check breath level to gauge whether breath is worth it
	if (m_breath < 15) 
	{
		if (direction == Direction::Up)
			reward += 100000.0f; 
		if (predictedNextPos.y > m_gameData.m_water->getPredictedNextWaterPosition() + segmentSize * 2) 
			reward -= 5000.0f;
	}
	else 
	{
		reward += GetWaterProximityReward(predictedNextPos, *m_gameData.m_water);
	}

	// Finds the closest collectable that's ready for collection
	if (m_closestCollectable && m_closestCollectable->getCollectableAliveStatus() && m_closestCollectable->getIsVineFullyGrown())
	{
		float foodProximityWeight = 5.0f;
		reward += GetFoodProximityReward(predictedNextPos, m_closestCollectable->getCollectablePosition()) * foodProximityWeight;
	}

	return reward;
}

float AISnake::GetWallProximityReward(sf::Vector2f predictedPos, const Wall& tankWalls, sf::RenderWindow* m_window)
{
	float reward = 0.0f;
	float dangerMultiplier = -5.0f; 

	// Increases negative reward dependent on distance
	if (predictedPos.y < 0 + segmentSize) // Top Side
		reward += dangerMultiplier * (segmentSize - (predictedPos.y - 0));
	if (predictedPos.x < tankWalls.getLeftWallPos() - (tankWalls.getWallWidth() / 2) + segmentSize) // Left Side
		reward += dangerMultiplier * (segmentSize - (predictedPos.x - (tankWalls.getLeftWallPos() - (tankWalls.getWallWidth() / 2))));
	if (predictedPos.y > m_window->getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight() - segmentSize) // Bottom side
		reward += dangerMultiplier * (segmentSize - (predictedPos.y - (m_window->getSize().y - tankWalls.getWallWidth() - tankWalls.getSurfaceHeight())));
	if (predictedPos.x > m_window->getSize().x - tankWalls.getWallWidth() - segmentSize) // Right Side
		reward += dangerMultiplier * (segmentSize - ((m_window->getSize().x - tankWalls.getWallWidth()) - predictedPos.x));

	return reward;
}

float AISnake::GetWaterProximityReward(sf::Vector2f predictedPos, const Water& water)
{
	float reward = 0.0f;
	float dangerMultiplier = -5.0f;
	float waterLevel = water.getPredictedNextWaterPosition();
	float surfaceBuffer = segmentSize * 1.5f; 

	// Increases negative reward dependent on distance
	if (predictedPos.y < waterLevel - segmentSize)
		reward += dangerMultiplier * (waterLevel - segmentSize - predictedPos.y);
	else if (predictedPos.y > waterLevel + segmentSize)
		reward += dangerMultiplier * (predictedPos.y - (waterLevel + segmentSize));
	else if (predictedPos.y < waterLevel + surfaceBuffer && predictedPos.y > waterLevel - surfaceBuffer)
		reward += 1.0f; 

	return reward;
}

float AISnake::GetFoodProximityReward(sf::Vector2f predictedPos, sf::Vector2f foodPos)
{
	float reward = 0.0f;
	float currentDistanceSq = (getSegmentList().front() - foodPos).lengthSquared();
	float predictedDistanceSq = (predictedPos - foodPos).lengthSquared();
	float rewardMultiplier = 2.0f; // Increase reward for getting closer

	if (predictedDistanceSq < currentDistanceSq)
		reward += rewardMultiplier * (currentDistanceSq - predictedDistanceSq); 

	return reward;
}

bool AISnake::FindClosestFood(GameData& m_gameData)
{
	m_closestCollectable = nullptr;
	float closestDistance{ std::numeric_limits<float>::max() };

	// Finds the closest collectible thats ready for collection
	for (Collectable* collectable : *m_gameData.m_collectableVector)
	{
		if (collectable->getCollectableAliveStatus() && collectable->getIsVineFullyGrown())
		{
			float distanceSq = (getSegmentList().front() - collectable->getCollectablePosition()).lengthSquared();

			if (distanceSq < closestDistance)
			{
				closestDistance = distanceSq;
				m_closestCollectable = collectable;
			}
		}
	}

	if (m_closestCollectable == nullptr)
		return false;

	return true;
}

AISnake::AISnake(int type, sf::Vector2f headPosition) : Snake(headPosition) {}

void AISnake::Update(GameData& m_gameData)
{
	FindClosestFood(m_gameData);

	// Adds all directions to vector to determine the best one
	std::vector<std::pair<float, Direction>> bestDirections;
	bestDirections.push_back({ CalculateRewardForDirection(Direction::Up, m_gameData), Direction::Up });
	bestDirections.push_back({ CalculateRewardForDirection(Direction::Left, m_gameData), Direction::Left });
	bestDirections.push_back({ CalculateRewardForDirection(Direction::Down, m_gameData), Direction::Down });
	bestDirections.push_back({ CalculateRewardForDirection(Direction::Right, m_gameData), Direction::Right });

	// Sorts the vector from best to worst
	std::sort(bestDirections.rbegin(), bestDirections.rend());

	if (!bestDirections.empty() && m_isAlive)
	{
		Direction bestDirection = bestDirections[0].second;

		// Checks if the best direction is the opposite of the previous one, i.e. a 180
		if ((bestDirection == Direction::Up && m_previousDirection == Direction::Down) || (bestDirection == Direction::Down && m_previousDirection == Direction::Up) || (bestDirection == Direction::Left && m_previousDirection == Direction::Right) || (bestDirection == Direction::Right && m_previousDirection == Direction::Left))
		{
			// If it's a reversal and there's a second best option, choose that
			if (bestDirections.size() > 1)
				m_direction = bestDirections[1].second;
		}
		else
			m_direction = bestDirection;
	}

	Move();
}