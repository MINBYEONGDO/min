#include "Bitmap.h"

Bitmap::Bitmap()
{
}
Bitmap::Bitmap(HDC hdc, LPCSTR filename, int Number)
{
	Init(hdc, filename, Number);
}

void Bitmap::Init(HDC hdc, LPCSTR filename, int Number)
{
	m_MemDC = CreateCompatibleDC(hdc);
	m_Bitmap = (HBITMAP)LoadImage(NULL, filename, IMAGE_BITMAP,0,0
	 ,LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_OldBitmap = (HBITMAP)SelectObject(m_MemDC, m_Bitmap);

	BITMAP BitMap_Info;
	GetObject(m_Bitmap, sizeof(BitMap_Info), &BitMap_Info);
	m_size.cx = BitMap_Info.bmWidth;
	m_size.cy = BitMap_Info.bmHeight;
}
void Bitmap::Draw(HDC MemDC, int x, int y, float spX, float spY)
{
	TransparentBlt(MemDC, x, y, m_size.cx*spX, m_size.cy*spY, m_MemDC, 0, 0, m_size.cx, m_size.cy, RGB(255, 0, 255));
}

Bitmap::~Bitmap()
{
	SelectObject(m_MemDC, m_OldBitmap);
	DeleteObject(m_Bitmap);
	DeleteDC(m_MemDC);
}
