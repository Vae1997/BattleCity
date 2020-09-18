#include				<stdio.h>
#include				"commonClass.h"
#include				"lessonX.h"
#include				<time.h>

CGameMain				g_GameMain;	
int g_iMap1[11][13] =							//0空地，1木头，2海洋，3铁皮，4地板，5草丛
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 0 },
	{ 0, 0, 0, 1, 1, 5, 5, 5, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 5, 5, 5 },
	{ 4, 4, 1, 1, 3, 3, 3, 3, 3, 5, 5, 5, 5 },
	{ 4, 4, 1, 1, 0, 0, 0, 0, 0, 5, 5, 5, 5 },
	{ 0, 0, 0, 0, 1, 1, 1, 1, 1, 5, 5, 5, 5 },
	{ 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 3, 0, 0, 3, 1, 3, 0, 2, 0, 0, 0 },
	{ 0, 0, 1, 0, 0, 3, 0, 3, 0, 2, 0, 0, 0 }
};
int g_iMap2[11][13] =							//0空地，1木头，2海洋，3铁皮，4地板，5草丛
{
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 1, 1, 5, 3, 5, 1, 1, 0, 0, 0 },
	{ 0, 0, 0, 5, 0, 1, 0, 1, 0, 5, 0, 0, 0 },
	{ 0, 0, 0, 5, 4, 2, 2, 2, 4, 5, 0, 0, 0 },
	{ 0, 0, 0, 5, 0, 1, 0, 1, 0, 5, 0, 0, 0 },
	{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
	{ 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0 },
	{ 0, 0, 0, 0, 0, 3, 1, 3, 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0, 3, 0, 3, 0, 0, 0, 0, 0 }
};

CGameMain::CGameMain()
{
	m_iGameState = 0;
	m_iBulletNum = 0;
	m_iPlayerBulletNum = 0;
	m_iTankEnemyNum = 0;
	m_iGameCount = 0;
	m_iScore = 0;
	m_iMaxScore = 0;
	m_iEnemy = 20;
	m_iLife = 3;
	m_iLevel = 1;
	m_iMaxTanksNum = 4;
	m_iZanTingColMessage = 0;
	m_iPlayerBulletMode = 0;

	m_fGameTime = 0.0f;
	m_fEnemyCreateTime = 0.0f;
	m_fGameWaitTime = 0;

	m_pSplash = new CSprite("splash");
	m_pStart = new CSprite("start");
	m_pScore = new CTextSprite("score");
	m_pMaxScore = new CTextSprite("maxScore");
	m_pEnemy = new CTextSprite("enemyNum");
	m_pLife = new CTextSprite("life");
	m_pLevel = new CTextSprite("level");
	
	m_pStartSound = new CSound("startTankWorld.ogg",0,1);
	m_pFire = new CSound("fire.wav", 0, 1);
	m_pBaoZha = new CSound("baozha.ogg", 0, 1);
	m_pHit = new CSound("hit.wav", 0, 1);
	m_pAdd = new CSound("add.wav", 0, 1);
	m_pEat = new CSound("eat.ogg", 0, 1);
	m_pGameOverS = new CSound("gameover.ogg", 0, 1);
	m_pSuccess = new CSound("success.ogg", 0, 0.5);
}

CGameMain::~CGameMain()
{
	delete m_pSplash;
	delete m_pStart;
}

void	CGameMain::GameMainLoop( float	fDeltaTime )
{
	switch( GetGameState() )
	{
	case 1:
		{
			GameInit();
			SetGameState(2); 
		}
		break;
	case 2:
		{
			  if (!m_pTankPlayer->spriteIsDead() && !m_pAim_nor->spriteIsDead())// && m_iEnemy != 0)
			{
				GameRun( fDeltaTime );
			}
			else 
			{		
				GameEnd();
				SetGameState(0);
			}
		}
		break;
	case 0:
	default:
		break;
	};
}

