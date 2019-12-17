#include "Bitmap.h"



Bitmap::Bitmap()
{
	m_image_x=0;
	m_image_y=0;
	siny = 0;
	cosx = 0;
	angle = 0;
	i = 0;
	j = 0;
	checkjump= false;
}

void Bitmap::Init(HDC hdc, HINSTANCE hInst)
{
	m_playerDC = CreateCompatibleDC(hdc);
	m_btPlayer = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_btOldPlayer = (HBITMAP)SelectObject(m_playerDC, m_btPlayer);

	m_backDC = CreateCompatibleDC(hdc);
	m_btBack = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_btOldBack = (HBITMAP)SelectObject(m_backDC, m_btBack);

	GetObject(m_btPlayer, sizeof(m_mapInfo), &m_mapInfo);

	m_size.cx = m_mapInfo.bmWidth;
	m_size.cy = m_mapInfo.bmHeight;
}
void Bitmap::Draw(HDC hdc, int x, int y,int spX, int spY)
{
	StretchBlt(hdc, 0, 0, 1024, 768, m_backDC, 0, 0, 102, 768, SRCCOPY);//���
	if (SaveKey == NOT)
		TransparentBlt(hdc, x + m_image_x, y + m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if(SaveKey == LEFT)
		TransparentBlt(hdc, x+m_image_x, y+m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if (SaveKey == RIGHT)
		TransparentBlt(hdc, x + m_image_x, y + m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if (SaveKey == UP)
		TransparentBlt(hdc, x + m_image_x, y + m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if (SaveKey == DOWN)
		TransparentBlt(hdc, x + m_image_x, y + m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if (SaveKey == JUMP)
		TransparentBlt(hdc, x + m_image_x, y + m_image_y - siny, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
}
void Bitmap::ChangeLocation(key Key,HWND hWnd,int change_x, int change_y)
{
	m_image_x = m_image_x+change_x;
	m_image_y = m_image_y+change_y;
	SaveKey = Key;
	if (Key == LEFT)
	{
		if (i == 3)
			i = 0;
		else
			i++;
		j = 2;
	}
	else if (Key == RIGHT)
	{
		if (i == 3)
			i = 0;
		else
			i++;
		j = 3;
	}
	else if (Key == UP)
	{
		if (i == 3)
			i = 0;
		else
			i++;
		j = 1;
	}
	else if (Key == DOWN)
	{
		if (i == 3)
			i = 0;
		else
			i++;
		j = 0;
	}
		InvalidateRect(hWnd, NULL, false);
}
void Bitmap::Jump( HWND hWnd)
{
	if (SaveKey == JUMP)
	{
		checkjump = true;
		if (checkjump == true)
		{
			if (angle < 180)
			{
				siny = sin((angle) / 57.3) * 50;
				angle++;
			}
			else if (angle >= 180)
			{
				angle = 0;
				checkjump = false;
				SaveKey = NOT;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
	}
}

Bitmap::~Bitmap()
{
}
