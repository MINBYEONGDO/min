
#pragma once
#include"Mecro.h"
#include"Bitmap.h"
#include"BitmapManager.h"
class Interface
{
private:
	Bitmap* m_pBitmap;
	int m_ix;
	int m_iy;
public:
	void SetBitmap(int index);
	void Draw(HDC hdc, HDC MemDC, int x, int y);
	Interface();
	~Interface();
};