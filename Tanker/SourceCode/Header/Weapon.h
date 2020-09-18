#pragma once
#include "CommonClass.h"

class Weapon :
	public CSprite
{
private:
	int					HP;
	int					direction;					//0ио,1ср,2об,3вС
//	int					m_iBaoType;					//0-zhadan,1-star,2-zanting

	float				speedX;
	float				speedY;

public:

	Weapon(const char* szName);
	~Weapon();

	int				getHP()						{ return HP; }
	int				getDir()					{ return direction; }
//	int				getBaoType()				{ return m_iBaoType; }
	float			getSpeedX()					{ return speedX; }
	float			getSpeedY()					{ return speedY; }
	
	void			setHP(int hp)				{ HP = hp; }
	void			setDir(int dir)				{ direction = dir; }
//	void			setBaoType(int type)		{ m_iBaoType = type; }
	void			setSpeedX(float sX)			{ speedX = sX; }
	void			setSpeedY(float sY)			{ speedY = sY; }

	bool			spriteIsDead();

	

	virtual void	init(){};
	virtual void	move(){};
	virtual void	move(float deltaTime){};
	virtual void	playerFire(){};
	virtual void    enemyFire(float deltaTime){};
	virtual void	OnSpriteColSprite(Weapon* sprite){};

};