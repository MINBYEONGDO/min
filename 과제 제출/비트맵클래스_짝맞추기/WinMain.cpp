#include <windows.h>
#include <math.h>
#include"Gamemanager.h"
#include<crtdbg.h>
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
char g_szClassName[256] = "Hello World!!";

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
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
	WndClass.lpszClassName = g_szClassName;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(g_szClassName, g_szClassName, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0))
	{
		TranslateMessage(&Message);
		DispatchMessage(&Message);
	}

	return (int)Message.wParam;
}

int x;
int y;
LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc, MemDC;
	PAINTSTRUCT ps;
	HBITMAP MyBitMap, OldBitMap;
	int icheck;
	switch (iMessage)
	{
	case 100:
		icheck = MessageBox(hWnd, TEXT("승리하셧습니다!다시 시작하실거면 RETRY 아니면 CANSEL을 누르세요"), TEXT("게임 종료 메시지"), MB_RETRYCANCEL);
		if(icheck == IDRETRY)
		{
			Gamemanager::GetInstans()->CardReset();
			Gamemanager::GetInstans()->Suffle(hWnd);
			//SendMessage(hWnd, WM_PAINT, 0, 0);
			InvalidateRect(hWnd, NULL, TRUE);
		}
		else if(icheck == IDCANCEL)
		{
			SendMessage(hWnd, WM_DESTROY, 0, 0);
		}
		return 0;
	case WM_CREATE:
		Gamemanager::GetInstans()->Init(hWnd, g_hInst);
		Gamemanager::GetInstans()->Suffle(hWnd);
		return 0;
	case WM_LBUTTONDOWN:
		x = LOWORD(lParam);
		y = HIWORD(lParam);
		Gamemanager::GetInstans()->ClickBitmap(hWnd, x, y);
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);

		Gamemanager::GetInstans()->Draw(hWnd,hdc, 20, 100);

		EndPaint(hWnd, &ps);
		return 0;
	case WM_TIMER:
		InvalidateRect(hWnd, NULL, TRUE);//타이머 사용
		return 0;
	case WM_DESTROY:
		Gamemanager::GetInstans()->Release();
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//클릭시 클릭한 부분만 다시 그리기 - 해결
//2개까지 유지하다가 2개이후에 돌려놓기 틀리면// 해결
//같으면 맞춘건 유지 - gamemanager 드로우에 if문 추가
//카드 순서 섞기 - gamemanger에서 랜덤으로 받고 ? 저장하기 중복 막고 지뢰찾기 찾아보기- 해결
//맞추고 끝나면 다시 할지 끝질 선택하게 하기 - 이건 나중에 생각하고
//승리 ,, 타이머

