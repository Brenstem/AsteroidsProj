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

private:
	RenderWindow mRenderWindow;
	bool mGameOver;

	void handleWindowEvents();
	void clearWindow();
	void displayWindow();
};

#endif // !INCLUDE_GAME