#include "Coin.h"

Coin::Coin(Game *game) :
	mRenderWindow(mRenderWindow),
	mGame(game)
{
}

void Coin::update()
{
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
