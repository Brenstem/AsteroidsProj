#ifndef ASTEROIDS_COIN_H
#define ASTEROIDS_COIN_H

#include "Object.h"

class Coin : Object
{
public:
	Coin(Game *game);
	~Coin();
	virtual void update() override;
	virtual void draw() override;
	virtual Vector2f getPos() override;
	virtual void setPos(Vector2f pos) override;
	virtual float getRad() override;

private:
	RenderWindow &mRenderWindow;

	Sprite mSprite;
	Vector2f mVelocity;
	float mRad;
};
#endif // !ASTEROIDS_COIN_H
