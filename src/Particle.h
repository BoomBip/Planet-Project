#pragma once

#include "SFML\Graphics.hpp"
///////////////////////////////////////////////////
//  Particle Class:
//  General class for all indevidual particles (planets)
//  Functions include:

//		-accelerationFromRadialField(...)
//			-Called for each particle against all other particles, each frame. 
//			-Calculates and adds up the gravitational acceleration from each.
//		-load(...)
//			-Initializes the particles starting varibles (particle objects might 
//			  be reused so the construtor is not always avaible)
//			-Called on particle start
//		-mergeParticle(...)
//			-Adds mass and velocity from a destroyed particle to this object
//			-Called when two particles hit each other
//		-destroyParticle();
//			-Puts particle into inacivity
//			-May be replaced at any time
//		-mark()
//			-Toggles a bool marking the particle for dystruction on next frame
//			-Called when particle collides with anouther
//			-Particles can't be destroyed immediatly otherwise they'll disapear and 
//			  move before all other particles can be affected by it
//
//  Other values and funtions are self-explanitory
///////////////////////////////////////////////////
class Particle
{
public:
	bool isActive;

	float radius;

	void updatePosition(float timeFactor);

	void accelerationFromRadialField(sf::Vector2f fieldLocation, float fieldMass); // circular, affected by distance

	void load(sf::Vector2f location, float mass, int id, sf::Vector2f velocity);
	
	void mergeParticle(sf::Vector2f velocity, float mass);

	void destroyParticle();

	void drawParticle(sf::RenderWindow& renderWindow);

	sf::Vector2f returnLocation();
	
	sf::Vector2f returnVelocity();

	float returnMass();

	int returnId();

	bool returnMark();

	void mark();

private:
	//graphics stuff
	sf::Font _font;

	bool _isLoaded;

	bool _isMarked;

	//physics stuff
	float particleMass;
	
	int particleId;

	sf::Vector2f particleLocation;

	sf::Vector2f particleVelocity;

	sf::Vector2f particleAcceleration;

	static float gConstant;

	static float vConstant; //universal constant that adjust velocity to be more managable
};