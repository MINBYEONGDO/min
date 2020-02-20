
#include "MapManager.h"

MapManager::MapManager()
{
}
void MapManager::Init(int Stage, HWND hWnd)
{
	SendMessage(hWnd, 101, 0, Stage);
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			MapList[i][j].Init(j, i);
		}
	}
	//#define FILELOAD 101 
}
void MapManager::FileDataLoad(int x, int y, int Data)
{
	MapList[y][x].FileDataLoad(Data);
}

bool MapManager::ContactIceBlock(RECT playerrect)
{
	RECT rect;
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (MapList[i][j].GetIce() == true)
			{
				if (IntersectRect(&rect, &MapList[i][j].GetRect(), &playerrect) == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool MapManager::ContactBlock(RECT playerrect)
{
	RECT rect;
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (MapList[i][j].GetContect() == true)
			{
				if (IntersectRect(&rect, &MapList[i][j].GetRect(), &playerrect) == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool MapManager::CrushBlock_Missile(RECT Missilerect, int Direction, int Number)
{
	RECT rect;
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (MapList[i][j].GetContectMissile() == true)
			{
				if (IntersectRect(&rect, &MapList[i][j].GetRect(), &Missilerect) == true)
				{
					if (MapList[i][j].GetBreakBlock() == true)
					{
						MapList[i][j].BreakBlock(Direction, Number);
					}
					return true;
				}
			}
		}
	}
	return false;
}


void MapManager::DrawMap(HDC hdc)
{
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (MapList[i][j].GetMapType() != 7)
				MapList[i][j].DrawMap(hdc);
		}
	}
}
void MapManager::DrawForestMap(HDC hdc)
{
	for (int i = 0; i < 18; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (MapList[i][j].GetMapType() == 7)
				MapList[i][j].DrawMap(hdc);
		}
	}
}
MapManager::~MapManager()
{
	//delete MapList;
}