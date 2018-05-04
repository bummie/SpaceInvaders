#include "Laser.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"
#include "../Handlers/GameObjectsManager.h"


Laser::Laser(SDL_Renderer* renderer, int x, int y) : Projectile(renderer, x, y)
{
	Projectile::Projectile(renderer, x, y);
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, m_imgPathLaser);
	direction = { 0, -1 };
	position.h = 16;
	position.w = 8;
	m_maxSpeed = .5f;
	m_hp = 0;
	tag = "Laser";
}

Laser::~Laser()
{
}

void Laser::Logic()
{
	if (getHp() <= 0) { return; }

	Projectile::Logic();
}

