#include "GameObjectsManager.h"


GameObjectsManager::~GameObjectsManager()
{
	for(auto gameObject : gameObjectsList)
	{
		delete(gameObject);
		gameObject = nullptr;
	}
}


