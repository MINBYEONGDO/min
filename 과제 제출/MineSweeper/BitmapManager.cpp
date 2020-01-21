#include "BitmapManager.h"

BitmapManager* BitmapManager::m_hThis = NULL;

BitmapManager::BitmapManager()
{
	BitmapNumber = 0;
	m_parrBitmap = new Bitmap[13];
}

void BitmapManager::Init(HWND hWnd, HDC hdc)//hdc2가 필요한가?
{
	TCHAR buf[256];
	TCHAR name[256];
	hdc = GetDC(hWnd);

	wsprintf(buf, "Mine//back.bmp");
	wsprintf(name, "back");
	m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
	BitmapNumber++;//0

	wsprintf(buf, "Mine//block.bmp");
	wsprintf(name, "block");
	m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
	BitmapNumber++;//1
	for (int i = 0; i < 9; i++)//2345678910
	{
		wsprintf(buf, "Mine//block_%d.bmp", i);
		wsprintf(name , "block_%d",i);
		m_parrBitmap[BitmapNumber].Init(hdc, buf , BitmapNumber);
		BitmapNumber++;
	}

	wsprintf(buf, "Mine//flag.bmp");
	wsprintf(name, "flag");
	m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
	BitmapNumber++;//11

	wsprintf(buf, "Mine//mine.bmp");
	wsprintf(name, "mine");
	m_parrBitmap[BitmapNumber].Init(hdc, buf, BitmapNumber);
	//12
	ReleaseDC(hWnd, hdc);
}
void BitmapManager::Release()
{
	for (int i = 0; i < 13; i++)
	{
		delete[i] m_parrBitmap;
		m_parrBitmap = { NULL };
	}
	delete(m_hThis);
}
BitmapManager::~BitmapManager()
{
}
