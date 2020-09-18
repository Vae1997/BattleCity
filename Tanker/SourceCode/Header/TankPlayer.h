#pragma once
#include "Tank.h"
#include "Weapon.h"
class TankPlayer :
	public Weapon
{
private:
	CSprite*	m_pPlayerBoom;
public:
	TankPlayer(const char* playerName);

	void			init();

	void			move(int iKey, bool bPress);

	void			playerFire(int);
	void			createBoom(float, float);

	void			OnSpriteColSprite(Weapon* sprite);
};

