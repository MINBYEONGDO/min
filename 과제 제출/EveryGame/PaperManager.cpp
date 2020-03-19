

#include "PaperManager.h"
#include "defines.h"


PaperManager::PaperManager()
{
	m_vecPaper.clear();
	m_CurPaper = 0;
	m_MaxPaper = 4;
	m_iAnswerCount = 0;
	m_LivePaper = 0;
	m_CheckAnswer = 30;
	m_bFirstCount == true;
}
void PaperManager::AddPaper()
{
	if (m_LivePaper != 4)
	{
		while (1)
		{
			Paper* ptmp = new Paper;
			ptmp->Init(m_CurPaper);
			m_vecPaper.push_back(ptmp);
			m_CurPaper++;
			m_LivePaper++;
			if (m_LivePaper == 4)
				break;
		}
	}
}

void PaperManager::Input(float fETime, int Direction)
{
	for (auto iter = m_vecPaper.begin(); iter != m_vecPaper.end(); iter++)
	{
		if ((*iter)->GetLive() == true)
		{
			if (Direction == UP)
			{
				if ((*iter)->GetColor() == GREEN)
					(*iter)->Input(UP, 1);
				else
				{
					(*iter)->Input(UP, 0);
					m_iAnswerCount = 0;
				}
			}
			else if (Direction == DOWN)
			{
				if ((*iter)->GetColor() == YELLOW)
					(*iter)->Input(DOWN, 1);
				else
				{
					(*iter)->Input(DOWN, 0);
					m_iAnswerCount = 0;
				}
			}
			else if (Direction == LEFT)
			{
				if ((*iter)->GetColor() == BLUE)
					(*iter)->Input(LEFT, 1);
				else
				{
					(*iter)->Input(LEFT, 0);
					m_iAnswerCount = 0;
				}
			}
			else if (Direction == RIGHT)
			{
				if ((*iter)->GetColor() == RED)
					(*iter)->Input(RIGHT, 1);
				else
				{
					(*iter)->Input(RIGHT, 0);
					m_iAnswerCount = 0;
				}
			}
			break;
		}
	}
}
void PaperManager::MovePaper()
{
	for (auto iter = m_vecPaper.begin(); iter != m_vecPaper.end(); iter++)
	{
		if ((*iter)->GetLive() == true)
		{
			(*iter)->Move();
			if ((*iter)->GetAnswer() == ANSWER)
				m_CheckAnswer = ANSWER;
			if (m_bFirstCount == true)
			{
				if ((*iter)->GetAnswer() == NOTANSWER)
				{
					m_CheckAnswer = NOTANSWER;
					m_bFirstCount = false;
				}
			}
			if ((*iter)->GetAnswer() == NOTHING)
			{
				m_bFirstCount = true;
			}
			if ((*iter)->GetReach() == true)
			{
				m_bReach = true;
			}
			break;
		}
	}
}
void PaperManager::PaperReach()
{
	for (auto iter = m_vecPaper.begin(); iter != m_vecPaper.end(); iter++)
	{
		if ((*iter)->GetLive() == true)
		{
			(*iter)->PaperReach();
			m_iAnswerCount++;//도달했으면 증가

			m_LivePaper--;
			AddPaper();
			m_bReach = false;
			break;
		}
	}
}

void PaperManager::Draw()
{
	//int size = m_vecPaper.size();
	//for (auto iter = m_vecPaper.end()-1; iter != m_vecPaper.begin(); iter--)
	//{
	// (*iter)->Draw();
	//}
	//m_vecPaper[0]->Draw();
	//for (int i = size - 1; i >= 0; i--)
	//{
	/// m_vecPaper[i]->Draw();
	//}
	int count = 0;
	for (auto iter = m_vecPaper.begin(); iter != m_vecPaper.end(); iter++)//뒤의 종이
	{
		if ((*iter)->GetLive() == true)
		{
			count++;
			if (count == 2)
			{
				(*iter)->Draw();
				break;
			}
		}
	}
	for (auto iter = m_vecPaper.begin(); iter != m_vecPaper.end(); iter++)//맨 처음 종이
	{
		if ((*iter)->GetLive() == true)
		{
			(*iter)->Draw();
			break;
		}
	}
}
void PaperManager::StateReset()
{
	if (m_CheckAnswer == NOTANSWER)
	{
		m_CheckAnswer = NOTHING;
	}
	if (m_iAnswerCount == 5)
		m_iAnswerCount = 0;
}
void PaperManager::Release()
{
	for (auto iter = m_vecPaper.begin(); iter != m_vecPaper.end(); iter++)
	{
		SAFE_DELETE((*iter));
	}
	m_vecPaper.clear();
	m_vecPaper.shrink_to_fit();
	m_CurPaper = 0;
	m_LivePaper = 0;
}

PaperManager::~PaperManager()
{
	for (auto iter = m_vecPaper.begin(); iter != m_vecPaper.end(); iter++)
	{
		delete (*iter);
	}
}
