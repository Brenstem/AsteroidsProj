#ifndef ASTEROIDS_COIN_H
#define ASTEROIDS_COIN_H

#include "Object.h"

class Coin : Object
{
public:
	Coin(Game *game, RenderWindow &renderWindow, Texture texture, Vector2f position, Vector2f velocity, float radius);
	~Coin();
	void update(float deltaTIme) override;
	virtual void draw() override;
	virtual Vector2f getPos() override;
	virtual void setPos(Vector2f pos) override;
	virtual float getRad() override;

private:
	RenderWindow &mRenderWindow;
	Game* mGame;
	Sprite mSprite;
	Vector2f mVelocity;
	float mRad;
};
#endif // !ASTEROIDS_COIN_H
