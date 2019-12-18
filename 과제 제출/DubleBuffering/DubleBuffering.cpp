
#include <Windows.h>
#include "Bitmap.h"
#include <vector>
using namespace std;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "GetKeyState";
LPCTSTR lpszClass = TEXT("GetKeyState");

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

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



static Bitmap bitmap;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (iMessage)
	{
	case WM_CREATE:

		SetTimer(hWnd, 1, 10, NULL);


		hdc = GetDC(hWnd);
		bitmap.Init(hWnd, hdc, g_hInst);
		ReleaseDC(hWnd, hdc);

		return 0;
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		bitmap.Draw(hdc, 0, 0);
		SetTimer(hWnd, 2, 10, NULL);
		EndPaint(hWnd, &ps);

		return 0;

	case WM_TIMER:
		switch (wParam)
		{
		case 1:
			if (GetKeyState(VK_LEFT) & 0x8000)
				bitmap.ChangeLocation(LEFT, hWnd, -10, 0);
			else if (GetKeyState(VK_RIGHT) & 0x8000)
				bitmap.ChangeLocation(RIGHT, hWnd, 10, 0);
			else if (GetKeyState(VK_UP) & 0x8000)
				bitmap.ChangeLocation(UP, hWnd, 0, -10);
			else if (GetKeyState(VK_DOWN) & 0x8000)
				bitmap.ChangeLocation(DOWN, hWnd, 0, +10);
			else if ((GetKeyState(VK_SPACE) & 0x8000))
				bitmap.ChangeLocation(JUMP, hWnd, 0, 0);
			InvalidateRect(hWnd, NULL, false);
			break;

		case 2:
			bitmap.Jump(hWnd);
			break;
		}
		return 0;
	case WM_DESTROY:

		KillTimer(hWnd, 1);
		PostQuitMessage(0);

		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}