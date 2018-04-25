#include "Enemy.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"

#include <iostream>

Enemy::Enemy(SDL_Renderer * renderer) : GameObject(renderer)
{
	texture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/enemy.bmp");
	tag = "Enemy";
}

Enemy::~Enemy()
{

}

void Enemy::Logic()
{
	GameObject::Logic();

	// Do more logic

}

void Enemy::Input()
{
	
}