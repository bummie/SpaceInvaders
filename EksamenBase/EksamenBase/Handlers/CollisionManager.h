#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

#include "../GameObjects\GameObject.h"
#include <vector>

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
	std::vector<GameObject*>* OnCollision(GameObject* gameObject);
};

#endif