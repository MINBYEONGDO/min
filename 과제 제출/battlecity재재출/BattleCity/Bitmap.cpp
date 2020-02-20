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
	m_MemDC = CreateCompatibleDC(hdc);
	m_Bitmap = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_Bitmap);

	BITMAP BitMap_Info;
	GetObject(m_Bitmap, sizeof(BitMap_Info), &BitMap_Info);
	m_size.cx = BitMap_Info.bmWidth;
	m_size.cy = BitMap_Info.bmHeight;
}
void Bitmap::Draw(HDC hdc, int x, int y, float spX, float spY)
{
	
	TransparentBlt(hdc, x, y, m_size.cx*spX, m_size.cy*spY, m_MemDC, 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
}

void Bitmap::PlayerGroundDraw(HDC hdc)
{
	BitBlt(hdc, 100, 100, 496, 468, m_MemDC, 0, 0,BLACKNESS);
}
void Bitmap::BackGroundDraw(HDC hdc)
{
	HBRUSH MyBrush, OldBrush;
	MyBrush = CreateSolidBrush(RGB(80, 80, 80));//È¸»ö
	OldBrush = (HBRUSH)SelectObject(hdc, MyBrush);
	BitBlt(hdc, 0, 0, 700, 700, m_MemDC, 0, 0, PATCOPY);
	SelectObject(hdc, OldBrush);
	DeleteObject(MyBrush);
}

Bitmap::~Bitmap()
{
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_Bitmap);
	DeleteDC(m_MemDC);
}