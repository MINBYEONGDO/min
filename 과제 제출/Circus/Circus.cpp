
#include "Circus.h"

Circus::Circus()
{
	m_imenu = 0;
	m_iState = 0;
	m_Move = 0;
	m_iStage = 1;
	m_iTimeBonus = 8000;
	m_bCheckTime = true;
	m_bEnd = true;
	m_player = new Player;
	m_dwLastTime = GetTickCount();
	m_dwCurTime = GetTickCount();
}
void Circus::Init(HWND hWnd)
{
	srand(time(NULL));
	m_hWnd = hWnd;
	hdc = GetDC(hWnd);
	CreateHDC1();
	CreateHDC2();
	BitmapManager::GetInstance()->Init(m_hWnd, MemDC[0], MemDC[1]);
	IM.Init(); //배경 정보입력
	oM.Init(); //장애물 정보입력
}


void Circus::MenuChoice()
{
	if (GetKeyState(VK_UP) & 0x8000)
	{
		m_imenu = 1;
		IM.MenuChoice(hdc, MemDC[1], m_imenu);
	}
	else if (GetKeyState(VK_DOWN) & 0x8000)
	{
		m_imenu = 2;
		IM.MenuChoice(hdc, MemDC[1], m_imenu);
	}
	else if (GetKeyState(VK_SPACE) & 0x8000)
	{
		if (m_imenu == 1)
		{
			m_iState = 1;
			DeleteHDC2();
			StageDisplay();
			IM.CircusBack(hdc, MemDC[0], 0, 0);
		}
		else if (m_imenu == 2)
		{
			m_bEnd = false;
			//SendMessage(m_hWnd, WM_DESTROY, 0, 0);
		}
	}
}

void Circus::StageDisplay()
{
	m_CurClock = clock();
	m_LastClock = clock();
	while (1)
	{
		m_CurClock = clock();
		if (m_CurClock - m_LastClock < 2000)
		{
			CreateHDC2();
			IM.StageDisplay(hdc, MemDC[1]);
			BitBlt(hdc, 0, 0, 455, 700, MemDC[1], 0, 0, SRCCOPY);
			DeleteHDC2();
		}
		else
			break;
	}
}
void Circus::Update()
{
	m_dwCurTime = GetTickCount();
	m_fDeltaTime = (m_dwCurTime - m_dwLastTime) / 1000.0f;
	m_dwLastTime = m_dwCurTime;

	m_CurClock = clock();// 시간
	if (m_bCheckTime == true)
	{
		m_LastClock = m_CurClock;
		m_bCheckTime = false;
	}
	if (m_CurClock - m_LastClock > 1000)
	{
		if (m_iTimeBonus != 0)
			m_iTimeBonus -= 100;
		m_bCheckTime = true;
	}
	if (m_iState == 0) //게임을 시작한 상태
	{
		IM.StartMenu(hdc, MemDC[1]);
		IM.DrawTitle(hdc, MemDC[1]);
		MenuChoice(); //메뉴 고르기
		BitBlt(hdc, 0, 0, 455, 700, MemDC[1], 0, 0, SRCCOPY);
	}
	else if (m_iState == 1) //타이틀에서 넘어오고 게임 플레이하는 상황
		PlayGame();
}

void Circus::PlayerMove()
{
	if (m_player->GetPlayerState() != DEATH)
	{
		if (oM.CheckRect(FRONT, m_player->GetRect()) == true)//프론트와 플레이어가 충돌하면
		{//4670 이후에 접촉보다 충돌이 먼저 접근?됨
			PlayerDeath();
		}
		else if (oM.CheckRect(RING, m_player->GetRect()) == true)//링과 플레이어가 충돌하면
			PlayerDeath();
	}

	if (GetKeyState(VK_LEFT) & 0x8000) //왼쪽이동
	{
		if (m_Move - 150 * m_fDeltaTime >= 0)//최소 이동 제 한
		{
			//if (m_Move - 65 + player->Getx() - 244 * m_fDeltaTime >= 4670)
			if (m_Move - 65 + m_player->Getx() - 150 * m_fDeltaTime > 4670)
			{
				if (oM.CheckRect(FRONT, m_player->GetRect()) == false)//안에 안들어 갔을때
					m_player->playerMove(m_Move - 65 + m_player->Getx(), (-150 * m_fDeltaTime));
			}
			//else if(m_Move - 65 + player->Getx() - 244 * m_fDeltaTime < 4670)
			else
			{
				oM.UpdateRect((-244) * m_fDeltaTime);//왜-244인가?
				if (oM.CheckRect(FRONT, m_player->GetRect()) == false)//길막확인용
				{
					m_Move = m_Move - 150 * m_fDeltaTime;
					oM.UpdateRect((-244) * m_fDeltaTime);
				}
				oM.UpdateRect(150 * m_fDeltaTime);
				m_player->playerMove(m_Move, (-150) * m_fDeltaTime);
			}
		}
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)//오른쪽이동
	{
		if (m_Move + 150 * m_fDeltaTime < 6050)//최대 이동 제한
		{
			if (m_Move - 65 + m_player->Getx() + (150 * m_fDeltaTime) >= 4670)
			{//player->playerMove(m_Move + 65+ 100 * m_fDeltaTime, (150 * m_fDeltaTime));
				if (oM.CheckRect(FRONT, m_player->GetRect()) == false)//안에 안들어 갔을때
					m_player->playerMove(m_Move - 65 + m_player->Getx(), (150 * m_fDeltaTime));
			}
			else
			{
				oM.UpdateRect(100 * m_fDeltaTime);
				if (oM.CheckRect(FRONT, m_player->GetRect()) == false)//안에 안들어 갔을때
				{
					m_Move = m_Move + 150 * m_fDeltaTime;
					oM.UpdateRect(100 * m_fDeltaTime);
				}
				oM.UpdateRect((-150) * m_fDeltaTime);
				m_player->playerMove(m_Move, (150 * m_fDeltaTime));
			}
		}
	}
	if (GetKeyState(VK_SPACE) & 0x8000)
		m_player->playerJump();
	IM.CircusBack(hdc, MemDC[0], m_Move, 0);
}

