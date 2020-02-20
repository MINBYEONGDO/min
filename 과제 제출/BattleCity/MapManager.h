

#pragma once
#include"Map.h"
class MapManager
{
private:
	Map MapList[18][15];
	HANDLE  m_hFile;
public:
	void Init(int Stage, HWND hWnd);
	void FileDataLoad(int x, int y, int Data);
	void DrawMap(HDC hdc);
	void DrawForestMap(HDC hdc);
	bool ContactBlock(RECT rect);
	bool ContactIceBlock(RECT rect);
	bool CrushBlock_Missile(RECT rect, int Direction, int Number);
	bool GetEnd()
	{
		for (int i = 0; i < 18; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				if (MapList[i][j].GetMapType() == 14)
				{
					return MapList[i][j].GetEnd();
				}
			}
		}
	}
	MapManager();
	~MapManager();
};