#ifndef _LESSON_X_H_
#define _LESSON_X_H_

#include <Windows.h>
#include "Tank.h"
#include "TankPlayer.h"
#include "Bullet.h"
#include "TankEnemy.h"
#include <vector>

using namespace std;

class	CGameMain
{
private:
	int					m_iBulletNum;
	int					m_iEnemy;
	int					m_iGameState;				// 游戏状态，0：结束或者等待开始；1：初始化；2：游戏进行中
	int					m_iGameCount;
	int					m_iLife;
	int					m_iLevel;
	int					m_iMaxScore;
	int					m_iMaxTanksNum;
	int                 m_iPlayerBulletNum;			//0子弹消失，1子弹存在
	int					m_iPlayerBulletMode;		//0-普通子弹，1-子弹加速，2-子弹威力提升
	int					m_iScore;
	int					m_iTankEnemyNum;
	int					m_iZanTingColMessage;		//0-未检测到暂停通知

	float				m_fEnemyCreateTime;
	float				m_fGameTime;
	float				m_fGameWaitTime;
	
	CSprite*			m_pSplash;
	CSprite*			m_pStart;
	CSprite*			m_pGameOver;

	CTextSprite*		m_pScore;
	CTextSprite*		m_pMaxScore;
	CTextSprite*		m_pEnemy;
	CTextSprite*		m_pLife;
	CTextSprite*		m_pLevel;

	Weapon*				m_pAim_nor;					
	
	TankPlayer*			m_pTankPlayer;

	vector<Weapon*>		m_vWeapon;

	CSound*				m_pStartSound;
	CSound*				m_pFire;
	CSound*				m_pBaoZha;
	CSound*				m_pHit;
	CSound*				m_pAdd;
	CSound*				m_pEat;
	CSound*				m_pGameOverS;
	CSound*				m_pSuccess;

public:
	CGameMain();           
	~CGameMain();           
	
	int				GetGameState()								{ return m_iGameState; }
	int				GetGameCount()								{ return m_iGameCount; }
	int				GetPlayerLife()								{ return m_iLife; }
	int				GetMaxTanksNum()							{ return m_iMaxTanksNum; }
	int				GetPlayerBulletNum()						{ return m_iPlayerBulletNum; }
	int				GetZanTingMessage()							{ return m_iZanTingColMessage; }
	int				GetBulletMode()								{ return m_iPlayerBulletMode; }
	vector<Weapon*> GetWeapon()									{ return m_vWeapon; }
	
	void			SetWeapon(vector<Weapon*> vWeapon)			{ m_vWeapon = vWeapon; }
	void			SetPlayerBulletNum(int num)					{ m_iPlayerBulletNum = num; }
	void			SetMaxTanksNum(int maxTanks)				{ m_iMaxTanksNum = maxTanks; }
	void			SetZanTingMessage(int z)					{ m_iZanTingColMessage = z; }
	void			SetBulletMode(int m)						{ m_iPlayerBulletMode = m; }
	void			SetGameState(const int iState)	
	{				
		m_iGameState = iState;
		if (m_iGameState == 2)
		{
			m_iGameCount++;							
		}
	}

	void			GameMainLoop(float	fDeltaTime);
	void			GameInit();
	void			GameRun(float fDeltaTime);
	void			GameEnd();

	void			OnKeyDown(const int iKey, const bool bAltPress, const bool bShiftPress, const bool bCtrlPress);
	void			OnKeyUp(const int iKey);

	void			OnSpriteColSprite(const char* srcName, const char* tarName);
	void			OnSpriteColWorldLimit(const char* szName, const int iColSide);
	
	void			addBullet(int dir, float x, float y, int owner);
	void			addTankEnemy(float deltaTime);
	void			addSpeedBullet(int dir, float x, float y, int owner);
	void			addForceBullet(int dir, float x, float y, int owner);

	void			loadMap(int level);

	Weapon*			findWeaponByName(const char* findName);
	void			delWeaponByName(const char* delName);

	void			deleteAllSprite();
	void			deleteAllEnemyInScene();

};

extern CGameMain	g_GameMain;

#endif 