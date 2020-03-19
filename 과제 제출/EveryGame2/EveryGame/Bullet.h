
#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "time.h"
class Bullet
{
private:
	float   m_fx;
	float   m_fy;
	float m_Movefx;// ÁÂÇ¥ º¯È­°ª 
	float m_Movefy;
	float m_Move;
	float m_Movea;
	bool m_bLive;
	RECT   m_rect;
	int m_BulletNumber;
	int m_StartDirection;
	JEngine::BitMap* m_pBitmap;
public:
	void Init(int Number, int player_x, int player_y);
	void Move(float fETime);
	void Out();//È­¸é¿¡¼­ ¹þ¾î³µÀ»¶§
	bool SideOut();
	void Draw();
	float Getx()
	{
		return m_fx;
	}
	float Gety()
	{
		return m_fy;
	}
	int GetBulletNumber()
	{
		return m_BulletNumber;
	}
	bool GetBulletLive()
	{
		return m_bLive;
	}
	RECT GetBulletRect()
	{
		return m_rect;
	}
	Bullet();
	~Bullet();
};