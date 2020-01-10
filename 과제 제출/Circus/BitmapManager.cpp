

#include "BitmapManager.h"

BitmapManager* BitmapManager::m_hThis = NULL;

BitmapManager::BitmapManager()
{
	bitmapnumber = 0;
	m_parrBitMap = new Bitmap[28];
}

void BitmapManager::Init(HWND hWnd, HDC hdc, HDC hdc2)
{
	TCHAR buf[256];
	TCHAR name[256];
	hdc = GetDC(hWnd);
	for (int i = 0; i < 3; i++)//012
	{
		wsprintf(buf, "Circus//player%d.bmp", i);
		wsprintf(name, "player%d", i);
		m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
		bitmapnumber++;
	}
	wsprintf(buf, "Circus//die.bmp");
	wsprintf(name, "die");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	for (int i = 0; i < 2; i++)
	{

		wsprintf(buf, "Circus//front%d.bmp", i);
		wsprintf(name, "front%d", i);
		m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
		bitmapnumber++;
	}
	for (int i = 0; i < 3; i++)
	{
		wsprintf(buf, "Circus//star%d.bmp", i);
		wsprintf(name, "star%d", i);
		m_parrBitMap[bitmapnumber].Init(hdc2, buf, bitmapnumber);
		bitmapnumber++;
	}//별 6,7,8
	 //불고리
	wsprintf(buf, "Circus//enemy.bmp");
	wsprintf(name, "enemy");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//enemy1.bmp");
	wsprintf(name, "enemy1");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;

	wsprintf(buf, "Circus//enemy_b.bmp");
	wsprintf(name, "enemy_b");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//enemy_1b.bmp");
	wsprintf(name, "enemy_1b");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;

	wsprintf(buf, "Circus//enemy_l.bmp");
	wsprintf(name, "enemy_l");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//enemy_f.bmp");
	wsprintf(name, "enemy_f");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//enemy_1f.bmp");
	wsprintf(name, "enemy_1f");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;

	wsprintf(buf, "Circus//enemy_l_b.bmp");
	wsprintf(name, "enemy_lb");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//enemy_l_f.bmp");
	wsprintf(name, "enemy_1f");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	//뒷배경
	wsprintf(buf, "Circus//back.bmp");
	wsprintf(name, "back");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//back_deco.bmp");
	wsprintf(name, "back_deco");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//back_normal.bmp");
	wsprintf(name, "back_noraml");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//back_normal2.bmp");
	wsprintf(name, "back_noraml2");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	//기타 오브젝트
	wsprintf(buf, "Circus//end.bmp");
	wsprintf(name, "end");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//cash.bmp");
	wsprintf(name, "cash");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//miter.bmp");
	wsprintf(name, "miter");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	wsprintf(buf, "Circus//Icon.bmp");
	wsprintf(name, "Life");
	m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
	bitmapnumber++;
	for (int i = 0; i < 2; i++)
	{
		wsprintf(buf, "Circus//win%d.bmp", i + 1);
		wsprintf(name, "win%d", i + 1);
		m_parrBitMap[bitmapnumber].Init(hdc, buf, bitmapnumber);
		bitmapnumber++;
	}
	ReleaseDC(hWnd, hdc);
}



void BitmapManager::Release()
{
	for (int i = 0; i < 28; i++)
	{
		delete[i] m_parrBitMap;
		m_parrBitMap = { NULL };
	}
	delete(m_hThis);
}
BitmapManager::~BitmapManager()
{
}