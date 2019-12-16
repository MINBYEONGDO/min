

#pragma once
#include<Windows.h>
#include"Mecro.h"
#include"Map.h"
class MapManager
{
private:
	Map m_MapList[8][8];
	int PieceMap_x;
	int PieceMap_y;
	int arr_x;
	int arr_y;
public:
	void Init();
	void MapSet();
	void MapDataSet();
	void UpdataMapData(int Number, bool bresult);
	void MapDraw(HDC hdc);
	void SearchMap(int Map_x, int Map_y);
	void SearchPieceMap(int Piece_x, int Piece_y);
	bool Searchobstruction(int Map_x, int Map_y, int Piece_x, int Piece_y, int PieceType, int playerteam, int playerTurn, int GameTurn);
	int CheckMap_x(int x, int y);
	int CheckMap_y(int x, int y);
	int CheckPieceTeam(int x, int y);
	MapManager();
	~MapManager();
};
