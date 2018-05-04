#include "Barricade.h"
#include "../Handlers/GameObjectsManager.h"
#include "SDL.h"

Barricade::Barricade(SDL_Renderer* renderer,  int x, int y)
{
	for(int i = 0; i < 6; i++)
	{
		int blockX = (i * 16) + x;
		int blockY = y;
		m_barricadeBlocks[i] = std::shared_ptr<BarricadeBlock>(new BarricadeBlock(renderer, blockX, blockY ));
		GameObjectsManager::getInstance().Add(m_barricadeBlocks[i]);
	}
}

Barricade::~Barricade()
{
}
