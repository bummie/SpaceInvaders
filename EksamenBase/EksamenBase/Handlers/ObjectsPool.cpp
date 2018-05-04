#include "ObjectsPool.h"
#include "GameObjectsManager.h"
#include <iostream>



ObjectsPool::ObjectsPool()
{
}


ObjectsPool::~ObjectsPool()
{
}

std::shared_ptr<GameObject> ObjectsPool::GetLaser(SDL_Renderer* renderer, int x, int y)
{
	if (m_objectsList.size() != 0)
	{
		for (auto projectile : m_objectsList)
		{
			if (projectile->tag == "Laser")
			{
				if (projectile->getHp() <= 0)
				{
					projectile->setHp(100);
					projectile->position = {
						x, y
					};
					return projectile;
				}
			}
		}
	} 
	auto poolLaser = std::shared_ptr<Laser>(new Laser(renderer, x, y));
	GameObjectsManager::getInstance().Add(poolLaser);
	m_objectsList.push_back(poolLaser);
	return poolLaser;
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
						x, y
					};
					std::cout << "Enemy Attack funnet... Returnerer!" << std::endl;
					return projectile;
				}
			}
		}
	}

	auto poolAttack = std::shared_ptr<EnemyAttack>(new EnemyAttack(renderer, x, y));
	GameObjectsManager::getInstance().Add(poolAttack);
	m_objectsList.push_back(poolAttack);
	std::cout << "Enemy Attack ikke funnet... Lager ny!" << std::endl;
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
						x, y
					};
					std::cout << "Snake funnet... Returnerer!" << std::endl;
					std::cout << "Hp: " << projectile->getHp() << std::endl; 
					std::cout << "Position x: " << projectile->position.x << std::endl << " Position y: " << projectile->position.y << std::endl;
					return projectile;
				}
			}
		}
	}

	auto poolSnake = std::shared_ptr<Snake>(new Snake(renderer, x, y));
	GameObjectsManager::getInstance().Add(poolSnake);
	m_objectsList.push_back(poolSnake);
	std::cout << "Snake ikke funnet... Lager ny!" << std::endl;
	return poolSnake;
}



