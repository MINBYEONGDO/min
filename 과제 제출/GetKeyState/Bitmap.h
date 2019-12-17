#pragma once
#include <windows.h>
#include <math.h>
using namespace std;
enum key
{
	NOT,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	JUMP,
};
class Bitmap
{
private:
	HDC m_playerDC, m_backDC;
	HBITMAP m_btPlayer, m_btBack;
	HBITMAP m_btOldPlayer, m_btOldBack;
	BITMAP m_mapInfo;
	SIZE m_size;
	int SaveKey;
	int m_image_x;//움직인 후의 이미지의 위치
	int m_image_y;
	int siny;
	int cosx;
	int angle;//각도
	int i;//배열처럼
	int j;//그림 활용하기 위해서
	bool checkjump;
public:
	void Init(HDC hdc,  HINSTANCE hInst);
	void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);
	void ChangeLocation(key Key,HWND hWnd, int change_x, int change_y);
	void Jump( HWND hWnd);
	Bitmap();
	~Bitmap();
};

