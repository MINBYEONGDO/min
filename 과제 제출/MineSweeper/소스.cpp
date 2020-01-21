
#include <windows.h>
#include "MineSweeper.h"
#include "resource.h"

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("MenuDLG");
MineSweeper g_MS;
HWND g_hWnd;
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF); //디버깅 후 메모리릭 체크
	//_crtBreakAlloc = 77; //메모리릭 위치 탐색 디버깅중
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = lpszClass;

	//메뉴 리소스를 작성해서 윈도우 클래스에 배치
	WndClass.lpszMenuName = MAKEINTRESOURCE(IDR_MENU1);

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	g_hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 275, 340, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(g_hWnd, nCmdShow);

	g_MS.Init(g_hWnd);

	while (true)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))//필요한가? 클릭해야 변화가 있는데??
		{
			if (Message.message == WM_QUIT)
				break;
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else
			g_MS.Update();
	}
	g_MS.Release();

	return (int)Message.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	POINT PT;
	switch (iMessage)
	{
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case ID_FILE_NEWGAME:
			if (MessageBox(hWnd, TEXT("새게임"), TEXT("새 게임을 시작하시겠습니까?"), MB_YESNO) == IDYES)
			{
				g_MS.NewGame();
			}
			break;
		case ID_FILE_OPTION:
			DialogBox(g_hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, AboutDlgProc);
			break;
		}
	case WM_LBUTTONDOWN:
	{
		PT.x = LOWORD(lParam);
		PT.y = HIWORD(lParam);
		g_MS.ClickMap(PT.x, PT.y);
	}
	break;
	case WM_RBUTTONDOWN:
	{
		PT.x = LOWORD(lParam);
		PT.y = HIWORD(lParam);
		g_MS.RightClick(PT.x, PT.y);
	}
	break;
	return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

BOOL CALLBACK AboutDlgProc(HWND hDlg, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HWND hRadio;
	switch (iMessage)
	{
	case WM_INITDIALOG:

		hRadio = GetDlgItem(hDlg, IDC_RADIO1);
		SendMessage(hRadio, BM_SETCHECK, BST_CHECKED, 0);

		return TRUE;

	case WM_COMMAND:

		switch (wParam)
		{
		case IDOK:

			if (IsDlgButtonChecked(hDlg, IDC_RADIO1) == BST_CHECKED)
			{
				MessageBox(hDlg, "Beginner", "초급자", MB_OK);
				SetWindowPos(g_hWnd, NULL, 0, 0, 275, 340, 0);
				g_MS.ChangeMode(BEGINNER);
			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO2) == BST_CHECKED)
			{
				MessageBox(hDlg, "Intermediate", "중급자", MB_OK);
				SetWindowPos(g_hWnd, NULL, 0, 0,480,555,0);
				g_MS.ChangeMode(INTERMEDIATE);
			}
			else if (IsDlgButtonChecked(hDlg, IDC_RADIO3) == BST_CHECKED)
			{
				MessageBox(hDlg, "Advanced ", "고급자", MB_OK);
				SetWindowPos(g_hWnd, NULL, 0, 0, 744, 854, 0);
				g_MS.ChangeMode(ADVANCED);// 새게임 시작으로 유도하는거 추가
			}

			EndDialog(hDlg, 0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDlg, 0);
			return TRUE;
		}
		break;
	}
	return FALSE;
}