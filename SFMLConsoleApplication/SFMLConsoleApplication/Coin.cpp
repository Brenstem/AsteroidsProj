#include "Coin.h"

using namespace sf;

Coin::Coin(RenderWindow& renderWindow, Texture& texture, Vector2f position, float velocity, float radius) :
	mRenderWindow(renderWindow)
{
	mSprite.setTexture(texture);
	mSprite.setPosition(position);
	mVelocity = velocity;
	mRad = radius;
}

Coin::~Coin()
{
}

void Coin::update(float deltaTime)
{
	Vector2f direction(0, 1);
	mSprite.move(deltaTime * mVelocity * direction);
}

void Coin::draw()
{
	mRenderWindow.draw(mSprite);
}

Vector2f Coin::getPos()
{
	return mSprite.getPosition();
}

float Coin::getRad()
{
	return mRad;
}

