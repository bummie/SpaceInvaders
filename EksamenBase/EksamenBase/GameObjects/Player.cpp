#include "Player.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"

#include <iostream>

Player::Player(SDL_Renderer * renderer) : GameObject(renderer)
{
	texture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/player.bmp");
	tag = "Player";
}

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
		texture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/enemy.bmp");
	}

	if (InputManager::getInstance().KeyDown(SDLK_SPACE))
	{
		std::cout << "SPACE" << std::endl;
		SoundManager::getInstance().PlaySound("Laser");
		SoundManager::getInstance().PlayMusic();

	}

	if (InputManager::getInstance().KeyDown(SDLK_g))
	{
		std::cout << "g" << std::endl;
		SoundManager::getInstance().PlaySound("Explosion");
		SoundManager::getInstance().StopMusic();
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