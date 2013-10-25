#include "Game.h"
#include <iostream>

Game::GameState Game::currGameState = Uninitalized;
sf::RenderWindow Game::mainWindow;
Time Game::time;
sf::Vector2f Game::initMouseInput;
Tracker* Game::particleTracker = Tracker::create(100);
int Game::currMassSetting;
int Game::halfScreenX = 512;
int Game::halfScreenY = 400;

/*
	Game Initalization
	-Sets up varibles
*/

void Game::start()
{
	if (currGameState != Uninitalized)
		return;

	mainWindow.create(sf::VideoMode((800), (600), 32), "Particles", sf::Style::Default);

	initMouseInput.x = 0;
	initMouseInput.y = 0;

	currGameState = Game::Playing;
	currMassSetting = 10;

	while (!isExiting())
		gameLoop();

	mainWindow.close();
}

bool Game::isExiting()
{
	if (currGameState == Game::Exiting)
		return true;
	else 
		return false;
}

void Game::gameLoop()
{
	sf::Event currentEvent;
	mainWindow.pollEvent(currentEvent);
		switch (currGameState)
		{
			case Game::Playing:
			{
			
			mainWindow.clear(sf::Color(0, 0, 0));
			
			float timeFactor = time.getTimeSinceLastFrame();

			particleTracker->update(sf::seconds(timeFactor), mainWindow);

			mainWindow.display();
			
			time.resetFrameTime();

			//Accepting user input
			//shut down when [x] button pressed
			if (currentEvent.type == sf::Event::Closed)
				currGameState = Game::Exiting;

			//exit on pressing escape
			if ((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Escape))
				currGameState = Game::Exiting;

			//change mass for future particles by pressing number keys
			if ((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Num1))
				currMassSetting = 10;
			if ((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Num2))
				currMassSetting = 100;
			if ((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Num3))
				currMassSetting = 1000;
			if ((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Num4))
				currMassSetting = 10000;
			if ((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Num5))
				currMassSetting = 100000;
			if((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Num6))
				currMassSetting = 1000000;
			if((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Num7))
				currMassSetting = 10000000;
			if((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Num8))
				currMassSetting = 100000000;
			if((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Num9))
				currMassSetting = 1000000000;
			//toggle negative mass setting
			if((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Dash))
				currMassSetting *= -1;
			
			//capture inital mouse click for spawning particles
			if ((currentEvent.type == sf::Event::MouseButtonPressed) && (currentEvent.mouseButton.button == sf::Mouse::Left))
			{
				const sf::Mouse mouse;
				initMouseInput.x = (mouse.getPosition(mainWindow).x);
				initMouseInput.y = (mouse.getPosition(mainWindow).y);
			}
			//capture mouse button release and calcualte velocy for new particle
			if ((currentEvent.type == sf::Event::MouseButtonReleased) && (currentEvent.mouseButton.button == sf::Mouse::Left))
			{
				const sf::Mouse mouse;
				sf::Vector2i releaseMouseInput = (mouse.getPosition(mainWindow));
				sf::Vector2f velocity((initMouseInput.x - releaseMouseInput.x), (initMouseInput.y - releaseMouseInput.y));

				particleTracker->addParticle(initMouseInput, velocity, currMassSetting);
			}

			//destoys all particles when delete is pressed
			//if ((currentEvent.type == sf::Event::KeyPressed) && (currentEvent.key.code == sf::Keyboard::Delete))
				//particleTracker.freeAll();

			//generates a disk of particles on right click
			if ((currentEvent.type == sf::Event::MouseButtonPressed) && (currentEvent.mouseButton.button == sf::Mouse::Right))
			{
				const sf::Mouse mouse;
				sf::Vector2f position;
				position.x = (mouse.getPosition(mainWindow).x);
				position.y = (mouse.getPosition(mainWindow).y);
				particleTracker->generateProtoDisk(currMassSetting, position);
			}
			
			break;
		}
	}
}
