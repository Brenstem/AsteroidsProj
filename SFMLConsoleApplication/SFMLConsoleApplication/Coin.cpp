#include "Coin.h"

//Constructor/Destructor
Coin::Coin(RenderWindow& renderWindow, Texture& texture, Vector2f position, float velocity, float radius) :
	mRenderWindow(renderWindow)
{
	mSprite.setTexture(texture);
	mSprite.setPosition(position);
	mVelocity = velocity;
	mRad = radius;
	mSprite.setOrigin(radius, radius);
}

Coin::~Coin()
{
}

//Handling coin object
void Coin::update(float deltaTime)
{
	Vector2f direction(0, 1);
	mSprite.move(deltaTime * mVelocity * direction);
}

void Coin::draw()
{
	mRenderWindow.draw(mSprite);
}

//Getters/Setters
Vector2f Coin::getPos()
{
	return mSprite.getPosition();
}

float Coin::getRad()
{
	return mRad;
}

