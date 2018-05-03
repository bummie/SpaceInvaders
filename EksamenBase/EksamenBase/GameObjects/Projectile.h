#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED

#include "GameObject.h"

class Projectile : public GameObject
{
protected:
	GameObject * owner;
	Vector2D direction;
	void CheckPosition();
public:
	Projectile(SDL_Renderer* renderer, int x, int y);
	~Projectile();
	void Logic();
	
};


#endif
