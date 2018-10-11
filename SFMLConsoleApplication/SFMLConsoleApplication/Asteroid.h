#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Asteroid
{
public:
	Asteroid(RenderWindow &renderWindow, Texture &texture, Vector2f position, float velocity, float radius);
	~Asteroid();
	void update(float deltaTime);
	void draw();

private:
	RenderWindow &mRenderWindow;
	Sprite mSprite;
	float mVelocity;
	float mRad;
};

#endif // !ASTEROIDS_ASTEROID_H
