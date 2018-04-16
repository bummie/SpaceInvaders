#include "GameObject.h"
#include "TextureManager.h"
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

void GameObject::Logic()
{
	position.x = std::rand() % 100;
	position.y = std::rand() % 100;
}
