#include "CollisionManager.h"
#include "GameObjectsManager.h"


CollisionManager::~CollisionManager()
{
}

std::vector<GameObject*>* CollisionManager::OnCollision(GameObject * gameObject)
{
	std::vector<GameObject*>* foundCollision = new std::vector<GameObject*>();
	for (auto go : GameObjectsManager::getInstance().gameObjectsList)
	{
		if (gameObject == go) { continue; }

		// TODO: Handle multiply collisions
		if (SDL_HasIntersection(&go->position, &gameObject->position))
		{
			foundCollision->push_back(go);
			//return go;
		}
	}

	if(foundCollision->size() > 0)
	{
		return foundCollision;
	}else
	{
		delete(foundCollision);
		return nullptr;
	}

	
}