void Circus::PlayerJump()
{
	if (oM.CheckRect(FRONT, m_player->GetRect()) == true)
		PlayerDeath();
	if (oM.CheckRect(RING, m_player->GetRect()) == true)
		PlayerDeath();
	if (oM.CheckMoney(m_player->GetRect()) == true)
	{
		m_player->UpdateScore(1);
	}
	m_fCurJumpTime += m_fDeltaTime;
	if (m_Move - 65 + m_player->Getx() + 200 * m_fDeltaTime > 4670)
	{
		if (m_Move + m_player->Getx() + 200 * m_fDeltaTime >= 5000)
		{
			if (m_player->Gety() + 63 >= 600)
			{
				m_player->ChangeState(PLAYEREND);
				if(m_iTimeBonus !=0)
					EndEvent(0);
				else if (m_iTimeBonus == 0)
					EndEvent(1);
			}
		}
		m_player->playerJumping(m_fCurJumpTime);
		m_player->playerMove(m_Move - 65 + m_player->Getx(), (200 * m_fDeltaTime));
	}
	else
	{
		oM.UpdateRect(100 * m_fDeltaTime);
		if (m_Move + 200 * m_fDeltaTime <= 4670)//최대 이동 제한
		{
			m_Move = m_Move + 200 * m_fDeltaTime;
			oM.UpdateRect(100 * m_fDeltaTime);
		}
		oM.UpdateRect((-150) * m_fDeltaTime);
		m_player->playerJumping(m_fCurJumpTime);
	}
	IM.CircusBack(hdc, MemDC[0], m_Move, 0);
	if (m_fCurJumpTime >= 1.0f)
	{
		m_fCurJumpTime = 0.0f;
		m_player->ChangeState(JUMP);
	}
}

void Circus::PlayGame()
{

	if (m_player->GetPlayerState() == JUMP)//점프 
		PlayerJump();
	else if (m_player->GetPlayerState() != JUMP)//플레이어가 점프상태가 아니라면
		PlayerMove(); //움직임 관련 함수로 이동

	if (oM.SearchPoint(m_player->Getx()) == true)
		m_player->UpdateScore(0); //점수

	IM.StatePlate(hdc, MemDC[0], m_player->GetPlayerLife(), m_player->GetScore(), m_iTimeBonus, m_iStage);
	if (oM.ObstacleGetx(m_Move) == true)
	{
		oM.Draw(hdc, MemDC[0], m_Move, 1); //장애물 그리기
		m_player->Draw(hdc, MemDC[0]); //총합적으로 플레이어의 현상태 그리기
		oM.Draw(hdc, MemDC[0], m_Move, 2); //장애물 그리기
	}
	else
	{
		oM.Draw(hdc, MemDC[0], m_Move, 0); //장애물 그리기
		m_player->Draw(hdc, MemDC[0]); //총합적으로 플레이어의 현상태 그리기
	}
	BitBlt(hdc, 0, 0, 455, 700, MemDC[0], 0, 0, SRCCOPY);
}
void  Circus::PlayerDeath()
{
	m_CurClock = clock();
	DeleteHDC1();
	CreateHDC1();
	m_player->playerDeath();
	IM.CircusBack(hdc, MemDC[0], m_Move, 0);
	IM.StatePlate(hdc, MemDC[0], m_player->GetPlayerLife(), m_player->GetScore(), m_iTimeBonus, m_iStage);
	oM.Draw(hdc, MemDC[0], m_Move, 0);
	m_player->Draw(hdc, MemDC[0]);
	m_LastClock = m_CurClock;
	BitBlt(hdc, 0, 0, 455, 700, MemDC[0], 0, 0, SRCCOPY);
	while (1)
	{
		m_CurClock = clock();
		if (m_CurClock - m_LastClock > 2000)
			break;
	}
	if (m_player->GetPlayerLife() == 0)
	{
		m_iState = 0;
		m_player->GameOver();
	}
	else
		StageDisplay();//죽엇지만 아직 목숨이 남아잇을때

			  //값 초기화
	m_player->ChangeState(DEATH); //플레이어 상태 변화시키기 stop으로
	m_player->PlayerReset();
	DataRelease();
}


