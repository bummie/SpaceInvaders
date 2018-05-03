#include "EnemyAttack.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"


EnemyAttack::EnemyAttack(SDL_Renderer* renderer) : Projectile(renderer)
{	
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, imgPathCrossDown);
	m_secondaryTexture = TextureManager::getInstance().GetTexture(renderer, imgPathCrossUp);
	direction = { 0 , 1 };
	position = {
		300, 300
	};
	position.h = 16;
	position.w = 8;


}


EnemyAttack::~EnemyAttack()
{
}

void EnemyAttack::Logic()
{

}
