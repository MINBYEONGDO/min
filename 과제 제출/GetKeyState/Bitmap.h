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
	int m_image_x;//������ ���� �̹����� ��ġ
	int m_image_y;
	int siny;
	int cosx;
	int angle;//����
	int i;//�迭ó��
	int j;//�׸� Ȱ���ϱ� ���ؼ�
	bool checkjump;
public:
	void Init(HDC hdc,  HINSTANCE hInst);
	void Draw(HDC hdc, int x, int y, int spX = 1, int spY = 1);
	void ChangeLocation(key Key,HWND hWnd, int change_x, int change_y);
	void Jump( HWND hWnd);
	Bitmap();
	~Bitmap();
};

