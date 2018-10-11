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
	, mAsteroidSpawnCounter(0)
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
	while (mRenderWindow.isOpen() && !mGameOver)
	{
		float deltaTime = frameClock.restart().asSeconds();
		mAsteroidSpawnCounter += deltaTime;
		handleWindowEvents();
		clearWindow();


		updateShip(deltaTime);
		updateCoin(deltaTime);
		updateAsteroid(deltaTime);

		drawCoin();
		drawShip();
		drawAsteroid();

		createAsteroid();

		handleCoinPickup();
		handleLostCoin();
		handleAsteroidCollisions();


		displayWindow();
	}
}


float Game::getRandomNumber(int min, int max)
{
	std::uniform_int_distribution<uint32_t> randomRange(min, max);

	return (float)(randomRange(mGenerator));
}

void Game::destroyCoin()
{
	delete mCoin;
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
	mCoin = new Coin(mRenderWindow, mCoinTexture, Vector2f(getRandomNumber(0, videoMode.width-COIN_RADIUS), -COIN_RADIUS), COIN_VELOCITY, COIN_RADIUS);
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
	mAsteroidSpawnCountModifier = ASTEROID_SPAWN_COUNT_BASE;
	if (mAsteroidSpawnCountModifier < mAsteroidSpawnCounter)
	{
		Asteroid *asteroid = new Asteroid(mRenderWindow, mAsteroidTexture, Vector2f(getRandomNumber(0, videoMode.width-ASTEROID_RADIUS), -ASTEROID_RADIUS), ASTEROID_MIN_VELOCITY, ASTEROID_RADIUS);
		astVector.push_back(asteroid);
		mAsteroidSpawnCounter = 0;
	}
	mAsteroidSpawnCountModifier = mAsteroidSpawnCountModifier * ASTEROID_SPAWN_COUNT_INCREMENT;
}

void Game::drawAsteroid()
{
	for (size_t i = 0; i < astVector.size(); i++)
	{
		astVector[i]->draw();
	}
}

void Game::updateAsteroid(float deltaTime)
{
	for (size_t i = 0; i < astVector.size(); i++)
	{
		astVector[i]->update(deltaTime);
	}
}

bool Game::overlap(Vector2f position0, float rad0, Vector2f position1, float rad1)
{
	float deltaX = position0.x - position1.x;
	float deltaY = position0.y - position1.y;
	float radiusSum = rad0 + rad1;
	return deltaX * deltaX * deltaY * deltaY < radiusSum * radiusSum;
}

bool Game::overlap(Ship * ship, Coin * coin)
{
	Vector2f shipPosition = ship->getPos();
	float shipRadius = ship->getRad();
	Vector2f coinPosition = coin->getPos();
	float coinRadius = coin->getRad();

	return overlap(shipPosition, shipRadius, coinPosition, coinRadius);
}

bool Game::overlap(Ship * ship, Asteroid *asteroid)
{
	Vector2f shipPosition = ship->getPos();
	float shipRadius = ship->getRad();
	Vector2f coinPosition = asteroid->getPos();
	float coinRadius = asteroid->getRad();

	return overlap(shipPosition, shipRadius, coinPosition, coinRadius);
}

void Game::handleCoinPickup()
{
	if (overlap(mShip, mCoin))
	{
		mLevel++;
		destroyCoin();
		createCoin();
	}
}

void Game::handleAsteroidCollisions()
{
	for (size_t i = 0; i < astVector.size(); i++)
	{
		if (overlap(mShip, astVector[i]))
		{
			mGameOver = true;
		}
	}
}

void Game::handleLostCoin()
{
	if (COIN_RADIUS + mRenderWindow.getSize().y < mCoin->getPos().y)
	{
		mGameOver = true;
	}
}
