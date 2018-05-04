#include "Player.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"
#include "../Handlers/GameObjectsManager.h"
#include "Laser.h"
#include "Enemy.h"
#include "../Handlers/ObjectsPool.h"

#include <memory>
#include <iostream>
#include <vector>

Player::Player(SDL_Renderer* renderer, int x, int y) : GameObject(renderer)
{
	position.x = x;
	position.y = y;
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/realplayer.bmp");
	tag = "Player";
	position.h = 25;
	position.w = 50;
	m_laser = std::shared_ptr<GameObject>(new Laser(renderer, (position.x + M_XOFFSET), (position.y + M_YOFFSET)));
	GameObjectsManager::getInstance().Add(m_laser);
}

Player::~Player()
{

}

void Player::Logic()
{
	GameObject::Logic();

	auto collision = CollisionManager::getInstance().OnCollision(this);

	if (m_laser != nullptr)
	{
		if (m_laser->getHp() <= 0)
		{
			Replenish();
		}
	}

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
		if (m_replenished)
		{
			Shoot();
		}
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

void Player::Shoot()
{
	std::cout << "SPACE" << std::endl;
	SoundManager::getInstance().PlaySound("Laser");
	m_laser->position.x = position.x + M_XOFFSET;
	m_laser->position.y = position.y + M_YOFFSET;
	m_laser->setHp(100);
	m_replenished = false;
}

void Player::Replenish()
{
	m_replenished = true;
}