void	CGameMain::GameInit()
{
	m_pStartSound->PlaySoundA();
	m_pSplash->SetSpriteVisible(false);
	m_pStart->SetSpriteVisible(false);
	
	loadMap(m_iLevel);

	m_pTankPlayer = new TankPlayer("myplayer");
	m_pTankPlayer->CloneSprite("player");
	m_pTankPlayer->init();
	
	m_pAim_nor = new Weapon("myAim");
	m_pAim_nor->CloneSprite("aim_nor");
	m_pAim_nor->SetSpriteCollisionReceive(true);
	m_pAim_nor->SetSpritePosition(0, 20);

	m_pGameOver = new CSprite("gameOver");
	m_pGameOver->CloneSprite("gameover");
	m_pGameOver->SetSpritePosition(0, 60);
	m_pGameOver->SetSpriteVisible(true);

	m_vWeapon.push_back(m_pTankPlayer);
	m_vWeapon.push_back(m_pAim_nor);

	m_iBulletNum = 0;
	m_iPlayerBulletNum = 0;
	m_iTankEnemyNum = 0;
	m_iEnemy = 20;
	m_iMaxTanksNum = 4;

	m_fEnemyCreateTime = 5.0f;
	m_fGameTime = 0.0f;
	m_fGameWaitTime = 0;

	FILE * fp = fopen("save.txt", "r+");
	if (fp)
	{
		fread(&m_iMaxScore, sizeof(int), 1, fp);
		fclose(fp);
	}
	m_pMaxScore = new CTextSprite("maxScore");
	m_pMaxScore->SetTextValue(m_iMaxScore);
	m_pLife->SetTextValue(m_iLife);
	m_pLevel->SetTextValue(m_iLevel);
}

void	CGameMain::GameRun( float fDeltaTime )
{
	int	currentEnemyNumInScene = 0;
	if (m_iMaxTanksNum > 0 && m_iEnemy > 3)
	{
		addTankEnemy(fDeltaTime);
	}
	for (unsigned int i = 0; i < m_vWeapon.size(); i++)
	{
		if (!m_vWeapon[i]->spriteIsDead())
		{
			Weapon* w = m_vWeapon[i];
			if (strstr(w->GetName(), "enemy") != NULL)
			{
				currentEnemyNumInScene++;
				if (m_iZanTingColMessage == 0)
				{
					m_vWeapon[i]->move(fDeltaTime);
					m_vWeapon[i]->enemyFire(fDeltaTime);
				}
				else
				{
					TankEnemy* enemy = (TankEnemy*)w;
					enemy->stopMove(fDeltaTime);
				}
			}
		}
		else
		{
			delWeaponByName(m_vWeapon[i]->GetName());
		}
	}
	m_fGameTime += m_fGameTime;

	m_pScore->SetTextValue(m_iScore);
	m_pMaxScore->SetTextValue(m_iMaxScore);
	m_pEnemy->SetTextValue(m_iEnemy);
	m_pLife->SetTextValue(m_iLife);
	m_pLevel->SetTextValue(m_iLevel);

	if (currentEnemyNumInScene == 0)
	{
		m_fGameWaitTime += fDeltaTime;
		if (m_fGameWaitTime > 3)
		{
			m_pSuccess->PlaySoundA();
		}
		if (m_fGameWaitTime > 5)
		{
			//go to next level
			m_iLevel++;
			SetGameState(1);
			m_fGameWaitTime = 0;
			deleteAllSprite();
		}
		
	}
	else
	{
		m_fGameWaitTime = 0;
	}

}

void	CGameMain::GameEnd()
{
	FILE * fp = fopen("save.txt", "w+");
	if (m_iScore>m_iMaxScore)
		fwrite(&m_iScore, sizeof(int), 1, fp);
	fclose(fp);
	m_pEnemy->SetTextValue(0);
	m_pLife->SetTextValue(0);
	m_pGameOver->SpriteMoveTo(0, 0, 100, true);
	m_pGameOverS->PlaySoundA();
	m_iLevel = 1;
	m_iLife = 3;
	m_iScore = 0;
	deleteAllSprite();
}

void	CGameMain::OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress){
	if (GetGameState() == 0)
	{
		if (iKey != KEY_NULL)
		{	
			if (GetGameCount() == 0)
			{
				m_iGameState = 1;
				m_iZanTingColMessage = 0;
				m_iPlayerBulletMode = 0;
				
			}
			else
			{
				m_pGameOver->SetSpriteVisible(false);
				m_pSplash->SetSpriteVisible(true);
				m_pStart->SetSpriteVisible(true);
				m_iGameCount = 0;
				m_iPlayerBulletNum == 0;
			}
		}
	}
	if (GetGameState() == 2)
	{
		m_pTankPlayer->move(iKey, true);
		if (m_iPlayerBulletNum != 1)
		{
			m_iPlayerBulletNum = 0;
		}
		if (m_iPlayerBulletNum == 0 && iKey == KEY_X)
		{
			int bulletType = GetBulletMode();
			m_pTankPlayer->playerFire(bulletType);
			m_iPlayerBulletNum++;
			m_pFire->PlaySoundA();
		}
	}
}

