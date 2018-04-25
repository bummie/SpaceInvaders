#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "SDL.h"
#include <string>

class GameObject
{	
protected:

	struct Vector2D
	{
		float x;
		float y;
	};

	//std::string imagePath;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	Vector2D velocity;
	Vector2D acceleration;
	float deAcceleration;
	float accelerationValue;
	const float MAX_SPEED = .5f;

public:
	GameObject(SDL_Renderer* renderer);
	~GameObject();

	SDL_Rect position;
	std::string tag;
	virtual void Logic();
	virtual void Draw();
	virtual void Input();
};

#endif 