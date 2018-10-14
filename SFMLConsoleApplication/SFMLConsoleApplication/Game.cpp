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
	const int SHIP_RADIUS = 32;
	const int SHIP_VELOCITY = 300;
	const int COIN_RADIUS = 16;
	const int COIN_VELOCITY = 40;
	const int ASTEROID_RADIUS = 32;
	const int ASTEROID_SPAWN_DELTA = 1;
	const int ASTEROID_SPAWN_COUNT_BASE = 1;
	const float ASTEROID_SPAWN_COUNT_INCREMENT = 0.98f;
	const int ASTEROID_MIN_VELOCITY = 80;
	const int ASTEROID_DELTA_VELOCITY = 200;
}

Game::Game() :
	mRenderWindow(videoMode, windowTitle, Style::Titlebar | Style::Close)
	, mGameOver(false)
	, mShip(0)
	, mCoin(0)
	, mLevel(START_LEVEL)
	, mAsteroidSpawnCounter(0)
	, mAsteroidSpawnCountModifier(ASTEROID_SPAWN_COUNT_BASE)
{
	mRenderWindow.setFramerateLimit(FRAMERATE_LIMIT);

	mCoinTexture.loadFromFile("CoinSprite.psd");
	mShipTexture.loadFromFile("ShipSprite.psd");
	mAsteroidTexture.loadFromFile("AsteroidSprite.psd");

	createShip();
	createCoin();
	
	std::cout << mCoinTexture.getSize().x;
	std::cout << mCoinTexture.getSize().y;

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

		createAsteroid();

		updateShip(deltaTime);
		updateCoin(deltaTime);
		updateAsteroid(deltaTime);

		draw();

		handleCoinPickup();
		handleLostCoin();
		handleAsteroidCollisions();
		handleAsteroidLoss();

		displayWindow();
	}
}


int Game::getRandomNumber(int min, int max)
{
	std::uniform_int_distribution<uint32_t> randomRange(min, max);

	return randomRange(mGenerator);
}


void Game::draw()
{
	mCoin->draw();
	mShip->draw();

	for (size_t i = 0; i < astVector.size(); i++)
	{
		astVector[i]->draw();
	}
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


void Game::destroyCoin()
{
	delete mCoin;
}


void Game::createCoin()
{
	mCoin = new Coin(mRenderWindow, mCoinTexture, Vector2f((float)(getRandomNumber(0, videoMode.width - COIN_RADIUS)), -COIN_RADIUS), COIN_VELOCITY, COIN_RADIUS);
}

void Game::createAsteroid()
{
	if (mAsteroidSpawnCountModifier < mAsteroidSpawnCounter)
	{
		Asteroid *asteroid = new Asteroid(mRenderWindow, mAsteroidTexture, Vector2f((float)(getRandomNumber(0, videoMode.width - ASTEROID_RADIUS)), -ASTEROID_RADIUS), (float)(getRandomNumber(ASTEROID_MIN_VELOCITY, ASTEROID_DELTA_VELOCITY)), ASTEROID_RADIUS);
		astVector.push_back(asteroid);
		mAsteroidSpawnCounter = 0;
	}
}

void Game::createShip()
{
	mShip = new Ship(mRenderWindow, mShipTexture, SHIP_STARTPOSITION, SHIP_VELOCITY, SHIP_RADIUS);
}


void Game::updateCoin(float deltaTime)
{
	mCoin->update(deltaTime);
}

void Game::updateShip(float deltaTime)
{
	mShip->update(deltaTime);
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
	float distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	return  distance <= radiusSum;
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
	Vector2f asteroidPosition = asteroid->getPos();
	float asteroidRadius = asteroid->getRad();

	return overlap(shipPosition, shipRadius, asteroidPosition, asteroidRadius);
}


void Game::handleCoinPickup()
{
	if (overlap(mShip, mCoin))
	{
		std::cout << "picked up coin, currently at level: " << mLevel << std::endl;
		mLevel++;
		destroyCoin();
		createCoin();
		mAsteroidSpawnCountModifier *= ASTEROID_SPAWN_COUNT_INCREMENT;
	}
}

void Game::handleAsteroidCollisions()
{
	for (size_t i = 0; i < astVector.size(); i++)
	{
		if (overlap(mShip, astVector[i]))
		{
			std::cout << "Collided with asteroid" << std::endl;
			mGameOver = true;
		}
	}
}

void Game::handleLostCoin()
{
	if (COIN_RADIUS + mRenderWindow.getSize().y < mCoin->getPos().y)
	{
		std::cout << "Coin out of scope" << std::endl;
		//mGameOver = true;
	}
}

void Game::handleAsteroidLoss()
{
	float maxY = mRenderWindow.getSize().y + (float)ASTEROID_RADIUS;
	AsteroidVector remainingAsteroids;

	for (size_t i = 0; i < astVector.size(); i++)
	{
		Asteroid *asteroid = astVector[i];
		if (asteroid->getPos().y < maxY)
		{
			remainingAsteroids.push_back(asteroid);
		}
		else
		{
			std::cout << "asteroid pushed back" << std::endl;
			delete asteroid;
		}
	}
	astVector = remainingAsteroids;
}
