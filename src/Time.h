#pragma once
#include "SFML\System\Clock.hpp"

////////////////////////////////////
//  Time Class:
//  Provides basic timers to the program to calculate frame times and the like
//  Provides two constant timers for the whole system
////////////////////////////////////

class Time
{
public:
	float getTimeSinceLastFrame(); // returns time, in secounds, since last frame

	int getFps();

	void resetFrameTime(); // must be called every frame

	float getTimerTime(); // returns current time in secounds

	void resetTimerTime(); // resets timer

private:
	sf::Clock frameTime; // holds frame time

	sf::Clock timerTime; // holds timer time

};