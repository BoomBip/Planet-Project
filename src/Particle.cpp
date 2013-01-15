#include "Particle.h"
#include <math.h>
#include <iostream>

//Some varivle initialization
float Particle::gConstant = 1.0;
float Particle::vConstant = 500;

bool m_active = false;
int id = -1;
float radius =0;

// timeFactor is the amount of time, in secounds, since the last frame update
void Particle::updatePosition(float timeFactor) 
	{
		if (m_active == true)
		{
			particleVelocity += (particleAcceleration * timeFactor);
			particleLocation += (particleVelocity / vConstant);
			particleAcceleration.x = 0;
			particleAcceleration.y = 0;

		}
	}

void Particle::accelerationFromRadialField(sf::Vector2f fieldLocation, float fieldMass)
	{
			//find distance away from field orign
			sf::Vector2f delta;
			delta.x = fieldLocation.x - particleLocation.x;
			delta.y = fieldLocation.y - particleLocation.y;

			float distance;
			distance = ((delta).x)*((delta).x) + ((delta).y)*((delta).y);
			
			//find direction of field orign
			float heading;
			heading = atan2((delta).y, (delta).x);

			//apply particleAcceleration
			float totalAcceleration;
			totalAcceleration = gConstant * (fieldMass) / (distance);
			
			particleAcceleration.x += (cos(heading) * totalAcceleration);
			particleAcceleration.y += (sin(heading) * totalAcceleration);
	}

void Particle::load(sf::Vector2f inputLocation, float inputMass, int idIN, sf::Vector2f inputVelocity)
	{
		particleLocation = inputLocation;
		
		particleVelocity.x = inputVelocity.x;
		particleVelocity.y = inputVelocity.y;
		particleAcceleration.x = 0;
		particleAcceleration.y = 0;
		particleMass = inputMass;
		isActive= true;
		id = idIN;
		_isMarked = false;

		radius = log(abs(particleMass))/2;
}
void Particle::mergeParticle(sf::Vector2f inputVelocity, float inputMass)
{
	particleMass += inputMass;
	particleVelocity.x += inputVelocity.x/particleMass;
	particleVelocity.y += inputVelocity.y/particleMass;
}

void Particle::destroyParticle()
	{
		//remove all details
		_isLoaded = false;
		particleVelocity.x = 0;
		particleVelocity.y = 0;
		particleAcceleration.x = 0;
		particleAcceleration.y = 0;
		m_active = false;
		radius = 0;
		_isMarked = false;
	}

void Particle::drawParticle(sf::RenderWindow& renderWindow)
	{
			if(m_active = true)
			{	
				radius = (log(abs(particleMass)))/2;

				sf::CircleShape circle;
				circle.setPosition(particleLocation.x, particleLocation.y);
				circle.setRadius(radius);

				if (particleMass < 0)
					circle.setFillColor(sf::Color(0, 0, 255, 255));
				else
					circle.setFillColor(sf::Color(255, 0, 0, 255));
				renderWindow.draw(circle);
			}
	}

sf::Vector2f Particle::returnLocation()
{
	return particleLocation;
}

sf::Vector2f Particle::returnVelocity()
{
	return particleVelocity;
}


float Particle::returnMass()
{
	return particleMass;
}

int Particle::returnId()
{
	return particleId;
}

bool Particle::returnMark()
{
	return _isMarked;
}

void Particle::mark()
{
	_isMarked = !_isMarked;
}