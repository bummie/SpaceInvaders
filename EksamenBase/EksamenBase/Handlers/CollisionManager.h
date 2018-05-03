#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

#include "../GameObjects\GameObject.h"
#include <vector>
#include <memory>

class CollisionManager
{
public:
	static CollisionManager& getInstance()
	{
		static CollisionManager instance;
		return instance;
	}

private:
	CollisionManager() {}
	CollisionManager(CollisionManager const&);
	void operator=(CollisionManager const&);

public:
	~CollisionManager();
	std::vector<std::shared_ptr<GameObject>>* OnCollision(GameObject * gameObject);
};

#endif