void	CGameMain::OnKeyUp(const int iKey)
{
	if (GetGameState() == 2)
	{
		m_pTankPlayer->move(iKey, false);
	}
}

void	CGameMain::OnSpriteColWorldLimit(const char* szName, const int iColSide)
{
	if (strstr(szName, "player") != NULL)
	{
		m_iPlayerBulletNum == 0;
		m_pTankPlayer->SetSpriteLinearVelocity(0, 0);
	}
	else if (strstr(szName, "enemy") != NULL)
	{
		Weapon* enemy = findWeaponByName(szName);
		enemy->SetSpriteLinearVelocity(0, 0);
		enemy->move();
	}
	else if (strstr(szName, "bullet") != NULL)
	{
		Bullet* bullet = (Bullet*)findWeaponByName(szName);
		if (bullet->getOwner() == 1 || bullet->getOwner() == 11||bullet->getOwner() == 12)
		{
			m_iPlayerBulletNum--;
		}
		bullet->setHP(0);
	}
}

void	CGameMain::addBullet(int dir, float x, float y,int owner)
{
	char* szName = CSystem::MakeSpriteName("bullet", m_iBulletNum);
	Bullet* pBullet = new Bullet(szName);
	pBullet->CloneSprite("bullet");
	pBullet->SetSpriteWorldLimit(WORLD_LIMIT_KILL, -26, -22, 26, 22);
	pBullet->SetSpritePosition(x, y);
	pBullet->SetSpriteCollisionActive(true,true);
	pBullet->move(dir);
	m_iBulletNum++;
	if (owner == 1)
	{
		pBullet->setOwner(1);
	}
	else
	{
		pBullet->setOwner(0);
	}

	m_vWeapon.push_back(pBullet);
}

void	CGameMain::addSpeedBullet(int dir, float x, float y, int owner)
{
	char* szName = CSystem::MakeSpriteName("speedbullet", m_iBulletNum);
	Bullet* pBullet = new Bullet(szName);
	pBullet->CloneSprite("bullet");
	pBullet->SetSpriteWorldLimit(WORLD_LIMIT_KILL, -26, -22, 26, 22);
	pBullet->SetSpritePosition(x, y);
	pBullet->SetSpriteCollisionActive(true, true);
	pBullet->setOwner(11);
	pBullet->moveSpeed(dir);
	m_iBulletNum++;
	m_vWeapon.push_back(pBullet);
}

void	CGameMain::addForceBullet(int dir, float x, float y, int owner)
{
	char* szName = CSystem::MakeSpriteName("forcebullet", m_iBulletNum);
	Bullet* pBullet = new Bullet(szName);
	pBullet->CloneSprite("bullet");
	pBullet->SetSpriteWorldLimit(WORLD_LIMIT_KILL, -26, -22, 26, 22);
	pBullet->SetSpritePosition(x, y);
	pBullet->SetSpriteCollisionActive(true, true);
	pBullet->setOwner(12);
	pBullet->moveForce(dir);
	m_iBulletNum++;
	m_vWeapon.push_back(pBullet);
}

void	CGameMain::addTankEnemy(float dTime)
{
	srand((unsigned)time(NULL));
	m_fEnemyCreateTime += dTime;
	if (m_fEnemyCreateTime > 2)
	{
		char* szName = CSystem::MakeSpriteName("enemy", m_iTankEnemyNum);
		TankEnemy* m_pTankEnemy = new TankEnemy(szName);

	//	int enemyType = CSystem::RandomRange(0, 3);
		int enemyType = rand() % 4;
		switch (enemyType)
		{
		case 0:
			m_pTankEnemy->CloneSprite("putong");
			m_pTankEnemy->init(0);
			break;
		case 1:
			m_pTankEnemy->CloneSprite("zhuangjia");
			m_pTankEnemy->init(1);
			break;
		case 2:
			m_pTankEnemy->CloneSprite("tuji");
			m_pTankEnemy->init(2);
			break;
		case 3:
			m_pTankEnemy->CloneSprite("nice");
			m_pTankEnemy->init(3);
			break;
		}
		m_iTankEnemyNum++;
		m_iMaxTanksNum--;
		m_vWeapon.push_back(m_pTankEnemy);
		m_fEnemyCreateTime = 0.0f;
		m_pAdd->PlaySoundA();
	}
}

