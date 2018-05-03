#include "Laser.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"

Laser::Laser(SDL_Renderer* renderer, int x, int y) : Projectile(renderer, x, y)
{
	Projectile::Projectile(renderer, x, y);
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, imgPathLaser);
	direction = { 0, -1 };

}


Laser::~Laser()
{
}

void Laser::Logic()
{
	Projectile::Logic();
}

