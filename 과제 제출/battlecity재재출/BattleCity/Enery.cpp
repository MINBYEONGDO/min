
#include "Enery.h"

Enery::Enery()
{
	Next = NULL;
	MissileList = NULL;
	m_FireCurClock = clock();
	m_FireLastClock = clock();
	m_MissileMoveCurClock = clock();
	m_MissileMoveLastClock = clock();
}
void Enery::Init()
{
}
void Enery::Init(Enery *enery, int Number, int TankType)
{
	enery->m_ix = 0;
	enery->m_iy = 0;
	enery->m_rect.bottom = enery->m_iy + 26;
	enery->m_rect.top = enery->m_iy;
	enery->m_rect.left = enery->m_ix + 1;
	enery->m_rect.right = enery->m_ix + 31;

	enery->m_CheckRect.bottom = enery->m_iy + 26;
	enery->m_CheckRect.top = enery->m_iy;
	enery->m_CheckRect.left = enery->m_ix + 1;
	enery->m_CheckRect.right = enery->m_ix + 31;

	enery->m_ilife = 1;
	if (TankType == BOSS)
	{
		enery->m_ihealth = 3;
		enery->m_Bitmap = BitmapManager::GetInstance()->GetImange(18);//15비트맵이 없네?
		enery->m_BitmapNumber = 18;
		enery->m_TankType = BOSS;
	}
	else
	{
		enery->m_ihealth = 1;
		enery->m_TankType = NOMAL;
		enery->m_Bitmap = BitmapManager::GetInstance()->GetImange(16);//15비트맵이 없네?
		enery->m_BitmapNumber = 16;
	}
	enery->m_EneryNumber = Number;
	enery->m_blive = true;//별도로 둔 이유? 생성하는거랑 다른거 할때 겹치는 변수라 감소하거나 하면
	enery->m_bRespawn = false;//다른 곳에 영향이 가서?
	enery->m_bRespawning = false; //생성시 충돌 방지용
	enery->m_Direction = DOWN;
	enery->Next = NULL;
	enery->MissileList = new MissileManager;
}
void Enery::Break()
{
	m_ihealth--;
	if (m_ihealth == 0)
	{
		m_ilife = 0;
		m_blive = false;
		m_bRespawn = false;
		m_bRespawning = false;
		m_ix = 0;
		m_iy = 0;
		m_rect.bottom = 0;
		m_rect.top = 0;
		m_rect.left = 0;
		m_rect.right = 0;
		m_CheckRect.bottom = 0;
		m_CheckRect.top = 0;
		m_CheckRect.right = 0;
		m_CheckRect.left = 0;
	}
}

