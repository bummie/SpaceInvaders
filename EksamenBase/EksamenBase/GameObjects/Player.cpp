#include "Player.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"
#include <iostream>
#include <vector>

Player::Player(SDL_Renderer * renderer) : GameObject(renderer)
{
	m_texture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/player.bmp");
	tag = "Player";
}

Player::~Player()
{

}

void Player::Logic() 
{
	GameObject::Logic();

	// Do more logic
	std::vector<GameObject*>* collision = CollisionManager::getInstance().OnCollision(this);
	if(collision != nullptr)
	{
		for(auto go : *collision)
		{
			std::cout << "I AM COLLIDING with " << go->id << std::endl;
		}
	}

	delete(collision);
}

void Player::Input() 
{
	if (InputManager::getInstance().KeyUp(SDLK_t))
	{
		std::cout << "Click" << std::endl;
		m_texture = TextureManager::getInstance().GetTexture(m_renderer, "Resources/Images/enemy.bmp");
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

	if (InputManager::getInstance().KeyHeld(SDLK_w) || InputManager::getInstance().KeyHeld(SDLK_UP))
	{
		m_acceleration.y = -m_accelerationValue;
	}

	if (InputManager::getInstance().KeyHeld(SDLK_s) || InputManager::getInstance().KeyHeld(SDLK_DOWN))
	{
		m_acceleration.y = m_accelerationValue;
	}

	if (InputManager::getInstance().KeyHeld(SDLK_a) || InputManager::getInstance().KeyHeld(SDLK_LEFT))
	{
		m_acceleration.x = -m_accelerationValue;
	}

	if (InputManager::getInstance().KeyHeld(SDLK_d) || InputManager::getInstance().KeyHeld(SDLK_RIGHT))
	{
		m_acceleration.x = m_accelerationValue;
	}

	if (InputManager::getInstance().KeyHeld(SDLK_w) == InputManager::getInstance().KeyHeld(SDLK_s))
	{
		m_acceleration.y = 0;
	}

	if (InputManager::getInstance().KeyHeld(SDLK_a) == InputManager::getInstance().KeyHeld(SDLK_d))
	{
		m_acceleration.x = 0;
	}
}