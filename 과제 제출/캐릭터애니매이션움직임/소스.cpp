#include <windows.h>
#include <math.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TransparentBlt");


int k = 0;//전체 이미지중 가로기준 몇번째
int j = 0;//전체 이미지중 세로기준 몇번째
int i = 0;//각도
int x = 650;//시작 위치
int y = 600;//시작 위치
int siny = 0;
int cosx = 0;
bool checkjump = false;

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

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1024, 768,
		NULL, (HMENU)NULL, hInstance, NULL);

	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	HDC hMemDC;
	HBITMAP hImage, hOldBitmap;
	int bx, by;
	BITMAP bit;


	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		hMemDC = CreateCompatibleDC(hdc);

		hImage = (HBITMAP)LoadImage(NULL, TEXT("image.bmp"),
			IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION);

		hOldBitmap = (HBITMAP)SelectObject(hMemDC, hImage);

		GetObject(hImage, sizeof(BITMAP), &bit);
		bx = bit.bmWidth;
		by = bit.bmHeight;

		if (checkjump == true)
		{
			TransparentBlt(hdc, x, y - siny, bx / 4, by / 4,
				hMemDC, (bx / 4) *k, (by / 4) * j, bx / 4, by / 4, RGB(255, 0, 255));
		}
		else
		{
			TransparentBlt(hdc, x, y, bx / 4, by / 4,
				hMemDC, (bx / 4) *k, (by / 4) * j, bx / 4, by / 4, RGB(255, 0, 255));
		}

		SelectObject(hMemDC, hOldBitmap);
		DeleteObject(hImage);
		DeleteDC(hMemDC);
		EndPaint(hWnd, &ps);
		SetTimer(hWnd, 1, 10, NULL);
		return 0;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
			if (checkjump == false)
			{
				x = x - 10;
				if (k == 3)
					k = 0;
				else
					k++;
				j = 2;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;

		case VK_RIGHT:
			if (checkjump == false)
			{
				x = x + 10;
				if (k == 3)
					k = 0;
				else
					k++;
				j = 3;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;

		case VK_UP:
			if (checkjump == false)
			{
				y = y - 10;
				if (k == 3)
					k = 0;
				else
					k++;
				j = 1;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		case VK_DOWN:
			if (checkjump == false)
			{
				y = y + 10;
				if (k == 3)
					k = 0;
				else
					k++;
				j = 0;
				InvalidateRect(hWnd, NULL, TRUE);
			}
			break;
		case VK_SPACE:
			checkjump = true;
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}
		return 0;
	case WM_TIMER:
		if (checkjump == true)
		{
			if (i < 180)
			{
				siny = sin((i) / 57.3) * 50;
				i++;
			}
			else if (i >= 180)
			{
				i = 0;
				checkjump = false;
			}
			InvalidateRect(hWnd, NULL, TRUE);
		}
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

