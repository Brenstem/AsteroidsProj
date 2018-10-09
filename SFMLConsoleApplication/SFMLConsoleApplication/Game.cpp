#include "Game.h"
#include "Coin.h"
#include <iostream>
#include <cstdlib>

namespace {
	const String windowTitle = "Asteroids";
	const VideoMode videoMode = VideoMode(768, 1024);
	const Color backgroundColor = Color::Black;
	const int FRAMERATE_LIMIT = 60;
	const int START_LEVEL = 1;
	const float SHIP_RADIUS = 20.0f;
	const float SHIP_VELOCITY = 0;
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
	, mCoin(0)
{
	mRenderWindow.setFramerateLimit(FRAMERATE_LIMIT);
	mCoinTexture.loadFromFile("CoinSprite.psd");
	createCoin();
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
		handleWindowEvents();
		clearWindow();

		drawCoin();

		displayWindow();
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

void Game::createCoin()
{
	mCoin = new Coin(mRenderWindow, mCoinTexture, getRandomPos(), COIN_VELOCITY, COIN_RADIUS);
}

Vector2f Game::getRandomPos()
{
	float x = (float)(std::rand() % mRenderWindow.getSize().x + 0);
	float y = (float)(std::rand()% mRenderWindow.getSize().y + 0);
	return Vector2f(x, y);
}

void Game::drawCoin() 
{
	mCoin->draw();
}
