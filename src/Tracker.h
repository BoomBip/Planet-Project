
#pragma once
#include <list>
#include <vector>
#include "Particle.h"

class Tracker
{
public:

	static Tracker* create(int initalCapacity);

	int addParticle(sf::Vector2f location, sf::Vector2f velocity, float mass);

	void generateProtoDisk(float mass, sf::Vector2f location);

	bool togglePause();

	void update(sf::Time timefactor, sf::RenderWindow& renderWindow);

private:
	//get rid of these
	Tracker(int initCap);
	Tracker(const Tracker& t);
	void operator=(const Tracker& t);
	~Tracker();

	void freeParticle(int id);

	int getFreeId();

	static void cleanup();

	static Tracker* instance;

	static std::vector<Particle*> _particles;
	static std::vector<int> _freeIds;

	bool _paused;
};