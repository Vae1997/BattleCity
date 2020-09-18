#pragma once
#include "commonclass.h"
#include "Weapon.h"
class Bullet :
	public Weapon
{
private:
	int m_iOwner;	//0表示敌方坦克，1表示我方坦克
public:
	Bullet(const char* szName);
	~Bullet();

	int getOwner()				{ return m_iOwner; }

	void setOwner(int owner)	{ m_iOwner = owner; }

	void move(int iDir);
	void moveSpeed(int);
	void moveForce(int);

	void OnSpriteColSprite(Weapon* sprite);
};