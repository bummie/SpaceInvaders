#include "Enemy.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"

#include <iostream>
#include <stdlib.h>  

Enemy::Enemy(SDL_Renderer * renderer) : GameObject(renderer)
{
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_squid_down.bmp");
	m_secondaryTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_squid_up.bmp");
	tag = "Enemy";
	position.x = rand() % 300;
	position.y = rand() % 300;
	position.h = 28;
	position.w = 28;
}

Enemy::~Enemy()
{

}

void Enemy::Logic()
{
	GameObject::Logic();

}

void Enemy::Input()
{
	
}