#include<windows.h>
#include<cmath>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("TextOut"); 

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
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

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	/*RECT rt = { 100, 100, 400, 300 };
	LPCSTR str = TEXT("So keep your eyes on me now"
		"무엇을 보든 좋아할 거야 닿을 수 없는 Level"
		"나와 대결 원한 널 확신해");*/
	int a = 0;
	int b = 0;
	int c = 0;

	switch (iMessage)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		//SetTextAlign(hdc, TA_CENTER);
		//TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);
		//DrawText(hdc, str, -1, &rt, DT_CENTER | DT_WORDBREAK);

		//for(int i = 0; i < 100; i++)
		//	SetPixel(hdc, 10 + (i * 3), 10 + (i * 3), RGB(0, 0, 0));
		SetPixel(hdc, 100 , 100 , RGB(0, 0, 0));
		for (int i = 0; i <= 100; i++)
		{
			a = (int)sqrt(10000 - ((i)*(i)));
			SetPixel(hdc, 100 + (i), 100 + a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 100; i++)
		{
			a = (int)sqrt(10000 - ((i)*(i)));
			SetPixel(hdc, 100 - (i), 100 - a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 100; i++)
		{
			a = (int)sqrt(10000 - ((i)*(i)));
			SetPixel(hdc, 100 + (i), 100 - a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 100; i++)
		{
			a = (int)sqrt(10000 - ((i)*(i)));
			SetPixel(hdc, 100 - (i), 100 + a, RGB(255, 0, 0));
		}

		//내원?
		for (int i = 0; i <= 100; i++)
		{
			a = (int)sqrt(10000 - ((i)*(i)));
			SetPixel(hdc, 400 + (i), 400 + a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 100; i++)
		{
			a = (int)sqrt(10000 - ((i)*(i)));
			SetPixel(hdc, 400 - (i), 400 - a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 100; i++)
		{
			a = (int)sqrt(10000 - ((i)*(i)));
			SetPixel(hdc, 400 + (i), 400 - a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 100; i++)
		{
			a = (int)sqrt(10000 - ((i)*(i)));
			SetPixel(hdc, 400 - (i), 400 + a, RGB(255, 0, 0));
		}


		//외원
		for (int i = 0; i <= 400; i++)
		{
			a = (int)sqrt(160000 - ((i)*(i)));
			SetPixel(hdc, 400 + (i), 400 + a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 400; i++)
		{
			a = (int)sqrt(160000 - ((i)*(i)));
			SetPixel(hdc, 400 - (i), 400 - a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 400; i++)
		{
			a = (int)sqrt(160000 - ((i)*(i)));
			SetPixel(hdc, 400 + (i), 400 - a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 400; i++)
		{
			a = (int)sqrt(160000 - ((i)*(i)));
			SetPixel(hdc, 400 - (i), 400 + a, RGB(255, 0, 0));
		}

		for (int i = 0; i <= 400; i++)
		{
			c = 400;//장축
			b = 100;//단축
		
			a = (int)sqrt(((b*b*c*c) - b*b*( i)*( i)) / (c*c));
			SetPixel(hdc, 400 + i, 400 + a, RGB(255, 0, 0));
		}
		for (int i = 0; i <= 400; i++)
		{
			c = 400;//장축
			b = 100;//단축
			a = (int)sqrt(((b*b*c*c) - b * b*(i)*(i)) / (c*c));
			SetPixel(hdc, 400 - i, 400 - a, RGB(0, 255, 0));
		}
		for (int i = 0; i <= 400; i++)
		{
			c = 400;//장축
			b = 100;//단축
			a = (int)sqrt(((b*b*c*c) - b * b*(i)*(i)) / (c*c));
			SetPixel(hdc, 400 + i, 400 - a, RGB(0, 0, 255));
		}
		for (int i = 0; i <= 400; i++)
		{
			c = 400;//장축
			b = 100;//단축
			a = (int)sqrt(((b*b*c*c) - b * b*(i)*(i)) / (c*c));
			SetPixel(hdc, 400 - i, 400 + a, RGB(10, 120, 180));
		}
	
		//MoveToEx(hdc, 50, 50, NULL);
		//LineTo(hdc, 300, 90);
		//Rectangle(hdc, 50, 100, 200, 180);
		//Ellipse(hdc, 220, 100, 400, 200);
		EndPaint(hWnd, &ps);

		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;

	case WM_LBUTTONDOWN:
		hdc = GetDC(hWnd);

		TextOut(hdc, 100, 100, TEXT("Beautiful Korea"), 15);

		ReleaseDC(hWnd, hdc);
		return 0; 
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}
