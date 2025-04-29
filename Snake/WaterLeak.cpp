#include "WaterLeak.h"

// Generates a random integer between two points
int getRandomInt(int min, int max)
{
	return min + std::rand() % (max - min + 1);
}

WaterLeak::WaterLeak(sf::Vector2f emissionPoint, unsigned int numParticles) : m_emissionPoint(emissionPoint), m_particles(numParticles)
{
	// Loops through a vector of particles generating some starter data
	for (auto& particle : m_particles)
	{
		float angle = (float)getRandomInt(-45, 45);

		float horizontalSpeed = -(float)getRandomInt(50, 150);
		float verticalSpeed = (float)getRandomInt(-50, 50);
		particle.velocity = sf::Vector2f(horizontalSpeed, verticalSpeed);

		particle.shape.setPosition(m_emissionPoint);
		particle.shape.setFillColor(sf::Color(12, 56, 133, 90)); // Blue
		particle.shape.setRadius(2.0f);
	}
}

void WaterLeak::Draw(sf::RenderWindow& window)
{
	for (const auto& particle : m_particles)
	{
		window.draw(particle.shape);
	}
}

void WaterLeak::Update(sf::Time deltaTime)
{
	float emitInterval = 1.0f / m_emissionRate;
	// Checks if the emission interval has passed, if so emits a particle and resets the clock for the next
	if (m_emissionClock.getElapsedTime().asSeconds() >= emitInterval)
	{
		EmitParticle();
		m_emissionClock.restart();
	}

	// Loops through the vector applying velocity to the particles and resetting them if off screen
	for (auto& particle : m_particles)
	{
		particle.shape.move(particle.velocity * deltaTime.asSeconds());

		if (particle.shape.getPosition().x < -10.0f)
		{
			particle.shape.setPosition(m_emissionPoint);
		}
	}
}

void WaterLeak::EmitParticle()
{
	float angle = (float)getRandomInt(-45, 45);

	float horizontalSpeed = -(float)getRandomInt(50, 150);
	float verticalSpeed = (float)getRandomInt(-50, 50);
	sf::Vector2f newVelocity = sf::Vector2f(horizontalSpeed, verticalSpeed);

	// Loops through the particle vector assigning data
	for (auto& particle : m_particles)
	{
		if (particle.shape.getPosition().x <= -10.0f)
		{
			particle.velocity = newVelocity;
			particle.shape.setPosition(m_emissionPoint);
			particle.shape.setFillColor(sf::Color(12, 56, 133, 90));
			return;
		}
	}
}