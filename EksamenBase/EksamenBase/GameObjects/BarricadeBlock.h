#ifndef BARRICADEBLOCK_H_INCLUDED
#define BARRICADEBLOCK_H_INCLUDED

#include "GameObject.h"

class BarricadeBlock : public GameObject
{
private:
	int m_oldHp;
public:
	BarricadeBlock(SDL_Renderer * renderer, int x, int y);
	~BarricadeBlock();
	void Logic();
	void Input();
};

#endif