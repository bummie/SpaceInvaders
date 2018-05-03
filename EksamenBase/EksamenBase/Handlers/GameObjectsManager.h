#ifndef GAMEOBJECTSMANAGER_H_INCLUDED
#define GAMEOBJECTSMANAGER_H_INCLUDED

#include "../GameObjects\GameObject.h"
#include <vector>
#include <string>
#include <memory>

class GameObjectsManager
{
public:
	static GameObjectsManager& getInstance()
	{
		static GameObjectsManager instance;
		return instance;
	}

private:
	GameObjectsManager() {}
	GameObjectsManager(GameObjectsManager const&);
	void operator=(GameObjectsManager const&);
	int gameObjectCounter = 0;

public:
	~GameObjectsManager();
	void Add(std::shared_ptr<GameObject> gameObject);
	std::vector<std::shared_ptr<GameObject>> gameObjectsList;

	void Remove(std::shared_ptr<GameObject> gameObject);
	std::vector<std::shared_ptr<GameObject>>* Find(std::string tag);

	void Draw();
	void Input();
	void Logic();

};

#endif