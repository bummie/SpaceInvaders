#ifndef ENEMY_ATTACK_H_INCLUDED
#define ENEMY_ATTACK_H_INCLUDED

#include "Projectile.h"

class EnemyAttack : Projectile
{
public:
	EnemyAttack(SDL_Renderer* renderer);
	~EnemyAttack();
	void Logic();
private:
	const std::string imgPathCrossDown = "Resources/Images/Projectiles/Projectile_cross_down.bmp";
	const std::string imgPathCrossUp = "Resources/Images/Projectiles/Projectile_cross_up.bmp";
};

#endif
