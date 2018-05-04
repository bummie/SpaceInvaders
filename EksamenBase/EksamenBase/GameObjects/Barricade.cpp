#include "Barricade.h"
#include "../Handlers/GameObjectsManager.h"
#include "SDL.h"

Barricade::Barricade(SDL_Renderer* renderer,  int x, int y)
{
	for(int i = 0; i < 6; i++)
	{
		int blockX = (i * 16) + x;
		int blockY = y;

		if(i == 4 || i == 5)
		{
			blockY = y + 16;
			
			if(i == 4)
			{
				blockX = x;
			}
			else
			{
				blockX = (3 * 16) + x;
			}
		}

		m_barricadeBlocks[i] = std::shared_ptr<BarricadeBlock>(new BarricadeBlock(renderer, blockX, blockY ));
		GameObjectsManager::getInstance().Add(m_barricadeBlocks[i]);
	}
}

Barricade::~Barricade()
{
}

/// <summary>
/// Resets the barricadeblocks
/// </summary>
void Barricade::ResetBarricadeBlocks()
{
	for (auto block : m_barricadeBlocks) 
	{
		block->setHp(100);
	}
}
