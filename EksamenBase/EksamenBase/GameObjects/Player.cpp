#include "Player.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"
#include "../Handlers/GameObjectsManager.h"
#include "Laser.h"
#include "Enemy.h"

#include <iostream>
#include <vector>

Player::Player(SDL_Renderer* renderer, int x, int y) : GameObject(renderer)
{
	position.x = x;
	position.y = y;
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/realplayer.bmp");
	tag = "Player";
	position.h = 40;
	position.w = 80;
}

Player::~Player()
{

}

void Player::Logic()
{
	GameObject::Logic();

	std::vector<GameObject*>* collision = CollisionManager::getInstance().OnCollision(this);

	if (collision != nullptr)
	{
		for (auto go : *collision)
		{
			std::cout << "I AM COLLIDING with " << go->id << std::endl;
		}
	}
	delete(collision);

	// Player collide with side walls
	if ((position.x < 0 && m_acceleration.x < 0) || (position.x >(GameHandler::SCREEN_WIDTH - position.w) && m_acceleration.x > 0))
	{
		m_acceleration.x = 0;
	}
}

void Player::Input()
{
	if (InputManager::getInstance().KeyDown(SDLK_SPACE))
	{
		std::cout << "SPACE" << std::endl;
		SoundManager::getInstance().PlaySound("Laser");
	}

	if (InputManager::getInstance().KeyHeld(SDLK_a))
	{
		if (position.x > 0)
		{
			m_acceleration.x = -m_accelerationValue;
		}
	}

	if (InputManager::getInstance().KeyHeld(SDLK_d))
	{
		if (position.x < (GameHandler::SCREEN_WIDTH - position.w))
		{
			m_acceleration.x = m_accelerationValue;
		}
	}

	if (InputManager::getInstance().KeyHeld(SDLK_a) == InputManager::getInstance().KeyHeld(SDLK_d))
	{
		m_acceleration.x = 0;
	}
}