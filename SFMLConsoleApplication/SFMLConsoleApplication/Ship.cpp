#include "Ship.h"
#include <iostream>

using namespace sf;

Ship::Ship(RenderWindow& renderWindow, Texture& texture, Vector2f position, float velocity, float radius) : 
	mRenderWindow(renderWindow)
{
	mSprite.setTexture(texture);
	mSprite.setPosition(position);
	mVelocity = velocity;
	mRad = radius;
}

Ship::~Ship()
{
}

void Ship::update(float deltaTime)
{
	updatePosition(deltaTime);
	constrainPosition();
}

void Ship::draw()
{
	mRenderWindow.draw(mSprite);
}

Vector2f  Ship::getPos()
{
	return mSprite.getPosition();
}

float Ship::getRad()
{
	return mRad;
}

void Ship::updatePosition(float deltaTime)
{
	float directionX = 0.0f;
	float directionY = 0.0f;
	if (Keyboard::isKeyPressed(Keyboard::Left)) {
		directionX -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Right)) {
		directionX += 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Up)) {
		directionY -= 1.0f;
	}
	if (Keyboard::isKeyPressed(Keyboard::Down)) {
		directionY += 1.0f;
	}
	Vector2f direction(directionX, directionY);
	mSprite.move(deltaTime * mVelocity * direction);
}

void Ship::constrainPosition()
{
	Vector2f windowSize = Vector2f((float(mRenderWindow.getSize().x)), (float(mRenderWindow.getSize().y)));
	float minXY = mRad;
	float maxX = windowSize.x - minXY;
	float maxY = windowSize.y - minXY;
	float xPos = mSprite.getPosition().x;
	float yPos = mSprite.getPosition().y;

	if (xPos < minXY)
	{
		xPos = minXY;
	}
	else if (xPos > maxX)
	{
		xPos = maxX;
	}
	if (yPos < minXY)
	{
		yPos = minXY;
	}
	else if (yPos > maxY)
	{
		yPos = maxY;
	}
	Vector2f shipPos(xPos, yPos);
	mSprite.setPosition(shipPos);
}
