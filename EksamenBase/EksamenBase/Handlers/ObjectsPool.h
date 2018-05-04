#ifndef OBJECTSPOOL_H_INCLUDED
#define OBJECTSPOOL_H_INCLUDED

#include "../GameObjects\GameObject.h"
#include "../GameObjects/Laser.h"
#include "../GameObjects/EnemyAttack.h"
#include "../GameObjects/Snake.h"
#include <vector>
#include <memory>

class ObjectsPool
{

	

public:

	static ObjectsPool& getInstance()
	{
		static ObjectsPool instance;
		return instance;
	}
	~ObjectsPool();
	std::shared_ptr<GameObject> GetEnemyAttack(SDL_Renderer* renderer, int x, int y);
	std::shared_ptr<GameObject> GetSnake(SDL_Renderer* renderer, int x, int y);
private:
	ObjectsPool();
	std::vector<std::shared_ptr<GameObject>> m_objectsList;

};

#endif