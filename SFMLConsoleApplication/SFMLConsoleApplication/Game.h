#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

#include "Coin.h"
#include "Ship.h"
#include "Asteroid.h"

class Game
{
public:
	//Constructor/destructor
	Game();
	~Game();

	//Public functions for Game
	void run();

private:
	//Membervariables for Game
	RenderWindow mRenderWindow;
	bool mGameOver;
	int mLevel;
	static std::mt19937 mGenerator;

	//Gameobject textures
	Texture mShipTexture;
	Texture mAsteroidTexture;
	Texture mCoinTexture;

	//Gameobjects
	Coin *mCoin;
	Ship *mShip;
	Asteroid *mAsteroid;
	typedef std::vector<Asteroid*> AsteroidVector;
	AsteroidVector astVector;

	//Asteroid spawn counters
	float mAsteroidSpawnCounter;
	float mAsteroidSpawnCountModifier;

	//Random number generator
	int getRandomNumber(int min, int max);

	//Drawing and updating all game objects
	void draw();
	void update(float deltaTime);

	//Handling the Renderwindow
	void handleWindowEvents();
	void clearWindow();
	void displayWindow();

	//Instantiating gameobjects and setting pointers
	void createCoin();
	void createShip();
	void createAsteroid();

	//Handles collision between all gameobjects
	bool overlap(Vector2f position0, float rad0, Vector2f position1, float rad1);
	bool overlap(Ship *ship, Coin *coin);
	bool overlap(Ship *ship, Asteroid *asteroid);

	//Handles objects interactions
	void handleCoinPickup();
	void handleAsteroidCollisions();
	void handleLostCoin();
	void handleAsteroidLoss();
};

#endif // !INCLUDE_GAME