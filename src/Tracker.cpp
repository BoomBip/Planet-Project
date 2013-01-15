#include "Tracker.h"
#include <iostream>

//std::vector<Particle> m_Particles;
//std::vector<int> m_freeParticles;

void Tracker::initialise(int reserve)
{
	Pause = false;
	m_Particles.reserve(reserve);
	m_freeParticles.reserve(reserve);
}

int Tracker::addParticle(sf::Vector2f location, sf::Vector2f velocity, float mass)
{
	int id = -1;

	if(m_freeParticles.size())//if there are any bullets existing
	{
		id = m_freeParticles.back(); //get the id of the last free bullet location
		m_freeParticles.pop_back(); //delete the last free bullet
	}
	else
	{
		id = m_Particles.size(); //id equals amount of bullets existing (+1)
		Particle newParticle;
		m_Particles.push_back(newParticle);//add new bullet
	}

	m_Particles[id].load(location, mass, id, velocity);
	return id;
}

void Tracker::generateProtoDisk(float mass, sf::Vector2f inputLocation)
{
	sf::Vector2f orgin = inputLocation;

	for (int i = 0; i < 50; i++)
	{
		float distance = std::rand() % 100;
		float heading = std::rand() % 7; //random direction

		sf::Vector2f location((cos(heading) * distance), (sin(heading) * distance));
		sf::Vector2f velocity(0.0f, 0.0f);
		addParticle(location, velocity, mass);
	}
}

void Tracker::freeParticle(int id)
{
	m_Particles[id].destroyParticle(); //kill the bullet
	m_freeParticles.push_back(id);//add it to free bullet list
}

void Tracker::freeAll()
{
	std::vector<Particle>::iterator j;
	for (j = m_Particles.begin(); j != m_Particles.end(); j++)
	{
		freeParticle(j->returnId());
	}
}

Particle& Tracker::getParticle(int id)
{
	return m_Particles[id];
}

void Tracker::iterateParticles(float timeFactor, sf::RenderWindow& renderWindow)
{
	std::vector<Particle>::iterator i;
	for (i = m_Particles.begin(); i != m_Particles.end(); i++)
	{
		if ((i->isActive) == true && Pause == false)
		{
			
			i->updatePosition(timeFactor);
			i->drawParticle(renderWindow);

			if (i->returnMark() == true)
			{
				freeParticle(i->returnId());
			}

			else
			{
				//sub-iterator for two particles affecting each other
				std::vector<Particle>::iterator j;
				for (j = m_Particles.begin(); j != m_Particles.end(); j++)
				{
					if (j->returnId() != i->returnId() && j->isActive)
					{
						//gravity between two particles
						i->accelerationFromRadialField(j->returnLocation(), (j->returnMass()));

						//Collision detection, finds distance between particles and mark() and murge() is applid to those who are too close
						long double distanceX, distanceY;
						distanceX = ((i->returnLocation()).x - (j->returnLocation()).x);
						distanceY = ((i->returnLocation()).y - (j->returnLocation()).y);

						if ((abs(distanceX) < i->radius) && (abs(distanceY) < i->radius))
						{
							i->mergeParticle(j->returnVelocity(), j->returnMass());
							j->mark();
						}
					}
				}
			}
		}	
	}
}