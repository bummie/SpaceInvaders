#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include "GameObject.h"

class Enemy : public GameObject
{
public:
	enum ENEMY_TYPE { SQUID, GHOST, ALIEN };

	Enemy(SDL_Renderer * renderer, int x, int y, ENEMY_TYPE type);
	~Enemy();
	void Logic();
	void Input();
private:
	ENEMY_TYPE m_type;
};

#endif