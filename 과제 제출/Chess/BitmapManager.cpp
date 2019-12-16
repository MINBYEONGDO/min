
#include "BitmapManager.h"

BitmapManager* BitmapManager::m_hThis = NULL;

BitmapManager::BitmapManager()
{
	bitmapnumber = 0;
	m_parrBitMap = new Bitmap[16];
}

void BitmapManager::Init(HWND hWnd)
{
	TCHAR buf[256];
	TCHAR name[256];
	HDC hdc = GetDC(hWnd);
	for (int i = 0; i < 6; i++)
	{
		wsprintf(buf, "CHESS//block_b_0%d.bmp", i);
		wsprintf(name, "block_b_0%d", i);
		m_parrBitMap[i].Init(hdc, buf, bitmapnumber);
		bitmapnumber++;
	}
	for (int i = 0; i < 6; i++)
	{
		wsprintf(buf, "CHESS//block_w_0%d.bmp", i);
		wsprintf(name, "block_w_0%d", i);
		m_parrBitMap[i + 6].Init(hdc, buf, bitmapnumber);
		bitmapnumber++;
	}
	for (int i = 0; i < 4; i++)
	{
		wsprintf(buf, "CHESS//block0%d.bmp", i);
		wsprintf(name, "block0%d", i);
		m_parrBitMap[i + 12].Init(hdc, buf, bitmapnumber);
		bitmapnumber++;
	}
	ReleaseDC(hWnd, hdc);
}

void BitmapManager::Release()
{
	for (int i = 0; i < 16; i++)
	{
		delete[i] m_parrBitMap;
		m_parrBitMap = { NULL };
	}
	delete(m_hThis);
}

BitmapManager::~BitmapManager()
{
}