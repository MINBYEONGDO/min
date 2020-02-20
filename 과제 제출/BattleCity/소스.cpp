
#include"Mecro.h"
#include"BattleCity.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("BattleCity");
HWND g_hWnd;
BattleCity g_BC;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF); //디버깅 후 메모리릭 체크
				 //	_crtBreakAlloc = 89 ; //메모리릭 위치 탐색 디버깅중
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, "Circus//icon.bmp");
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	RegisterClass(&WndClass);

	g_hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, 0, 0, 700, 700, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(g_hWnd, nCmdShow);
	g_BC.Init(g_hWnd);
	while (true)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			if (Message.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		if (g_BC.GetGameState() == 0)
		{
			g_BC.Menu();
		}
		else
			g_BC.Update();
	}
	g_BC.Release();
	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	POINT pt;
	switch (iMessage)
	{
	case WM_COMMAND:
	case 101:
	{
		char buf[256];
		int Data;
		wsprintf(buf, "Stage%d_Map.txt", lParam);
		HANDLE hFile = CreateFile(buf, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
		for (int i = 0; i < 18; i++)
		{
			for (int j = 0; j < 15; j++)
			{
				DWORD readB;
				ReadFile(hFile, &Data, sizeof(int), &readB, NULL);
				g_BC.FileDataLoad(j, i, Data);
			}
		}
		CloseHandle(hFile);
	}
	break;
	case WM_LBUTTONDOWN:
	{
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
	}
	break;
	case WM_KEYDOWN:
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (g_BC.GetGameState() == MENU)
				g_BC.MenuChoice(LEFT);
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (g_BC.GetGameState() == MENU)
				g_BC.MenuChoice(RIGHT);
		}
		if (GetKeyState(VK_UP) & 0x8000)
		{
			if (g_BC.GetGameState() == MENU)
				g_BC.MenuChoice(UP);
		}
		if (GetKeyState(VK_DOWN) & 0x8000)
		{
			if (g_BC.GetGameState() == MENU)
				g_BC.MenuChoice(DOWN);
		}
		if (GetKeyState(VK_SPACE) & 0x8000)
		{
			if (g_BC.GetGameState() == MENU)
				g_BC.MenuChoice(SPACE);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}