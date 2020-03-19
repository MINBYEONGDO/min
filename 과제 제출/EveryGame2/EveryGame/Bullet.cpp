
#include "Bullet.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"


Bullet::Bullet()
{
}
void Bullet::Init(int Number, int player_x, int player_y)
{
	//srand(time(NULL));

	float Rdirection;
	float Rfx;
	float Rfy;
	float RMx;
	float RMy;
	Rdirection = rand() % 4;//상하 좌우
	//Rdirection = DOWN;
	Rfx = rand() % 414;
	Rfy = rand() % 585;
	RMx = rand() % 10;
	RMy = rand() % 10;
	m_BulletNumber = Number;
	if (Rdirection == UP)
	{
		m_fy = 92;
		m_fx = Rfx;
		if (m_fx >= player_x)
			m_Movefx = m_fx - player_x;
		else if (m_fx < player_x)
			m_Movefx = player_x - m_fx;
		m_Movefy = player_y;
		m_Move = m_Movefx * m_Movefx + m_Movefy * m_Movefy;
		m_Move = sqrt(m_Move);
		m_Movefx = m_Movefx / m_Move;
		m_Movefy = m_Movefy / m_Move;
		
		if (m_fx > player_x)
			m_Movefx = (-1)*m_Movefx;
		m_StartDirection = UP;
	}
	if (Rdirection == DOWN)
	{
		m_fy = 585;
		m_fx = Rfx;
		if (m_fx >= player_x)
			m_Movefx = m_fx - player_x;
		else if (m_fx < player_x)
			m_Movefx = player_x - m_fx;
		m_Movefy = 585 - player_y;
		m_Move = m_Movefx * m_Movefx + m_Movefy * m_Movefy;
		m_Move = sqrt(m_Move);
		m_Movefx = m_Movefx / m_Move;
		m_Movefy = m_Movefy / m_Move;
		m_Movefy = (-1)* m_Movefy;
		if (m_fx > player_x)
			m_Movefx = (-1)*m_Movefx;
		m_StartDirection = DOWN;
	}
	if (Rdirection == LEFT)
	{
		m_fx = 0;
		m_fy = Rfy;
		if (m_fy >= player_y)
			m_Movefy = m_fy - player_y;
		else if (m_fy < player_y)
			m_Movefy = player_y - m_fy;
		m_Movefx = player_x;
		m_Move = m_Movefx * m_Movefx + m_Movefy * m_Movefy;
		m_Move = sqrt(m_Move);
		m_Movefx = m_Movefx / m_Move;
		m_Movefy = m_Movefy / m_Move;
		if (m_fy > player_y)
			m_Movefy = (-1)*m_Movefy;
		m_StartDirection = LEFT;
	}
	if (Rdirection == RIGHT)
	{
		m_fx = 414;
		m_fy = Rfy;
		if (m_fy >= player_y)
			m_Movefy = m_fy - player_y;
		else if (m_fy < player_y)
			m_Movefy = player_y - m_fy;

		m_Movefx = 414 - player_x;
		m_Move = m_Movefx * m_Movefx + m_Movefy * m_Movefy;
		m_Move = sqrt(m_Move);
		m_Movefx = m_Movefx / m_Move;
		m_Movefy = m_Movefy / m_Move;
		m_Movefx = (-1)* m_Movefx;
		if (m_fy > player_y)
			m_Movefy = (-1)*m_Movefy;
		m_StartDirection = RIGHT;
	}
	m_bLive = true;
	m_rect.bottom = m_fy + 17;
	m_rect.top = m_fy + 0;
	m_rect.left = m_fx + 0;
	m_rect.right = m_fx + 18;
	m_pBitmap = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//FlightGameBullet.bmp");
}
void Bullet::Move(float fETime)
{
	//공식이 아니라 clock으로 해서 시간 간격을 주고
	// m_Move fx  들로 각도를 줘야 할듯
	//이렇게 되면 speed 가 필요 없는뎅
	//Manager 생성하고 vec로 할지 Next로할지 생각해볼것

	if (m_bLive == true)
	{
		m_fx += m_Movefx;//곱셉이라 속도가 가속되고 일정치 않게 된다.
		m_fy += m_Movefy;
		m_rect.bottom = m_fy + 17;
		m_rect.top = m_fy + 0;
		m_rect.left = m_fx + 0;
		m_rect.right = m_fx + 18;

	}
}
bool Bullet::SideOut()
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
void Bullet::Out()
{
	m_bLive = false;
}

void Bullet::Draw()
{
	if (m_bLive == true)
		m_pBitmap->Draw(m_fx, m_fy);
}

Bullet::~Bullet()
{
}