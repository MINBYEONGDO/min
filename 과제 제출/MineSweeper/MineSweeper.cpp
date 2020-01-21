#include "MineSweeper.h"


MineSweeper::MineSweeper()
{
	m_player = new Player;
	IF = new Interface;
	m_Mode = 0;
	m_Save_x = 0;
	m_Save_y = 0;
}

void MineSweeper::Init(HWND hWnd)
{
	srand(time(NULL));
	m_player->Init(m_Mode);
	m_hWnd = hWnd;
	m_hdc = GetDC(hWnd);
	CreateHDC();
	BitmapManager::GetInstance()->Init(m_hWnd, MemDC);
	MM = new MapManager;
	MM->MapListInit(m_Mode);
}
void MineSweeper::Update()
{
	IF->Draw(MemDC, m_Mode);
	MM->MapDraw(MemDC, m_Mode);
	BitBlt(m_hdc, 0, 0, 1000, 1000, MemDC, 0, 0, SRCCOPY);
}                      //이게 최종 도화지?사이즈가 된다.
void MineSweeper::NewGame()
{
	MM->Release();
	delete MM;
	m_Mode = m_Mode;
	m_Save_x = 0;
	m_Save_y = 0;
	m_player->Init(m_Mode);
	IF->Draw(m_hdc, m_Mode);
	MM = new MapManager;
	MM->MapListInit(m_Mode);
}
void MineSweeper::AginGame()
{
	m_Mode = m_Mode;
	m_player->Init(m_Mode);
	MM->ResetFlag(m_Mode);
	m_Save_x = 0;
	m_Save_y = 0;
	MM->MapReCover(m_Mode);
}

void  MineSweeper::EndGame()
{
	SendMessage(m_hWnd, WM_DESTROY, 0, 0);
}
void MineSweeper::GameOver()
{
	int MessageAnswer;
	MessageAnswer = MessageBox(m_hWnd, TEXT("게임에서 졌습니다."), TEXT("패  배"), MB_YESNOCANCEL);
	if (MessageAnswer == IDYES)
	{
		NewGame();
	}
	else if (MessageAnswer == IDNO)
	{
		AginGame();
	}
	else
	{
		EndGame();
	}
}

void MineSweeper::ClickMap(int pt_x, int pt_y)
{
	if (MM->ClickMap(m_Mode, pt_x, pt_y) == true)//어디까지나 지뢰게임 영역인지 인터페이스 영역인지 
	{//만약 지뢰게임 영역이라면 그 좌표의 xy line 값 찾기
		m_Save_x = MM->ClickMap_x(m_Mode, pt_x, pt_y);
		m_Save_y = MM->ClickMap_y(m_Mode, pt_x, pt_y);
		if (MM->CheckMine(m_Mode, m_Save_x, m_Save_y) == true)//빈공간을 클릭했을때
		{
			if (MM->CheckMapFlag(m_Mode, m_Save_x, m_Save_y) == false)
				MM->SearchMine(m_Mode, m_Save_x, m_Save_y);
		}
		else//지뢰를 클릭했을때 게임 오버
		{
			if (MM->CheckMapFlag(m_Mode, m_Save_x, m_Save_y) == false)
			{
				MM->MapReverse(m_Mode, m_Save_x, m_Save_y);
				MM->MapDraw(MemDC, m_Mode);
				BitBlt(m_hdc, 0, 0, 1000, 1000, MemDC, 0, 0, SRCCOPY);
				GameOver();
			}
		}
	}
}
void MineSweeper::RightClick(int x, int y)
{//비트맵 바꾸기 11와 1로 
	if (MM->ClickMap(m_Mode, x, y) == true)//어디까지나 지뢰게임 영역인지 인터페이스 영역인지 
	{
		m_Save_x = MM->ClickMap_x(m_Mode, x, y);
		m_Save_y = MM->ClickMap_y(m_Mode, x, y);
		if (m_player->GetFlag() != 0)
		{
			MM->RightClick(m_Mode, m_Save_x, m_Save_y);
			if (MM->CheckMapFlag(m_Mode, m_Save_x, m_Save_y) == true)
			{
				m_player->FlagDown();//무조건 다운하면 안됨
			}
			else if (MM->CheckMapFlag(m_Mode, m_Save_x, m_Save_y) == false)
			{
				m_player->FlagUp(m_Mode);//무조건 다운하면 안됨
			}
		}
		else
		{
			if (MM->CheckMapFlag(m_Mode, m_Save_x, m_Save_y) == true)
			{
				m_player->FlagUp(m_Mode);//무조건 다운하면 안됨
			}
		}
		//MM->RightClick(m_Mode, m_Save_x, m_Save_y);
		Win();
	}
}

void MineSweeper::Win()
{//플레이어의 깃발이 0이 되고 모든 지뢰 맵이 m_Flag true
	if (m_player->GetFlag() == 0 && MM->CheckMineFlag(m_Mode))
	{
		if (MessageBox(m_hWnd, TEXT("승  리"), TEXT("승리하였습니다."), MB_YESNO) == IDYES)
		{
			NewGame();
		}
		else
		{
			SendMessage(m_hWnd, WM_DESTROY, 0, 0);
		}
	}
}

void MineSweeper::ChangeMode(int Number)
{
	if (Number == BEGINNER)
		m_Mode = 0;
	else if (Number == INTERMEDIATE)
		m_Mode = 1;
	else if (Number == ADVANCED)
		m_Mode = 2;
	NewGame();
}

void MineSweeper::CreateHDC()
{
	MemDC = CreateCompatibleDC(m_hdc);
	m_Bitmap = CreateCompatibleBitmap(m_hdc, 1000, 1000);
	m_OldBitmap = (HBITMAP)SelectObject(MemDC, m_Bitmap);
}
void MineSweeper::DeleteHDC()
{
	SelectObject(MemDC, m_OldBitmap);
	DeleteObject(m_Bitmap);
	DeleteDC(MemDC);
}
void MineSweeper::Release()
{
	MM->Release();
	delete MM;
	delete m_player;
	delete IF;
	BitmapManager::GetInstance()->Release();
	DeleteHDC();
}
MineSweeper::~MineSweeper()
{
}
