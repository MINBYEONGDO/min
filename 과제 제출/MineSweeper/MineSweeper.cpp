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
}                      //�̰� ���� ��ȭ��?����� �ȴ�.
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
	MessageAnswer = MessageBox(m_hWnd, TEXT("���ӿ��� �����ϴ�."), TEXT("��  ��"), MB_YESNOCANCEL);
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
	if (MM->ClickMap(m_Mode, pt_x, pt_y) == true)//�������� ���ڰ��� �������� �������̽� �������� 
	{//���� ���ڰ��� �����̶�� �� ��ǥ�� xy line �� ã��
		m_Save_x = MM->ClickMap_x(m_Mode, pt_x, pt_y);
		m_Save_y = MM->ClickMap_y(m_Mode, pt_x, pt_y);
		if (MM->CheckMine(m_Mode, m_Save_x, m_Save_y) == true)//������� Ŭ��������
		{
			if (MM->CheckMapFlag(m_Mode, m_Save_x, m_Save_y) == false)
				MM->SearchMine(m_Mode, m_Save_x, m_Save_y);
		}
		else//���ڸ� Ŭ�������� ���� ����
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
{//��Ʈ�� �ٲٱ� 11�� 1�� 
	if (MM->ClickMap(m_Mode, x, y) == true)//�������� ���ڰ��� �������� �������̽� �������� 
	{
		m_Save_x = MM->ClickMap_x(m_Mode, x, y);
		m_Save_y = MM->ClickMap_y(m_Mode, x, y);
		if (m_player->GetFlag() != 0)
		{
			MM->RightClick(m_Mode, m_Save_x, m_Save_y);
			if (MM->CheckMapFlag(m_Mode, m_Save_x, m_Save_y) == true)
			{
				m_player->FlagDown();//������ �ٿ��ϸ� �ȵ�
			}
			else if (MM->CheckMapFlag(m_Mode, m_Save_x, m_Save_y) == false)
			{
				m_player->FlagUp(m_Mode);//������ �ٿ��ϸ� �ȵ�
			}
		}
		else
		{
			if (MM->CheckMapFlag(m_Mode, m_Save_x, m_Save_y) == true)
			{
				m_player->FlagUp(m_Mode);//������ �ٿ��ϸ� �ȵ�
			}
		}
		//MM->RightClick(m_Mode, m_Save_x, m_Save_y);
		Win();
	}
}

void MineSweeper::Win()
{//�÷��̾��� ����� 0�� �ǰ� ��� ���� ���� m_Flag true
	if (m_player->GetFlag() == 0 && MM->CheckMineFlag(m_Mode))
	{
		if (MessageBox(m_hWnd, TEXT("��  ��"), TEXT("�¸��Ͽ����ϴ�."), MB_YESNO) == IDYES)
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
