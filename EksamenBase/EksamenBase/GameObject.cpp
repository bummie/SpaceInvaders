#include "GameObject.h"
#include "TextureManager.h"
#include "InputManager.h"
#include <iostream>
#include <cmath>   

GameObject::GameObject(SDL_Renderer* _renderer)
{
	position = SDL_Rect();
	position.h = 16;
	position.w = 16;

	velocity = { 0.0f, 0.0f };
	acceleration = { 0.0f, 0.0f };
	deAcceleration = 1.0f;
	accelerationValue = 1.0f;

	renderer = _renderer;
	texture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/bear.bmp");
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	if(texture == nullptr)
	{
		std::cout << "Texture is null" << std::endl;
		return;
	}
	SDL_RenderCopy(renderer, texture, NULL, &position);
}

void GameObject::Input()
{
	if (InputManager::getInstance().KeyHeld(SDLK_w))
	{
		acceleration.y = -accelerationValue;
	}
	
	if (InputManager::getInstance().KeyHeld(SDLK_s))
	{
		acceleration.y = accelerationValue;
	}

	if (InputManager::getInstance().KeyHeld(SDLK_a))
	{
		acceleration.x = -accelerationValue;
	}
	
	if (InputManager::getInstance().KeyHeld(SDLK_d))
	{
		acceleration.x = accelerationValue;
	}

	if(!InputManager::getInstance().KeyHeld(SDLK_w) && !InputManager::getInstance().KeyHeld(SDLK_s))
	{
		acceleration.y = 0;
	}

	if(!InputManager::getInstance().KeyHeld(SDLK_a) && !InputManager::getInstance().KeyHeld(SDLK_d))
	{
		acceleration.x = 0;
	}
}

void GameObject::Logic()
{
	//std::cout << "Acc: x: " << acceleration.x << " y: " << acceleration.y << std::endl;
	//std::cout << "Vel: x: " << velocity.x << " y: " << velocity.y << std::endl;

	if(acceleration.x != 0)
	{
		velocity.x += acceleration.x;
	}else
	{
		velocity.x += -(1.0f, velocity.x) * deAcceleration;
	}
	
	if (acceleration.y != 0)
	{
		velocity.y += acceleration.y;
	}
	else
	{
		velocity.y += -(1.0f, velocity.y) * deAcceleration;
	}

	if (std::abs(velocity.y) > MAX_SPEED) { velocity.y = copysign(1.0f, velocity.y) * MAX_SPEED; }
	if (std::abs(velocity.x) > MAX_SPEED) { velocity.x = copysign(1.0f, velocity.x) * MAX_SPEED; }

	position.x += velocity.x;
	position.y += velocity.y;
}
