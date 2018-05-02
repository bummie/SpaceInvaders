#include "Snake.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"


Snake::Snake(SDL_Renderer * renderer) : Projectile(renderer)
{
	Projectile::Projectile(renderer);
	m_texture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/snake.bmp");
}

Snake::~Snake()
{
}

void Snake::Logic()
{
	Projectile::Logic();
}
