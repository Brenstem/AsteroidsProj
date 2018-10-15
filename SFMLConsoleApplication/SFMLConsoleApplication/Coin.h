#ifndef ASTEROIDS_COIN_H
#define ASTEROIDS_COIN_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Coin
{
public:
	//Constructor/destructor
	Coin(RenderWindow &renderWindow, Texture &texture, Vector2f position, float velocity, float radius);
	~Coin();

	//Handling coin object
	void update(float deltaTime);
	void draw();

	//Getters/Setters
	Vector2f getPos();
	float getRad();

private:
	//Membervariables for Coin
	RenderWindow &mRenderWindow;
	Sprite mSprite;
	float mVelocity;
	float mRad;
};
#endif // !ASTEROIDS_COIN_H
