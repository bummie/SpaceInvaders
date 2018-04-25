#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(SDL_Renderer* renderer);
	~Player();
	void Logic();
	void Input();
};

#endif