void Enery::Respawn(int Number)
{
	if (m_bRespawn == false)
	{
		m_bRespawning = true;
		m_bRespawn = true;
		if (Number % 3 == 0)
		{
			m_ix = 100;
			m_iy = 100;
			m_rect.bottom = m_iy + 26;
			m_rect.top = m_iy;
			m_rect.left = m_ix + 1;
			m_rect.right = m_ix + 31;

			m_CheckRect.bottom = m_iy + 26;
			m_CheckRect.top = m_iy;
			m_CheckRect.left = m_ix + 1;
			m_CheckRect.right = m_ix + 31;
		}
		else if (Number % 3 == 1)
		{
			m_ix = 350;
			m_iy = 100;
			m_rect.bottom = m_iy + 26;
			m_rect.top = m_iy;
			m_rect.left = m_ix + 1;
			m_rect.right = m_ix + 31;

			m_CheckRect.bottom = m_iy + 26;
			m_CheckRect.top = m_iy;
			m_CheckRect.left = m_ix + 1;
			m_CheckRect.right = m_ix + 31;
		}
		else if (Number % 3 == 2)
		{
			m_ix = 500;
			m_iy = 100;
			m_rect.bottom = m_iy + 26;
			m_rect.top = m_iy;
			m_rect.left = m_ix + 1;
			m_rect.right = m_ix + 31;

			m_CheckRect.bottom = m_iy + 26;
			m_CheckRect.top = m_iy;
			m_CheckRect.left = m_ix + 1;
			m_CheckRect.right = m_ix + 31;
		}
	}
}
void Enery::ChangeRespwaning()
{
	m_bRespawning = false;
}
void Enery::BitmapChange()
{
	if (m_bRespawn == true && m_TankType == NOMAL)
	{
		if (m_Direction == DOWN)
		{
			if (m_BitmapNumber != 16 && m_BitmapNumber != 17)//전에 다른 방향을 보고 있을때
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(16);
				m_BitmapNumber = 16;
			}
			else if (m_BitmapNumber == 16)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(17);
				m_BitmapNumber = 17;
			}
			else if (m_BitmapNumber == 17)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(16);
				m_BitmapNumber = 16;
			}
		}
		else if (m_Direction == LEFT)
		{
			if (m_BitmapNumber != 19 && m_BitmapNumber != 20)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(19);
				m_BitmapNumber = 19;
			}
			else if (m_BitmapNumber == 19)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(20);
				m_BitmapNumber = 20;
			}
			else if (m_BitmapNumber == 20)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(19);
				m_BitmapNumber = 19;
			}
		}
		else if (m_Direction == RIGHT)
		{
			if (m_BitmapNumber != 22 && m_BitmapNumber != 23)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(22);
				m_BitmapNumber = 22;
			}
			else if (m_BitmapNumber == 22)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(23);
				m_BitmapNumber = 23;
			}
			else if (m_BitmapNumber == 23)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(22);
				m_BitmapNumber = 22;
			}
		}
		else if (m_Direction == UP)
		{
			if (m_BitmapNumber != 25 && m_BitmapNumber != 26)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(25);
				m_BitmapNumber = 25;
			}
			else if (m_BitmapNumber == 26)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(25);
				m_BitmapNumber = 25;
			}
			else if (m_BitmapNumber == 25)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(26);
				m_BitmapNumber = 26;
			}
		}
	}
	if (m_bRespawn == true && m_TankType == BOSS)
	{
		if (m_Direction == DOWN)
		{
			if (m_BitmapNumber != 18)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(18);
				m_BitmapNumber = 18;
			}
		}
		else if (m_Direction == LEFT)
		{
			if (m_BitmapNumber != 21)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(21);
				m_BitmapNumber = 21;
			}
		}
		else if (m_Direction == RIGHT)
		{
			if (m_BitmapNumber != 24)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(24);
				m_BitmapNumber = 24;
			}

		}
		else if (m_Direction == UP)
		{
			if (m_BitmapNumber != 27)
			{
				m_Bitmap = BitmapManager::GetInstance()->GetImange(27);
				m_BitmapNumber = 27;
			}
		}
	}
}

