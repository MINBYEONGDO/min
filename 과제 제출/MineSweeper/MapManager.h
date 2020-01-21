
#pragma once
#include"Mecro.h"
#include"Map.h"
class MapManager
{
private:
 Map* MapList;
 Map* m_Maptmp;
 int m_MaxMine;
public:
 void MapListInit(int Mode);
 void SetMapData(int Mode);

 void MapReverse(int Mode, int x, int y);
 void MapReCover(int Mode);
 void MapDraw(HDC hdc, int Mode);
 void SearchMine(int Mode, int x, int y);
 void RightClick(int Mode, int x, int y);
 void ResetFlag(int Mode);
 bool ClickMap(int Mode, int Pt_x, int Pt_y);
 bool CheckMine(int Mode, int xline, int yline);
 bool CheckMapFlag(int Mode, int xline, int yline);
 bool CheckMineFlag(int Mode);
 int ClickMap_x(int Mode, int Pt_x, int Pt_y);
 int ClickMap_y(int Mode, int Pt_x, int Pt_y);
 void Release();
 MapManager();
 ~MapManager();
};