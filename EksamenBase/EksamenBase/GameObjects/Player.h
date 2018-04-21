#ifndef Player_H_INCLUDED
#define Player_H_INCLUDED

#include "GameObject.h"

class Player : public GameObject
{
public:
	Player(SDL_Renderer* renderer) : GameObject(renderer) {};
	~Player();
	void Logic();
	void Input();
};

#endif