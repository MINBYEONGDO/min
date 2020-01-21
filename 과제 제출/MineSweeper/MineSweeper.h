
#pragma once
#include"Mecro.h"
#include"Player.h"
#include"MapManager.h"
#include"Interface.h"
#include"BitmapManager.h"
class MineSweeper
{
private:
	Player *m_player;
	MapManager *MM;
	Interface *IF;

	HWND m_hWnd;
	HDC m_hdc;
	HDC MemDC;
	HBITMAP m_Bitmap;
	HBITMAP m_OldBitmap;

	int m_Mode;//0비기닝 //1 인터// 2 어드밴스드
	int m_Save_x;
	int m_Save_y;
public:
	void Init(HWND hWnd);
	void Update();
	void ClickMap(int x, int y);
	void RightClick(int x, int y);
	void ChangeMode(int Number);
	void Win();

	void NewGame();
	void AginGame();
	void EndGame();
	void WinGame();
	void GameOver();

	void CreateHDC();
	void DeleteHDC();
	void Release();
	MineSweeper();
	~MineSweeper();
};