
#include "Bitmap.h"



Bitmap::Bitmap()
{
	m_image_x = 0;
	m_image_y = 0;
	siny = 0;
	cosx = 0;
	angle = 0;
	i = 0;
	j = 0;
	checkjump = false;
}

void Bitmap::Init(HWND hWnd, HDC hdc, HINSTANCE hInst)
{
	/*m_playerDC = CreateCompatibleDC(hdc);
	m_btPlayer = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0,
	 LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_btOldPlayer = (HBITMAP)SelectObject(m_playerDC, m_btPlayer);

	m_backDC = CreateCompatibleDC(hdc);
	m_btBack = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0,
	 LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_btOldBack = (HBITMAP)SelectObject(m_backDC, m_btBack);*/
	m_3DC = CreateCompatibleDC(hdc);
	m_bt3 = CreateCompatibleBitmap(hdc, 1024, 768);
	m_btOld3 = (HBITMAP)SelectObject(m_3DC, m_bt3);

	m_playerDC = CreateCompatibleDC(m_3DC);
	m_btPlayer = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_btOldPlayer = (HBITMAP)SelectObject(m_playerDC, m_btPlayer);

	m_backDC = CreateCompatibleDC(m_3DC);
	m_btBack = (HBITMAP)LoadImage(NULL, "back.bmp", IMAGE_BITMAP, 0, 0,
		LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_btOldBack = (HBITMAP)SelectObject(m_backDC, m_btBack);

	GetObject(m_btPlayer, sizeof(m_mapInfo), &m_mapInfo);

	m_size.cx = m_mapInfo.bmWidth;
	m_size.cy = m_mapInfo.bmHeight;
	ReleaseDC(hWnd, hdc);
}
void Bitmap::Draw(HDC hdc, int x, int y, int spX, int spY)
{
	BitBlt(m_3DC, 0, 0, 1024, 768, m_backDC, 0, 0, SRCCOPY);//배경
	//StretchBlt(hdc, 0, 0, 1024, 768, m_3DC, 0, 0, 102, 768, SRCCOPY);//배경
	if (SaveKey == NOT)
		TransparentBlt(m_3DC, x + m_image_x, y + m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if (SaveKey == LEFT)
		TransparentBlt(m_3DC, x + m_image_x, y + m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if (SaveKey == RIGHT)
		TransparentBlt(m_3DC, x + m_image_x, y + m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if (SaveKey == UP)
		TransparentBlt(m_3DC, x + m_image_x, y + m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if (SaveKey == DOWN)
		TransparentBlt(m_3DC, x + m_image_x, y + m_image_y, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	else if (SaveKey == JUMP)
		TransparentBlt(m_3DC, x + m_image_x, y + m_image_y - siny, m_size.cx / 4, m_size.cy / 4, m_playerDC, (m_size.cx / 4)*i, (m_size.cy / 4)*j, m_size.cx / 4, m_size.cy / 4, RGB(255, 0, 255));
	BitBlt(hdc, 0, 0, 1024, 768, m_3DC, 0, 0, SRCCOPY);
}
void Bitmap::ChangeLocation(key Key, HWND hWnd, int change_x, int change_y)
{
	m_image_x = m_image_x + change_x;
	m_image_y = m_image_y + change_y;
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
void Bitmap::Jump(HWND hWnd)
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
			InvalidateRect(hWnd, NULL, false);
		}
	}
}

Bitmap::~Bitmap()
{
}