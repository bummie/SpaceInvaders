#ifndef BARRICADE_H_INCLUDED
#define BARRICADE_H_INCLUDED

#include "BarricadeBlock.h"
#include <memory>

class Barricade
{
private:
	std::shared_ptr<BarricadeBlock> m_barricadeBlocks[6];
public:
	Barricade(SDL_Renderer * renderer, int x, int y);
	~Barricade();
};

#endif