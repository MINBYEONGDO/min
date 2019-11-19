#include<windows.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvernt, DWORD dwTime);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Input_Mouse");

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

int x = 110;
int y = 120;
bool bounce = false;//튕기기 전과 튕기기후 구분하기 위해서
bool xplus = true;//엑스값 증가할때
bool yplus = true;//와이값 증가할때 false면 감소할때
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	SYSTEMTIME st;
	static TCHAR sTime[128];

	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd,1,10,TimerProc);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Rectangle(hdc, 100, 100, 1000, 600);
		Ellipse(hdc, x, y, x + 100, y + 100);
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvernt, DWORD dwTime)
{
	if (x <= 100)
	{
		bounce = true;
		xplus = true;
	}
	else if(x + 100 >= 1000)
	{
		bounce = true;
		xplus = false;
	}
	else if(y <= 100)
	{
		bounce = true;
		yplus = true;
	}
	else if(y + 100 >= 600)
	{
		bounce = true;
		yplus = false;
	}
	if (bounce == false)
	{
		x ++;
		y ++;
	}
	else if (bounce == true)
	{
		if (xplus == true && yplus == true)
		{
			x++;
			y++;
		}
		else if (xplus == true && yplus == false)
		{
			x++;
			y--;
		}
		else if (xplus == false && yplus == true)
		{
			x--;
			y++;
		}
		else if (xplus == false && yplus == false)
		{
			x--;
			y--;
		}
	}
		InvalidateRect(hWnd, NULL, TRUE);
}