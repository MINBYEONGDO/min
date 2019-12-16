
#pragma once
#include"Mecro.h"
#include"PieceManager.h"
class Player
{
private:
	PieceManager *MyPieceList;
	int m_inumber;
public:
	void Init(int Number);
	void FirstDraw(HDC hdc);
	void MoveMyPiece(int playernumber, int m_Map_x, int m_Map_y, int Piece_x, int Piece_y);
	void AttackedPieceResult(int x, int y);
	void MyPawnPromotion(int playerteamNumber, int x, int y, int Number);
	bool CheckPieceMate();
	bool MyPieceAttack(int x, int y);
	int CheckPiece_x(int x, int y);
	int CheckPiece_y(int x, int y);
	int CheckPieceType(int x, int y);
	int CheckPieceFirstMove(int x, int y);
	inline int GetNumber()
	{
		return m_inumber;
	}
	Player();
	~Player();
};