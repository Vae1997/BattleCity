#pragma once
#include "Weapon.h"
#include <time.h>
Weapon::Weapon(const char* wName) :CSprite(wName)
{
	direction = 0;
	speedX = 0.f;
	speedY = 0.f;
	HP = 2;
//	m_iBaoType = 0;
}

Weapon::~Weapon()
{

}

bool Weapon::spriteIsDead()
{
	if (HP == 0)
	{
		return true;
	}
	return false;
}

