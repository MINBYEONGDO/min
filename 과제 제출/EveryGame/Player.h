#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "TimeManager.h"
class Player
{
private:
	float   m_fx;
	float   m_fy;
	float   m_fSpeedX;
	bool m_bLive;
	int m_ExplosionNumber;
	int m_Score;
	RECT   m_rect0;//赣府
	RECT m_rect1;//朝俺
	RECT m_rect2;//个烹
	RECT m_rect3;//部府
	RECT m_CheckRect0;
	RECT m_CheckRect1;
	RECT m_CheckRect2;
	RECT m_CheckRect3;
	JEngine::BitMap* m_pBitmap;
	JEngine::TimeManager* m_pTimer;
	JEngine::RECT m_Rect;
public:
	void Init();
	void RectInit();
	void TimeScore();
	void StarScore(int Score);
	void Input(float fETime, int Number);
	void PlayerDeath();
	void ChangeExplosionBitmap();
	void PlayerReborn();
	void Draw();
	void ScoreReset();
	int Getx()
	{
		return m_fx;
	}
	int Gety()
	{
		return m_fy;
	}
	RECT GetPlayerRect(int Number)
	{
		if (Number == 0)
			return m_rect0;
		else if (Number == 1)
			return m_rect1;
		else if (Number == 2)
			return m_rect2;
		else if (Number == 3)
			return m_rect3;
	}
	int GetScore()
	{
		return m_Score;
	}
	bool GetPlayerLive()
	{
		return m_bLive;
	}
	Player();
	~Player();
};