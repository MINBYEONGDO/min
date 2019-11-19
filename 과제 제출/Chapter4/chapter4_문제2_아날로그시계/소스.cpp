#include<windows.h>
#include<cmath>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void CALLBACK TimerProc(HWND hWnd, UINT uMsg, UINT idEvernt, DWORD dwTime);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("Timer");

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

SYSTEMTIME st;//컴퓨터 시간

int g_Hourx;
int g_Houry;
int g_Minutex;
int g_Minutey;
int g_Sec_x;
int g_Sec_y;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	static TCHAR sTime[128];
	int x;
	int y;
	int hournumber = 1;
	HDC hdc;
	PAINTSTRUCT ps;
	switch (iMessage)
	{
	case WM_CREATE:
		SetTimer(hWnd, 1, 1000, TimerProc);
		SendMessage(hWnd, WM_TIMER, 1, 0);
		return 0;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		Ellipse(hdc, 200, 200, 400, 400);
		hournumber = 1;
		for (int i = 0; i < 360; i++)
		{
			if (i % 30 == 0)
			{
				x = cos(((i)-60)/ 57.3) * 80;
				y = sin(((i)-60)/ 57.3) * 80;
				wsprintf(sTime, TEXT("%d"), hournumber);
				SetTextAlign(hdc, TA_CENTER);
				TextOut(hdc, 300 + x, 295 + y, sTime, lstrlen(sTime));
				hournumber++;
			}
		}
		MoveToEx(hdc,300,300, NULL);
		LineTo(hdc,300+ g_Hourx,300+ g_Houry);
		MoveToEx(hdc, 300, 300, NULL);
		LineTo(hdc, 300 + g_Minutex, 300 + g_Minutey);
		MoveToEx(hdc, 300, 300, NULL);
		LineTo(hdc, 300+g_Sec_x, 300+g_Sec_y);
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
	GetLocalTime(&st);
	g_Hourx = cos(((st.wHour * 30 + (30 * st.wMinute) / 60) -90)/57.3) * 50;
	g_Houry = sin(((st.wHour * 30 + (30 * st.wMinute) / 60) -90)/57.3) * 50;
	g_Minutex = cos((( 6 * st.wMinute+ (6 * st.wSecond)/60)-90)/57.3) * 70;
	g_Minutey = sin((( 6 * st.wMinute + (6 * st.wSecond) / 60)-90) / 57.3) * 70;
	g_Sec_x = cos(( (6 * st.wSecond)-90) / 57.3) * 100;
	g_Sec_y = sin(( (6 * st.wSecond)-90) /  57.3) * 100;
	InvalidateRect(hWnd, NULL, TRUE);

}