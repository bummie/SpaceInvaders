#ifndef ENEMY_ATTACK_H_INCLUDED
#define ENEMY_ATTACK_H_INCLUDED

#include "Projectile.h"

class EnemyAttack : Projectile
{
public:
	EnemyAttack(SDL_Renderer* renderer);
	~EnemyAttack();
	void Logic();
};

#endif
