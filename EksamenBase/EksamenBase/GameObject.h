#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "SDL.h"

class GameObject
{	
private:

	struct Vector2D
	{
		float x;
		float y;
	};

	//std::string imagePath;
	SDL_Rect position;
	SDL_Texture* texture;
	SDL_Renderer* renderer;
	Vector2D velocity;
	Vector2D acceleration;
	float deAcceleration;
	float accelerationValue;
	const float MAX_SPEED = 10.0f;

public:
	GameObject(SDL_Renderer* renderer);
	~GameObject();
	
	void Logic();
	void Draw();
	void Input();
};

#endif 