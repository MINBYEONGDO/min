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
		icheck = MessageBox(hWnd, TEXT("�¸��ϼ˽��ϴ�!�ٽ� �����ϽǰŸ� RETRY �ƴϸ� CANSEL�� ��������"), TEXT("���� ���� �޽���"), MB_RETRYCANCEL);
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
		InvalidateRect(hWnd, NULL, TRUE);//Ÿ�̸� ���
		return 0;
	case WM_DESTROY:
		Gamemanager::GetInstans()->Release();
		KillTimer(hWnd, 1);
		PostQuitMessage(0);
		return 0;
	}

	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}

//Ŭ���� Ŭ���� �κи� �ٽ� �׸��� - �ذ�
//2������ �����ϴٰ� 2�����Ŀ� �������� Ʋ����// �ذ�
//������ ����� ���� - gamemanager ��ο쿡 if�� �߰�
//ī�� ���� ���� - gamemanger���� �������� �ް� ? �����ϱ� �ߺ� ���� ����ã�� ã�ƺ���- �ذ�
//���߰� ������ �ٽ� ���� ���� �����ϰ� �ϱ� - �̰� ���߿� �����ϰ�
//�¸� ,, Ÿ�̸�

