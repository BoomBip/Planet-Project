#include "Particle.h"
#include <math.h>
#include <iostream>


Particle::Particle(int id, sf::Vector2f location, sf::Vector2f velocity, float mass) : 
	id(id),
	pos(location),
	vel(velocity),
	acc(sf::Vector2f(0,0)),
	mass(mass),
	radius(-1),
	mark(TOBEADDED){}

void Particle::refactor(sf::Vector2f location, sf::Vector2f velocity, float imass){
	pos = location;
	vel = velocity;
	mass = imass;
	radius = -1;
	acc = sf::Vector2f(0,0);
	mark = TOBEADDED;
}

// timeFactor is the amount of time, in secounds, since the last frame update
void Particle::update(sf::Time timeFactor) 
{
	vel += (acc * timeFactor.asSeconds());
	nPos += (vel * timeFactor.asSeconds());
	acc = sf::Vector2f(0,0);
}

void Particle::advance(){
	pos = nPos;
	nPos = pos;
}

void Particle::addAcel(Particle* a)
{
	//find distance away from field orign
	sf::Vector2f delta = pos - a->getPos();

	float distanceSquare = ((delta.x)*(delta.x) + (delta.y)*(delta.y));

	acc += (a->getMass() / distanceSquare) * delta;
}

void Particle::draw(sf::RenderWindow& renderWindow){
	sf::CircleShape circle;
	circle.setPosition(pos);
	circle.setRadius(getRadius());

	if (mass < 0)
		circle.setFillColor(sf::Color(0, 0, 255, 255));
	else
		circle.setFillColor(sf::Color(255, 0, 0, 255));

	renderWindow.draw(circle);
}

float Particle::getMass(){
	return mass;
}

sf::Vector2f Particle::getPos(){
	return pos;
}

float Particle::getRadius(){
	if(radius < 0)
		radius = std::log(mass);

	return radius;
}

sf::Vector2f Particle::getVel(){
	return vel;
}

MarkStatus Particle::getMark(){
	return mark;
}

void Particle::setMark(MarkStatus imark){
	mark = imark;
}