void Circus::EndEvent(int Number)//춤 배경 변화 -> 스코어 ->메세지 박스 -> 화면 or 그냥 종료
{
	int Count = 0;
	int CheckBonusTime = m_iTimeBonus;
	m_CurClock = clock();
	m_LastClock = clock();
	DeleteHDC1();
	CreateHDC1();
	if (Number == 0)
	{
		while (1)
		{
			m_CurClock = clock();
			if (m_iTimeBonus == 0)
			{
				DeleteHDC1();
				if (MessageBox(m_hWnd, TEXT("게임을 종료하시겠습니까?"), TEXT("게임 클리어"), MB_OKCANCEL) == IDOK)
				{
					//m_bEnd = false;
					SendMessage(m_hWnd, WM_DESTROY, 0, 0);
				}
				else
				{
					m_player->PlayerClear();
					DataRelease();
					m_iState = 0;
				}
				break;
			}
			else
			{
				m_player->playerReachEnd();
				m_player->BonusScore(1);
				m_iTimeBonus -= 1;
				IM.CircusBack(hdc, MemDC[0], m_Move, Count);
				IM.StatePlate(hdc, MemDC[0], m_player->GetPlayerLife(), m_player->GetScore(), m_iTimeBonus, m_iStage);
				oM.Draw(hdc, MemDC[0], m_Move, WIN);//end만 출력하기 위해서 4라는 별도의 상황을 만듬
				m_player->Draw(hdc, MemDC[0]);
				BitBlt(hdc, 0, 0, 455, 700, MemDC[0], 0, 0, SRCCOPY);
				Count++;
				if (Count == 2)
					Count = 0;
			}
		}
	}
	else if (Number == 1)
	{
		while (1)
		{
			m_CurClock = clock();
			if (m_CurClock - m_LastClock < 3000)
			{
				m_player->playerReachEnd();
				m_player->BonusScore(1);
				m_iTimeBonus -= 1;
				IM.CircusBack(hdc, MemDC[0], m_Move, Count);
				IM.StatePlate(hdc, MemDC[0], m_player->GetPlayerLife(), m_player->GetScore(), m_iTimeBonus, m_iStage);
				oM.Draw(hdc, MemDC[0], m_Move, WIN);//end만 출력하기 위해서 4라는 별도의 상황을 만듬
				m_player->Draw(hdc, MemDC[0]);
				BitBlt(hdc, 0, 0, 455, 700, MemDC[0], 0, 0, SRCCOPY);
				Count++;
				if (Count == 2)
					Count = 0;
			}
			else
			{
				DeleteHDC1();
				if (MessageBox(m_hWnd, TEXT("게임을 종료하시겠습니까?"), TEXT("게임 클리어"), MB_OKCANCEL) == IDOK)
				{
					SendMessage(m_hWnd, WM_DESTROY, 0, 0);
				}
				else
				{
					m_player->PlayerClear();
					DataRelease();
					m_iState = 0;
				}
				break;
			}
		}
	}
}

void Circus::CreateHDC1()
{
	MemDC[0] = CreateCompatibleDC(hdc); //게임플레이용 도화지
	m_BitMap[0] = CreateCompatibleBitmap(hdc, 455, 700);
	m_OldBitmap[0] = (HBITMAP)SelectObject(MemDC[0], m_BitMap[0]);
}
void Circus::CreateHDC2()
{
	MemDC[1] = CreateCompatibleDC(hdc); //타이틀용 도화지 
	m_BitMap[1] = CreateCompatibleBitmap(hdc, 455, 700);
	m_OldBitmap[1] = (HBITMAP)SelectObject(MemDC[1], m_BitMap[1]);
}
void Circus::DeleteHDC1()
{
	SelectObject(MemDC[0], m_OldBitmap[0]);
	DeleteObject(m_BitMap[0]);
	DeleteDC(MemDC[0]);
}
void Circus::DeleteHDC2()
{
	SelectObject(MemDC[1], m_OldBitmap[1]);
	DeleteObject(m_BitMap[1]);
	DeleteDC(MemDC[1]);
}


void Circus::DataRelease()
{
	m_Move = 0;//첫 위치로 이동하게 하기 - 배경 등의 위치는 초기화된다.
	m_iTimeBonus = 8000;
	m_fCurJumpTime = 0;//점프시간 초기화 - 안하면 점프하고 죽었을시 점프 위치가 시간에 의해 남아있음
	oM.Init();//장애물 위치 초기화
	DeleteHDC1();
	DeleteHDC2();
	CreateHDC1();
	CreateHDC2();
}
void Circus::Release()
{
	//delete m_player;
	//BitmapManager::GetInstance()->Release();
	//delete player;
}

Circus::~Circus()
{
	//Release();
	BitmapManager::GetInstance()->Release();
	//delete m_player;
}