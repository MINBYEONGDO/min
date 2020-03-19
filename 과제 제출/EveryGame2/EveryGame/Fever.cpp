
#include "Fever.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"


Fever::Fever()
{
	m_FeverState = NON;//피버 상태 0,1,2,3
	m_Fevergauge = 0; //피버 게이지 계수
	m_FeverTimeCount = 0;//피버 유지시간체크
	m_bFever = false;//현재 피버상태인지 아닌지
	m_bFeverChange = false;
	m_DrawEffect = true;
}
void Fever::Init()
{
	m_pFever1 = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//Fever1.bmp");
	m_pFever2 = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//Fever2.bmp");
	m_pFever3 = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//Fever3.bmp");
	m_pFeverEffect = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//FeverEffect3.bmp");
}
void Fever::Update(int GameType)
{
	if (GameType == FLIGHTGAME)
	{
		if (m_FeverState == NON)
		{
			if (m_Fevergauge + 0.08 < 1)
			{

				m_Fevergauge += 0.08;
			}
			else if (m_Fevergauge + 0.08 >= 1)
			{
				m_Fevergauge = 0;
				m_FeverState = NOMAL;
				m_bFever = true;
				m_bFeverChange = true;
				m_FeverTimeCount = 0;
			}
		}
		else if (m_FeverState == NOMAL)
		{
			if (m_Fevergauge + 0.1 < 1)
			{
				m_Fevergauge += 0.1;
			}
			else if (m_Fevergauge + 0.08 >= 1)
			{
				m_Fevergauge = 0;
				m_FeverState = SUPER;
				m_bFever = true;
				m_bFeverChange = true;
				m_FeverTimeCount = 0;
			}
		}
		else if (m_FeverState == SUPER)
		{
			if (m_Fevergauge + 0.12 < 1)
			{
				m_Fevergauge += 0.12;
			}
			else if (m_Fevergauge + 0.08 >= 1)
			{
				m_Fevergauge = 0;
				m_FeverState = ULTRA;
				m_bFever = true;
				m_bFeverChange = true;
				m_FeverTimeCount = 0;
			}
		}
		else if (m_FeverState == ULTRA)
		{
			if (m_Fevergauge + 0.15 < 1)
			{
				m_Fevergauge += 0.15;
			}
		}
	}
	else if (GameType == PAPERGAME)
	{
		if (m_Fevergauge >= 1)
		{
			m_Fevergauge = 0;
			if (m_FeverState == NON)
			{
				m_FeverState = NOMAL;
				m_bFever = true;
				m_bFeverChange = true;
				m_FeverTimeCount = 0;
			}
			else if (m_FeverState == NOMAL)
			{
				m_FeverState = SUPER;
				m_bFeverChange = true;
				m_FeverTimeCount = 0;
			}
			else if (m_FeverState == SUPER)
			{
				m_FeverState = ULTRA;
				m_bFeverChange = true;
				m_FeverTimeCount = 0;
			}
		}
	}
	if (m_bFever == true)
		FeverTime();
}
void Fever::FeverTime()
{
	if (m_FeverTimeCount != 5)
		m_FeverTimeCount++;
	else
	{
		m_bFever = false;
		m_FeverState = NON;
		m_Fevergauge = 0;
		m_FeverTimeCount = 0;
	}
}
void Fever::FeverGauge()
{
	if (m_FeverState == NON)
	{
		if (m_Fevergauge + 0.10 < 1)
			m_Fevergauge += 0.10;
		else if (m_Fevergauge + 0.10 >= 1)
			m_Fevergauge = 1;
	}
	if (m_FeverState == NOMAL)
	{
		if (m_Fevergauge + 0.13 < 1)
			m_Fevergauge += 0.13;
		else if (m_Fevergauge + 0.13 >= 1)
			m_Fevergauge = 1;
	}
	if (m_FeverState == SUPER)
	{
		if (m_Fevergauge + 0.15 < 1)
			m_Fevergauge += 0.15;
		else if (m_Fevergauge + 0.15 >= 1)
			m_Fevergauge = 1;
	}
	if (m_FeverState == ULTRA)
	{
		if (m_Fevergauge + 0.15 < 1)
			m_Fevergauge += 0.15;
		else if (m_Fevergauge + 0.15 >= 1)
			m_Fevergauge = 1;
	}
}
void Fever::FeverGaugeDisCount()
{
	if (m_Fevergauge > 0.4)
		m_Fevergauge = m_Fevergauge - 0.4;
	else if (m_Fevergauge <= 0.4)
		m_Fevergauge = 0;
}
void Fever::FeverChangeReset()
{
	m_bFeverChange = false;
}
void Fever::Draw()
{
	if (m_FeverState == NON)
		m_pFever1->DynamicDrawBitblt(20, 55, m_Fevergauge, 1);
	if (m_FeverState == NOMAL)
	{
		m_pFever1->DynamicDrawBitblt(20, 55, 1, 1);
		m_pFever2->DynamicDrawBitblt(20, 55, m_Fevergauge, 1);
	}
	if (m_FeverState == SUPER)
	{
		m_pFever2->DynamicDrawBitblt(20, 55, 1, 1);
		m_pFever3->DynamicDrawBitblt(20, 55, m_Fevergauge, 1);
	}
	if (m_FeverState == ULTRA)
		m_pFever3->DynamicDrawBitblt(20, 55, 1, 1);
	if (m_bFever == true)//타이머 사용하기?
	{
		if (m_DrawEffect == true)
		{
			m_pFeverEffect->Draw(0, 0);
			m_DrawEffect = false;
		}
		else
			m_DrawEffect = true;
	}
}

void Fever::FeverReset()
{
	m_FeverState = NON;
	m_Fevergauge = 0; //피버 게이지 계수
	m_FeverTimeCount = 0;//피버 유지시간체크
	m_bFever = false;//현재 피버상태인지 아닌지
	m_bFeverChange = false;
}

Fever::~Fever()
{
}
