#ifndef ASTEROIDS_OBJECT_H
#define ASTEROIDS_OBJECT_H
#include "SFML/Graphics.hpp"
class Game;

using namespace sf;

class Object
{
public:
	Object(Game *game);
	virtual ~Object() = 0;
	virtual void update() = 0;
	virtual void draw() = 0;
	virtual Vector2f getPos() = 0;
	virtual void setPos(Vector2f pos) = 0;
	virtual float getRad() = 0;

protected:
	RenderWindow &mRenderWindow;
	Game* mGame;
};

#endif // !1

