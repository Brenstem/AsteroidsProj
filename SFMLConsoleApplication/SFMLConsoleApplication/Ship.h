#ifndef ASTEROIDS_SHIP_H
#define ASTEROIDS_SHIP_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Ship
{
public:
	//Constructor/Destructor
	Ship(RenderWindow& renderWindow, Texture& texture, Vector2f position, float velocity, float radius);
	~Ship();

	//Handling ship object
	void update(float deltaTime);
	void draw();	

	//Getters/Setters
	Vector2f getPos();
	float getRad();

protected:
	//Memeber variables for ship
	RenderWindow &mRenderWindow;
	Sprite mSprite;
	float mVelocity;
	float mRad;

	//Handles ship movement
	void updatePosition(float deltaTime);
	void constrainPosition();
};

#endif // !ASTEROIDS_SHIP_H

