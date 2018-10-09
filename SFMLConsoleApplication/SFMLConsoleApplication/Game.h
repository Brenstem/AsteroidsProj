#ifndef ASTEROIDS_GAME_H
#define ASTEROIDS_GAME_H

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
class Object;

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

	typedef std::vector<Object> ObjVector;
	ObjVector objVector;

	void handleWindowEvents();
	void clearWindow();
	void displayWindow();

	void createCoin();
};

#endif // !INCLUDE_GAME