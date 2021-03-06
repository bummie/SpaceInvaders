#include "GameObject.h"
#include <iostream>
#include <cmath>  
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"

GameObject::GameObject(SDL_Renderer* renderer)
{
	m_deathTexture = nullptr;
	m_hasShownDeathTexture = false;
	m_deathTextureDuration = 100;
	m_deathTextureTimePassed = 0;

	position = SDL_Rect();
	position.h = 64;
	position.w = 64;

	m_velocity = { 0.0f, 0.0f };
	m_acceleration = { 0.0f, 0.0f };
	m_deAcceleration = 1.0f;
	m_accelerationValue = .1f;
	m_hp = 100;
	tag = "GameObject";

	GameObject::m_renderer = renderer;
}

GameObject::~GameObject()
{
}

void GameObject::Draw()
{
	if (getHp() <= 0) 
	{ 
		if (m_deathTexture == nullptr || m_hasShownDeathTexture) { return; }
		
		SDL_RenderCopy(m_renderer, m_deathTexture, NULL, &position);

		if(m_deathTextureTimePassed >= m_deathTextureDuration)
		{
			m_hasShownDeathTexture = true;
			m_deathTextureTimePassed = 0;
		}
		
		m_deathTextureTimePassed += GameHandler::getDeltaTime();
		return;
	}

	if(m_defTexture == nullptr)
	{
		std::cout << "Texture is null" << std::endl;
		return;
	}
	if (m_secondaryTexture == nullptr)
	{
		SDL_RenderCopy(m_renderer, m_defTexture, NULL, &position);
		return;
	}
	if (m_firstTexture)
	{
		SDL_RenderCopy(m_renderer, m_defTexture, NULL, &position);
	}
	else if (!m_firstTexture)
	{
		SDL_RenderCopy(m_renderer, m_secondaryTexture, NULL, &position);
	}
	
	m_currentTime += GameHandler::getDeltaTime();
	
	if (m_currentTime > 200)
	{
		if (m_firstTexture)
		{
			m_firstTexture = false;
		}
		else if (!m_firstTexture)
		{
			m_firstTexture = true;
		}
		m_currentTime = 0;
	}
}

void GameObject::Input()
{
	if (getHp() <= 0) { return; }
}

/// <summary>
/// Returns HP
/// </summary>
/// <returns></returns>
int GameObject::getHp() const
{
	return m_hp;
}

/// <summary>
/// Sets HP
/// </summary>
/// <param name="hp"></param>
void GameObject::setHp(int hp)
{
	m_hp = hp;
}

void GameObject::ResetAnim()
{
	m_currentTime = 0;
	m_firstTexture = true;
	m_hasShownDeathTexture = false;
}

void GameObject::Logic()
{
	if (getHp() <= 0) { return; }

	if(m_acceleration.x != 0)
	{
		m_velocity.x += m_acceleration.x;
	}else
	{
		m_velocity.x += -(1.0f, m_velocity.x) * m_deAcceleration;
	}
	
	if (m_acceleration.y != 0)
	{
		m_velocity.y += m_acceleration.y;
	}
	else
	{
		m_velocity.y += -(1.0f, m_velocity.y) * m_deAcceleration;
	}

	if (std::abs(m_velocity.y) > m_maxSpeed) { m_velocity.y = copysign(1.0f, m_velocity.y) * m_maxSpeed; }
	if (std::abs(m_velocity.x) > m_maxSpeed) { m_velocity.x = copysign(1.0f, m_velocity.x) * m_maxSpeed; }

	position.x += m_velocity.x * GameHandler::getDeltaTime();
	position.y += m_velocity.y * GameHandler::getDeltaTime();
}