#include "BarricadeBlock.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/GameObjectsManager.h"

BarricadeBlock::BarricadeBlock(SDL_Renderer* renderer, int x, int y) : GameObject(renderer)
{
	GameObject::GameObject(renderer);
	tag = "BarricadeBlock";
	position.x = x;
	position.y = y;
	position.h = 16;
	position.w = 16;
	m_defTexture = TextureManager::getInstance().GetTexture(m_renderer, "Resources/Images/Barricade/barricade_0.bmp");
	m_oldHp = m_hp;
}

BarricadeBlock::~BarricadeBlock()
{
}

void BarricadeBlock::Logic()
{
	GameObject::Logic();

	if (GameObject::getHp() == m_oldHp) { return; }

	if(GameObject::getHp() <= 80 && GameObject::getHp() > 60)
	{
		m_defTexture = TextureManager::getInstance().GetTexture(m_renderer, "Resources/Images/Barricade/barricade_1.bmp");
		m_oldHp = GameObject::getHp();
	}else if (GameObject::getHp() <= 60 && GameObject::getHp() > 40)
	{
		m_defTexture = TextureManager::getInstance().GetTexture(m_renderer, "Resources/Images/Barricade/barricade_2.bmp");
		m_oldHp = GameObject::getHp();
	}
	else if (GameObject::getHp() <= 40 && GameObject::getHp() > 20) 
	{
		m_defTexture = TextureManager::getInstance().GetTexture(m_renderer, "Resources/Images/Barricade/barricade_3.bmp");
		m_oldHp = GameObject::getHp();
	}else if(GameObject::getHp() <= 20)
	{
		// DEAD
	}
}

void BarricadeBlock::Input()
{
}
