#pragma once
#include "Bullet.h"
#include "lessonX.h"

Bullet::Bullet(const char* szName) :Weapon(szName)
{
}
Bullet::~Bullet()
{
	
}
void Bullet::move(int iDir)
{
	setDir(iDir);
	switch (getDir())
	{
	case 0:
		setSpeedX(0);
		setSpeedY(-20);
		break;
	case 1:
		setSpeedX(20);
		setSpeedY(0);
		break;
	case 2:
		setSpeedX(0);
		setSpeedY(20);
		break;
	case 3:
		setSpeedX(-20);
		setSpeedY(0);
		break;
	}
	SetSpriteRotation(getDir() * 90);
	SetSpriteLinearVelocity(getSpeedX(), getSpeedY());
}
void Bullet::moveSpeed(int iDir)
{
	setDir(iDir);
	switch (getDir())
	{
	case 0:
		setSpeedX(0);
		setSpeedY(-30);
		break;
	case 1:
		setSpeedX(30);
		setSpeedY(0);
		break;
	case 2:
		setSpeedX(0);
		setSpeedY(30);
		break;
	case 3:
		setSpeedX(-30);
		setSpeedY(0);
		break;
	}
	SetSpriteRotation(getDir() * 90);
	SetSpriteLinearVelocity(getSpeedX(), getSpeedY());
}
void Bullet::moveForce(int iDir)
{
	setDir(iDir);
	switch (getDir())
	{
	case 0:
		setSpeedX(0);
		setSpeedY(-40);
		break;
	case 1:
		setSpeedX(40);
		setSpeedY(0);
		break;
	case 2:
		setSpeedX(0);
		setSpeedY(40);
		break;
	case 3:
		setSpeedX(-40);
		setSpeedY(0);
		break;
	}
	SetSpriteRotation(getDir() * 90);
	SetSpriteLinearVelocity(getSpeedX(), getSpeedY());
}

void Bullet::OnSpriteColSprite(Weapon* sprite)
{
	if (sprite == NULL)
	{
		return;
	}
	if ((strstr(sprite->GetName(), "muWall"))
		|| (strstr(sprite->GetName(), "bullet"))
		|| (strstr(sprite->GetName(), "enemy"))
		|| (strstr(sprite->GetName(), "tieWall"))
		|| (strstr(sprite->GetName(), "player")))
	{
		if (getOwner() == 1 || getOwner() == 11 || getOwner() == 12)
		{
			g_GameMain.SetPlayerBulletNum(0);
		}
		setHP(0);//子弹消失
	}
	if ((getOwner() == 1 || getOwner() == 11 || getOwner() == 12) && strstr(sprite->GetName(), "aim_nor") != NULL)  //我方坦克子弹与军营发生碰撞
	{
		return;
	}
	if (getOwner() == 0 && strstr(sprite->GetName(), "enemy") != NULL) //敌方坦克子弹打中敌方坦克
	{
		return;
	}
	if (!(strstr(sprite->GetName(), "haiWall")))
	{
		if (!strstr(sprite->GetName(), "player"))
		{
			if (strstr(sprite->GetName(), "enemy"))
			{
				int zhuangjiaHP = sprite->getHP();
				sprite->setHP(--zhuangjiaHP);
			}
			else
			{
				sprite->setHP(0);
			}
		}
		else
		{
			sprite->setHP(g_GameMain.GetPlayerLife());
		}
	}
	if (strstr(sprite->GetName(), "tieWall"))
	{
		if (getOwner() != 12)
		{
			sprite->setHP(2);
		}
		else
		{
			sprite->setHP(0);
		}
	}
	
}