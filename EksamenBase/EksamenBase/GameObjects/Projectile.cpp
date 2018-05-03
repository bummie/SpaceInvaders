#include "Projectile.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"


Projectile::Projectile(SDL_Renderer* renderer) : GameObject(renderer)
{
	tag = "Projectile";
	position = {
		400, 400
	};
	position.h = 16;
	position.w = 8;
}


Projectile::~Projectile()
{
}

void Projectile::Logic()
{
	GameObject::Logic();
	m_velocity.y = M_MAX_SPEED * direction.y;

}

