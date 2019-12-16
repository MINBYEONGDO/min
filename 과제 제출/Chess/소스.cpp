
#include"Mecro.h"
#include"GameManager.h"
#include"BitmapManager.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("PtInRect");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF); //����� �� �޸𸮸� üũ
	//_crtBreakAlloc = 106; //�޸𸮸� ��ġ Ž�� �������
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass�� �⺻ ������ȯ���� ����� ����ü��. �ɹ������� �ؿ��� ����.
	WndClass.cbClsExtra = 0; //���࿵��
	WndClass.cbWndExtra = 0; //���࿵�� (�Ű�x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //����
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //Ŀ��
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //������ ���
	WndClass.hInstance = hInstance;//(���α׷� �ڵ鰪(��ȣ)���)
	WndClass.lpfnWndProc = WndProc; //���μ��� �Լ� ȣ��
	WndClass.lpszClassName = lpszClass; //Ŭ���� �̸�
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//�������� ������ ������ ���� �� �ٽ� �׸���.
	RegisterClass(&WndClass);  //������� WidClass�� ���

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 615, 700, NULL, (HMENU)NULL, hInstance, NULL);//����âũ�������� ���⼭
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, NULL, 0, 0))//����ڿ��� �޽����� �޾ƿ��� �Լ�(WM_QUIT �޽��� ���� �� ����)
	{
		TranslateMessage(&Message); //  Ű���� �Է� �޽��� ó���Լ�
		DispatchMessage(&Message); //���� �޽����� WndProc�� �����ϴ� �Լ�
	}
	return (int)Message.wParam;
}

static GameManager GM;

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	POINT in_Pt;
	POINT MovePt;

	switch (iMessage)
	{
	case WM_CREATE:
		GM.Init(hWnd);
		return 0;
	case 100:
		SendMessage(hWnd, WM_DESTROY, 0, 0);
		return 0;
	case WM_LBUTTONDOWN:
		//�� ĭ�� ü������ �ִ°� Ȯ�� 1->������ ��ĭ�� ü���� �����Է��ϱ�
		//���� ü�����ΰ� Ȯ�� 2->�ڽ�Ŭ������ �����ϰ� ���� 
		//�ʰ� �� ��ǥ ��ġ ������ Ȯ��
		//�������� �´� �̵���λ���
		//�ٽ� Ŭ�� �ϰ� �� �� ����ġ�� ��ǥ�� 
		//�ٽ� Ŭ���� ��� �ϴ°�?? �ݹ� ������ �ٽ� �ϴµ� �װ� �ߴ��� ���ߴ��� ���ϴ°� 
		//���ӸŴ������� bool�� ����ؼ� �����Ѵ�?
		if (GM.GetbClick() == false)
		{
			in_Pt.x = LOWORD(lParam);
			in_Pt.y = HIWORD(lParam);
			GM.Click(in_Pt.x, in_Pt.y);
		}
		// �̵���� �׸��� �Լ��� ����
		else if (GM.GetbClick() == true)
		{
			MovePt.x = LOWORD(lParam);
			MovePt.y = HIWORD(lParam);
			GM.Move(hWnd, lParam, MovePt.x, MovePt.y);
			//�ʿ� �� ��ġ�� �ǽ��� �����ϴ°� �˸��� bool ���� ��ȭ�ʿ�(�� ������ �¾Ƽ� �̵���������)
			InvalidateRect(hWnd, NULL, TRUE);

		}
		GM.ChangeClick();
		return 0;
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);
		GM.Draw(hdc);
		GM.CheckMate(hWnd);
		EndPaint(hWnd, &ps);

		return 0;

	case WM_DESTROY:
		BitmapManager::GetInstance()->Release();
		PostQuitMessage(0);
		return 0;
	}
	return(DefWindowProc(hWnd, iMessage, wParam, lParam));
}