void Enery::Move(int MapType, float Moving)
{
	if (m_bRespawn == true && m_blive == true && m_TankType == NOMAL)
	{
		if (MapType == NOT)
		{
			if (m_Direction == UP)
			{
				if (m_rect.top >= 100)
				{
					m_iy -= 50 * Moving;
					m_rect.top -= 50 * Moving;
					m_rect.bottom -= 50 * Moving;
				}
			}
			else if (m_Direction == DOWN)
			{
				if (m_rect.bottom <= 568)
				{
					m_iy += 100 * Moving;
					m_rect.top += 100 * Moving;
					m_rect.bottom += 100 * Moving;
				}
			}
			else if (m_Direction == LEFT)
			{
				if (m_rect.left >= 100)
				{
					m_ix -= 50 * Moving;
					m_rect.left -= 50 * Moving;
					m_rect.right -= 50 * Moving;
				}
			}
			else if (m_Direction == RIGHT)
			{
				if (m_rect.right <= 595)
				{
					m_ix += 100 * Moving;
					m_rect.left += 100 * Moving;
					m_rect.right += 100 * Moving;
				}
			}
		}
		else if (MapType == ICE)
		{
			if (m_Direction == UP)
			{
				if (m_rect.top >= 100)
				{
					m_iy -= 140 * Moving;
					m_rect.top -= 140 * Moving;
					m_rect.bottom -= 140 * Moving;
				}
			}
			else if (m_Direction == DOWN)
			{
				if (m_rect.bottom <= 568)
				{
					m_iy += 240 * Moving;
					m_rect.top += 240 * Moving;
					m_rect.bottom += 240 * Moving;
				}
			}
			else if (m_Direction == LEFT)
			{
				if (m_rect.left >= 100)
				{
					m_ix -= 140 * Moving;
					m_rect.left -= 140 * Moving;
					m_rect.right -= 140 * Moving;
				}
			}
			else if (m_Direction == RIGHT)
			{
				if (m_rect.right <= 595)
				{
					m_ix += 240 * Moving;
					m_rect.left += 240 * Moving;
					m_rect.right += 240 * Moving;
				}
			}
		}
	}
	else if (m_bRespawn == true && m_blive == true && m_TankType == BOSS)
	{
		if (MapType == NOT)
		{
			if (m_Direction == UP)
			{
				if (m_rect.top >= 100)
				{
					m_iy -= 100 * Moving;
					m_rect.top -= 100 * Moving;
					m_rect.bottom -= 100 * Moving;
				}
			}
			else if (m_Direction == DOWN)
			{
				if (m_rect.bottom <= 568)
				{
					m_iy += 150 * Moving;
					m_rect.top += 150 * Moving;
					m_rect.bottom += 150 * Moving;
				}
			}
			else if (m_Direction == LEFT)
			{
				if (m_rect.left >= 100)
				{
					m_ix -= 100 * Moving;
					m_rect.left -= 100 * Moving;
					m_rect.right -= 100 * Moving;
				}
			}
			else if (m_Direction == RIGHT)
			{
				if (m_rect.right <= 595)
				{
					m_ix += 150 * Moving;
					m_rect.left += 150 * Moving;
					m_rect.right += 150 * Moving;
				}
			}
		}
		else if (MapType == ICE)
		{
			if (m_Direction == UP)
			{
				if (m_rect.top >= 100)
				{
					m_iy -= 190 * Moving;
					m_rect.top -= 190 * Moving;
					m_rect.bottom -= 190 * Moving;
				}
			}
			else if (m_Direction == DOWN)
			{
				if (m_rect.bottom <= 568)
				{
					m_iy += 290 * Moving;
					m_rect.top += 290 * Moving;
					m_rect.bottom += 290 * Moving;
				}
			}
			else if (m_Direction == LEFT)
			{
				if (m_rect.left >= 100)
				{
					m_ix -= 190 * Moving;
					m_rect.left -= 190 * Moving;
					m_rect.right -= 190 * Moving;
				}
			}
			else if (m_Direction == RIGHT)
			{
				if (m_rect.right <= 595)
				{
					m_ix += 290 * Moving;
					m_rect.left += 290 * Moving;
					m_rect.right += 290 * Moving;
				}
			}
		}
	}
}
void Enery::CheckRectReset()
{
	m_CheckRect = m_rect;
}
void Enery::CheckMove(int MapType, float Moving)
{
	if (m_bRespawn == true && m_blive == true && m_TankType == NOMAL)
	{
		if (MapType == NOT)
		{
			if (m_Direction == UP)
			{
				if (m_rect.top >= 100)
				{
					m_CheckRect.top -= 50 * Moving;
					m_CheckRect.bottom -= 50 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == DOWN)
			{
				if (m_rect.bottom <= 568)
				{
					m_CheckRect.top += 100 * Moving;
					m_CheckRect.bottom += 100 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == LEFT)
			{
				if (m_rect.left >= 100)
				{
					m_CheckRect.left -= 50 * Moving;
					m_CheckRect.right -= 50 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == RIGHT)
			{
				if (m_rect.right <= 595)
				{
					m_CheckRect.left += 100 * Moving;
					m_CheckRect.right += 100 * Moving;
				}
				else
					ChnageDirection();
			}
		}
		else if (MapType == ICE)
		{
			if (m_Direction == UP)
			{
				if (m_rect.top >= 100)
				{
					m_CheckRect.top -= 140 * Moving;
					m_CheckRect.bottom -= 140 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == DOWN)
			{
				if (m_rect.bottom <= 568)
				{
					m_CheckRect.top += 240 * Moving;
					m_CheckRect.bottom += 240 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == LEFT)
			{
				if (m_rect.left >= 100)
				{
					m_CheckRect.left -= 140 * Moving;
					m_CheckRect.right -= 140 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == RIGHT)
			{
				if (m_rect.right <= 595)
				{
					m_CheckRect.left += 240 * Moving;
					m_CheckRect.right += 240 * Moving;
				}
				else
					ChnageDirection();
			}
		}
	}
	if (m_bRespawn == true && m_blive == true && m_TankType == BOSS)
	{
		if (MapType == NOT)
		{
			if (m_Direction == UP)
			{
				if (m_rect.top >= 100)
				{
					m_CheckRect.top -= 100 * Moving;
					m_CheckRect.bottom -= 100 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == DOWN)
			{
				if (m_rect.bottom <= 568)
				{
					m_CheckRect.top += 150 * Moving;
					m_CheckRect.bottom += 150 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == LEFT)
			{
				if (m_rect.left >= 100)
				{
					m_CheckRect.left -= 100 * Moving;
					m_CheckRect.right -= 100 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == RIGHT)
			{
				if (m_rect.right <= 595)
				{
					m_CheckRect.left += 150 * Moving;
					m_CheckRect.right += 150 * Moving;
				}
				else
					ChnageDirection();
			}
		}
		else if (MapType == ICE)
		{
			if (m_Direction == UP)
			{
				if (m_rect.top >= 100)
				{
					m_CheckRect.top -= 190 * Moving;
					m_CheckRect.bottom -= 190 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == DOWN)
			{
				if (m_rect.bottom <= 568)
				{
					m_CheckRect.top += 290 * Moving;
					m_CheckRect.bottom += 290 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == LEFT)
			{
				if (m_rect.left >= 100)
				{
					m_CheckRect.left -= 190 * Moving;
					m_CheckRect.right -= 190 * Moving;
				}
				else
					ChnageDirection();
			}
			else if (m_Direction == RIGHT)
			{
				if (m_rect.right <= 595)
				{
					m_CheckRect.left += 290 * Moving;
					m_CheckRect.right += 290 * Moving;
				}
				else
					ChnageDirection();
			}
		}
	}
}
void Enery::ChnageDirection()
{
	int r_Direction;
	while (1)
	{
		r_Direction = rand() % 4;
		if (m_Direction == UP && r_Direction != UP)
		{
			m_Direction = r_Direction;
			break;
		}
		else if (m_Direction == DOWN && r_Direction != DOWN)
		{
			m_Direction = r_Direction;
			break;
		}
		else if (m_Direction == LEFT && r_Direction != LEFT)
		{
			m_Direction = r_Direction;
			break;
		}
		else if (m_Direction == RIGHT && r_Direction != RIGHT)
		{
			m_Direction = r_Direction;
			break;
		}
	}
}

void Enery::Fire()
{
	if (m_blive == true && m_bRespawn == true && m_TankType == NOMAL)
	{
		m_FireCurClock = clock();
		if (m_FireCurClock - m_FireLastClock > 1000)
		{
			m_FireLastClock = clock();
			MissileList->Init(m_ix, m_iy, m_Direction);
		}
	}
	else if (m_blive == true && m_bRespawn == true && m_TankType == BOSS)
	{
		m_FireCurClock = clock();
		if (m_FireCurClock - m_FireLastClock > 700)
		{
			m_FireLastClock = clock();
			MissileList->Init(m_ix, m_iy, m_Direction);
		}
	}
}
void Enery::MissileMove()
{
	if (m_TankType == NOMAL)
	{
		m_MissileMoveCurClock = clock();
		if (m_MissileMoveCurClock - m_MissileMoveLastClock > 70)
		{
			m_MissileMoveLastClock = clock();
			MissileList->Move();
		}
	}
	else if (m_TankType == BOSS)
	{
		m_MissileMoveCurClock = clock();
		if (m_MissileMoveCurClock - m_MissileMoveLastClock > 50)
		{
			m_MissileMoveLastClock = clock();
			MissileList->Move();
		}
	}
}
void Enery::MissileChangeStateCruch(int MissileNumber, int CrushType)
{
	MissileList->ChangeStateCrush(MissileNumber);
	MissileList->Explosion(MissileNumber, CrushType);
}
void Enery::Draw(HDC hdc)
{
	m_Bitmap->Draw(hdc, m_ix, m_iy);
}
void Enery::Draw(HDC hdc, Enery* Node)
{
	if (m_blive == true && m_bRespawn == true)
	{
		m_Bitmap->Draw(hdc, m_ix, m_iy);
	}
	MissileList->Draw(hdc);
	MissileList->ExplosionEvent();
	MissileList->Crush();
}

void Enery::SetNext(Enery* Node)
{
	if (Next == NULL)
	{
		Next = Node;
		Next->Next = NULL;
	}
	else
	{
		Next->SetNext(Node);
	}
}
void Enery::ChageNext(Enery* Node)
{
	Node = Node->Next;
}
void Enery::Release(Enery* Node)
{
	while (Node != NULL)
	{
		Node = Node->Next;
		Release(Node);
		if (Node != NULL)
		{
			Node->MissileList->Release();
			delete Node->MissileList;
		}
		delete Node;
		Node = NULL;
	}
}
void Enery::Release()
{
	MissileList->Release();
	delete MissileList;
}

Enery::~Enery()
{
}