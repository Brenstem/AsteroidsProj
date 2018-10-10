#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include "Coin.h"
#include "Ship.h"

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

	Ship *mShip;
	Texture mShipTexture;
	Coin *mCoin;
	Texture mCoinTexture;

	void handleWindowEvents();
	void clearWindow();
	void displayWindow();

	void createCoin();
	void drawCoin();

	void createShip();
	void drawShip();
	void updateShip(float deltaTime);

	Vector2f getRandomPos();
};

#endif // !INCLUDE_GAME