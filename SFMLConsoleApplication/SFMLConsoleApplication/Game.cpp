#include "Game.h"
#include <iostream>
#include <cstdlib>

std::mt19937 Game::mGenerator;

namespace {
	const String windowTitle = "Asteroids";
	const VideoMode videoMode = VideoMode(768, 1024);
	const Color backgroundColor = Color::Black;
	const Vector2f SHIP_STARTPOSITION = Vector2f(354, 850);
	const int FRAMERATE_LIMIT = 60;
	const int START_LEVEL = 1;
	const float SHIP_RADIUS = 20.0f;
	const float SHIP_VELOCITY = 300.0f;
	const float COIN_RADIUS = 16.0f;
	const float COIN_VELOCITY = 40.0f;
	const float ASTEROID_RADIUS = 32.0f;
	const float ASTEROID_SPAWN_DELTA = 1.0f;
	const float ASTEROID_SPAWN_COUNT_BASE = 1.0f;
	const float ASTEROID_SPAWN_COUNT_INCREMENT = 0.5f;
	const float ASTEROID_MIN_VELOCITY = 80.0f;
	const float ASTEROID_DELTA_VELOCITY = 200.0f;
}

Game::Game() :
	mRenderWindow(videoMode, windowTitle, Style::Titlebar | Style::Close)
	, mGameOver(false)
	, mShip(0)
	, mCoin(0)
	, mLevel(START_LEVEL)
{
	mRenderWindow.setFramerateLimit(FRAMERATE_LIMIT);

	mCoinTexture.loadFromFile("CoinSprite.psd");
	mShipTexture.loadFromFile("ShipSprite.psd");
	mAsteroidTexture.loadFromFile("AsteroidSprite.psd");

	createShip();
	createCoin();
	

	mGenerator.seed((unsigned int)(time(0)));
}

Game::~Game()
{
}

void Game::run()
{
	Clock frameClock;
	mAsteroidSpawnClock;
	while (mRenderWindow.isOpen() && !mGameOver)
	{
		float deltaTime = frameClock.restart().asSeconds();
		handleWindowEvents();
		clearWindow();
		createAsteroid();

		updateShip(deltaTime);
		updateCoin(deltaTime);
		updateAsteroid(deltaTime);

		drawCoin();
		drawShip();
		drawAsteroid();

		displayWindow();
	}
}


Vector2f Game::getRandomPos(int min, int max)
{
	std::uniform_int_distribution<uint32_t> randomRange(min, max);

	float x = (float)(randomRange(mGenerator));
	float y = (float)(randomRange(mGenerator));
	return Vector2f(x, y);
}

void Game::handleWindowEvents() 
{
	Event event;
	while (mRenderWindow.pollEvent(event)) 
	{
		if (event.type == Event::Closed) 
		{
			mRenderWindow.close();
		}
	}
}

void Game::clearWindow()
{
	mRenderWindow.clear(backgroundColor);
}

void Game::displayWindow()
{
	mRenderWindow.display();
}

void Game::createCoin()
{
	mCoin = new Coin(mRenderWindow, mCoinTexture, getRandomPos(0, videoMode.width), COIN_VELOCITY, COIN_RADIUS);
}

void Game::drawCoin() 
{
	mCoin->draw();
}

void Game::updateCoin(float deltaTime)
{
	mCoin->update(deltaTime);
}

void Game::createShip()
{
	mShip = new Ship(mRenderWindow, mShipTexture, SHIP_STARTPOSITION, SHIP_VELOCITY, SHIP_RADIUS);
}

void Game::drawShip()
{
	mShip->draw();
}

void Game::updateShip(float deltaTime)
{
	mShip->update(deltaTime);
}

void Game::createAsteroid()
{
	if (ASTEROID_SPAWN_DELTA < mAsteroidSpawnClock.getElapsedTime().asSeconds())
	{
		//int spawnCount = int(ASTEROID_SPAWN_COUNT_BASE + mLevel * ASTEROID_SPAWN_COUNT_INCREMENT);
		for (size_t i = 0; 0 < 1; i++)
		{
			std::cout << astVector.size();
			Asteroid *asteroid = new Asteroid(mRenderWindow, mAsteroidTexture, getRandomPos(0, videoMode.width), ASTEROID_MIN_VELOCITY, ASTEROID_RADIUS);
			astVector.push_back(asteroid);
		}
		mAsteroidSpawnClock.restart();
	}
}

void Game::drawAsteroid()
{
	for (size_t i = 0; i < astVector.size(); i++)
	{
		std::cout << "drawing asteroid" << std::endl;
		mAsteroid = astVector[i];
		mAsteroid->draw();
	}
}

void Game::updateAsteroid(float deltaTime)
{
	for (size_t i = 0; i < astVector.size(); i++)
	{
		std::cout << "updating asteroid" << std::endl;
		mAsteroid = astVector[i];
		mAsteroid->update(deltaTime);
	}
}
