#include "Enemy.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/GameObjectsManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"

#include "Snake.h"
#include "EnemyAttack.h"
#include "../Handlers/ObjectsPool.h"

#include <iostream>
#include <memory>
#include <stdlib.h>  

Enemy::Enemy(SDL_Renderer * renderer, int x, int y, ENEMY_TYPE type) : GameObject(renderer)
{
	switch (type)
	{
	case Enemy::SQUID:
			m_defTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_squid_down.bmp");
			m_secondaryTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_squid_up.bmp");
		break;
	case Enemy::GHOST:
			m_defTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_ghost_down.bmp");
			m_secondaryTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_ghost_up.bmp");
		break;
	case Enemy::ALIEN:
			m_defTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_alien_down.bmp");
			m_secondaryTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_alien_up.bmp");
		break;
	default:
		m_defTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_squid_down.bmp");
		m_secondaryTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_squid_up.bmp");
		break;
	}

	m_deathTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Explode/Explode_enemy.bmp");
	tag = "Enemy";
	m_type = type;

	position.x = x;
	position.y = y;
	position.h = 28;
	position.w = 28;
}

Enemy::~Enemy()
{

}

void Enemy::Logic()
{
	GameObject::Logic();
	if (getHp() <= 0) { return; }

	if ((rand() % 7000/GameHandler::level) == 1)
	{
		if ((rand() % 10) > 5)
		{
			ObjectsPool::getInstance().GetSnake(m_renderer, position.x, position.y);
		}else
		{
			ObjectsPool::getInstance().GetEnemyAttack(m_renderer, position.x, position.y);
		}
	}

	std::vector<std::shared_ptr<GameObject>>* collision = CollisionManager::getInstance().OnCollision(this);

	if (collision != nullptr)
	{
		for (auto go : *collision)
		{
			if (go->tag == "BarricadeBlock")
			{
				go->setHp(0);
				SoundManager::getInstance().PlaySound("Explosion");
				return;
			}
		}
	}
	delete(collision);
}

