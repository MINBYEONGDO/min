
#include "Bitmap.h"



Bitmap::Bitmap()
{
}

Bitmap::Bitmap(HDC hdc, LPCSTR FileName, int Number)
{
	Init(hdc, FileName, Number);
}

void Bitmap::Init(HDC hdc, LPCSTR FileName, int Number)
{
	MemDC = CreateCompatibleDC(hdc);
	m_BitMap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);

	m_OldBitMap = (HBITMAP)SelectObject(MemDC, m_BitMap);
	BITMAP BitMap_Info;
	GetObject(m_BitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_size.cx = BitMap_Info.bmWidth;
	m_size.cy = BitMap_Info.bmHeight;
	m_BitmapNumber = Number;
}
void Bitmap::Draw(HDC hdc, int x, int y, float spX, float spY)
{
	//BitBlt(hdc, x, y, m_size.cx, m_size.cy, MemDC, 0, 0, SRCCOPY);
	StretchBlt(hdc, x, y, m_size.cx * spX, m_size.cy * spY, MemDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}
void Bitmap::CheckDraw(HDC hdc, int x, int y, float spX, float spY)
{
	StretchBlt(hdc, x, y, m_size.cx * spX, m_size.cy * spY, MemDC, 0, 0, m_size.cx, m_size.cy, Block_2);
}
void Bitmap::PieceDraw(HDC hdc, int x, int y, float spX, float spY)
{
	TransparentBlt(hdc, x, y, m_size.cx * spX, m_size.cy * spY, MemDC, 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
}
Bitmap::~Bitmap()
{
	SelectObject(MemDC, m_OldBitMap);
	DeleteObject(m_BitMap);
	DeleteDC(MemDC);
}