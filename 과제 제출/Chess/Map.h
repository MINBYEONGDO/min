
#pragma once
#include"Mecro.h"
#include"Bitmap.h"
#include"BitmapManager.h"
class Map
{
private:
	Bitmap* m_pBitMap;
	int m_index;
	int     m_ix;
	int     m_iy;
	float m_fSpX;
	float m_fSpY;
	RECT m_Rect;
	bool m_bexitPiece;
	int m_iPlayer; //0 ºó°÷ 1 °ËÀº»ö 2 Èò»ö
public:
	Map();
	void SetMap(int index);
	void SetMapData(int x, int y, float spX, float spY, bool checkpiece, int checkteam, int i, int j);
	void Draw(HDC hdc);
	void CheckDraw(HDC hdc);
	void MapExitPiece(int Number, bool bresult, int iCase);
	void MapChangeMapTeam(int Number, bool bresult, int iCase);
	inline bool CheckPieceMap()
	{
		return m_bexitPiece;
	}
	inline RECT GetRect()
	{
		return m_Rect;
	}
	inline int GetMap_x()
	{
		return m_ix;
	}
	inline int GetMap_y()
	{
		return m_iy;
	}
	inline int CheckTeam()
	{
		return m_iPlayer;
	}
	~Map();
};