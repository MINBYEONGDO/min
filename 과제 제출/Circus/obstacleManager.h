
#pragma once
#include"Mecro.h"
#include"obstacle.h"
class obstacleManager
{
private:
	Ring *FireRing;
	Front *FireFront;
	End *m_End;
	Money *m_Money;
	int m_imageChange;

	//시간측정용
	float m_CurClock;
	float m_LastClock;
public:
	void Init();
	void SetBitmap();
	bool SearchPoint(float player_x);
	void Draw(HDC hdc, HDC MemDC, int Move, int Number);
	bool CheckRect(int type, RECT playerRect);
	bool CheckMoney(RECT playerRect);
	void UpdateRect(float Move);
	bool ObstacleGetx(int Move);
	obstacleManager();
	~obstacleManager();
};