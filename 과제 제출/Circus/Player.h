
#pragma once
#include"Mecro.h"
#include"BitmapManager.h"

class Player
{
private:
	float m_ix;
	float m_iy;
	float m_jump_y;
	int m_life;
	int imageindex;
	bool m_bSurvival;
	int m_istate;

	int m_iScore;
	RECT m_Rect;

	float m_CurClock;
	float m_LastClock;
	Bitmap *m_playerMotionList[4];
public:
	Player();
	void Init();
	void playerMove(int Move, float Move_x);
	void playerJump();
	void playerJumping(float time);
	void playerDeath();
	void ChangeState(int Number);
	void UpdateScore(int ScoreType);
	void BonusScore(int Bonus);
	void playerReachEnd();
	void PlayerReset();
	void PlayerClear();
	void GameOver();
	void Draw(HDC hdc, HDC MemDC);
	float inline Getx()
	{
		return m_ix;
	}
	float inline Gety()
	{
		return m_iy;
	}
	int inline GetPlayerState()
	{
		return m_istate;//플레이어의 상태
	}//STOP 을 다른걸로 바꾸기
	int inline GetPlayerLife()
	{
		return m_life;
	}//생명갯수
	int inline GetScore()
	{
		return m_iScore;
	}//점수 //방식 변경하기
	RECT inline GetRect()
	{
		return m_Rect;
	}//충돌범위 출력
	~Player();
};