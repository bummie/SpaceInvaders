#include "MysteryShip.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/GameHandler.h"
#include <stdlib.h>

MysteryShip::MysteryShip(SDL_Renderer * renderer) : GameObject(renderer)
{
	GameObject::GameObject(renderer);
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Enemies/Enemy_spaceship.bmp");
	m_deathTexture = TextureManager::getInstance().GetTexture(renderer, "Resources/Images/Explode/Explode_enemy.bmp");
	position.x = -48;
	position.y = 70;
	position.w = 96 / 3;
	position.h = 48 / 3;
	m_maxSpeed = 0.15f;
	tag = "MysteryShip";
	m_canRespawn = true;
}

MysteryShip::~MysteryShip()
{

}

void MysteryShip::Logic()
{
	GameObject::Logic();

	if(!m_canRespawn)
	{
		if(position.x < -50 || position.x > GameHandler::SCREEN_WIDTH + 10)
		{
			m_canRespawn = true;
		}
	}

	if(rand() % 500 == 250)
	{
		if (GameObject::getHp() <= 0 || m_canRespawn) 
		{
			if (rand() % 10 >= 5)
			{
				m_acceleration.x = -1;
				position.x = GameHandler::SCREEN_WIDTH;
			}else
			{
				m_acceleration.x = 1;
				position.x = -48;
			}

			ResetAnim();
			GameObject::setHp(100);
			m_canRespawn = false;
		}
	}
}

void MysteryShip::Input()
{
}
