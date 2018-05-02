#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "Projectile.h"


class Snake : Projectile
{
public:
	Snake(SDL_Renderer* renderer);
	~Snake();
	void Logic();
};

#endif