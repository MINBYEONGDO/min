
#include "Star.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"



Star::Star()
{
	m_pBitmap1 = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//FlightGameStar1.bmp");
	m_pBitmap2 = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//FlightGameStar2.bmp");
	m_pBitmap3 = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//FlightGameStar3.bmp");
}
void Star::Init(int GameType, int Number, int Hit, int Score, int playerx, int playery)
{
	float Rdirection;
	float Rfx;
	float Rfy;
	float RMx;
	float RMy;
	if (GameType == FLIGHTGAME)
	{
		Rdirection = rand() % 4;//상하 좌우
		Rfx = (rand() % 322) + 92;
		Rfy = (rand() % 493) + 92;
		RMx = rand() % 6;
		RMy = rand() % 6;
		m_StarNumber = Number;
		if (Rdirection == UP)
		{
			m_fy = 100;
			m_fx = Rfx;
			if (m_fx >= playerx)
				m_Movefx = m_fx - playerx;
			else if (m_fx < playerx)
				m_Movefx = playerx - m_fx;
			m_Movefy = playery;
			m_Move = m_Movefx * m_Movefx + m_Movefy * m_Movefy;
			m_Move = sqrt(m_Move);
			m_Movefx = m_Movefx / m_Move;
			m_Movefy = m_Movefy / m_Move;
			if (m_fx > playerx)
				m_Movefx = (-1)*m_Movefx;
			m_StartDirection = UP;
		}
		if (Rdirection == DOWN)
		{
			m_fy = 545;
			m_fx = Rfx;
			if (m_fx >= playerx)
				m_Movefx = m_fx - playerx;
			else if (m_fx < playerx)
				m_Movefx = playerx - m_fx;
			m_Movefy = 585 - playery;
			m_Move = m_Movefx * m_Movefx + m_Movefy * m_Movefy;
			m_Move = sqrt(m_Move);
			m_Movefx = m_Movefx / m_Move;
			m_Movefy = m_Movefy / m_Move;
			m_Movefy = (-1)* m_Movefy;
			if (m_fx > playerx)
				m_Movefx = (-1)*m_Movefx;
			m_StartDirection = DOWN;
		}
		if (Rdirection == LEFT)
		{
			m_fx = 0;
			m_fy = Rfy;
			if (m_fy >= playery)
				m_Movefy = m_fy - playery;
			else if (m_fy < playery)
				m_Movefy = playery - m_fy;
			m_Movefx = playerx;
			m_Move = m_Movefx * m_Movefx + m_Movefy * m_Movefy;
			m_Move = sqrt(m_Move);
			m_Movefx = m_Movefx / m_Move;
			m_Movefy = m_Movefy / m_Move;
			if (m_fy > playery)
				m_Movefy = (-1)*m_Movefy;
			m_StartDirection = LEFT;
		}
		if (Rdirection == RIGHT)
		{
			m_fx = 414;
			m_fy = Rfy;
			if (m_fy >= playery)
				m_Movefy = m_fy - playery;
			else if (m_fy < playery)
				m_Movefy = playery - m_fy;

			m_Movefx = 414 - playerx;
			m_Move = m_Movefx * m_Movefx + m_Movefy * m_Movefy;
			m_Move = sqrt(m_Move);
			m_Movefx = m_Movefx / m_Move;
			m_Movefy = m_Movefy / m_Move;
			m_Movefx = (-1)* m_Movefx;
			if (m_fy > playery)
				m_Movefy = (-1)*m_Movefy;
			m_StartDirection = RIGHT;
		}
	}
	else if (GameType == PAPERGAME)
	{
		m_fy = 320;
		m_fx = 180;
		m_StarNumber = Number;
	}
	m_bLive = true;
	m_rect.bottom = m_fy + 59;
	m_rect.top = m_fy + 0;
	m_rect.left = m_fx + 0;
	m_rect.right = m_fx + 53;
	m_StarScore = 100 + 100 * Hit;
	LScore = new JEngine::Label;
	LScore->Init(to_string(m_StarScore), m_fx + 15, m_fy + 20, 0);
	if (Hit < 5)// 피버에 따라 색변화?
		m_pBitmap = m_pBitmap1;
	else if (Hit >= 5 && Hit < 14)
		m_pBitmap = m_pBitmap2;
	else if (Hit >= 14)
		m_pBitmap = m_pBitmap3;
}
void Star::Move()
{
	if (m_bLive == true)
	{
		m_fx += m_Movefx;//곱셉이라 속도가 가속되고 일정치 않게 된다.
		m_fy += m_Movefy;
		m_rect.bottom = m_fy + 59;
		m_rect.top = m_fy + 0;
		m_rect.left = m_fx + 0;
		m_rect.right = m_fx + 53;
		LScore->Init(to_string(m_StarScore), m_fx + 15, m_fy + 20, 0);
		//if (m_rect.top < 92)
		// m_bLive = false;
		//else if (m_rect.bottom > 608)
		// m_bLive = false;
		//else if (m_rect.left > 414)
		// m_bLive = false;
		//else if (m_rect.right < 0)
		// m_bLive = false;
	}
}
bool Star::SideOut()
{
	if (m_rect.top < 92)
		return false;
	else if (m_rect.bottom > 608)
		return false;
	else if (m_rect.left > 414)
		return false;
	else if (m_rect.right < 0)
		return false;
	return true;
}
void Star::Out()
{
	//m_StarNumber--;
	m_bLive = false;
}
void Star::BitmapChange(int Hit)//점수초과시 비트맵 변경
{
	m_StarScore = 100 + 100 * Hit;
	if (Hit < 5)// 피버에 따라 색변화?
		m_pBitmap = m_pBitmap1;
	else if (Hit >= 5 && Hit < 14)
		m_pBitmap = m_pBitmap2;
	else if (Hit >= 14)
		m_pBitmap = m_pBitmap3;
	LScore->Init(to_string(m_StarScore), m_fx + 15, m_fy + 20, 0);
}
void Star::Draw()
{
	if (m_bLive == true)
	{
		m_pBitmap->Draw(m_fx, m_fy);
		LScore->Draw();
	}
}
void  Star::Release()
{
	JEngine::ResoucesManager::GetInstance()->~ResoucesManager();
}
Star::~Star()
{
	//JEngine::ResoucesManager::GetInstance()->~ResoucesManager();
	delete LScore;
}