#include "Projectile.h"
#include "../Handlers/GameHandler.h"
#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"

/// <summary>
/// Checks whether the projectil is out of bounds or not
/// </summary>
void Projectile::CheckPosition()
{
	if (position.y > GameHandler::SCREEN_HEIGHT || position.y < 0)
	{
		setHp(0);
	}
}

Projectile::Projectile(SDL_Renderer* renderer, int x, int y) : GameObject(renderer)
{
	tag = "Projectile";
	m_renderer = renderer;
	m_maxSpeed = .3f;
	position = { x, y };	
}

Projectile::~Projectile()
{
}

void Projectile::Logic()
{
	GameObject::Logic();
	CheckPosition();
	m_acceleration.y = (m_maxSpeed * direction.y);

	std::vector<std::shared_ptr<GameObject>>* collision = CollisionManager::getInstance().OnCollision(this);

	if (collision != nullptr)
	{
		std::cout << "Collision: " << tag << std::endl;
		for (auto go : *collision)
		{
			if (go->tag == "Enemy" && tag == "Laser")
			{
				GameHandler::score += 40;
				go->setHp(0);
				setHp(0);
				return;
			}
			else if(go->tag == "Player" && (tag == "EnemyAttack" || tag == "Snake"))
			{
				go->setHp(0);
				setHp(0);
			}
		}
	}
	delete(collision);
}

