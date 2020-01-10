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


	MemDC1 = CreateCompatibleDC(hdc);
	m_BitMap1 = (HBITMAP)LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0
		, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitmap1 = (HBITMAP)SelectObject(MemDC1, m_BitMap1);

	BITMAP BitMap_Info;
	GetObject(m_BitMap1, sizeof(BitMap_Info), &BitMap_Info);
	m_size.cx = BitMap_Info.bmWidth;
	m_size.cy = BitMap_Info.bmHeight;
}


void Bitmap::Draw(HDC hdc, HDC MemDC, int x, int y, float spX, float spY)
{
	TransparentBlt(MemDC, x, y, m_size.cx * spX, m_size.cy * spY, MemDC1, 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
}

Bitmap::~Bitmap()
{
	SelectObject(MemDC1, m_OldBitmap1);
	DeleteObject(m_BitMap1);
	DeleteDC(MemDC1);
}
