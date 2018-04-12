#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED
#include "SDL.h"
#include <string>
#include "Vector2D.h"

class GameObject
{	
private:
	std::string imagePath;
	SDL_Rect* rect;
public:
	GameObject();
	~GameObject();
	
	void Draw();
	void Update();

	Vector2D Position;
};

#endif 