#include "Laser.h"

#include "../Handlers/InputManager.h"
#include "../Handlers/TextureManager.h"
#include "../Handlers/SoundManager.h"
#include "../Handlers/CollisionManager.h"
#include "../Handlers/GameHandler.h"
#include "../Handlers/GameObjectsManager.h"


Laser::Laser(SDL_Renderer* renderer, int x, int y) : Projectile(renderer, x, y)
{
	Projectile::Projectile(renderer, x, y);
	m_defTexture = TextureManager::getInstance().GetTexture(renderer, imgPathLaser);
	direction = { 0, -1 };
	position.h = 16;
	position.w = 8;
	m_maxSpeed = .5f;
}


Laser::~Laser()
{
}

void Laser::Logic()
{
	if (getHp() <= 0) { return; }

	Projectile::Logic();

	std::vector<GameObject*>* collision = CollisionManager::getInstance().OnCollision(this);

	if (collision != nullptr)
	{
		for (auto go : *collision)
		{
			std::cout << "LASER: " << go->id << std::endl;
			if(go->tag != "Player")
			{
				go->setHp(0);
				setHp(0);
				return;
			}
		}
	}
	delete(collision);

}

