
#pragma once
#include"Mecro.h"
#include"Tank.h"
class Player : public Tank
{
private:
	int m_shieldCurClock;
	int m_ShieldLastClock;
	int m_shieldChangeCurClock;
	int m_ShieldChangeLastClock;
	int ShieldImageNumber;
	Bitmap* ShieldBitmap;
	bool m_bshield;
	bool m_bRespawn;
public:
	virtual void Init();
	void CheckMove(int MapType, int Direction, float m_fDeltaTime);
	void CheckRectReset();
	void Move(int MapState, int Move, float Moving);
	bool ContactObject(RECT ObjectRect);//���ʹ��� �̻��� �浹��?
	void ShieldTime();
	void NewStageSet();
	void NewGameSet();
	void RespawnReset();//��Ȱ�� �ٸ� ���ʹ̵�� �浹�� ������ �ʱ�ȭ�ؼ� �浹�����ϰ�
	void Fire();
	void MissileMove();
	void MissileChangeStateCruch(int Number, int CrushType);
	void Break();
	virtual void Draw(HDC hdc);
	void ImageChange(int Direction);
	int GetX()
	{
		return m_ix;
	}
	int Gety()
	{
		return m_iy;
	}
	int GetLife()
	{
		return m_ilife;
	}
	RECT GetCheckRect()
	{
		return m_CheckRect;
	}
	RECT GetRect()
	{
		return m_rect;
	}
	RECT GetMissileRect(int Number)
	{
		return MissileList->CheckRect(Number);
	}
	int GetMissileMax()
	{
		return MissileList->GetMax();
	}
	int GetMissileDirection(int Number)
	{
		return MissileList->GetDirection(Number);
	}
	bool GetRespawn()
	{
		return m_bRespawn;
	}
	bool GetShield()
	{
		return m_bshield;
	}
	Player();
	~Player();
};
