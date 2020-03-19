
#include "BulletManager.h"



BulletManager::BulletManager()
{
	m_vecBullet.clear();//혹시모를 초기화??
	m_MaxBullet = 20;// 최대 갯수
	m_CurBullet = 0;//현재 갯수
	m_LiveBullet = 0;
}
void  BulletManager::AddBullet(int player_x, int player_y)
{
	if (m_LiveBullet < m_MaxBullet)
	{
		Bullet* btmp = new Bullet;
		btmp->Init(m_CurBullet, player_x, player_y);
		m_vecBullet.push_back(btmp);
		m_CurBullet++;
		m_LiveBullet++;
	}
}

void  BulletManager::Draw()
{
	for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
	{
		(*iter)->Draw();
	}
}
void BulletManager::MoveBullet(float fETime)
{
	for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
	{
		(*iter)->Move(fETime);
	}
	for (int i = 0; i < m_CurBullet; i++)
	{
		if (m_vecBullet[i]->GetBulletLive() == true && m_vecBullet[i]->SideOut() == false) // 범위를 완전히 벗어나서 죽으면
		{
			m_vecBullet[i]->Out();
			m_LiveBullet--;
		}         
	}
}

void  BulletManager::BulletDelete(int Number)
{
	int itmp;
	vector<Bullet*> vtmp;
	for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
	{
		if ((*iter)->GetBulletNumber() == Number)
		{
			(*iter)->Out();
			m_LiveBullet--;
		}
	}
}

bool BulletManager::Contact(RECT player)
{
	RECT rect;
	for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
	{
		if (IntersectRect(&rect, &player, &(*iter)->GetBulletRect()) == true && (*iter)->GetBulletLive() == true)
		{
			BulletDelete((*iter)->GetBulletNumber());
			return true;
		}
	}
	return false;
}

void BulletManager::Release()
{
	for (auto iter = m_vecBullet.begin(); iter != m_vecBullet.end(); iter++)
	{
		//SAFE_DELETE((*iter));
		delete (*iter);
	}
	m_vecBullet.clear();
	m_vecBullet.shrink_to_fit();
	m_CurBullet = 0;
	m_LiveBullet = 0;
}

BulletManager::~BulletManager()
{
}