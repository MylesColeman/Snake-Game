#pragma once
#include <SFML/Graphics.hpp>

class WaterLeak
{
private:
	struct Particle
	{
		sf::CircleShape shape;
		sf::Vector2f velocity;
	};

	std::vector<Particle> m_particles;
	sf::Vector2f m_emissionPoint;
	sf::Clock m_emissionClock;
	float m_emissionRate{ 50.0f }; // Particles per second

	void EmitParticle();
public:
	WaterLeak(sf::Vector2f emissionPoint, unsigned int numParticles = 200);

	void Draw(sf::RenderWindow& window);
	void Update(sf::Time deltaTime);
};