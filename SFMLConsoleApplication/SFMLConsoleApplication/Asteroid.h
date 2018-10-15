#ifndef ASTEROIDS_ASTEROID_H
#define ASTEROIDS_ASTEROID_H

#include "SFML/Graphics.hpp"

using namespace sf;

class Asteroid
{
public:
	//Constructor/Destructor
	Asteroid(RenderWindow &renderWindow, Texture &texture, Vector2f position, float velocity, float radius);
	~Asteroid();

	//Handles Asteroid object
	void update(float deltaTime);
	void draw();

	//Getters/Setters
	Vector2f getPos();
	float getRad();

private:
	//Member variables
	RenderWindow &mRenderWindow;
	Sprite mSprite;
	float mVelocity;
	float mRad;
};

#endif // !ASTEROIDS_ASTEROID_H
