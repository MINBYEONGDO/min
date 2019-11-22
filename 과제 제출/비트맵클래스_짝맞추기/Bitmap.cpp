
#include "Bitmap.h"
#include"resource.h"


Bitmap::Bitmap()
{
}

Bitmap::Bitmap(HDC hdc, HINSTANCE hInst, int CardType)
{
	m_bCardBack = true;
	m_bCardState = false;
	m_CardType = CardType;
	Init(hdc, hInst);
	m_CardNumber = 21;
}

void Bitmap::Init(HDC hdc, HINSTANCE hInst)
{
	int i = 0;
	if (m_CardType == DOG)
		i = IDB_BITMAP1;
	else if (m_CardType == TIGER)
		i = IDB_BITMAP2;
	else if (m_CardType == DUCK)
		i = IDB_BITMAP3;
	else if (m_CardType == ELEPHAT)
		i = IDB_BITMAP4;
	else if (m_CardType == COW)
		i = IDB_BITMAP5;
	else if (m_CardType == HORSE)
		i = IDB_BITMAP6;
	else if (m_CardType == CAT)
		i = IDB_BITMAP7;
	else if (m_CardType == MONKEY)
		i = IDB_BITMAP8;
	else if (m_CardType == FLOG)
		i = IDB_BITMAP9;
	else if (m_CardType == CHICKEN)
		i = IDB_BITMAP10;
	else if (m_CardType == BACKCARD)
		i = IDB_BITMAP11;
	MemDC = CreateCompatibleDC(hdc);
	m_pMyBitMap = LoadBitmap(hInst, MAKEINTRESOURCE(i));
	m_pOldBitMap = (HBITMAP)SelectObject(MemDC, m_pMyBitMap);

	BITMAP Bit_Info;
	GetObject(m_pMyBitMap, sizeof(Bit_Info), &Bit_Info);
	m_size.cx = Bit_Info.bmWidth;
	m_size.cy = Bit_Info.bmHeight;
}
void Bitmap::Draw(HDC hdc, int x, int y, bool back, int spX, int spY)
{
	if (back == false)
		BitBlt(hdc, x, y, m_size.cx, m_size.cy, MemDC, 0, 0, SRCCOPY);
	else if (back == true)
		BitBlt(hdc, x, y, m_size.cx, m_size.cy, MemDC, 0, 0, IDB_BITMAP11);
	//StretchBlt(hdc, x, y, m_size.cx * spX, m_size.cy * spY, MemDC, 0, 0, m_size.cx, m_size.cy, SRCCOPY);
}
void Bitmap::CardStateChange()
{
	if (m_bCardState == true)
		m_bCardState = false;
	else if (m_bCardState == false)
		m_bCardState = true;
}

void Bitmap::ReverseCard()
{
	if (m_bCardBack == true)
		m_bCardBack = false;
	else if (m_bCardBack == false)
		m_bCardBack = true;
}
void Bitmap::SetCardNumber(int Number)
{
	m_CardNumber = Number;
	m_bCardBack = true;
	m_bCardState = false;
}

void Bitmap::ResetCard()
{
	m_CardNumber = 21;
}
Bitmap::~Bitmap()
{
	SelectObject(MemDC, m_pOldBitMap);
	DeleteObject(m_pMyBitMap);
	DeleteDC(MemDC);
}