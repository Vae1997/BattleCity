#pragma once
#include "commonclass.h"
#include "Weapon.h"
class Bullet :
	public Weapon
{
private:
	int m_iOwner;	//0��ʾ�з�̹�ˣ�1��ʾ�ҷ�̹��
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