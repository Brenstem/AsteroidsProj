#include "Asteroid.h"

// Constructor/Destructor
Asteroid::Asteroid(RenderWindow & renderWindow, Texture & texture, Vector2f position, float velocity, float radius) :
	mRenderWindow(renderWindow)
{
	mSprite.setTexture(texture);
	mSprite.setPosition(position);
	mVelocity = velocity;
	mRad = radius;
	mSprite.setOrigin(radius, radius);
}

Asteroid::~Asteroid()
{
}

// Handles gameobject
void Asteroid::update(float deltaTime)
{
	Vector2f dir(0, 1);
	mSprite.move(deltaTime * mVelocity * dir);
}

void Asteroid::draw()
{
	mRenderWindow.draw(mSprite);
}

// Getters/Setters
Vector2f Asteroid::getPos()
{
	return mSprite.getPosition();
}

float Asteroid::getRad()
{
	return mRad;
}
