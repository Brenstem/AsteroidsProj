#ifndef ASTEROIDS_COIN_H
#define ASTEROIDS_COIN_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Coin
{
public:
	Coin(RenderWindow &renderWindow, Texture &texture, Vector2f position, float velocity, float radius);
	~Coin();

	void update(float deltaTime);
	void draw();

	Vector2f getPos();
	float getRad();

private:
	RenderWindow &mRenderWindow;
	Sprite mSprite;
	float mVelocity;
	float mRad;
};
#endif // !ASTEROIDS_COIN_H
