#include "Projectile.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"


Projectile::Projectile(SDL_Renderer* renderer) : GameObject(renderer)
{
	m_texture = TextureManager::getInstance().GetTexture(renderer, imgPath);
	tag = "Projectile";
}


Projectile::~Projectile()
{
}

void Projectile::Logic()
{
	GameObject::Logic();
}
