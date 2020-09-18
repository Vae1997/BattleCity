#include "Tank.h"

Tank::Tank(const char* szName) :CSprite(szName)
{
	direction = 0;
	speedX = 0.f;
	speedY = 0.f;
	HP = 2;			//所有坦克初始血量
}

