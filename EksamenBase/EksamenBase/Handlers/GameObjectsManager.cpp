#include "GameObjectsManager.h"
#include <algorithm>

GameObjectsManager::~GameObjectsManager()
{
	for(auto gameObject : gameObjectsList)
	{
		delete(gameObject);
		gameObject = nullptr;
	}
}

/// <summary>
/// Adds the given gameobject to the list
/// </summary>
/// <param name="gameObject"></param>
void GameObjectsManager::Add(GameObject* gameObject)
{
	for (auto listGameObject : gameObjectsList)
	{
		if(listGameObject == gameObject)
		{
			return;
		}
	}
	gameObject->id = gameObjectCounter++;
	gameObjectsList.push_back(gameObject);
}

/// <summary>
/// Removes the given gameobject
/// </summary>
/// <param name="gameObject"></param>
void GameObjectsManager::Remove(GameObject* gameObject)
{
	auto position = std::find(gameObjectsList.begin(), gameObjectsList.end(), gameObject);
	if (position != gameObjectsList.end())
	{
		delete(&(*position));
		gameObjectsList.erase(position);
	}
	
}

/// <summary>
/// Retuns an array of gameobject with given tag
/// TODO:: Test it out, not sure if it works yo
/// </summary>
/// <param name="tag"></param>
/// <returns></returns>
GameObject** GameObjectsManager::Find(std::string tag)
{
	std::vector<GameObject*> foundGameObjects;

	for (auto listGameObject : gameObjectsList)
	{
		if (listGameObject->tag.compare(tag))
		{
			foundGameObjects.push_back(listGameObject);
		}
	}

	if(foundGameObjects.size() <= 0)
	{
		return nullptr;
	}

	return foundGameObjects.data();
}

/// <summary>
/// Draws all of the gameobject
/// </summary>
void GameObjectsManager::Draw()
{
	for (auto gameObject : gameObjectsList)
	{
		gameObject->Draw();
	}
}

/// <summary>
/// Handles the input for all the gameobjects
/// </summary>
void GameObjectsManager::Input()
{
	for (auto gameObject : gameObjectsList)
	{
		gameObject->Input();
	}
}

/// <summary>
/// Handles all the logic
/// </summary>
void GameObjectsManager::Logic()
{
	for (auto gameObject : gameObjectsList)
	{
		gameObject->Logic();
	}
}