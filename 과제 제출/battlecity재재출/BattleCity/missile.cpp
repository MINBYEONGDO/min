
#include "missile.h"



missile::missile()
{
	Link = NULL;
	m_Number = 0;
	m_Count = 0;
	ExplosionCurClock = clock();
	ExplosionLastClock = clock();
}
void missile::Init()//필요한가?
{
	m_ix;
	m_iy;
	m_Bitmap = BitmapManager::GetInstance()->GetImange(38);//아니면 39
}
void missile::CreateMissile(missile *Missile, int Tank_x, int Tank_y, int Tank_Direction, int Number)
{
	Missile->m_Bitmap = BitmapManager::GetInstance()->GetImange(38);//아니면 39
	if (Tank_Direction == UP)
	{
		Missile->m_ix = Tank_x + 13;
		Missile->m_iy = Tank_y - 10;
	}
	else if (Tank_Direction == DOWN)
	{
		Missile->m_ix = Tank_x + 13;
		Missile->m_iy = Tank_y + 26;
	}
	else if (Tank_Direction == LEFT)
	{
		Missile->m_ix = Tank_x - 5;
		Missile->m_iy = Tank_y + 11;
	}
	else if (Tank_Direction == RIGHT)
	{
		Missile->m_ix = Tank_x + 30;
		Missile->m_iy = Tank_y + 9;
	}
	Missile->m_Rect.top = Missile->m_iy - 2;
	Missile->m_Rect.bottom = Missile->m_iy + 7;
	Missile->m_Rect.left = Missile->m_ix - 2;
	Missile->m_Rect.right = Missile->m_ix + 7;


	Missile->m_Direction = Tank_Direction;
	Missile->m_Number = Number;
	Missile->m_bCrush = false;
	Missile->m_bExplosion = false;
	Missile->m_bExplosionEnd = false;
	Missile->m_iExplosion = 0;
	m_Count++;
	Missile->Link = NULL;
}
void missile::Draw(HDC hdc, missile* Node)
{
	if (m_bExplosionEnd == false)
		m_Bitmap->Draw(hdc, m_ix, m_iy);
}
void missile::Move()
{
	if (m_bCrush == false)
	{
		if (m_Direction == UP)
		{
			if (m_iy >= 100)
			{
				m_iy -= 15;
				m_Rect.bottom = m_iy + 7;
				m_Rect.top = m_iy - 2;
			}
			else//범위초과시
			{
				m_bCrush = true;
				m_bExplosion = true;
				m_iCrushType = BLOCK;
			}

		}
		else if (m_Direction == DOWN)
		{
			if (m_iy <= 550)
			{
				m_iy += 15;
				m_Rect.bottom = m_iy + 7;
				m_Rect.top = m_iy - 2;
			}
			else//범위초과시
			{
				m_bCrush = true;
				m_bExplosion = true;
				m_iCrushType = BLOCK;
			}
		}
		else if (m_Direction == LEFT)
		{
			if (m_ix >= 100)
			{
				m_ix -= 15;
				m_Rect.left = m_ix - 2;
				m_Rect.right = m_ix + 7;
			}
			else//범위초과시
			{
				m_bCrush = true;
				m_bExplosion = true;
				m_iCrushType = BLOCK;
			}
		}
		else if (m_Direction == RIGHT)
		{
			if (m_ix <= 580)
			{
				m_ix += 15;
				m_Rect.left = m_ix - 2;
				m_Rect.right = m_ix + 7;
			}
			else//범위초과시
			{
				m_bCrush = true;
				m_iCrushType = BLOCK;
				m_bExplosion = true;
			}
		}
	}
}


void missile::Delete(missile** Node, int Number)
{
	missile* tmp1;
	missile* tmp2;

	if ((*Node) == NULL)
		return;
	if ((*Node)->m_Number == 0 && Number == 0)
	{
		tmp1 = (*Node);
		(*Node) = (*Node)->Link;
		delete tmp1;
		tmp1 = NULL;
	}
	else
	{
		tmp1 = (*Node);
		tmp2 = (*Node)->Link->Link;
		//(*Node) = (*Node)->Link;
		delete tmp1->Link;
		//delete tmp2;
		tmp1->Link = NULL;
		tmp1->Link = tmp2;
	}
}
void missile::ExplosionEvent()
{
	if (m_iCrushType == MISSILE)
	{
		m_iExplosion = 0;
		m_bExplosionEnd = true;
	}
	ExplosionCurClock = clock();
	if (ExplosionCurClock - ExplosionLastClock > 150)
	{
		ExplosionLastClock = clock();
		if (m_iExplosion == 0 && m_bExplosion == true)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(31);
			m_ix -= 15;
			m_iExplosion++;
		}
		else if (m_iExplosion == 1 && m_bExplosion == true)
		{
			if (m_iCrushType == BLOCK)
			{
				m_iExplosion = 0;
				m_bExplosionEnd = true;
			}
			else
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(32);
				m_iExplosion++;
			}
		}
		else if (m_iExplosion == 2 && m_bExplosion == true)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(33);
			m_iExplosion++;
		}
		else if (m_iExplosion == 3 && m_bExplosion == true)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(34);
			m_ix -= 15;
			m_iExplosion++;
		}
		else if (m_iExplosion == 4 && m_bExplosion == true)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(35);
			m_ix -= 5;
			m_iExplosion++;
		}
		else if (m_iExplosion == 5 && m_bExplosion == true)
		{
			//m_Bitmap = BitmapManager::GetInstance()->GetImange(38);
			m_iExplosion = 0;
			m_bExplosionEnd = true;
		}
	}
}
void missile::ReNumber(int Number)
{
	m_Number = Number;
}
void missile::SetLink(missile* Node)
{
	if (Link == NULL)
	{
		Link = Node;
		Link->Link = NULL;
	}
	else
	{
		Link->SetLink(Node);
	}
}
void missile::ChangeStateCrush()
{
	m_bCrush = true;
}
void missile::Explosion(int CrushType)
{
	m_bExplosion = true;
	m_iCrushType = CrushType;
}

void missile::Release(missile* Node)
{
	while (Node != NULL)
	{
		Node = Node->Link;
		Release(Node);
		delete Node;
		Node = NULL;
	}
}

missile::~missile()
{
}