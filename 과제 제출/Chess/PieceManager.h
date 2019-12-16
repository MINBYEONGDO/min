
#pragma once
#include"Mecro.h"
#include"Piece.h"
class PieceManager
{
private:
	Piece *m_PieceList;
	Piece *m_Piecetmp;
protected:

public:
	void Init(int number);
	void PieceSet();
	void FirstDraw(HDC hdc);
	void Move(int playernumber, int Map_x, int Map_y, int Piece_x, int Piece_y);
	void AttackedPieceResult(int x, int y);
	void PawnPromotion(int playerteamNumber, int x, int y, int Number);
	bool PieceAttack(int x, int y);
	bool CheckSurvival();
	int GetPieceRect_x(int x, int y);
	int GetPieceRect_y(int x, int y);
	int GetPieceType(int x, int y);
	int GetPieceFirstMove(int x, int y);
	PieceManager();
	~PieceManager();
};