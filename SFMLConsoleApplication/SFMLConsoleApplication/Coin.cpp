#include "Coin.h"

using namespace sf;

Coin::Coin(RenderWindow& renderWindow, Texture& texture, Vector2f position, float velocity, float radius) :
	mRenderWindow(renderWindow)
{
	mSprite.setTexture(texture);
	setPos(position);
}

Coin::~Coin()
{
}

void Coin::update(float deltaTime)
{
	mSprite.move(deltaTime * mVelocity);
}

void Coin::draw()
{
	mRenderWindow.draw(mSprite);
}

Vector2f Coin::getPos()
{
	return mSprite.getPosition();
}

void Coin::setPos(Vector2f pos)
{
	mSprite.setPosition(pos);
}

float Coin::getRad()
{
	return 0.0f;
}