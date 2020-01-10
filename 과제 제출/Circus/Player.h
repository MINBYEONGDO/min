
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
		return m_istate;//�÷��̾��� ����
	}//STOP �� �ٸ��ɷ� �ٲٱ�
	int inline GetPlayerLife()
	{
		return m_life;
	}//������
	int inline GetScore()
	{
		return m_iScore;
	}//���� //��� �����ϱ�
	RECT inline GetRect()
	{
		return m_Rect;
	}//�浹���� ���
	~Player();
};