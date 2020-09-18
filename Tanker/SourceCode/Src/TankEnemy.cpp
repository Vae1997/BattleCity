#include "TankEnemy.h"
#include "LessonX.h"
#include <time.h>
TankEnemy::TankEnemy(const char* enemyName):Weapon(enemyName)
{
	m_iEnemyType = 0;
	m_iBaowuNum = 0;

	m_fChangeDirTime = 0;
	m_fBulletCreateTime = 0;
	m_fStopTime = 0;

}
TankEnemy::~TankEnemy()
{

}

void TankEnemy::init(int enemyType)
{
	setEnemyType(enemyType);
	if (enemyType == 0 || enemyType == 3)
	{
		setHP(1);
		SetSpriteLinearVelocity(0.0f, 5.0f);
	}
	if (enemyType == 1)
	{
		setHP(3);
		SetSpriteLinearVelocity(0.0f, 3.0f);
	}
	if (enemyType == 2)
	{
		setHP(1);
		SetSpriteLinearVelocity(0.0f, 15.0f);
	}
	setDir(2);
	int pos = CSystem::RandomRange(0, 2);
	float posX;
	switch (pos)
	{
	case 0:
		posX = -24.0f;
		break;
	case 1:
		posX = 0.0f;
		break;
	case 2:
		posX = 24.0f;
		break;
	}
	SetSpritePosition(posX, -20);
	SetSpriteCollisionActive(true, true);
	SetSpriteRotation(float(getDir() * 90));
	SetSpriteWorldLimit(WORLD_LIMIT_STICKY, -26, -22, 26, 22);
}

void TankEnemy::move()
{
	int dir = CSystem::RandomRange(0, 3);
//	int dir = 0;
	if (dir == 0 || dir == 1 || dir == 2)
	{
		dir += 1;
	}
	else
	{
		dir = 0;
	}
	setDir(dir);
	if (m_iEnemyType == 1)
	{
		switch (dir)
		{
		case 0:
			setSpeedX(0);
			setSpeedY(-3);
			break;
		case 1:
			setSpeedX(3);
			setSpeedY(0);
			break;
		case 2:
			setSpeedX(0);
			setSpeedY(3);
			break;
		case 3:
			setSpeedX(-3);
			setSpeedY(0);
			break;
		}
	}
	else if (m_iEnemyType== 2)
	{
		switch (dir)
		{
		case 0:
			setSpeedX(0);
			setSpeedY(-15);
			break;
		case 1:
			setSpeedX(15);
			setSpeedY(0);
			break;
		case 2:
			setSpeedX(0);
			setSpeedY(15);
			break;
		case 3:
			setSpeedX(-15);
			setSpeedY(0);
			break;
		}
	}
	else
	{
		switch (dir)
		{
		case 0:
			setSpeedX(0);
			setSpeedY(-5);
			break;
		case 1:
			setSpeedX(5);
			setSpeedY(0);
			break;
		case 2:
			setSpeedX(0);
			setSpeedY(5);
			break;
		case 3:
			setSpeedX(-5);
			setSpeedY(0);
			break;
		}
	}
	SetSpriteRotation(float(getDir() * 90));
	SetSpriteLinearVelocity(getSpeedX(), getSpeedY());
}

void TankEnemy::move(float cdTime)
{
	m_fChangeDirTime += cdTime;
	if (m_fChangeDirTime > 2.0f)
	{
		move();
		m_fChangeDirTime = 0;
	}
}

void TankEnemy::enemyFire(float bcTime)
{
	m_fBulletCreateTime += bcTime;
	if (m_fBulletCreateTime > 3.0f)
	{
		m_fBulletCreateTime = 0.0f;
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
		g_GameMain.addBullet(getDir(), x, y, 0);
	}
}

void TankEnemy::createBoom(float x, float y)
{
	m_pEnemyBoom = new CSprite("baozha");
	m_pEnemyBoom->CloneSprite("baozha");
	m_pEnemyBoom->SetSpriteCollisionActive(0, 0);
	m_pEnemyBoom->SetSpritePosition(x, y);
	m_pEnemyBoom->SetSpriteLifeTime(1);
}

void TankEnemy::createBaowu(float x, float y,int type)
{
	vector<Weapon*> tmpWeapon = g_GameMain.GetWeapon();
	if (type == 0)
	{
		char* szName = CSystem::MakeSpriteName("zhadan", m_iBaowuNum);
		m_pZhaDan = new Weapon(szName);
		m_pZhaDan->CloneSprite("zhadan");
		m_pZhaDan->SetSpriteCollisionActive(0, 1);
		m_pZhaDan->SetSpritePosition(x, y);
		tmpWeapon.push_back(m_pZhaDan);
		m_pZhaDan->SetSpriteLifeTime(15);
	}
	if (type == 1)
	{
		char* szName = CSystem::MakeSpriteName("star", m_iBaowuNum);
		m_pStar = new Weapon(szName);
		m_pStar->CloneSprite("star");
//		m_pStar->setBaoType(1);
		m_pStar->SetSpriteCollisionActive(0, 1);
		m_pStar->SetSpritePosition(x, y);
		tmpWeapon.push_back(m_pStar);
		m_pStar->SetSpriteLifeTime(30);
	}
	if (type == 2)
	{
		char* szName = CSystem::MakeSpriteName("zanting", m_iBaowuNum);
		m_pZanTing = new Weapon(szName);
		m_pZanTing->CloneSprite("zanting");
//		m_pZanTing->setBaoType(2);
		m_pZanTing->SetSpriteCollisionActive(0, 1);
		m_pZanTing->SetSpritePosition(x, y);
		tmpWeapon.push_back(m_pZanTing);
//		m_pZanTing->SetSpriteLifeTime(30);
	}
	g_GameMain.SetWeapon(tmpWeapon);
	m_iBaowuNum++;
}

void TankEnemy::OnSpriteColSprite(Weapon* sprite)
{
	if (sprite == NULL)
	{
		return;
	}
	if (strstr(sprite->GetName(), "star") == NULL
		&& strstr(sprite->GetName(), "zanting") == NULL
		&& strstr(sprite->GetName(), "zhadan") == NULL
		&& strstr(sprite->GetName(), "enemy") == NULL)
	{
		SetSpriteLinearVelocity(0, 0);
		m_fChangeDirTime = 1.9f;
	}
}
void TankEnemy::stopMove(float time)
{
	m_fStopTime += time;
	if (m_fStopTime < 5.0f)
	{
		SetSpriteLinearVelocity(0.0f, 0.0f);
	}
	else 
	{
		m_fStopTime = 0;
		g_GameMain.SetZanTingMessage(0);
	}
	
}
