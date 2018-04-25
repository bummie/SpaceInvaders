#include "CollisionManager.h"
#include "GameObjectsManager.h"


CollisionManager::~CollisionManager()
{
}

/// <summary>
/// Returns a nullptr if no collision
/// Else returns the gameobject the given gameobject
/// is colliding with
/// </summary>
/// <param name="gameObject"></param>
/// <returns></returns>
GameObject* CollisionManager::IsColliding(GameObject * gameObject)
{
	for(auto go : GameObjectsManager::getInstance().gameObjectsList)
	{
		if (gameObject == go) { continue; }

		// TODO: Handle multiply collisions
		if (SDL_HasIntersection(&go->position, &gameObject->position))
		{
			return go;
		}	
	}

	return nullptr;
}
