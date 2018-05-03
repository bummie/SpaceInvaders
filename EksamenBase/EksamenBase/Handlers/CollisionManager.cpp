#include "CollisionManager.h"
#include "GameObjectsManager.h"


CollisionManager::~CollisionManager()
{
}

/// <summary>
/// When there happens a collision with given object
/// This method will return a vector with the objects 
/// being collided with.
/// </summary>
/// <param name="gameObject"></param>
/// <returns></returns>
std::vector<GameObject*>* CollisionManager::OnCollision(GameObject * gameObject)
{
	std::vector<GameObject*>* foundCollision = new std::vector<GameObject*>();
	for (auto go : GameObjectsManager::getInstance().gameObjectsList)
	{
		if (gameObject == go) { continue; }

		if (SDL_HasIntersection(&go->position, &gameObject->position) && go->getHp() > 0)
		{
			foundCollision->push_back(go);
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