void	CGameMain::loadMap(int level)
{
	char* szName;
	int tempMap[11][13];
	if (level == 1)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				tempMap[i][j] = g_iMap1[i][j];
			}
		}
	}
	else //if (level == 2)
	{
		for (int i = 0; i < 11; i++)
		{
			for (int j = 0; j < 13; j++)
			{
				tempMap[i][j] = g_iMap2[i][j];
			}
		}
	}
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < 13; j++)
		{
			float x, y;
			if (tempMap[i][j] == 1)
			{
				szName = CSystem::MakeSpriteName("muWall", j + i * 13 + i);
				Weapon* pWall = new Weapon(szName);
				pWall->CloneSprite("mu");
				pWall->SetSpriteCollisionActive(false, true);
				pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
				x = float(-24 + 4 * j);
				y = float(-20 + 4 * i);
				pWall->SetSpritePosition(x, y);
				m_vWeapon.push_back(pWall);
			}
			if (tempMap[i][j] == 2)
			{
				szName = CSystem::MakeSpriteName("haiWall", j + i * 13 + i);
				Weapon* pWall = new Weapon(szName);
				pWall->CloneSprite("hai");
				pWall->SetSpriteCollisionActive(false, true);
				pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
				x = float(-24 + 4 * j);
				y = float(-20 + 4 * i);
				pWall->SetSpritePosition(x, y);
				m_vWeapon.push_back(pWall);
			}
			if (tempMap[i][j] == 3)
			{
				szName = CSystem::MakeSpriteName("tieWall", j + i * 13 + i);
				Weapon* pWall = new Weapon(szName);
				pWall->CloneSprite("tie");
				pWall->SetSpriteCollisionActive(false, true);
				pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
				x = float(-24 + 4 * j);
				y = float(-20 + 4 * i);
				pWall->SetSpritePosition(x, y);
				m_vWeapon.push_back(pWall);
			}
			if (tempMap[i][j] == 4)
			{
				szName = CSystem::MakeSpriteName("diban", j + i * 13 + i);
				Weapon* pWall = new Weapon(szName);
				pWall->CloneSprite("diban");
				pWall->SetSpriteCollisionActive(false, false);
				pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
				x = float(-24 + 4 * j);
				y = float(-20 + 4 * i);
				pWall->SetSpritePosition(x, y);
				m_vWeapon.push_back(pWall);
			}
			if (tempMap[i][j] == 5)
			{
				szName = CSystem::MakeSpriteName("shuWall", j + i * 13 + i);
				Weapon* pWall = new Weapon(szName);
				pWall->CloneSprite("shu");
				pWall->SetSpriteCollisionActive(false, false);
				pWall->SetSpriteCollisionResponse(COL_RESPONSE_CUSTOM);
				x = float(-24 + 4 * j);
				y = float(-20 + 4 * i);
				pWall->SetSpritePosition(x, y);
				m_vWeapon.push_back(pWall);
			}
		}
	}
}

Weapon* CGameMain::findWeaponByName(const char* fName)
{
	for (unsigned int i = 0; i < m_vWeapon.size(); i++)
	{
		if (strcmp(fName, m_vWeapon[i]->GetName()) == 0)
		{
			return m_vWeapon[i];
		}
	}
}

void	CGameMain::delWeaponByName(const char* delName)
{
	vector<Weapon*>::iterator it = m_vWeapon.begin();
	for (; it != m_vWeapon.end();)
	{
		Weapon* weapon = *it;
		if (strcmp(delName, weapon->GetName()) == 0)
		{
			m_vWeapon.erase(it);
			weapon->DeleteSprite();
			delete weapon;
			break;
		}
		else
		{
			it++;
		}
	}
}

