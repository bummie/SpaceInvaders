#include "GameObject.h"
#include "TextureManager.h"
#include "InputManager.h"
#include <iostream>
#include <cmath>  
#include "GameHandler.h"

GameObject::GameObject(SDL_Renderer* renderer)
{
	position = SDL_Rect();
	position.h = 64;
	position.w = 64;

	velocity = { 0.0f, 0.0f };
	acceleration = { 0.0f, 0.0f };
	deAcceleration = 1.0f;
	accelerationValue = .1f;

	GameObject::renderer = renderer;
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

	position.x += velocity.x * GameHandler::getDeltaTime();
	position.y += velocity.y * GameHandler::getDeltaTime();
}