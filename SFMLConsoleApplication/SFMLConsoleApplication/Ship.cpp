#include "Ship.h"

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
}
