#pragma once
#include<Windows.h>
class Bitmap
{
private:
	HDC MemDC1;//전체 그리기, 플레이어, 장애물, 배경
	HBITMAP m_BitMap1;
	HBITMAP m_OldBitmap1;
	SIZE m_size;
	TCHAR m_Name;
public:
	void Init(HDC hdc, LPCSTR FileName, int Number);
	void Draw(HDC hdc, HDC MemDC, int x, int y, float spX = 1, float spY = 1);
	inline SIZE GetSize()
	{
		return m_size;
	}
	Bitmap();
	Bitmap(HDC hdc, LPCSTR FileName, int Number);
	~Bitmap();
};
