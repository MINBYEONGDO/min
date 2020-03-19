
#include "Paper.h"
#include "InputManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"


Paper::Paper()
{
	m_Movefx = 0;//이동속도에 필요
	m_Movefy = 0;
	m_PaperNumber = 0;
	m_bMove = false;//확정아님
	m_breach = false;
}
void Paper::Init(int Number)
{
	int RColor = rand() % 4;
	//m_MoveDirection = 5;
	m_fx = 155;//배치에 필요
	m_fy = 297;
	m_Movefx = 0;//이동속도에 필요
	m_Movefy = 0;
	m_Color = RColor;//색깔확인
	if (m_Color == GREEN)
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//ColoredPaperGreen.bmp");//비트맵
	else if (m_Color == BLUE)
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//ColoredPaperBlue.bmp");//비트맵
	else if (m_Color == RED)
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//ColoredPaperRed.bmp");//비트맵
	else if (m_Color == YELLOW)
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//ColoredPaperYellow.bmp");//비트맵
	m_PaperNumber = Number;
	m_bMove = false;//확정아님
	m_Score = 90;
	m_bReturn = false;
	m_Answer = NOTHING;
	m_bLive = true;
	m_MoveDirection = DONMOVE;
}
void Paper::Input(int Direction, int MoveType)
{
	if (m_bMove == false)//하나만 움직이게 하기 위해서
	{
		if (Direction == UP)
		{
			m_MoveDirection = UP;
			m_Movefx = 0;
			m_Movefy = 10;
			m_bMove = true;
		}
		else if (Direction == DOWN)
		{
			m_MoveDirection = DOWN;
			m_Movefx = 0;
			m_Movefy = 10;
			m_bMove = true;
		}
		else if (Direction == LEFT)
		{
			m_MoveDirection = LEFT;
			m_Movefx = 10;
			m_Movefy = 0;
			m_bMove = true;
		}
		else if (Direction == RIGHT)
		{
			m_MoveDirection = RIGHT;
			m_Movefx = 10;
			m_Movefy = 0;
			m_bMove = true;
		}
		if (MoveType == 0)
			m_Answer = NOTANSWER;
		else if (MoveType == 1)
			m_Answer = ANSWER;
	}
}
void Paper::Move()
{
	if (m_bLive == true)
	{
		if (m_MoveDirection == UP)
		{
			if (m_Answer == ANSWER)
			{
				if (m_fy > 148)
					m_fy -= m_Movefy;
				else
				{
					m_breach = true;
					m_MoveDirection = DONMOVE;
				}
			}
			else if (m_Answer == NOTANSWER)
			{
				if (m_fy > 250 && m_bReturn == false)
				{
					m_fy -= m_Movefy;
				}
				else
				{
					if (m_fy < 297)
					{
						m_bReturn = true;
						m_fy += m_Movefy;
					}
					else
					{
						m_bReturn = false;
						m_fy = 297;
						m_bMove = false;
						m_Answer = NOTHING;
					}
				}
			}
		}
		else if (m_MoveDirection == DOWN)
		{
			if (m_Answer == ANSWER)
			{
				if (m_fy < 443)
					m_fy += m_Movefy;
				else
				{
					m_breach = true;
					m_MoveDirection = DONMOVE;
				}
			}
			else if (m_Answer == NOTANSWER)
			{
				if (m_fy < 350 && m_bReturn == false)
				{
					m_fy += m_Movefy;
				}
				else
				{
					if (m_fy < 297)
					{
						m_bReturn = true;
						m_fy -= m_Movefy;
					}
					else
					{
						m_bReturn = false;
						m_fy = 297;
						m_bMove = false;
						m_Answer = NOTHING;
					}
				}
			}
		}
		else if (m_MoveDirection == LEFT)
		{
			if (m_Answer == ANSWER)
			{
				if (m_fx > 16)
					m_fx -= m_Movefx;
				else
				{
					m_breach = true;
					m_MoveDirection = DONMOVE;
				}
			}
			else if (m_Answer == NOTANSWER)
			{
				if (m_fx > 100 && m_bReturn == false)
				{
					m_fx -= m_Movefx;
				}
				else
				{
					if (m_fy < 155)
					{
						m_bReturn = true;
						m_fx += m_Movefx;
					}
					else
					{
						m_bReturn = false;
						m_fx = 155;
						m_bMove = false;
						m_Answer = NOTHING;
					}
				}
			}
		}
		else if (m_MoveDirection == RIGHT)
		{
			if (m_Answer == ANSWER)
			{
				if (m_fx < 291)
					m_fx += m_Movefx;
				else
				{
					m_MoveDirection = DONMOVE;
					m_breach = true;
				}
			}
			else if (m_Answer == NOTANSWER)
			{
				if (m_fx < 220 && m_bReturn == false)
				{
					m_fx += m_Movefx;
				}
				else
				{
					if (m_fy < 155)
					{
						m_bReturn = true;
						m_fx -= m_Movefx;
					}
					else
					{
						m_bReturn = false;
						m_fx = 155;
						m_bMove = false;
						m_Answer = NOTHING;
					}
				}
			}
		}
	}
}
void Paper::Draw()
{
	if (m_bLive == true)
		m_pBitmap->Draw(m_fx, m_fy);
}
void Paper::PaperReach()
{
	m_breach = false;
	m_bMove = false;
	m_Answer = NOTHING;
	m_bLive = false;
}
Paper::~Paper()
{
}