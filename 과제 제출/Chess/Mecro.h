#pragma once
#include<Windows.h>
#include<string>
#include<vector>
using namespace std;
#define NOT 20 //Çã°ø°ª?
enum Block
{
	B_pawn = 0,
	B_Knight,
	B_Bishop,
	B_Rook,
	B_King,
	B_queen,
	W_pawn,
	W_Knight,
	W_Bishop,
	W_Rook,
	W_King,
	W_Queen,
	Block_0,
	Block_1,
	Block_2,
};
enum PieceType
{
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
	PAWN,
};
