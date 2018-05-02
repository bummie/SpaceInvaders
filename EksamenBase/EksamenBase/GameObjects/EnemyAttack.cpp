#include "EnemyAttack.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"


EnemyAttack::EnemyAttack(SDL_Renderer* renderer) : Projectile(renderer)
{	
	Projectile::Projectile(renderer);
	m_texture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/enemy_attack.bmp");

}


EnemyAttack::~EnemyAttack()
{
}

void EnemyAttack::Logic()
{

}
