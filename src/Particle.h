#pragma once

#include "SFML\Graphics.hpp"

#define maxVelocity 100

enum MarkStatus{
	NOMARK,
	TOBEDELETED,
	TOBEADDED,
	DELETED
};

class Particle {
public:

	const int id;

	Particle(int id, sf::Vector2f location, sf::Vector2f velocity, float mass);

	void refactor(sf::Vector2f location, sf::Vector2f velocity, float mass);

	void update(sf::Time delta);

	void advance();

	void addAcel(Particle* a);

	void draw(sf::RenderWindow& renderWindow);

	float getMass();

	sf::Vector2f getPos();

	float getRadius();

	sf::Vector2f getVel();

	MarkStatus getMark();

	void setMark(MarkStatus mark);

private:

	MarkStatus mark;

	float mass;

	float radius;

	sf::Vector2f pos;

	sf::Vector2f nPos;

	sf::Vector2f vel;

	sf::Vector2f acc;
};
