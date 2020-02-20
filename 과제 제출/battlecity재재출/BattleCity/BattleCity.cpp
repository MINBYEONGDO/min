
#include "BattleCity.h"

BattleCity::BattleCity()
{
	m_iStage = 1;//�� �ټ�
	m_iGameState = MENU;
	CurClock = clock();
	LastClock = clock();
	Space_CurClock = clock();
	Space_LastClock = clock();
	Stage_LastClock = clock();
	CreateEneryCurClock = clock();
	CreateEneryLastClock = clock();
	m_dwLastTime = GetTickCount();
	m_dwCurTime = GetTickCount();
}
void BattleCity::Init(HWND hWnd)
{
	srand(time(NULL));
	m_hWnd = hWnd;
	m_hdc = GetDC(m_hWnd);
	CreateHDC();
	BitmapManager::GetInstance()->Init(m_hWnd, m_hdc);
	MM = new MapManager;//�����Ҵ�
	EM = new EneryManager;
	m_player = new Player;
	IM.Init(m_iStage);
	MM->Init(m_iStage, m_hWnd);
	EM->Init(m_iStage);
	m_player->Init();
}
void BattleCity::FileDataLoad(int x, int y, int Data)// mm->init ->�ҽ� -> ���� -> mm
{
	MM->FileDataLoad(x, y, Data);
}

void BattleCity::StageImage()
{
	bitmap.BackGroundDraw(MemDC);
	IM.Stage(MemDC, m_iStage);
}

void BattleCity::ClearImage()
{
	bitmap.BackGroundDraw(MemDC);
	IM.Clear(MemDC);
}
void BattleCity::DefeatImage()
{
	bitmap.BackGroundDraw(MemDC);
	IM.Defeat(MemDC);
}
void BattleCity::Menu()
{
	bitmap.BackGroundDraw(MemDC);
	IM.Menu(MemDC);
	Draw();
}
void BattleCity::MenuChoice(int Choice)
{
	if (Choice == UP)
		IM.MoveChoice(MemDC, UP);
	else if (Choice == DOWN)
		IM.MoveChoice(MemDC, DOWN);
	else if (Choice == SPACE)
	{
		if (IM.GetChoiceNumber() == 0)
			m_iGameState = STAGE;
		else if (IM.GetChoiceNumber() == 1)
			SendMessage(m_hWnd, WM_DESTROY, 0, 0);
	}
}
void BattleCity::SetDeltaTime()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwLastTime) / 1000.0f;
	m_dwLastTime = m_dwCurTime;
}
void BattleCity::Defeat()
{
	m_iStage = 1;
	m_iGameState = DEFEAT;
	EM->Release();
	EM->Init(m_iStage);
	delete MM;
	MM = new MapManager;//�����Ҵ�
	MM->Init(m_iStage, m_hWnd);
	m_player->NewGameSet();
	Stage_LastClock = clock();
	Stage_LastClock = clock();
}
void BattleCity::Update()
{
	SetDeltaTime();
	if (m_iGameState == STAGE)//�������� �Ѿ�� �κ�
	{
		Stage_CurClock = clock();
		if (Stage_CurClock - Stage_LastClock > 2000)
		{
			Stage_LastClock = clock();
			m_iGameState = PLAYGAME;
		}
		StageImage();
	}
	else if (m_iGameState == END)
	{
		Stage_CurClock = clock();
		if (Stage_CurClock - Stage_LastClock > 2000)
		{
			Stage_LastClock = clock();
			m_iGameState = MENU;
		}
		ClearImage();
	}
	else if (m_iGameState == DEFEAT)
	{
		Stage_CurClock = clock();
		if (Stage_CurClock - Stage_LastClock > 2000)
		{
			Stage_LastClock = clock();
			m_iGameState = MENU;
		}
		DefeatImage();
	}
	else if (m_iGameState == PLAYGAME)
	{
		bitmap.BackGroundDraw(MemDC);//�⺻ ���̽� ȸ�� ����ȭ��
		IM.GameInterface(m_player->GetLife(), m_iStage);//�ֺ� �������̽�
		IM.Draw(MemDC, m_player->GetLife(), m_iStage, EM->GetLiveEnery());
		CreateEnery();
		if (m_player->GetShield() == true)
			m_player->ShieldTime();
		MissileAction();
		EneryAction();//���ʹ� ����
		PlayerAction();//�÷��̾� ����
		if (m_player->GetLife() < 0)
			Defeat();
		if (EM->GetLiveEnery() == 0)
		{
			StageClear();
			return;
		}
	}
	Draw();
}

