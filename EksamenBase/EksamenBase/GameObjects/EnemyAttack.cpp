#include "EnemyAttack.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"


EnemyAttack::EnemyAttack(SDL_Renderer* renderer) : Projectile(renderer)
{	
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, imgPathCrossDown);
	direction = { 0 , 1 };


}


EnemyAttack::~EnemyAttack()
{
}

void EnemyAttack::Logic()
{

}
