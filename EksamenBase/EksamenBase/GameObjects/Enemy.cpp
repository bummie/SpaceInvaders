#include "Enemy.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"

#include <iostream>
#include <stdlib.h>  

Enemy::Enemy(SDL_Renderer * renderer) : GameObject(renderer)
{
	m_texture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_spaceship.bmp");
	tag = "Enemy";
}

Enemy::~Enemy()
{

}

void Enemy::Logic()
{
	GameObject::Logic();

	// Do more logic
	position.x = std::cos(degree) * 100 + 300;
	position.y = std::sin(degree) * 100 + 300;

	degree++;
	if (degree >= 360) { degree = 0; }

}

void Enemy::Input()
{
	
}