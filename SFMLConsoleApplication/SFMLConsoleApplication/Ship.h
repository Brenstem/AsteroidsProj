#ifndef ASTEROIDS_SHIP_H
#define ASTEROIDS_SHIP_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Ship
{
public:
	Ship(RenderWindow& renderWindow, Texture& texture, Vector2f position, float velocity, float radius);
	~Ship();

	void update(float deltaTime);
	void draw();	

	Vector2f getPos();
	float getRad();

protected:
	RenderWindow &mRenderWindow;
	Sprite mSprite;
	float mVelocity;
	float mRad;

	void updatePosition(float deltaTime);
	void constrainPosition();
};

#endif // !ASTEROIDS_SHIP_H

