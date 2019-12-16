
#include "Player.h"



Player::Player()
{

}
void Player::Init(int Number)
{
	m_inumber = Number;
	MyPieceList = new PieceManager;
	MyPieceList->Init(Number);
}
void Player::FirstDraw(HDC hdc)
{
	MyPieceList->FirstDraw(hdc);
}
void Player::AttackedPieceResult(int x, int y)
{
	MyPieceList->AttackedPieceResult(x, y);
}
void Player::MoveMyPiece(int playernumber, int m_Map_x, int m_Map_y, int Piece_x, int Piece_y)
{
	MyPieceList->Move(playernumber, m_Map_x, m_Map_y, Piece_x, Piece_y);
}
void Player::MyPawnPromotion(int playerteamNumber, int x, int y, int Number)
{
	MyPieceList->PawnPromotion(playerteamNumber, x, y, Number);
}

int Player::CheckPiece_x(int x, int y)
{
	return MyPieceList->GetPieceRect_x(x, y);
}

int Player::CheckPiece_y(int x, int y)
{
	return MyPieceList->GetPieceRect_y(x, y);
}

int Player::CheckPieceType(int x, int y)
{
	return MyPieceList->GetPieceType(x, y);
}

int Player::CheckPieceFirstMove(int x, int y)
{
	return MyPieceList->GetPieceFirstMove(x, y);
}
bool Player::MyPieceAttack(int x, int y)
{
	return MyPieceList->PieceAttack(x, y);
}
bool Player::CheckPieceMate()
{
	return MyPieceList->CheckSurvival();
}

Player::~Player()
{
	delete MyPieceList;
}