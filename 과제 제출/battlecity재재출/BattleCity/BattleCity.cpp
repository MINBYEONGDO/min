
#include "BattleCity.h"

BattleCity::BattleCity()
{
	m_iStage = 1;//총 다섯
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
	MM = new MapManager;//동적할당
	EM = new EneryManager;
	m_player = new Player;
	IM.Init(m_iStage);
	MM->Init(m_iStage, m_hWnd);
	EM->Init(m_iStage);
	m_player->Init();
}
void BattleCity::FileDataLoad(int x, int y, int Data)// mm->init ->소스 -> 여기 -> mm
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
	MM = new MapManager;//동적할당
	MM->Init(m_iStage, m_hWnd);
	m_player->NewGameSet();
	Stage_LastClock = clock();
	Stage_LastClock = clock();
}
void BattleCity::Update()
{
	SetDeltaTime();
	if (m_iGameState == STAGE)//스테이지 넘어가는 부분
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
		bitmap.BackGroundDraw(MemDC);//기본 베이스 회색 바탕화면
		IM.GameInterface(m_player->GetLife(), m_iStage);//주변 인터페이스
		IM.Draw(MemDC, m_player->GetLife(), m_iStage, EM->GetLiveEnery());
		CreateEnery();
		if (m_player->GetShield() == true)
			m_player->ShieldTime();
		MissileAction();
		EneryAction();//에너미 동작
		PlayerAction();//플레이어 동작
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

	m_iStage++;//스테이지 증가
	if (m_iStage > 5)//스테이지 5클리어시 메뉴로 돌아가게 하기
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
		EM->Init(m_iStage);//5까지 
		delete MM;
		MM = new MapManager;//동적할당
		MM->Init(m_iStage, m_hWnd);
		m_player->NewGameSet();
		Stage_LastClock = clock();
	}
}
void BattleCity::CreateEnery()//에너미 생성 순차적으로
{
	CreateEneryCurClock = clock();
	if (CreateEneryCurClock - CreateEneryLastClock > 1000)//적 생성 텀 3초
	{
		CreateEneryLastClock = clock();
		if (EM->GetRespawnEnery() < EM->GetMax())
  			EM->Respawn();
	}
}
void BattleCity::MissileAction()
{
	EneryMissileActive();
	PlayerMissileActive();//미사일 충돌
	RECT rect;
	RECT Rtmp;
	RECT Rtmp1;
	if (m_player->GetMissileMax() != 0)//플레이어 미사일
	{
		for (int i = 0; i < EM->GetMax(); i++)//에너미 로테이션
		{
			if (EM->GetMissileMax(i) != 0)//미사일
			{
				for (int j = 0; j < EM->GetMissileMax(i); j++)//그 에너미의 미사일 로테이션
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
	if (CurClock - LastClock > 50)//미사일 이동속도 제한
	{
		LastClock = CurClock;
		m_player->MissileMove();//미사일 이동
	}
	RECT Rtmp;
	if (m_player->GetMissileMax() != 0)//미사일 벽과 충돌
	{
		for (int i = 0; i < m_player->GetMissileMax(); i++)
		{
			Rtmp = m_player->GetMissileRect(i);
			if (MM->CrushBlock_Missile(Rtmp, m_player->GetMissileDirection(i), PLAYER) == true)
			{
				m_player->MissileChangeStateCruch(i, BLOCK);
			}
		}
		for (int i = 0; i < m_player->GetMissileMax(); i++)//캐릭터 미사일과 이너미와의 충돌
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
	for (int i = 0; i < EM->GetMax(); i++)//에너미 로테이션
	{
		if (EM->GetMissileMax(i) != 0)//미사일 벽과 충돌
		{
			for (int j = 0; j < EM->GetMissileMax(i); j++)//그 에너미의 미사일 로테이션
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
			for (int j = 0; j < EM->GetMissileMax(i); j++)//그 에너미의 미사일 로테이션
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
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)//빙판위에 있는 경우와 아닌경우가 속도가 다르기에
			m_player->CheckMove(ICE, LEFT, m_fDeltaTime); //상황에 따라 이동값을 다르게 주기 위해서 이다.
		else
			m_player->CheckMove(NOT, LEFT, m_fDeltaTime);
		if (MM->ContactIceBlock(m_player->GetCheckRect()) == true)//빙판위에 있는지 확인하는 경우
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
		else if (MM->ContactBlock(m_player->GetCheckRect()) == false)//빙판위에 플레이어가 없다면의 상황
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
	if (GetKeyState(VK_SPACE) & 0x8000)//공격
	{
		Space_CurClock = clock();
		if (Space_CurClock - Space_LastClock > 300)//발사속도 제한
		{
			Space_LastClock = clock();
			m_player->Fire();//미사일 생성
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
		if (MM->ContactIceBlock(EM->GetEneryCheckRect(i)) == true)//체크렉 상황에 맞게 설정
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
			if (i != j)//다른 에너미들과 현재 에너미와 충돌했을때
			{
				if (EM->GetEneryRespawning(i) == false) //j의 Respawning값은 EM->ContactObject에서 체크 하지만
				{                                       //i의 Respawning 값은 체크 안해 주었기에 거기서 문제가 생겼다.
						  //하나만 체크해버리면 하나만 false값일때도 충돌이 발생하기 때문이다.
					if (EM->ContactObject(j, Rtmp) == true)
					{
						EM->ChangeDirection(i);//방향전환
						EM->ImageChange(i);
						EM->ChangeDirection(j);//방향전환
						EM->ImageChange(j);
					}
				}
			}
		}
		if (MM->ContactIceBlock(EM->GetEneryCheckRect(i)) == true)//체크렉 상황에 맞게 설정
		{
			if (MM->ContactBlock(Rtmp) == false && EM->ContactObject(i, m_player->GetCheckRect()) == true && m_player->GetRespawn() == true)
			{
				EM->EneryMove(ICE, i, m_fDeltaTime);
			}
			else if (MM->ContactBlock(Rtmp) == false && EM->ContactObject(i, m_player->GetCheckRect()) == false)
			{// 충돌 안했으면 그상태 그대로 이동(벽돌과 플레이어)
				EM->EneryMove(ICE, i, m_fDeltaTime);
			}
			else if (MM->ContactBlock(Rtmp) == true || (EM->ContactObject(i, m_player->GetCheckRect()) == true && m_player->GetRespawn() == false))
			{//충돌 했으면 방향전환(벽돌과 플레이어)
				EM->ChangeDirection(i);//방향전환
			}
		}
		else
		{
			if (MM->ContactBlock(Rtmp) == false && EM->ContactObject(i, m_player->GetCheckRect()) == true && m_player->GetRespawn() == true)
			{
				EM->EneryMove(NOT, i, m_fDeltaTime);
			}
			else if (MM->ContactBlock(Rtmp) == false && EM->ContactObject(i, m_player->GetCheckRect()) == false)
			{// 충돌 안했으면 그상태 그대로 이동(벽돌과 플레이어)
				EM->EneryMove(NOT, i, m_fDeltaTime);
			}
			else if (MM->ContactBlock(Rtmp) == true || (EM->ContactObject(i, m_player->GetCheckRect()) == true && m_player->GetRespawn() == false))
			{//충돌 했으면 방향전환(벽돌과 플레이어)
				EM->ChangeDirection(i);//방향전환
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
		MM->DrawForestMap(MemDC);//숲풀용
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