#include "BitmapManager.h"

BitmapManager* BitmapManager::m_hThis = NULL;

BitmapManager::BitmapManager()
{
	BitmapNumber = 0;
	m_parrBitmap = new Bitmap[47];
}

void BitmapManager::Init(HWND hWnd, HDC hdc)
{
	TCHAR buf[256];
	TCHAR name[256];
	hdc = GetDC(hWnd);
	
	for (int i = 0; i < 10; i++)
	{
		wsprintf(buf, "BattleCity//block0%d.bmp", i);
		wsprintf(name, "block0%d", i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	for (int i = 10; i < 16; i++)
	{
		wsprintf(buf, "BattleCity//block%d.bmp", i);
		wsprintf(name, "block%d", i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	for (int i = 0; i < 3; i++)
	{
		wsprintf(buf, "BattleCity//e_down_0%d.bmp",i);
		wsprintf(name, "e_down_0%d",i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	for (int i = 0; i < 3; i++)
	{
		wsprintf(buf, "BattleCity//e_left_0%d.bmp", i);
		wsprintf(name, "e_left_0%d", i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	for (int i = 0; i < 3; i++)
	{
		wsprintf(buf, "BattleCity//e_right_0%d.bmp", i);
		wsprintf(name, "e_right_0%d", i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	for (int i = 0; i < 3; i++)
	{
		wsprintf(buf, "BattleCity//e_up_0%d.bmp", i);
		wsprintf(name, "e_up_0%d", i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	wsprintf(buf, "BattleCity//enemy_icon.bmp");
	wsprintf(name, "enemy_icon");
	m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
	BitmapNumber++;
	wsprintf(buf, "BattleCity//player_icon.bmp");
	wsprintf(name, "player_icon");
	m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
	BitmapNumber++;
	wsprintf(buf, "BattleCity//Stage_icon.bmp");
	wsprintf(name, "stage_icon");
	m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
	BitmapNumber++;
	for (int i = 0; i < 5; i++)
	{
		wsprintf(buf, "BattleCity//explosion_0%d.bmp",i);
		wsprintf(name, "explosion_0%d", i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	for (int i = 0; i < 2; i++)
	{
		wsprintf(buf, "BattleCity//shield_0%d.bmp", i);
		wsprintf(name, "shield_0%d",i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	wsprintf(buf, "BattleCity//missile_00.bmp");
	wsprintf(name, "missile");
	m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
	BitmapNumber++;
	for (int i = 0; i < 2; i++)
	{
		wsprintf(buf, "BattleCity//tank_down_0%d.bmp",i);
		wsprintf(name, "tank_down_0%d.bmp",i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	for (int i = 0; i < 2; i++)
	{
		wsprintf(buf, "BattleCity//tank_left_0%d.bmp", i);
		wsprintf(name, "tank_left_0%d.bmp", i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	for (int i = 0; i < 2; i++)
	{
		wsprintf(buf, "BattleCity//tank_right_0%d.bmp", i);
		wsprintf(name, "tank_right_0%d.bmp", i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
	for (int i = 0; i < 2; i++)
	{
		wsprintf(buf, "BattleCity//tank_up_0%d.bmp", i);
		wsprintf(name, "tank_up_0%d.bmp", i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
		BitmapNumber++;
	}
}
void BitmapManager::Release()
{
	for (int i = 0; i < 46; i++)
	{
		delete[i] m_parrBitmap;
		m_parrBitmap = NULL;
	}
	delete m_hThis;
}
BitmapManager::~BitmapManager()
{
}
