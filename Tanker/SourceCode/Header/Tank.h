#pragma once
#include "D:\系统\Desktop\Tanker\Tanker\SourceCode\Header\commonclass.h"
class Tank :
	public CSprite
{
private:
	int HP;
//	int initX;
//	int initY;
	int direction;			//0上,1右,2下,3左
	float speedX;
	float speedY;

//	float countShellTime;	//发射子弹的冷却时间
//	float firingFrequency;	//射击频率

	
	
public:
	//构造函数
	Tank(const char* szName);
	//get方法
	int			getHP()						{ return HP; }
	int			getDir()					{ return direction; }
	float		getSpeedX()					{ return speedX; }
	float		getSpeedY()					{ return speedY; }
	//set方法
	void		setHP(int hp)				{ HP = hp; }
	void		setDir(int dir)				{ direction = dir; }
	void		setSpeedX(float sX)			{ speedX = sX; }
	void		setSpeedY(float sY)			{ speedY = sY; }
	
};

