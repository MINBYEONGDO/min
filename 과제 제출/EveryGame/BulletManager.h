
#pragma once
#include "Bullet.h"
#include "SingleTon.h"
class BulletManager
{
private:
	vector<Bullet*> m_vecBullet;
	Bullet* m_arr[20];
	int m_MaxBullet;// ÃÖ´ë °¹¼ö
	int m_CurBullet;//ÇöÀç °¹¼ö
	int m_LiveBullet;

public:
	void AddBullet(int player_x, int player_y);
	void Draw();
	void MoveBullet(float fETime);
	void BulletDelete(int Number);
	bool Contact(RECT player);
	void Release();
	BulletManager();
	~BulletManager();
};