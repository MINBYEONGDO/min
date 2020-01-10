#pragma once
#include<Windows.h>
#include"Bitmap.h"

class BitmapManager
{
private:
	HDC MemDC[1];//전체 그리기, 플레이어, 장애물, 배경
	HBITMAP m_BitMap[1];
	HBITMAP m_OldBitmap[1];
	Bitmap* m_parrBitMap;
	static BitmapManager* m_hThis;
	int bitmapnumber;
public:
	static BitmapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitmapManager;
		return m_hThis;
	}
	Bitmap* GetImage(int index)
	{
		return &m_parrBitMap[index];
	}
	void Release();
	void Init(HWND hWnd, HDC hdc, HDC hdc2);
	BitmapManager();
	~BitmapManager();
};