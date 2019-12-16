
#include"Mecro.h"
#include"GameManager.h"
#include"BitmapManager.h"
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR lpszClass = TEXT("PtInRect");


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPervlnstance, LPSTR lpszCmdParam, int nCmdShow)
{
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF); //디버깅 후 메모리릭 체크
	//_crtBreakAlloc = 106; //메모리릭 위치 탐색 디버깅중
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;
	//WndClass는 기본 윈도우환경을 만드는 구조체다. 맴버변수는 밑에와 같다.
	WndClass.cbClsExtra = 0; //예약영역
	WndClass.cbWndExtra = 0; //예약영역 (신경x)
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //배경색
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW); //커서
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION); //아이콘 모양
	WndClass.hInstance = hInstance;//(프로그램 핸들값(번호)등록)
	WndClass.lpfnWndProc = WndProc; //프로세스 함수 호출
	WndClass.lpszClassName = lpszClass; //클레스 이름
	WndClass.lpszMenuName = NULL;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;//윈도우의 수직과 수평이 변경 시 다시 그린다.
	RegisterClass(&WndClass);  //만들어진 WidClass를 등록

	hWnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, 0, 0, 615, 700, NULL, (HMENU)NULL, hInstance, NULL);//시작창크기조절은 여기서
	ShowWindow(hWnd, nCmdShow);
	while (GetMessage(&Message, NULL, 0, 0))//사용자에게 메시지를 받아오는 함수(WM_QUIT 메시지 받을 시 종료)
	{
		TranslateMessage(&Message); //  키보드 입력 메시지 처리함수
		DispatchMessage(&Message); //받은 메시지를 WndProc에 전달하는 함수
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
		//그 칸에 체스말이 있는가 확인 1->이전에 맵칸에 체스말 여부입력하기
		//무슨 체스말인가 확인 2->자식클래스로 이전하고 나서 
		//맵과 말 좌표 위치 말종류 확인
		//말종류에 맞는 이동경로생성
		//다시 클릭 하고 그 곳 맵위치의 좌표값 
		//다시 클릭을 어떻게 하는가?? 콜백 끝나고 다시 하는데 그걸 했는지 않했는지 정하는걸 
		//게임매니저에서 bool을 사용해서 결정한다?
		if (GM.GetbClick() == false)
		{
			in_Pt.x = LOWORD(lParam);
			in_Pt.y = HIWORD(lParam);
			GM.Click(in_Pt.x, in_Pt.y);
		}
		// 이동경로 그리는 함수를 생성
		else if (GM.GetbClick() == true)
		{
			MovePt.x = LOWORD(lParam);
			MovePt.y = HIWORD(lParam);
			GM.Move(hWnd, lParam, MovePt.x, MovePt.y);
			//맵에 그 위치에 피스가 존재하는걸 알리는 bool 변수 변화필요(단 조건이 맞아서 이동했을때만)
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