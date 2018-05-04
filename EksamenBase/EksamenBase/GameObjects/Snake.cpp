#include "Snake.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"

Snake::Snake(SDL_Renderer * renderer, int x, int y) : Projectile(renderer, x, y)
{
	Projectile::Projectile(renderer, x, y);
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Projectiles/Projectile_snake_down.bmp");
	m_secondaryTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Projectiles/Projectile_snake_up.bmp");
	direction = { 0 , 1 };
	position.h = 16;
	position.w = 8;
	m_renderer = renderer;
	tag = "Snake";
}

Snake::~Snake()
{
}

void Snake::Logic()
{
	Projectile::Logic();
	
}

