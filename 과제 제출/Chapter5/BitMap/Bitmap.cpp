#include "resource.h"
#include<windows.h>
#include<crtdbg.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM );
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BitMap");
enum Animal
{
	NOTING,
	DOG,
	TIGER,
	DUCK,
	ELEPHANT,
	COW,
	HORSE,
};
class Bitmap
{
private:
	int m_animalNumber;
	HDC  m_MemDC;
	HBITMAP m_myBitmap, m_oldBitmap;
protected:

public:
	void SetBitMap(HDC hdc,  int x, int y, int animal_Number)
	{
		m_MemDC = CreateCompatibleDC(hdc);
		m_myBitmap = LoadBitmap(g_hInst, MAKEINTRESOURCE(animal_Number));
		m_oldBitmap = (HBITMAP)SelectObject(m_MemDC, m_myBitmap);
		BitBlt(hdc, x, y, 145, 235, m_MemDC, 0, 0, SRCCOPY);
		SelectObject(m_MemDC, m_oldBitmap);
		DeleteObject(m_myBitmap);
		DeleteDC(m_MemDC);
	}
	int CheckBitMap(HWND hWnd,int x, int y)
	{
		if ((x >= 100 && x <= 245) && (y >= 100 && y <= 335))
		{
			m_animalNumber = DOG;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if ((x >= 300 && x <= 445) && (y >= 100 && y <= 335))
		{
			m_animalNumber = TIGER;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if ((x >= 500 && x <= 645) && (y >= 100 && y <= 335))
		{
			m_animalNumber = DUCK;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if ((x >= 700 && x <= 845) && (y >= 100 && y <= 335))
		{
			m_animalNumber = ELEPHANT;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if ((x >= 900 && x <= 1045) && (y >= 100 && y <= 335))
		{
			m_animalNumber = COW;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if ((x >=1100 && x <= 1245) && (y >= 100 && y <= 335))
		{
			m_animalNumber = HORSE;
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return m_animalNumber;
	}
};
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	_CrtDumpMemoryLeaks();
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

int OK = NOTING;

void ShowMessageBox(HWND hWnd)
{
	if (OK == DOG)
	{
		MessageBox(hWnd, TEXT("강아지 입니다"), TEXT("MessageBox"), MB_OK) == IDOK;
		OK = NOTING;
	}
	else if (OK == TIGER)
	{
		MessageBox(hWnd, TEXT("호랑이 입니다"), TEXT("MessageBox"), MB_OK) == IDOK;
		OK = NOTING;
	}
	else if (OK == DUCK)
	{
		MessageBox(hWnd, TEXT("병아리 입니다"), TEXT("MessageBox"), MB_OK) == IDOK;
		OK = NOTING;
	}
	else if (OK == ELEPHANT)
	{
		MessageBox(hWnd, TEXT("코끼리 입니다"), TEXT("MessageBox"), MB_OK) == IDOK;
		OK = NOTING;
	}
	else if (OK == COW)
	{
		MessageBox(hWnd, TEXT("소 입니다"), TEXT("MessageBox"), MB_OK) == IDOK;
		OK = NOTING;
	}
	else if (OK == HORSE)
	{
		MessageBox(hWnd, TEXT("말 입니다"), TEXT("MessageBox"), MB_OK) == IDOK;
		OK = NOTING;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	int x;
	int y;
	Bitmap *bitmap = new Bitmap;//클래스
	HDC hdc;
	PAINTSTRUCT ps;
	//HBITMAP myBitmap, oldBitmap;

	switch (iMessage)
	{
	case WM_CREATE:
		//여기서 동적할당?
		//배열이면 유지해야 하나?

		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		OK=bitmap->CheckBitMap(hWnd, x, y);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		bitmap->SetBitMap(hdc,100,  100, IDB_BITMAP1);
		bitmap->SetBitMap(hdc, 300, 100, IDB_BITMAP3);
		bitmap->SetBitMap(hdc, 500, 100, IDB_BITMAP2);
		bitmap->SetBitMap(hdc, 700, 100, IDB_BITMAP4);
		bitmap->SetBitMap(hdc, 900, 100, IDB_BITMAP5);
		bitmap->SetBitMap(hdc, 1100, 100, IDB_BITMAP6);
		ShowMessageBox(hWnd);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		//delete bitmap;
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

