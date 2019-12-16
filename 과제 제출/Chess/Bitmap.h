
#pragma once
#include"Mecro.h"
class Bitmap
{
private:
	HDC MemDC;
	HBITMAP m_BitMap;
	HBITMAP m_OldBitMap;
	SIZE m_size;
	TCHAR m_Name[256];
	int m_BitmapNumber;
public:
	void Init(HDC hdc, LPCSTR FileName, int Number);
	void Draw(HDC hdc, int x, int y, float spX, float spY);
	void CheckDraw(HDC hdc, int x, int y, float spX, float spY);
	void PieceDraw(HDC hdc, int x, int y, float spX, float spY);
	inline SIZE GetSize()
	{
		return m_size;
	}
	Bitmap();
	Bitmap(HDC hdc, LPCSTR FileName, int Number);
	~Bitmap();
};