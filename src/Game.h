#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include "Time.h"
#include "Particle.h"
#include "Tracker.h"

class Game
{
public:
	static void start();
	

private:
	static bool isExiting();
	static void gameLoop();

	enum GameState { Uninitalized, ShowingSplash, Paused, ShowingMenu, Playing, Exiting };

	static GameState currGameState;
	static sf::RenderWindow mainWindow;
	
	static Time time;
	static sf::Vector2f initMouseInput;

	static Tracker particleTracker;
	static int currMassSetting;
	static int halfScreenX;
	static int halfScreenY;
	
};