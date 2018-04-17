#include "GameObject.h"
#include "TextureManager.h"
#include "InputManager.h"
#include <iostream>

GameObject::GameObject(SDL_Renderer* _renderer)
{
	position =  SDL_Rect();
	position.h = 16;
	position.w = 16;

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
		position.y -= 10;
	}

	if (InputManager::getInstance().KeyHeld(SDLK_s))
	{
		position.y += 10;
	}

	if (InputManager::getInstance().KeyHeld(SDLK_a))
	{
		position.x -= 10;
	}

	if (InputManager::getInstance().KeyHeld(SDLK_d))
	{
		position.x += 10;
	}
}

void GameObject::Logic()
{
	//position.x = std::rand() % 100;
	//position.y = std::rand() % 100;
}
