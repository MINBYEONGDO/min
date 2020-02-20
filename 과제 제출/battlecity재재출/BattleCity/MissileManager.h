

#pragma once
#include"Mecro.h"
#include"missile.h"
class MissileManager
{
private:
	missile *MissileList;
	missile *m_pMissiletmp;
	int m_Max;
public:
	void Init(int Tank_x, int Tank_y, int Tank_Direction);
	void Move();
	void ReNumber();
	void Explosion(int Number, int CrushType);
	void ExplosionEvent();
	void Crush();
	void ChangeStateCrush(int Number);
	RECT CheckRect(int Number);
	int GetDirection(int Number);
	void Draw(HDC hdc);
	void Release();
	inline int GetMax()
	{
		return m_Max;
	}
	MissileManager();
	~MissileManager();
};