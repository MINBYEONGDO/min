#pragma once
#include"Mecro.h"
class Bitmap
{
private:
	HDC m_MemDC;
	HBITMAP m_Bitmap;
	HBITMAP m_OldBitmap;
	SIZE m_size;
	TCHAR m_Name;
public:
	void Init(HDC hdc, LPCSTR filename, int Number);
	void Draw(HDC MemDC, int x, int y , float spX = 1, float spY = 1);
	inline SIZE GetSize()
	{
		return m_size;
	}
	Bitmap();
	Bitmap(HDC hdc, LPCSTR FileName, int Number);
	~Bitmap();
};

