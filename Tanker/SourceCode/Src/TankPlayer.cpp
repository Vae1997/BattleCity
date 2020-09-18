#include "TankPlayer.h"
#include "LessonX.h"
TankPlayer::TankPlayer(const char* playerName):Weapon(playerName)
{
}
void TankPlayer::init()
{
	setHP(3);												//player血量
	SetSpritePosition(-8, 20);
	SetSpriteWorldLimit(WORLD_LIMIT_NULL, -27, -23, 27, 23);//碰撞有代码控制，左上，右下坐标
	SetSpriteCollisionActive(true, true);					//player产生接受碰撞
	SetSpriteVisible(true);
}

void TankPlayer::move(int iKey, bool bPress)
{
	if (bPress)
	{
		switch (iKey)
		{
		case KEY_UP:
			setDir(0);
			setSpeedX(0);
			setSpeedY(-8);
			break;
		case KEY_RIGHT:
			setDir(1);
			setSpeedX(8);
			setSpeedY(0);
			break;
		case KEY_DOWN:
			setDir(2);
			setSpeedX(0);
			setSpeedY(8);
			break;
		case KEY_LEFT:
			setDir(3);
			setSpeedX(-8);
			setSpeedY(0);
			break;
		}
		SetSpriteRotation(float(getDir() * 90));
		SetSpriteLinearVelocity(getSpeedX(), getSpeedY());
	}
	else
	{
		if (iKey == KEY_UP || iKey == KEY_RIGHT || iKey == KEY_DOWN || iKey == KEY_LEFT)
		{
			setSpeedX(0);
			setSpeedY(0);
			SetSpriteLinearVelocity(getSpeedX(), getSpeedY());
		}
	}
}

void TankPlayer::playerFire(int bulletType)
{
	float x, y;
	x = GetSpritePositionX();
	y = GetSpritePositionY();
	switch (getDir())
	{
	case 0:
		y = y - GetSpriteHeight() / 2 - 1;
		break;
	case 1:
		x = x + GetSpriteWidth() / 2 + 1;
		break;
	case 2:
		y = y + GetSpriteHeight() / 2 + 1;
		break;
	case 3:
		x = x - GetSpriteWidth() / 2 - 1;
		break;
	}
	if (bulletType == 0)
	{
		g_GameMain.addBullet(getDir(), x, y, 1);
	}
	if (bulletType == 1)
	{
		g_GameMain.addSpeedBullet(getDir(), x, y, 1);
	}
	if (bulletType == 2)
	{
		g_GameMain.addForceBullet(getDir(), x, y, 1);
	}
}

void TankPlayer::createBoom(float x, float y)
{
	m_pPlayerBoom = new CSprite("baozha");
	m_pPlayerBoom->CloneSprite("baozha");
	m_pPlayerBoom->SetSpriteCollisionActive(0, 0);
	m_pPlayerBoom->SetSpritePosition(x, y);
	m_pPlayerBoom->SetSpriteLifeTime(1);
}

void TankPlayer::OnSpriteColSprite(Weapon* sprite)
{
	 if (strstr(sprite->GetName(), "Wall") != NULL
		|| strstr(sprite->GetName(), "myAim") != NULL)
//		|| strstr(sprite->GetName(), "enemy") != NULL)
	{
		SetSpriteLinearVelocity(0, 0);
	}
}




