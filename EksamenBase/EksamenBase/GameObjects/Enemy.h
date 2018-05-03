#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "GameObject.h"

class Enemy : public GameObject
{
public:
	Enemy(SDL_Renderer* renderer);
	~Enemy();
	void Logic();
	void Input();
};

#endif