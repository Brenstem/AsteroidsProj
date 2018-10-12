#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include <vector>

#include "Coin.h"
#include "Ship.h"
#include "Asteroid.h"


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
	typedef std::vector<Asteroid*> AsteroidVector;
	AsteroidVector astVector;

	Texture mShipTexture;
	Texture mAsteroidTexture;
	Texture mCoinTexture;

	Coin *mCoin;
	Ship *mShip;
	Asteroid *mAsteroid;

	float mAsteroidSpawnCounter;
	float mAsteroidSpawnCountModifier;

	void draw();

	void handleWindowEvents();
	void clearWindow();
	void displayWindow();

	void createCoin();
	void updateCoin(float deltaTime);
	void destroyCoin();

	void createShip();
	void updateShip(float deltaTime);

	void createAsteroid();
	void updateAsteroids(float deltaTime);

	bool overlap(Vector2f position0, float rad0, Vector2f position1, float rad1);
	bool overlap(Ship *ship, Coin *coin);
	bool overlap(Ship *ship, Asteroid *asteroid);

	void handleCoinPickup();
	void handleAsteroidCollisions();
	void handleLostCoin();
	void handleAsteroidLoss();

	int getRandomNumber(float min, float max);

};

#endif // !INCLUDE_GAME