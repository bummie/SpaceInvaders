#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "Projectile.h"


class Snake : public Projectile
{
public:
	Snake(SDL_Renderer* renderer);
	~Snake();
	void Logic();
private:
	const std::string imgPathSnakeDown = "Resources/Images/Projectiles/Projectile_snake_down.bmp";
	const std::string imgPathSnakeUp = "Resources/Images/Projectiles/Projectile_snake_up.bmp";
};

#endif