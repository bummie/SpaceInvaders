#ifndef COLLISIONMANAGER_H_INCLUDED
#define COLLISIONMANAGER_H_INCLUDED

#include "../GameObjects\GameObject.h"

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
	GameObject* IsColliding(GameObject* gameObject);
};

#endif