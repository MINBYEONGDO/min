
#include "Map.h"

Map::Map()
{
	m_ix = 0;
	m_iy = 0;
	m_MapNumber = 0;
	m_Rect.bottom = 0;
	m_Rect.top = 0;
	m_Rect.left = 0;
	m_Rect.right = 0;
	m_MapType = 0;
	//m_iCrushDirection = NON;
	m_bExist = false;
	m_bBreak = false;
	m_bContect = false;
	m_bContectMissile = false;
	m_bIce = false;
	m_End = false;
}

void Map::Init(int xline, int yline)
{
	m_ix = xline * 33 + 100;
	m_iy = yline * 26 + 100;
	m_MapNumber++;
	if (m_MapType == 2)
	{
		m_Rect.bottom = m_iy + 13;
		m_Rect.top = m_iy + 0;
		m_Rect.left = m_ix + 0;
		m_Rect.right = m_ix + 33;
	}
	else if (m_MapType == 3)
	{
		m_Rect.bottom = m_iy + 25;
		m_Rect.top = m_iy + 0;
		m_Rect.left = m_ix + 0;
		m_Rect.right = m_ix + 16;
	}
	else if (m_MapType == 4)
	{
		m_Rect.bottom = m_iy + 25;
		m_Rect.top = m_iy + 12;
		m_Rect.left = m_ix + 0;
		m_Rect.right = m_ix + 33;
	}
	else if (m_MapType == 5)
	{
		m_Rect.bottom = m_iy + 25;
		m_Rect.top = m_iy + 0;
		m_Rect.left = m_ix + 16;
		m_Rect.right = m_ix + 33;
	}
	else if (m_MapType == 10)
	{
		m_Rect.bottom = m_iy + 13;
		m_Rect.top = m_iy + 0;
		m_Rect.left = m_ix + 0;
		m_Rect.right = m_ix + 33;
	}
	else if (m_MapType == 11)
	{
		m_Rect.bottom = m_iy + 25;
		m_Rect.top = m_iy + 0;
		m_Rect.left = m_ix + 16;
		m_Rect.right = m_ix + 33;
	}
	else if (m_MapType == 12)
	{
		m_Rect.bottom = m_iy + 25;
		m_Rect.top = m_iy + 12;
		m_Rect.left = m_ix + 0;
		m_Rect.right = m_ix + 33;
	}
	else if (m_MapType == 13)
	{
		m_Rect.bottom = m_iy + 26;
		m_Rect.top = m_iy + 0;
		m_Rect.left = m_ix + 0;
		m_Rect.right = m_ix + 16;
	}
	else if (m_MapType == 14)
	{
		m_Rect.bottom = m_iy + 25;
		m_Rect.top = m_iy + 0;
		m_Rect.left = m_ix +0;
		m_Rect.right = m_ix + 33;
	}
	else
	{
		m_Rect.bottom = m_iy + 25;
		m_Rect.top = m_iy + 0;
		m_Rect.left = m_ix + 0;
		m_Rect.right = m_ix + 33;
	}
}
void Map::FileDataLoad(int MapData)
{
	if (MapData != 0)//빈공간 빼고는 다 존재여부 true
		m_bExist = true;
	if ((MapData >= 1 && MapData <= 5) || (MapData >= 8 && MapData <= 12))//탱크가 못 지나가는 비트맵
		m_bContect = true;
	if ((MapData >= 1 && MapData <= 5))//미사일로 부셔질 수 있는 블록
		m_bBreak = true;
	if ((MapData >= 1 && MapData <= 5) || (MapData >= 9 && MapData <= 12))//미사일과 충돌하는 비트맵들
		m_bContectMissile = true;
	if (MapData == 6)
		m_bIce = true;
	if (MapData == 14)
	{
		m_End = true;
		m_bBreak = true;
		m_bContectMissile =true;
	}
	m_MapType = MapData;
	m_Bitmap = BitmapManager::GetInstance()->GetImange(MapData - 1);

}

void  Map::BreakBlock(int Direction, int tank)
{
	if (m_MapType == 14 && tank == ENERY)
	{
		m_End = false;
		m_MapType = 14;
		m_Rect.bottom = 0;
		m_Rect.left = 0;
		m_Rect.right = 0;
		m_Rect.top = 0;
	}
	else if (Direction == UP && m_MapType != 14)
	{
		if (m_MapType == 1)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(1);
			m_MapType = 2;
			m_Rect.bottom = m_iy + 13;
			m_Rect.top = m_iy + 0;
			m_Rect.left = m_ix + 0;
			m_Rect.right = m_ix + 33;
		}
		else
		{
			m_MapType = 0;
			m_Rect.bottom = 0;
			m_Rect.left = 0;
			m_Rect.right = 0;
			m_Rect.top = 0;
		}
	}
	else if (Direction == DOWN && m_MapType != 14)
	{
		if (m_MapType == 1)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(3);
			m_MapType = 4;
			m_Rect.bottom = m_iy + 26;
			m_Rect.top = m_iy + 12;
			m_Rect.left = m_ix + 0;
			m_Rect.right = m_ix + 33;
		}
		else
		{
			m_MapType = 0;
			m_Rect.bottom = 0;
			m_Rect.left = 0;
			m_Rect.right = 0;
			m_Rect.top = 0;
		}
	}
	else if (Direction == LEFT && m_MapType != 14)
	{
		if (m_MapType == 1)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(2);
			m_MapType = 3;
			m_Rect.bottom = m_iy + 26;
			m_Rect.top = m_iy + 0;
			m_Rect.left = m_ix + 0;
			m_Rect.right = m_ix + 16;
		}
		else
		{
			m_MapType = 0;
			m_Rect.bottom = 0;
			m_Rect.left = 0;
			m_Rect.right = 0;
			m_Rect.top = 0;
		}
	}
	else if (Direction == RIGHT && m_MapType != 14)
	{
		if (m_MapType == 1)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(4);
			m_MapType = 5;
			m_Rect.bottom = m_iy + 26;
			m_Rect.top = m_iy + 0;
			m_Rect.left = m_ix + 16;
			m_Rect.right = m_ix + 33;
		}
		else
		{
			m_MapType = 0;
			m_Rect.bottom = 0;
			m_Rect.left = 0;
			m_Rect.right = 0;
			m_Rect.top = 0;
		}
	}
}

void Map::DrawMap(HDC hdc)
{
	if (m_MapType != 0)
	{
		m_Bitmap->Draw(hdc, m_ix, m_iy);
	}
}
Map::~Map()
{
}
