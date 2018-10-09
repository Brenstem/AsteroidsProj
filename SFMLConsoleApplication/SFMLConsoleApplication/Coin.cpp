#include "Coin.h"

Coin::Coin(Game * game, RenderWindow & renderWindow, Texture texture, Vector2f position, Vector2f velocity, float radius) :
	mRenderWindow(mRenderWindow)
	, mGame(game)
{
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
