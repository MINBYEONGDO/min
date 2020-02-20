

#pragma once
#include"Mecro.h"
#include"MissileManager.h"
#include"BitmapManager.h"
class Tank
{
private:
protected:
	int m_ix;
	int m_iy;
	RECT m_rect;
	RECT m_CheckRect;

	int m_Direction;
	int m_ilife;
	int m_ihealth;
	Bitmap* m_Bitmap;
	int m_BitmapNumber;
	MissileManager *MissileList;
public:
	Tank();
	virtual void Init() = 0;
	virtual void Draw(HDC hdc) = 0;
	virtual void Fire() = 0;
	virtual void CheckRectReset() = 0;
	virtual void Break() = 0;
	virtual void MissileChangeStateCruch(int Number, int CrushType) = 0;
	~Tank();
};
