#include "obstacleManager.h"

obstacleManager::obstacleManager()
{
	FireRing = new Ring[20];
	FireFront = new Front[10];
	m_End = new End; // Rect필요 , 충돌이 필요하니 인터페이스보다 옵스태클쪽에 더 적합
	m_Money= new Money;
	m_imageChange = 0;
}

void obstacleManager::Init()
{
	int RNumber = 0;
	RNumber = rand() %19;
	for (int i = 0; i < 20; i++)
		FireRing[i].SetData(i, RING);
	for (int i = 0; i < 10; i++)
		FireFront[i].SetData(i, FRONT);
	m_End->SetData(0, END);
	m_Money->SetData(RNumber,MONEY);
	SetBitmap();
}
bool obstacleManager::CheckRect(int type, RECT playerRect)
{
	RECT rect;
	if (type == RING)
	{
		for (int i = 0; i < 20; i++)
		{
			if (IntersectRect(&rect, &FireRing[i].GetRect(), &playerRect) == true)
				return true;
		}
	}
	else if (type == FRONT)
	{
		for (int i = 0; i < 10; i++)
		{
			if (IntersectRect(&rect, &FireFront[i].GetRect1(), &playerRect) == true)
				return true;
			else if (IntersectRect(&rect, &FireFront[i].GetRect2(), &playerRect) == true)
				return true;
		}
	}
	else if (type == END)
	{
		if (IntersectRect(&rect, &m_End->GetRect(), &playerRect) == true)
			return true;
	}
	return false;
}
bool  obstacleManager::CheckMoney(RECT playerRect)
{
	RECT rect;
	if (m_Money->CheckLive() == true)
	{
		if (IntersectRect(&rect, &m_Money->GetRect(), &playerRect) == true)
		{
			m_Money->ChangeState();
			return true;
		}
	}
	return false;
}
void obstacleManager::SetBitmap()
{
	for (int i = 0; i < 20; i++)
		FireRing[i].SetBitmap(9);
	for (int i = 0; i < 10; i++)
		FireFront[i].SetBitmap(4);
	m_End->SetBitmap(22);
	m_Money->SetBitmap(23);
}

void obstacleManager::Draw(HDC hdc, HDC MemDC, int Move, int Number)
{
	m_CurClock = clock();
	if (m_CurClock - m_LastClock > 200)
	{
		m_LastClock = clock();
		if (m_imageChange == 1)
			m_imageChange = 0;
		else if (m_imageChange == 0)
			m_imageChange = 1;
	}
	if (Number != WIN)//끝날때 End만 출력하기 위해서
	{
		for (int i = 0; i < 20; i++)
		{
			FireRing[i].CheckifMove(Move);//플레이어와 일정간격에 위치하면
					 // 그 위치에 맞는 링만 움직일수 있도록하는 함수
			FireRing[i].MoveRect(Move);//링은 현재 플레이어가 이동함에 따라
					 //변화도 하지만 링 자체도 일정속도로 이동한다 이를 위해 사용하는 함수
			if (Number == 1)
				FireRing[i].Draw(hdc, MemDC, i, Move, m_imageChange + 2);
			else if (Number == 2)
				FireRing[i].Draw(hdc, MemDC, i, Move - 26, m_imageChange + 5);
			else
				FireRing[i].Draw(hdc, MemDC, i, Move, m_imageChange);

		}
		for (int i = 0; i < 10; i++)
		{
			FireFront[i].Draw(hdc, MemDC, i, Move, m_imageChange);
			FireFront[i].MoveRect(Move);
		}
		if (m_Money->CheckLive() == true)
		{
			m_Money->Draw(hdc, MemDC, 0, Move, 0);
			m_Money->MoveRect(Move);
		}
	}
	m_End->Draw(hdc, MemDC, 0, Move, 0);
}

void obstacleManager::UpdateRect(float Move)
{
	m_Money->UpdateRect(Move);
	for (int i = 0; i < 20; i++)
		FireRing[i].UpdateRect(Move);
	for (int i = 0; i < 10; i++)
		FireFront[i].UpdateRect(Move);
	m_End->UpdateRect(Move);
}

bool obstacleManager::ObstacleGetx(int Move)
{
	for (int i = 0; i < 20; i++)
	{
		if (FireRing[i].Getx() + 50 >= 65 + Move && FireRing[i].Getx() <= 133 + Move)
		{// 앞의 것이 플레이어의 뒷 랭틍글 래프트 / 뒤의꺼가 플레이어의 앞 렉탱글 라이트
			return true;
		}
	}
	return false;
}


bool obstacleManager::SearchPoint(float player_x)
{
	for (int i = 0; i < 20; i++)
	{
		if (FireRing[i].GetRectRight() <= player_x && FireRing[i].GetScroeGive() == true)
		{
			FireRing[i].ChangeScoreGive();
			return true;
		}
	}
	for (int i = 0; i < 10; i++)
	{
		if (FireFront[i].GetRectRight2() <= player_x && FireFront[i].GetScroeGive() == true)
		{
			FireFront[i].ChangeScoreGive();
			return true;
		}
	}
	return false;
}
obstacleManager::~obstacleManager()
{
	delete[20] FireRing;
	delete[10] FireFront;
	delete m_End;
	delete m_Money;
}