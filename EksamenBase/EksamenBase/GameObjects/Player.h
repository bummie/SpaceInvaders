#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include "GameObject.h"
#include <memory>

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
	std::shared_ptr<GameObject> m_laser;
	const int M_XOFFSET = 21;
	const int M_YOFFSET = -12;

};

#endif