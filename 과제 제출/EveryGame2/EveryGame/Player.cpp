
#include "Player.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"



Player::Player()
{
	m_fx = 0;
	m_fy = 0;
	m_fSpeedX = 200;
	m_Score = 0;
	m_bLive = true;
	m_ExplosionNumber = 0;
	m_pTimer = new JEngine::TimeManager;
}


void Player::Init()
{
	m_fx = 180;
	m_fy = 300;
	m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//FlightGameFlight.bmp");
	m_pTimer->init(true, 3);
	m_bLive = true;
	RectInit();
}
void Player::RectInit()
{
	//머리
	m_rect0.bottom = m_fy + 20;//21
	m_rect0.top = m_fy + 1;
	m_rect0.left = m_fx + 31;//30
	m_rect0.right = m_fx + 35;//36
	m_CheckRect0.bottom = m_fy + 20;
	m_CheckRect0.top = m_fy + 0;
	m_CheckRect0.left = m_fx + 31;
	m_CheckRect0.right = m_fx + 35;
	//날개
	m_rect1.bottom = m_fy + 44;//45
	m_rect1.top = m_fy + 21;
	m_rect1.left = m_fx + 2;//1
	m_rect1.right = m_fx + 64;//65
	m_CheckRect1.bottom = m_fy + 44;
	m_CheckRect1.top = m_fy + 21;
	m_CheckRect1.left = m_fx + 1;
	m_CheckRect1.right = m_fx + 65;
	//몸통
	m_rect2.bottom = m_fy + 58;//59
	m_rect2.top = m_fy + 45;
	m_rect2.left = m_fx + 28;//27
	m_rect2.right = m_fx + 42;//43
	m_CheckRect2.bottom = m_fy + 58;
	m_CheckRect2.top = m_fy + 45;
	m_CheckRect2.left = m_fx + 28;
	m_CheckRect2.right = m_fx + 42;
	//꼬리
	m_rect3.bottom = m_fy + 69;//70
	m_rect3.top = m_fy + 59;
	m_rect3.left = m_fx + 22;//21
	m_rect3.right = m_fx + 49;//50
	m_CheckRect3.bottom = m_fy + 69;
	m_CheckRect3.top = m_fy + 59;
	m_CheckRect3.left = m_fx + 22;
	m_CheckRect3.right = m_fx + 49;
}
void Player::Input(float fETime, int Number)
{
	if (m_bLive == true)
	{
		if (Number == UP)
		{
			m_CheckRect0.top -= fETime * m_fSpeedX;
			if (m_CheckRect0.top < 92)
				return;
		}
		else if (Number == DOWN)
		{
			m_CheckRect3.bottom += fETime * m_fSpeedX;
			if (m_CheckRect3.bottom > 608)
				return;
		}
		else if (Number == LEFT)
		{
			m_CheckRect1.left -= fETime * m_fSpeedX;
			if (m_CheckRect1.left < 0)
				return;

		}
		else if (Number == RIGHT)
		{
			m_CheckRect1.right += fETime * m_fSpeedX;
			if (m_CheckRect1.right > 414)
				return;
		}
		RectInit();//확인후 초기화시키기 
		if (Number == UP)
		{
			m_fy -= fETime * m_fSpeedX;
		}
		else if (Number == DOWN)
		{
			m_fy += fETime * m_fSpeedX;
		}
		else if (Number == LEFT)
		{
			m_fx -= fETime * m_fSpeedX;

		}
		else if (Number == RIGHT)
		{
			m_fx += fETime * m_fSpeedX;
		}
	}
	RectInit();
}


void Player::PlayerDeath()
{
	m_bLive = false;
}
void Player::PlayerReborn()
{
	m_fx = 180;
	m_fy = 300;
	m_bLive = true;
}
void Player::TimeScore()
{
	m_Score += 3;
}
void Player::StarScore(int Score)
{
	m_Score += Score;
}
void Player::ScoreReset()
{
	m_Score = 0;
}
void Player::ChangeExplosionBitmap()
{
	if (m_ExplosionNumber == 0)
	{
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//explosion1.bmp");
		m_ExplosionNumber = 1;
	}
	else if (m_ExplosionNumber == 1)
	{
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//explosion2.bmp");
		m_ExplosionNumber = 2;
	}
	else if (m_ExplosionNumber == 2)
	{
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//explosion3.bmp");
		m_ExplosionNumber = 3;
	}
	else if (m_ExplosionNumber == 3)
	{
		PlayerReborn();
		m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//FlightGameFlight.bmp");
		m_ExplosionNumber = 0;
	}
}
void Player::Draw()
{
	if (m_bLive == false)
	{
		if (m_pTimer->Update() == true)
		{
			ChangeExplosionBitmap();
		}
	}
	m_pBitmap->Draw(m_fx, m_fy);
}
Player::~Player()
{
	JEngine::ResoucesManager::GetInstance()->~ResoucesManager();
	delete m_pTimer;
}
