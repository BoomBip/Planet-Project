#include "SFML\System\Clock.hpp"
#include "Time.h"

float Time::getTimeSinceLastFrame()
{
	return (frameTime.getElapsedTime().asSeconds());
}

int Time::getFps()
{
	return (1/getTimeSinceLastFrame());
}

void Time::resetFrameTime()
{
	frameTime.restart();
}

float Time::getTimerTime()
{
	return (timerTime.getElapsedTime().asSeconds());
}

void Time::resetTimerTime()
{
	timerTime.restart();
}