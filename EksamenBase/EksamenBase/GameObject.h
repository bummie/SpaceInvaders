#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "SDL.h"
#include <string>

class GameObject
{	
private:
	std::string imagePath;
	SDL_Rect position;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
public:
	GameObject(SDL_Renderer* renderer);
	~GameObject();
	
	void Logic();
	void Draw();
	void Input();
	
};

#endif 