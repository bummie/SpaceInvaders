#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(SDL_Renderer * renderer, int x, int y);
	~Player();
	void Logic();
	void Input();
	void Replenish();
private:
	bool m_replenished = true;
	void Shoot();
	GameObject* currentLaser;
};

#endif