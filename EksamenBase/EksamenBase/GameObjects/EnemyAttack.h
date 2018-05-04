#ifndef ENEMY_ATTACK_H_INCLUDED
#define ENEMY_ATTACK_H_INCLUDED

#include "Projectile.h"

class EnemyAttack : public Projectile
{
public:
	EnemyAttack(SDL_Renderer* renderer, int x, int y);
	~EnemyAttack();
	void Logic();
private:
	const std::string m_imgPathCrossDown = "Resources/Images/Projectiles/Projectile_cross_down.bmp";
	const std::string m_imgPathCrossUp = "Resources/Images/Projectiles/Projectile_cross_up.bmp";
};

#endif
