#pragma once
#include "D:\ϵͳ\Desktop\Tanker\Tanker\SourceCode\Header\commonclass.h"
class Tank :
	public CSprite
{
private:
	int HP;
//	int initX;
//	int initY;
	int direction;			//0��,1��,2��,3��
	float speedX;
	float speedY;

//	float countShellTime;	//�����ӵ�����ȴʱ��
//	float firingFrequency;	//���Ƶ��

	
	
public:
	//���캯��
	Tank(const char* szName);
	//get����
	int			getHP()						{ return HP; }
	int			getDir()					{ return direction; }
	float		getSpeedX()					{ return speedX; }
	float		getSpeedY()					{ return speedY; }
	//set����
	void		setHP(int hp)				{ HP = hp; }
	void		setDir(int dir)				{ direction = dir; }
	void		setSpeedX(float sX)			{ speedX = sX; }
	void		setSpeedY(float sY)			{ speedY = sY; }
	
};

