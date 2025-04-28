#include "Water.h"
#include "Wall.h"
#include "Snake.h"

Water::Water(const sf::RenderWindow& window, const Wall& tankWalls)
{
	m_waterLevel = ((float)window.getSize().y - tankWalls.getSurfaceHeight() - tankWalls.getWallWidth()); // Sets the starting water level
}

void Water::Draw(sf::RenderWindow& window, const Wall& tankWalls)
{
	m_water.setSize({ (float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth(), m_waterLevel });
	m_water.setFillColor(sf::Color(12, 56, 133, 90)); // Dark Blue
	m_water.setOrigin({ ((float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth()) / 2, 0 });
	m_water.setPosition({ (((float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth()) / 2) + tankWalls.getLeftWallPos(), m_predictedNextWaterPosition - Snake::segmentSize });
	window.draw(m_water);
}

void Water::Update(const sf::Time& gameTimer, const sf::Time& gameTime)
{
	m_waterRatio = gameTimer / gameTime;

	// Water level multiplied by the water ratio gives us the game time divided up into the screen height - from this we can compare where the next water position should be; and then implement it. 
	if (m_waterLevel * m_waterRatio > m_predictedNextWaterPosition)
	{
		m_water.setPosition({ m_water.getPosition().x, m_predictedNextWaterPosition });
		m_predictedNextWaterPosition = m_water.getPosition().y + Snake::segmentSize;
	}
}

// Resets the water for game cycling
void Water::reset(const sf::RenderWindow& window, const Wall& tankWalls)
{
	m_waterLevel = ((float)window.getSize().y - tankWalls.getSurfaceHeight() - tankWalls.getWallWidth());
	m_predictedNextWaterPosition = 0;
	m_water.setPosition({ (((float)window.getSize().x - tankWalls.getLeftWallPos() - tankWalls.getWallWidth()) / 2) + tankWalls.getLeftWallPos(), m_predictedNextWaterPosition });
}

const float& Water::getPredictedNextWaterPosition() const
{
	return m_predictedNextWaterPosition;
}