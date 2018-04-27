#ifndef GAMEOBJECTSMANAGER_H_INCLUDED
#define GAMEOBJECTSMANAGER_H_INCLUDED

#include "../GameObjects\GameObject.h"
#include <vector>
#include <string>

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
	std::vector<GameObject*> gameObjectsList;

	void Add(GameObject* gameObject);
	void Remove(GameObject* gameObject);
	GameObject** Find(std::string tag);

	void Draw();
	void Input();
	void Logic();

};

#endif