#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Coin.h"
#include "Ship.h"
#include "Asteroid.h"
#include <random>
#include <vector>

using namespace sf;

class Game
{
public:
	Game();
	~Game();
	void run();
	float f = 10;

private:
	RenderWindow mRenderWindow;
	bool mGameOver;
	int mLevel;
	static std::mt19937 mGenerator;

	Ship *mShip;
	Texture mShipTexture;

	Coin *mCoin;
	Texture mCoinTexture;

	typedef std::vector<Asteroid*> AsteroidVector;
	AsteroidVector astVector;
	Texture mAsteroidTexture;
	Clock mAsteroidSpawnClock;
	Asteroid *mAsteroid;

	void handleWindowEvents();
	void clearWindow();
	void displayWindow();

	void createCoin();
	void drawCoin();
	void updateCoin(float deltaTime);

	void createShip();
	void drawShip();
	void updateShip(float deltaTime);

	void createAsteroid();
	void drawAsteroid();
	void updateAsteroid(float deltaTime);

	Vector2f getRandomPos(int min, int max);
};

#endif // !INCLUDE_GAME