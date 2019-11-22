
#pragma once
#include<Windows.h>
#include"Bitmap.h"
#include<time.h>
#include<vector>
using namespace std;
class Gamemanager
{
	vector<Bitmap*>m_vecBitmapList;
private:
	static Gamemanager* m_pThis;
	int m_Count;
	int m_ClickCount;
	int m_VictoryCount;
public:
	static Gamemanager* GetInstans()
	{
		if (m_pThis == NULL)
		{
			m_pThis = new Gamemanager;
		}
		return m_pThis;
	}
	Gamemanager();

	void Init(HWND hWnd, HINSTANCE hInst);
	void Draw(HWND hWnd, HDC hdc, int x, int y);
	void ClickBitmap(HWND hWnd, int x, int y);
	void MatchingCard(HWND hWnd);//두카드가 일치하는지 확인
	void Suffle(HWND  hWnd);
	void CardReset();
	void Release();

	~Gamemanager();
};