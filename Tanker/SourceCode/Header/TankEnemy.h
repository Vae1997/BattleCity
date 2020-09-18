#pragma once
#include "Tank.h"
#include "Weapon.h"
class TankEnemy :
	public Weapon
{
private:
	
	int					m_iEnemyType;				//0普通，1装甲，2突击,3宝物坦克
	int					m_iBaowuNum;

	float				m_fChangeDirTime;
	float				m_fBulletCreateTime;
	float				m_fStopTime;

	CSprite*			m_pEnemyBoom;
	
	Weapon*				m_pZhaDan;
	Weapon*				m_pStar;
	Weapon*				m_pZanTing;

public:
	TankEnemy(const char* enemyName);
	~TankEnemy();

	int		getEnemyType()				{ return m_iEnemyType; }
	void    setEnemyType(int type)		{ m_iEnemyType = type; }

	float	getcdTime()					{ return m_fChangeDirTime; }
	void	setcdTime(float time)		{ m_fChangeDirTime = time; }

	void init(int type);
	void move();
	void move(float time);				
	void enemyFire(float bcTime);
	void createBoom(float x,float y);
	void createBaowu(float x, float y,int type);

	void OnSpriteColSprite(Weapon* s);

	void			stopMove(float time);
};