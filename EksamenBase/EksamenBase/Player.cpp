#include "Player.h"
#include "InputManager.h"
#include "TextureManager.h"
#include <iostream>

Player::~Player()
{

}

void Player::Logic() 
{
	GameObject::Logic();

	// Do more logic

}


void Player::Input() 
{
	if (InputManager::getInstance().KeyUp(SDLK_t))
	{
		std::cout << "Click" << std::endl;
		texture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/test.bmp");
	}

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

	if (!InputManager::getInstance().KeyHeld(SDLK_w) && !InputManager::getInstance().KeyHeld(SDLK_s))
	{
		acceleration.y = 0;
	}

	if (!InputManager::getInstance().KeyHeld(SDLK_a) && !InputManager::getInstance().KeyHeld(SDLK_d))
	{
		acceleration.x = 0;
	}
}