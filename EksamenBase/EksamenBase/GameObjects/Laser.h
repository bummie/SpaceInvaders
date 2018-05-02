#ifndef LASER_H_INCLUDED
#define LASER_H_INCLUDED

#include "Projectile.h"

class Laser : public Projectile
{
public:
	Laser(SDL_Renderer* renderer);
	~Laser();
	void Logic();
};

#endif