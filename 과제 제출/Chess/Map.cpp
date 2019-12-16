
#include "Map.h"


Map::Map()
{
	m_index = 0;
	m_iPlayer = 0;
}

void Map::SetMap(int index)
{
	m_pBitMap = BitmapManager::GetInstance()->GetImage(index);
}

void Map::SetMapData(int x, int y, float spX, float spY, bool checkPiece, int checkblack, int i, int j)
{
	m_ix = x;
	m_iy = y;
	m_fSpX = spX;
	m_fSpY = spY;
	m_bexitPiece = checkPiece;
	m_iPlayer = checkblack;
	m_Rect = { x,y,x + 75,y + 75 };
}

void Map::MapExitPiece(int Number, bool bresult, int iCase)
{
	if (bresult == false)
	{
		if (m_bexitPiece == false)
			m_bexitPiece = true;
		else if (m_bexitPiece == true)
			m_bexitPiece = false;
	}
	if (bresult == true)
	{
		if (iCase == 0)
		{
			if (m_bexitPiece == false)
				m_bexitPiece = true;
			else if (m_bexitPiece == true)
				m_bexitPiece = false;
		}
	}
}

void Map::MapChangeMapTeam(int Number, bool bresult, int iCase)
{
	if (bresult == false)
	{
		if (Number == 0)//검은색일때
		{
			if (m_iPlayer == 1)
				m_iPlayer = 0;
			else if (m_iPlayer == 0)
				m_iPlayer = 1;
		}
		else if (Number == 1)//흰색일때
		{
			if (m_iPlayer == 2)
				m_iPlayer = 0;
			else if (m_iPlayer == 0)
				m_iPlayer = 2;
		}
	}
	else if (bresult == true)
	{
		if (iCase == 0)//이동전의 좌표일때
		{
			if (Number == 0)//검은색일때
			{
				if (m_iPlayer == 1)
					m_iPlayer = 0;
				else if (m_iPlayer == 0)
					m_iPlayer = 1;
			}
			else if (Number == 1)//흰색일때
			{
				if (m_iPlayer == 2)
					m_iPlayer = 0;
				else if (m_iPlayer == 0)
					m_iPlayer = 2;
			}
		}
		else if (iCase == 1)
		{
			if (Number == 0)//검은색일때
			{
				if (m_iPlayer == 1)
					m_iPlayer = 0;
				else if (m_iPlayer == 0)
					m_iPlayer = 1;
				else if (m_iPlayer == 2)
					m_iPlayer = 1;
			}
			else if (Number == 1)//흰색일때
			{
				if (m_iPlayer == 2)
					m_iPlayer = 0;
				else if (m_iPlayer == 0)
					m_iPlayer = 2;
				else if (m_iPlayer == 1)
					m_iPlayer = 2;
			}
		}
	}
}

void Map::Draw(HDC hdc)
{
	m_pBitMap->Draw(hdc, m_ix, m_iy, m_fSpX, m_fSpY);
}
void  Map::CheckDraw(HDC hdc)
{
	m_pBitMap->CheckDraw(hdc, m_ix, m_iy, m_fSpX, m_fSpY);
}


Map::~Map()
{
}