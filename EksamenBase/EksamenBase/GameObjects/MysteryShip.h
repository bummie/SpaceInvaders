#ifndef MYSTERYSHIP_H_INCLUDED
#define MYSTERYSHIP_H_INCLUDED

#include "GameObject.h"
class MysteryShip : public GameObject
{
private:
	bool m_canRespawn;
public:
	MysteryShip(SDL_Renderer * renderer);
	~MysteryShip();
	void Logic();
	void Input();
};

#endif