void BattleCity::StageClear()
{
	m_iGameState = STAGE;

	m_iStage++;//�������� ����
	if (m_iStage > 5)//�������� 5Ŭ����� �޴��� ���ư��� �ϱ�
	{
		m_iStage = 1;
		m_iGameState = END;
		EM->Release();
		EM->Init(m_iStage);
		delete MM;
		MM = new MapManager;
		MM->Init(m_iStage, m_hWnd);
		m_player->NewStageSet();
		Stage_LastClock = clock();
		Stage_LastClock = clock();
	}
	else
	{
		m_iGameState = STAGE;
		EM->Release();
		EM->Init(m_iStage);//5���� 
		delete MM;
		MM = new MapManager;//�����Ҵ�
		MM->Init(m_iStage, m_hWnd);
		m_player->NewGameSet();
		Stage_LastClock = clock();
	}
}
void BattleCity::CreateEnery()//���ʹ� ���� ����������
{
	CreateEneryCurClock = clock();
	if (CreateEneryCurClock - CreateEneryLastClock > 1000)//�� ���� �� 3��
	{
		CreateEneryLastClock = clock();
		if (EM->GetRespawnEnery() < EM->GetMax())
  			EM->Respawn();
	}
}
void BattleCity::MissileAction()
{
	EneryMissileActive();
	PlayerMissileActive();//�̻��� �浹
	RECT rect;
	RECT Rtmp;
	RECT Rtmp1;
	if (m_player->GetMissileMax() != 0)//�÷��̾� �̻���
	{
		for (int i = 0; i < EM->GetMax(); i++)//���ʹ� �����̼�
		{
			if (EM->GetMissileMax(i) != 0)//�̻���
			{
				for (int j = 0; j < EM->GetMissileMax(i); j++)//�� ���ʹ��� �̻��� �����̼�
				{
					Rtmp = EM->GetMissileRect(i, j);
					for (int k = 0; k < m_player->GetMissileMax(); k++)
					{
						Rtmp1 = m_player->GetMissileRect(k);
						if (IntersectRect(&rect, &Rtmp1, &Rtmp) == true)
						{
							m_player->MissileChangeStateCruch(k, MISSILE);
							EM->MissileChangeStateCruch(i, j, MISSILE);
						}
					}
				}
			}
		}
	}
}
void BattleCity::PlayerMissileActive()
{
	CurClock = clock();
	if (CurClock - LastClock > 50)//�̻��� �̵��ӵ� ����
	{
		LastClock = CurClock;
		m_player->MissileMove();//�̻��� �̵�
	}
	RECT Rtmp;
	if (m_player->GetMissileMax() != 0)//�̻��� ���� �浹
	{
		for (int i = 0; i < m_player->GetMissileMax(); i++)
		{
			Rtmp = m_player->GetMissileRect(i);
			if (MM->CrushBlock_Missile(Rtmp, m_player->GetMissileDirection(i), PLAYER) == true)
			{
				m_player->MissileChangeStateCruch(i, BLOCK);
			}
		}
		for (int i = 0; i < m_player->GetMissileMax(); i++)//ĳ���� �̻��ϰ� �̳ʹ̿��� �浹
		{
			Rtmp = m_player->GetMissileRect(i);
			if (EM->ContactObject(Rtmp) == true)
			{
				m_player->MissileChangeStateCruch(i, TANK);
				EM->BreakEnery();
			}
		}
	}
}
void BattleCity::EneryMissileActive()
{
	EM->Fire();
	EM->MissileMove();
	RECT Rtmp;
	for (int i = 0; i < EM->GetMax(); i++)//���ʹ� �����̼�
	{
		if (EM->GetMissileMax(i) != 0)//�̻��� ���� �浹
		{
			for (int j = 0; j < EM->GetMissileMax(i); j++)//�� ���ʹ��� �̻��� �����̼�
			{
				Rtmp = EM->GetMissileRect(i, j);
				if (MM->CrushBlock_Missile(Rtmp, EM->GetMissileDirection(i, j), ENERY) == true)
				{
					EM->MissileChangeStateCruch(i, j, BLOCK);
					if (MM->GetEnd() == false)
					{
						Defeat();
						return;
					}
				}
			}
			for (int j = 0; j < EM->GetMissileMax(i); j++)//�� ���ʹ��� �̻��� �����̼�
			{
				Rtmp = EM->GetMissileRect(i, j);
				if (m_player->ContactObject(Rtmp) == true)
				{
					EM->MissileChangeStateCruch(i, j, TANK);
					if (m_player->GetShield() == false)
						m_player->Break();
				}
			}
		}
	}
}
void BattleCity::PlayerAction()
{
	if (m_player->GetRespawn() == true)
	{
		if (EM->ContactObject(m_player->GetCheckRect()) == false)
		{
			m_player->RespawnReset();
		}
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		m_player->ImageChange(LEFT);
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)//�������� �ִ� ���� �ƴѰ�찡 �ӵ��� �ٸ��⿡
			m_player->CheckMove(ICE, LEFT, m_fDeltaTime); //��Ȳ�� ���� �̵����� �ٸ��� �ֱ� ���ؼ� �̴�.
		else
			m_player->CheckMove(NOT, LEFT, m_fDeltaTime);
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)//�������� �ִ��� Ȯ���ϴ� ���
		{
			if (MM->ContactBlock(m_player->GetCheckRect()) == false)
			{
				if (m_player->GetRespawn() == false)
				{
					if (EM->ContactObject(m_player->GetCheckRect()) == false)
						m_player->Move(ICE, LEFT, m_fDeltaTime);//ice
				}
				else if (m_player->GetRespawn() == true)
				{
					m_player->Move(ICE, LEFT, m_fDeltaTime);
				}

			}
		}
		else if (MM->ContactBlock(m_player->GetCheckRect()) == false)//�������� �÷��̾ ���ٸ��� ��Ȳ
		{
			if (m_player->GetRespawn() == false)
			{
				if (EM->ContactObject(m_player->GetCheckRect()) == false)
					m_player->Move(NOT, LEFT, m_fDeltaTime);
			}
			else if (m_player->GetRespawn() == true)
			{
				m_player->Move(NOT, LEFT, m_fDeltaTime);
			}
		}
		m_player->CheckRectReset();
	}
	else if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		m_player->ImageChange(RIGHT);
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)
			m_player->CheckMove(ICE, RIGHT, m_fDeltaTime);
		else
			m_player->CheckMove(NOT, RIGHT, m_fDeltaTime);
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)
		{
			if (MM->ContactBlock(m_player->GetCheckRect()) == false)
			{
				if (m_player->GetRespawn() == false)
				{
					if (EM->ContactObject(m_player->GetCheckRect()) == false)
						m_player->Move(ICE, RIGHT, m_fDeltaTime);//ice
				}
				else if (m_player->GetRespawn() == true)
				{
					m_player->Move(ICE, RIGHT, m_fDeltaTime);
				}
			}
		}
		else if (MM->ContactBlock(m_player->GetCheckRect()) == false)
		{
			if (MM->ContactBlock(m_player->GetCheckRect()) == false)
			{
				if (m_player->GetRespawn() == false)
				{
					if (EM->ContactObject(m_player->GetCheckRect()) == false)
						m_player->Move(NOT, RIGHT, m_fDeltaTime);
				}
				else if (m_player->GetRespawn() == true)
					m_player->Move(NOT, RIGHT, m_fDeltaTime);
			}
		}
		m_player->CheckRectReset();
	}
	else if (GetKeyState(VK_UP) & 0x8000)
	{
		m_player->ImageChange(UP);
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)
			m_player->CheckMove(ICE, UP, m_fDeltaTime);
		else
			m_player->CheckMove(NOT, UP, m_fDeltaTime);
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)
		{
			if (MM->ContactBlock(m_player->GetCheckRect()) == false)
			{
				if (m_player->GetRespawn() == false)
				{
					if (EM->ContactObject(m_player->GetCheckRect()) == false)
						m_player->Move(ICE, UP, m_fDeltaTime);
				}
				else if (m_player->GetRespawn() == true)
					m_player->Move(ICE, UP, m_fDeltaTime);
			}
		}
		else if (MM->ContactBlock(m_player->GetCheckRect()) == false)
		{
			if (MM->ContactBlock(m_player->GetCheckRect()) == false)
			{
				if (m_player->GetRespawn() == false)
				{
					if (EM->ContactObject(m_player->GetCheckRect()) == false)
						m_player->Move(NOT, UP, m_fDeltaTime);
				}
				else if (m_player->GetRespawn() == true)
					m_player->Move(NOT, UP, m_fDeltaTime);
			}
		}
		m_player->CheckRectReset();
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_player->ImageChange(DOWN);
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)
			m_player->CheckMove(ICE, DOWN, m_fDeltaTime);
		else
			m_player->CheckMove(NOT, DOWN, m_fDeltaTime);
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)
		{
			if (MM->ContactBlock(m_player->GetCheckRect()) == false)
			{
				if (m_player->GetRespawn() == false)
				{
					if (EM->ContactObject(m_player->GetCheckRect()) == false)
						m_player->Move(ICE, DOWN, m_fDeltaTime);//ice
				}
				else if (m_player->GetRespawn() == true)
				{
					m_player->Move(ICE, DOWN, m_fDeltaTime);
				}
			}
		}
		else if (MM->ContactBlock(m_player->GetCheckRect()) == false)
		{
			if (m_player->GetRespawn() == false)
			{
				if (EM->ContactObject(m_player->GetCheckRect()) == false)
					m_player->Move(NOT, DOWN, m_fDeltaTime);
			}
			else if (m_player->GetRespawn() == true)
				m_player->Move(NOT, DOWN, m_fDeltaTime);
		}
		m_player->CheckRectReset();
	}
	if (GetKeyState(VK_SPACE) & 0x8000)//����
	{
		Space_CurClock = clock();
		if (Space_CurClock - Space_LastClock > 300)//�߻�ӵ� ����
		{
			Space_LastClock = clock();
			m_player->Fire();//�̻��� ����
		}
	}
}
void BattleCity::EneryAction()
{
	RECT Rtmp;
	int Count = 0;
	for (int i = 0; i < EM->GetRespawnEnery(); i++)
	{
		EM->EneryResetRespawning(i, m_player->GetCheckRect());
		if (MM->ContactIceBlock(EM->GetEneryCheckRect(i)) == true)//üũ�� ��Ȳ�� �°� ����
		{
			EM->CheckMove(ICE, i, m_fDeltaTime);
			Rtmp = EM->GetEneryCheckRect(i);
		}
		else
		{
			EM->CheckMove(NOT, i, m_fDeltaTime);
			Rtmp = EM->GetEneryCheckRect(i);
		}
		for (int j = 0; j < EM->GetRespawnEnery(); j++)
		{
			if (i != j)//�ٸ� ���ʹ̵�� ���� ���ʹ̿� �浹������
			{
				if (EM->GetEneryRespawning(i) == false) //j�� Respawning���� EM->ContactObject���� üũ ������
				{                                       //i�� Respawning ���� üũ ���� �־��⿡ �ű⼭ ������ �����.
						  //�ϳ��� üũ�ع����� �ϳ��� false���϶��� �浹�� �߻��ϱ� �����̴�.
					if (EM->ContactObject(j, Rtmp) == true)
					{
						EM->ChangeDirection(i);//������ȯ
						EM->ImageChange(i);
						EM->ChangeDirection(j);//������ȯ
						EM->ImageChange(j);
					}
				}
			}
		}
		if (MM->ContactIceBlock(EM->GetEneryCheckRect(i)) == true)//üũ�� ��Ȳ�� �°� ����
		{
			if (MM->ContactBlock(Rtmp) == false && EM->ContactObject(i, m_player->GetCheckRect()) == true && m_player->GetRespawn() == true)
			{
				EM->EneryMove(ICE, i, m_fDeltaTime);
			}
			else if (MM->ContactBlock(Rtmp) == false && EM->ContactObject(i, m_player->GetCheckRect()) == false)
			{// �浹 �������� �׻��� �״�� �̵�(������ �÷��̾�)
				EM->EneryMove(ICE, i, m_fDeltaTime);
			}
			else if (MM->ContactBlock(Rtmp) == true || (EM->ContactObject(i, m_player->GetCheckRect()) == true && m_player->GetRespawn() == false))
			{//�浹 ������ ������ȯ(������ �÷��̾�)
				EM->ChangeDirection(i);//������ȯ
			}
		}
		else
		{
			if (MM->ContactBlock(Rtmp) == false && EM->ContactObject(i, m_player->GetCheckRect()) == true && m_player->GetRespawn() == true)
			{
				EM->EneryMove(NOT, i, m_fDeltaTime);
			}
			else if (MM->ContactBlock(Rtmp) == false && EM->ContactObject(i, m_player->GetCheckRect()) == false)
			{// �浹 �������� �׻��� �״�� �̵�(������ �÷��̾�)
				EM->EneryMove(NOT, i, m_fDeltaTime);
			}
			else if (MM->ContactBlock(Rtmp) == true || (EM->ContactObject(i, m_player->GetCheckRect()) == true && m_player->GetRespawn() == false))
			{//�浹 ������ ������ȯ(������ �÷��̾�)
				EM->ChangeDirection(i);//������ȯ
			}
		}
		EM->CheckRectReset(i);
		EM->ImageChange(i);
	}
}
void BattleCity::Draw()
{
	if (m_iGameState == PLAYGAME)
	{
		bitmap.PlayerGroundDraw(MemDC);
		MM->DrawMap(MemDC);
		EM->Draw(MemDC);
		m_player->Draw(MemDC);
		MM->DrawForestMap(MemDC);//��Ǯ��
	}
	BitBlt(m_hdc, 0, 0, 700, 700, MemDC, 0, 0, SRCCOPY);
}
void BattleCity::CreateHDC()
{
	MemDC = CreateCompatibleDC(m_hdc);
	m_Bitmap = CreateCompatibleBitmap(m_hdc, 1000, 1000);
	m_OldBitmap = (HBITMAP)SelectObject(MemDC, m_Bitmap);
}
void BattleCity::DeleteHDC()
{
	SelectObject(MemDC, m_OldBitmap);
	DeleteObject(m_Bitmap);
	DeleteDC(MemDC);
}

void BattleCity::Release()
{
	DeleteHDC();
	EM->Release();
	delete MM;
	delete EM;
	delete m_player;
	BitmapManager::GetInstance()->Release();
}

BattleCity::~BattleCity()
{
}