#include "EnemyAttack.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"


EnemyAttack::EnemyAttack(SDL_Renderer* renderer, int x, int y) : Projectile(renderer, x, y)
{	
	Projectile::Projectile(renderer, x , y);
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, imgPathCrossDown);
	m_secondaryTexture = TextureManager::getInstance().GetTexture(renderer, imgPathCrossUp);
	position.h = 16;
	position.w = 8;
	direction = { 0, 1 };

}


EnemyAttack::~EnemyAttack()
{
}

void EnemyAttack::Logic()
{
	Projectile::Logic();
}
