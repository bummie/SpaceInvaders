#include "GameObjectsManager.h"
#include <algorithm>
#include <iostream>

GameObjectsManager::~GameObjectsManager()
{
	for(auto gameObject : gameObjectsList)
	{
		//delete(gameObject);
		//gameObject = nullptr;
	}
}

/// <summary>
/// Adds the given gameobject to the list
/// </summary>
/// <param name="gameObject"></param>
void GameObjectsManager::Add(std::shared_ptr<GameObject> gameObject)
{
	for (auto listGameObject : gameObjectsList)
	{
		if(listGameObject == gameObject)
		{
			return;
		}
	}
	gameObject->id = m_gameObjectCounter++;
	gameObjectsList.push_back(std::move(gameObject));
	//std::cout << gameObjectsList.size() << "/" << gameObjectsList.capacity() << std::endl;
}

/// <summary>
/// Removes the given gameobject
/// </summary>
/// <param name="gameObject"></param>
void GameObjectsManager::Remove(std::shared_ptr<GameObject> gameObject)
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
std::vector<std::shared_ptr<GameObject>>* GameObjectsManager::Find(std::string tag)
{
	std::vector<std::shared_ptr<GameObject>>* foundGameObjects = new std::vector<std::shared_ptr<GameObject>>();
	for (auto listGameObject : GameObjectsManager::getInstance().gameObjectsList)
	{
		if (!listGameObject->tag.compare(tag))
		{
			foundGameObjects->push_back(listGameObject);
		}
	}

	if (foundGameObjects->size() > 0)
	{
		return foundGameObjects;
	}
	else
	{
		delete(foundGameObjects);
		return nullptr;
	}
}

/// <summary>
/// Draws all of the gameobject
/// </summary>
void GameObjectsManager::Draw()
{
	std::vector<std::shared_ptr<GameObject>> copyGameObjectsList;
	copyGameObjectsList.assign(gameObjectsList.begin(), gameObjectsList.end());

	for (auto gameObject : copyGameObjectsList)
	{
		gameObject->Draw();
	}
}

/// <summary>
/// Handles the input for all the gameobjects
/// </summary>
void GameObjectsManager::Input()
{
	std::vector<std::shared_ptr<GameObject>> copyGameObjectsList;
	copyGameObjectsList.assign(gameObjectsList.begin(), gameObjectsList.end());

	for (auto gameObject : copyGameObjectsList)
	{
		gameObject->Input();
	}
}

/// <summary>
/// Handles all the logic
/// </summary>
void GameObjectsManager::Logic()
{
	std::vector<std::shared_ptr<GameObject>> copyGameObjectsList;
	copyGameObjectsList.assign(gameObjectsList.begin(), gameObjectsList.end());

	for (auto gameObject : copyGameObjectsList)
	{	
		gameObject->Logic();
	}
}