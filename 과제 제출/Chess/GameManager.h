
#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
#include"MapManager.h"
#include"PieceManager.h"
#include"Player.h"

class GameManager
{
private:
	MapManager m_MapManager;
	PieceManager m_PieceManager;
	Player *m_player;
	bool m_bClick;
	int m_iPieceType;//현재 선택한 말의 종류
	int m_Piece_x;
	int m_Piece_y;
	int m_Map_x;
	int m_Map_y;
	int m_iTurn;
public:
	GameManager();
	~GameManager();
	void ChangeClick();
	inline bool GetbClick()
	{
		return m_bClick;
	}
	void Init(HWND hWnd);
	void Draw(HDC hdc);
	void Click(int x, int y);
	void Move(HWND hWnd, LPARAM lParam, int movex, int movey);
	void CheckMate(HWND hWnd);
	int CheckPiece_x(int x, int y);
	int CheckPiece_y(int x, int y);
	int CheckPieceType(int x, int y);
	int CheckMap_x(int x, int y);
	int CheckMap_y(int x, int y);
};