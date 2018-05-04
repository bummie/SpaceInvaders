#ifndef LASER_H_INCLUDED
#define LASER_H_INCLUDED

#include "Projectile.h"

class Laser : public Projectile
{
public:
	Laser(SDL_Renderer* renderer, int x, int y);
	~Laser();
	void Logic();
private:
	const std::string m_imgPathLaser = "Resources/Images/Projectiles/Projectile_beam.bmp";
	
};

#endif