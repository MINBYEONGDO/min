#include "Timer.h"//클락이 나았나? 흠


Timer::Timer()
{
	m_ms = 0;
	m_Second = 45;
	m_bTimeOut = false;
}
void Timer::Init(int Number)
{
	m_msLabel = new JEngine::Label;
	m_msLabel->Init("00", 230, 400, NULL);//620//590
	m_SecLabel = new JEngine::Label;
	m_SecLabel->Init("45 : ", 200, 400, NULL);
}
void Timer::Update()
{
	string time;
	if (m_ms != 0)
		m_ms--;
	else if (m_ms == 0 && m_Second != 0)
	{
		m_Second--;
		m_ms = 99;
	}
	time = to_string(m_Second);
	time = time + " : ";
	m_SecLabel->Init(time, 200, 625, NULL);
	time = to_string(m_ms);
	if (m_ms < 10)
		time = "0" + time;
	m_msLabel->Init(time, 230, 625, NULL);
	if (m_ms == 0 && m_Second == 0)
	{
		m_bTimeOut = true;
		return;
	}
}

void Timer::Draw()
{
	m_msLabel->Draw();
	m_SecLabel->Draw();
}
Timer::~Timer()
{
	delete m_msLabel ;
	delete m_SecLabel ;
}