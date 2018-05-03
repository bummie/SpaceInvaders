#include "Laser.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"

Laser::Laser(SDL_Renderer* renderer) : Projectile(renderer)
{
	Projectile::Projectile(renderer);
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, imgPathLaser);
}


Laser::~Laser()
{
}

void Laser::Logic()
{
	Projectile::Logic();
}
