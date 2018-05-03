#include "Snake.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"


Snake::Snake(SDL_Renderer * renderer) : Projectile(renderer)
{
	Projectile::Projectile(renderer);
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, imgPathSnakeDown);
	m_secondaryTexture = TextureManager::getInstance().GetTexture(renderer, imgPathSnakeUp);
	direction = { 0 , 1 };
	position = {
		400, 400
	};
	position.h = 24;
	position.w = 12;
}

Snake::~Snake()
{
}

void Snake::Logic()
{
	Projectile::Logic();
	
}