void	CGameMain::OnSpriteColSprite(const char* srcName, const char* tarName)
{
	Weapon* tarSprite = findWeaponByName(tarName);
	if (strstr(srcName, "bullet") != NULL)
	{
		if (strstr(tarName, "zhadan") == NULL
			&& strstr(tarName, "zanting") == NULL
			&& strstr(tarName, "star") == NULL)
		{
			Bullet* tmpBullet = (Bullet*)findWeaponByName(srcName);
			if (strstr(tarName, "bullet") != NULL)
			{
				Bullet* tmpBullet2 = (Bullet*)findWeaponByName(tarName);
				if ((tmpBullet->getOwner() == 1 || tmpBullet->getOwner() == 11 || tmpBullet->getOwner() == 12)
					&& tmpBullet2->getOwner() == 0)
				{
					m_iPlayerBulletNum--;
					m_pHit->PlaySoundA();
				}
			}
			if ((tmpBullet->getOwner() == 1 || tmpBullet->getOwner() == 11 || tmpBullet->getOwner() == 12)
				&& strstr(tarName, "enemy") != NULL)
			{
				if (tarSprite->getHP() == 1)
				{
					m_iScore++;
					m_iEnemy--;
					m_iMaxTanksNum++;
					//敌人所在位置产生爆炸
					TankEnemy* enemy = (TankEnemy*)tarSprite;
					float x = enemy->GetSpritePositionX();
					float y = enemy->GetSpritePositionY();
					enemy->createBoom(x, y);
					m_pBaoZha->PlaySoundA();
					if (enemy->getEnemyType() == 3)
					{
						//随机出现宝物
						x = (float)CSystem::RandomRange(-20, 20);
						y = (float)CSystem::RandomRange(-15, 15);
						srand((unsigned)time(NULL));
						int type = rand() % 3;
						enemy->createBaowu(x, y, type);
					}
				}
				if (tarSprite->getHP() == 2)
				{
					tarSprite->SetSpriteColorRed(123);
					tarSprite->SetSpriteColorBlue(123);
					tarSprite->SetSpriteColorGreen(123);
					m_pHit->PlaySoundA();
				}
				if (tarSprite->getHP() == 3)
				{
					tarSprite->SetSpriteColorRed(255);
					tarSprite->SetSpriteColorBlue(0);
					tarSprite->SetSpriteColorGreen(255);
					m_pHit->PlaySoundA();
				}

			}
			if (tmpBullet->getOwner() == 0 && strstr(tarName, "player") != NULL)
			{
				m_iLife--;
				if (m_iLife > 0)
				{
					TankPlayer* p = (TankPlayer*)tarSprite;
					float x = p->GetSpritePositionX();
					float y = p->GetSpritePositionY();
					p->createBoom(x, y);
					m_pBaoZha->PlaySoundA();
					m_pTankPlayer->setDir(0);
					m_pTankPlayer->SetSpritePosition(-8, 20);
					m_iPlayerBulletNum = 0;
					m_iPlayerBulletMode = 0;
				}
			}
			tmpBullet->OnSpriteColSprite(tarSprite);
		}
	}
	else if (strcmp(srcName, "myplayer") == 0)
	{
		SetPlayerBulletNum(0);
		if (strstr(tarName, "zhadan") != NULL)
		{
			deleteAllEnemyInScene();
			tarSprite->DeleteSprite();
			m_pBaoZha->PlaySoundA();
		}
		else if (strstr(tarName, "star") != NULL)
		{
			if (m_iPlayerBulletMode < 2)
			{
				m_iPlayerBulletMode++;//得到star，mode提升
			}
			tarSprite->DeleteSprite();
			m_pEat->PlaySoundA();
		}
		else if (strstr(tarName, "zanting") != NULL)
		{
			m_iZanTingColMessage = 1;//接收到暂停通知
			tarSprite->DeleteSprite();
			m_pEat->PlaySoundA();
		}
		else
		{
			m_pTankPlayer->OnSpriteColSprite(tarSprite);
		}
	}
	else if (strstr(srcName, "enemy") != NULL)
	{
		TankEnemy* tmpEnemy = (TankEnemy*)findWeaponByName(srcName);
		
		tmpEnemy->OnSpriteColSprite(tarSprite);
	}
}

void	CGameMain::deleteAllSprite()
{
	while (!m_vWeapon.empty())
	{
		vector<Weapon*>::iterator itr = m_vWeapon.begin();
		Weapon* w = *itr;
		m_vWeapon.erase(itr);
		w->DeleteSprite();
		delete w;
	}
}

void    CGameMain::deleteAllEnemyInScene()
{
	int currentEnemyCount = 0;
	for (unsigned int i = 0; i < m_vWeapon.size(); i++)
	{
		Weapon* w = m_vWeapon[i];
		if (strstr(w->GetName(), "enemy") != NULL)
		{
			currentEnemyCount++;
			w->setHP(0);
		}
	}
	m_iEnemy -= currentEnemyCount;
	m_iMaxTanksNum += currentEnemyCount;
	m_iScore += currentEnemyCount;
}

