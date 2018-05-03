#include "Projectile.h"
#include "../Handlers/GameHandler.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"


void Projectile::CheckPosition()
{
	if (position.y > GameHandler::SCREEN_HEIGHT || position.y < 0)
	{
		setHp(0);
	}
}

Projectile::Projectile(SDL_Renderer* renderer, int x, int y) : GameObject(renderer)
{
	tag = "Projectile";
	m_maxSpeed = .3f;
	position = {
		x, y
	};
	
}


Projectile::~Projectile()
{
}

void Projectile::Logic()
{
	GameObject::Logic();
	CheckPosition();
	m_acceleration.y = (m_maxSpeed * direction.y);

}

