
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
	IM.Init(); //��� �����Է�
	oM.Init(); //��ֹ� �����Է�
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

	m_CurClock = clock();// �ð�
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
	if (m_iState == 0) //������ ������ ����
	{
		IM.StartMenu(hdc, MemDC[1]);
		IM.DrawTitle(hdc, MemDC[1]);
		MenuChoice(); //�޴� ����
		BitBlt(hdc, 0, 0, 455, 700, MemDC[1], 0, 0, SRCCOPY);
	}
	else if (m_iState == 1) //Ÿ��Ʋ���� �Ѿ���� ���� �÷����ϴ� ��Ȳ
		PlayGame();
}

void Circus::PlayerMove()
{
	if (m_player->GetPlayerState() != DEATH)
	{
		if (oM.CheckRect(FRONT, m_player->GetRect()) == true)//����Ʈ�� �÷��̾ �浹�ϸ�
		{//4670 ���Ŀ� ���˺��� �浹�� ���� ����?��
			PlayerDeath();
		}
		else if (oM.CheckRect(RING, m_player->GetRect()) == true)//���� �÷��̾ �浹�ϸ�
			PlayerDeath();
	}

	if (GetKeyState(VK_LEFT) & 0x8000) //�����̵�
	{
		if (m_Move - 150 * m_fDeltaTime >= 0)//�ּ� �̵� �� ��
		{
			//if (m_Move - 65 + player->Getx() - 244 * m_fDeltaTime >= 4670)
			if (m_Move - 65 + m_player->Getx() - 150 * m_fDeltaTime > 4670)
			{
				if (oM.CheckRect(FRONT, m_player->GetRect()) == false)//�ȿ� �ȵ�� ������
					m_player->playerMove(m_Move - 65 + m_player->Getx(), (-150 * m_fDeltaTime));
			}
			//else if(m_Move - 65 + player->Getx() - 244 * m_fDeltaTime < 4670)
			else
			{
				oM.UpdateRect((-244) * m_fDeltaTime);//��-244�ΰ�?
				if (oM.CheckRect(FRONT, m_player->GetRect()) == false)//�渷Ȯ�ο�
				{
					m_Move = m_Move - 150 * m_fDeltaTime;
					oM.UpdateRect((-244) * m_fDeltaTime);
				}
				oM.UpdateRect(150 * m_fDeltaTime);
				m_player->playerMove(m_Move, (-150) * m_fDeltaTime);
			}
		}
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)//�������̵�
	{
		if (m_Move + 150 * m_fDeltaTime < 6050)//�ִ� �̵� ����
		{
			if (m_Move - 65 + m_player->Getx() + (150 * m_fDeltaTime) >= 4670)
			{//player->playerMove(m_Move + 65+ 100 * m_fDeltaTime, (150 * m_fDeltaTime));
				if (oM.CheckRect(FRONT, m_player->GetRect()) == false)//�ȿ� �ȵ�� ������
					m_player->playerMove(m_Move - 65 + m_player->Getx(), (150 * m_fDeltaTime));
			}
			else
			{
				oM.UpdateRect(100 * m_fDeltaTime);
				if (oM.CheckRect(FRONT, m_player->GetRect()) == false)//�ȿ� �ȵ�� ������
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
		if (m_Move + 200 * m_fDeltaTime <= 4670)//�ִ� �̵� ����
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

	if (m_player->GetPlayerState() == JUMP)//���� 
		PlayerJump();
	else if (m_player->GetPlayerState() != JUMP)//�÷��̾ �������°� �ƴ϶��
		PlayerMove(); //������ ���� �Լ��� �̵�

	if (oM.SearchPoint(m_player->Getx()) == true)
		m_player->UpdateScore(0); //����

	IM.StatePlate(hdc, MemDC[0], m_player->GetPlayerLife(), m_player->GetScore(), m_iTimeBonus, m_iStage);
	if (oM.ObstacleGetx(m_Move) == true)
	{
		oM.Draw(hdc, MemDC[0], m_Move, 1); //��ֹ� �׸���
		m_player->Draw(hdc, MemDC[0]); //���������� �÷��̾��� ������ �׸���
		oM.Draw(hdc, MemDC[0], m_Move, 2); //��ֹ� �׸���
	}
	else
	{
		oM.Draw(hdc, MemDC[0], m_Move, 0); //��ֹ� �׸���
		m_player->Draw(hdc, MemDC[0]); //���������� �÷��̾��� ������ �׸���
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
		StageDisplay();//�׾����� ���� ����� ����������

			  //�� �ʱ�ȭ
	m_player->ChangeState(DEATH); //�÷��̾� ���� ��ȭ��Ű�� stop����
	m_player->PlayerReset();
	DataRelease();
}


void Circus::EndEvent(int Number)//�� ��� ��ȭ -> ���ھ� ->�޼��� �ڽ� -> ȭ�� or �׳� ����
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
				if (MessageBox(m_hWnd, TEXT("������ �����Ͻðڽ��ϱ�?"), TEXT("���� Ŭ����"), MB_OKCANCEL) == IDOK)
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
				oM.Draw(hdc, MemDC[0], m_Move, WIN);//end�� ����ϱ� ���ؼ� 4��� ������ ��Ȳ�� ����
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
				oM.Draw(hdc, MemDC[0], m_Move, WIN);//end�� ����ϱ� ���ؼ� 4��� ������ ��Ȳ�� ����
				m_player->Draw(hdc, MemDC[0]);
				BitBlt(hdc, 0, 0, 455, 700, MemDC[0], 0, 0, SRCCOPY);
				Count++;
				if (Count == 2)
					Count = 0;
			}
			else
			{
				DeleteHDC1();
				if (MessageBox(m_hWnd, TEXT("������ �����Ͻðڽ��ϱ�?"), TEXT("���� Ŭ����"), MB_OKCANCEL) == IDOK)
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
	MemDC[0] = CreateCompatibleDC(hdc); //�����÷��̿� ��ȭ��
	m_BitMap[0] = CreateCompatibleBitmap(hdc, 455, 700);
	m_OldBitmap[0] = (HBITMAP)SelectObject(MemDC[0], m_BitMap[0]);
}
void Circus::CreateHDC2()
{
	MemDC[1] = CreateCompatibleDC(hdc); //Ÿ��Ʋ�� ��ȭ�� 
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
	m_Move = 0;//ù ��ġ�� �̵��ϰ� �ϱ� - ��� ���� ��ġ�� �ʱ�ȭ�ȴ�.
	m_iTimeBonus = 8000;
	m_fCurJumpTime = 0;//�����ð� �ʱ�ȭ - ���ϸ� �����ϰ� �׾����� ���� ��ġ�� �ð��� ���� ��������
	oM.Init();//��ֹ� ��ġ �ʱ�ȭ
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