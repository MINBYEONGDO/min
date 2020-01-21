#include "Player.h"

Player::Player()
{
	m_iFlag=0;
}
void Player::Init(int Mode)
{
	if(Mode == BEGINNER)
		m_iFlag = 10;
	else if (Mode == INTERMEDIATE)
		m_iFlag = 50;
	else if (Mode == ADVANCED)
		m_iFlag = 80;
}

void Player::FlagDown()
{
	if (m_iFlag >0)
		m_iFlag--;
}
void Player::FlagUp(int Mode)
{
	if (Mode == BEGINNER)
	{
		if(m_iFlag <10)
			m_iFlag++;
	}
	else if (Mode == INTERMEDIATE)
	{
		if (m_iFlag < 50)
			m_iFlag++;
	}
	else if (Mode == ADVANCED)
	{
		if (m_iFlag < 80)
			m_iFlag++;
	}
}

Player::~Player()
{
}
