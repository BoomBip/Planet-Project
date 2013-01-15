#include "Particle.h"
#include <vector>

class Tracker
{
public:

	void initialise(int reserve);

	int addParticle(sf::Vector2f location, sf::Vector2f velocity, float mass);

	void generateProtoDisk(float mass, sf::Vector2f location);

	void freeParticle(int id);

	void freeAll();

	Particle& getParticle(int id);

	void iterateParticles(float timeFactor, sf::RenderWindow& renderWindow);

	std::vector<Particle> m_Particles;

	std::vector<int> m_freeParticles;

	bool Pause;
};