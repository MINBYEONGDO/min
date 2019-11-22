
#include "Gamemanager.h"


Gamemanager* Gamemanager::m_pThis = NULL;

Gamemanager::Gamemanager()
{
	m_Count = 0;
	m_ClickCount = 0;
	m_VictoryCount = 0;
}
void Gamemanager::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);
	int CardType;
	for (int i = 0; i < 20; i++)
	{
		if (m_Count < 2)
		{
			CardType = DOG;
		}
		else if (m_Count < 4)
		{
			CardType = TIGER;
		}
		else if (m_Count < 6)
		{
			CardType = DUCK;
		}
		else if (m_Count < 8)
		{
			CardType = ELEPHAT;
		}
		else if (m_Count < 10)
		{
			CardType = COW;
		}
		else if (m_Count < 12)
		{
			CardType = HORSE;
		}
		else if (m_Count < 14)
		{
			CardType = CAT;
		}
		else if (m_Count < 16)
		{
			CardType = MONKEY;
		}
		else if (m_Count < 18)
		{
			CardType = FLOG;
		}
		else if (m_Count < 20)
		{
			CardType = CHICKEN;
		}
		m_vecBitmapList.push_back(new Bitmap(hdc, hInst, CardType));
		m_Count++;
	}
}
void Gamemanager::Draw(HWND hWnd, HDC hdc, int x, int y)
{
	int Number;
	for (auto iter = m_vecBitmapList.begin(); iter != m_vecBitmapList.end(); iter++)
	{
		Number = (*iter)->GetNumber();
		if (Number < 10)
		{
			if ((*iter)->GetBack() == false)
			{
				(*iter)->Draw(hdc, x + Number * 150, y, false);
			}
			else if ((*iter)->GetBack() == true)
			{
				(*iter)->Draw(hdc, x + Number * 150, y, true);
			}
		}
		else if (Number < 20)
		{
			if ((*iter)->GetBack() == false)
			{
				(*iter)->Draw(hdc, x + (Number - 10) * 150, y + 250, false);
			}
			else if ((*iter)->GetBack() == true)
			{
				(*iter)->Draw(hdc, x + (Number - 10) * 150, y + 250, true);
			}
		}
	}
	//그리고 나서 결과관련 함수 별도 생성
	MatchingCard(hWnd);
}

void Gamemanager::MatchingCard(HWND hWnd)
{
	int count = 0;
	int CardTypeTmp;
	if (m_ClickCount == 2)//두개를 클릭했을때
	{
		for (auto iter = m_vecBitmapList.begin(); iter != m_vecBitmapList.end(); iter++)
		{
			if (count == 0 && (*iter)->GetBack() == false && (*iter)->GetState() == false)
			{
				CardTypeTmp =(*iter)->GetCardType();//타입 저장
				(*iter)->CardStateChange();// 1번 정답상태 유지
				count++;
			}
			else if (count == 1 && (*iter)->GetBack() == false && (*iter)->GetState() == false)
			{
				if (CardTypeTmp == (*iter)->GetCardType())
				{
					(*iter)->CardStateChange();//2번 정답상태 유지
					m_VictoryCount++;
					if (m_VictoryCount == 10)
					{
						m_VictoryCount = 0;
						SendMessage(hWnd, 100,0,0);
						return;
					}
				}
				else if (CardTypeTmp != (*iter)->GetCardType())
				{//틀렸기에 정답상태로 바꿀필요가 없음
					(*iter)->ReverseCard();//뒷면으로 만들기
					for (auto iter2 = m_vecBitmapList.begin(); iter2 != m_vecBitmapList.end(); iter2++)
					{
						if ((*iter2)->GetBack() == false && (*iter2)->GetState() == true && (*iter2)->GetCardType() == CardTypeTmp)
						{
							(*iter2)->ReverseCard();//첫번째 카드 뒤집기
							(*iter2)->CardStateChange();//첫번째 카드 상태 바꾸기
						}
					}
					SetTimer(hWnd, 1, 1000, NULL);
				}
				count = 0;
			}
		}
		m_ClickCount = 0;
	}
}

void Gamemanager::ClickBitmap(HWND hWnd, int x, int y)
{
	
	for (int i = 0; i < 10; i++)
	{
		if ((x >= 20 + i * 150 && x <= 20 + (i * 150) + 145) && (y >= 100 && y <= 335))
		{
			for (auto iter = m_vecBitmapList.begin(); iter != m_vecBitmapList.end(); iter++)
			{
				if ((*iter)->GetNumber() == i)
				{
					if ((*iter)->GetState() == false)
					{
						(*iter)->ReverseCard();
						m_ClickCount++;
						InvalidateRect(hWnd, NULL, TRUE);
					}
				}
			}
		}
	}
	for (int i = 10; i < 20; i++)
	{
		if (((x >= 20 + (i - 10) * 150 && x <= 20 + 145 + (i - 10) * 150)) && (y >= 350 && y <= 535))
		{
			for (auto iter = m_vecBitmapList.begin(); iter != m_vecBitmapList.end(); iter++)
			{
				if ((*iter)->GetNumber() == i)
				{
					if ((*iter)->GetState() == false)
					{
						(*iter)->ReverseCard();
						m_ClickCount++;
						InvalidateRect(hWnd, NULL, TRUE);
					}
				}
			}
		}
	}
}


void Gamemanager::Suffle(HWND hWnd)
{
	srand(time(NULL));
	int CardNumber;
	bool CheckNumber = true;
	for (auto iter = m_vecBitmapList.begin(); iter != m_vecBitmapList.end(); iter++)
	{
		CardNumber=rand() % 20;
		for (auto iter2 = m_vecBitmapList.begin(); iter2 != m_vecBitmapList.end(); iter2++)
		{
			if ((*iter2)->GetNumber() == CardNumber)//같은 값이 이미 사용했다면
			{
				CheckNumber = false;
				break;
			}
			else
				CheckNumber = true;
		}
		if (CheckNumber == false)
			iter--;
		else if (CheckNumber == true)
			(*iter)->SetCardNumber(CardNumber);
	}
}
void Gamemanager::CardReset()
{
	for (auto iter = m_vecBitmapList.begin(); iter != m_vecBitmapList.end(); iter++)
	{
		(*iter)->ResetCard();
	}
}
void Gamemanager::Release()
{
	for (auto iter = m_vecBitmapList.begin(); iter != m_vecBitmapList.end(); iter++)
	{
		delete *iter;
		*iter = NULL;
	}
	delete(m_pThis);
}

Gamemanager::~Gamemanager()
{
}
