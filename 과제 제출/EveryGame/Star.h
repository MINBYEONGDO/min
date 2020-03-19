
#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Player.h"
#include "BulletManager.h"
#include "TimeManager.h"
#include "Label.h"
class Star
{
private:
	float   m_fx;
	float   m_fy;
	float m_Movefx;// ÁÂÇ¥ º¯È­°ª 
	float m_Movefy;
	float m_Move;
	float m_Movea;
	bool m_bLive;
	int m_StarScore;
	int m_StarNumber;
	int m_StartDirection;
	RECT   m_rect;
	RECT m_CheckRect;
	JEngine::Label* LScore;
	JEngine::BitMap* m_pBitmap;
	JEngine::BitMap* m_pBitmap1;
	JEngine::BitMap* m_pBitmap2;
	JEngine::BitMap* m_pBitmap3;
public:
	Star();
	void Release();
	void Init(int GameType, int Number, int Hit, int Score, int playerx, int playery);
	void Move();
	void BitmapChange(int Hit);
	void Out();
	bool SideOut();
	void Draw();
	~Star();
	int GetScore()
	{
		return m_StarScore;
	}
	int GetNumber()
	{
		return m_StarNumber;
	}
	bool GetLive()
	{
		return m_bLive;
	}
	RECT GetRect()
	{
		return m_rect;
	}
};