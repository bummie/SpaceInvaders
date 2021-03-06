#include "ObjectsPool.h"
#include "GameObjectsManager.h"
#include <iostream>



ObjectsPool::ObjectsPool()
{
}


ObjectsPool::~ObjectsPool()
{
}

std::shared_ptr<GameObject> ObjectsPool::GetEnemyAttack(SDL_Renderer* renderer, int x, int y)
{
	if (m_objectsList.size() != 0)
	{
		for (auto projectile : m_objectsList)
		{
			if (projectile->tag == "EnemyAttack")
			{
				if (projectile->getHp() <= 0)
				{
					projectile->setHp(100);
					projectile->position = {
						x, y, 8, 16
					};
					projectile->ResetAnim();
					return projectile;
				}
			}
		}
	}

	auto poolAttack = std::shared_ptr<EnemyAttack>(new EnemyAttack(renderer, x, y));
	GameObjectsManager::getInstance().Add(poolAttack);
	m_objectsList.push_back(poolAttack);
	return poolAttack;
}

std::shared_ptr<GameObject> ObjectsPool::GetSnake(SDL_Renderer* renderer, int x, int y)
{
	if (m_objectsList.size() != 0)
	{
		for (auto projectile : m_objectsList)
		{
			if (projectile->tag == "Snake")
			{
				if (projectile->getHp() <= 0)
				{
					projectile->setHp(100);
					projectile->position = {
						x, y, 8, 16
					};
					projectile->ResetAnim();
					return projectile;
				}
			}
		}
	}

	auto poolSnake = std::shared_ptr<Snake>(new Snake(renderer, x, y));
	GameObjectsManager::getInstance().Add(poolSnake);
	m_objectsList.push_back(poolSnake);
	return poolSnake;
}



