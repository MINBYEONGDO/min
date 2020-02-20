
#include "Player.h"

Player::Player()
{
	m_shieldCurClock = clock();
	m_ShieldLastClock = clock();
	m_shieldChangeCurClock = clock();
	m_ShieldChangeLastClock = clock();
	MissileList = NULL;
}
void Player::Init()
{
	MissileList = new MissileManager;
	m_ix = 365;
	m_iy = 490;
	m_rect.bottom = m_iy + 26;
	m_rect.top = m_iy;
	m_rect.left = m_ix + 1;
	m_rect.right = m_ix + 31;
	m_CheckRect.bottom = m_iy + 26;
	m_CheckRect.top = m_iy;
	m_CheckRect.left = m_ix + 1;
	m_CheckRect.right = m_ix + 31;
	m_Direction = UP;
	m_ilife = 3;
	m_ihealth = 1;
	m_Bitmap = BitmapManager::GetInstance()->GetImange(45);
	m_BitmapNumber = 45;
	m_bshield = false;
	m_bRespawn = true;
}

void Player::NewStageSet()
{
	MissileList->Release();
	delete MissileList;
	MissileList = new MissileManager;
	m_ix = 365;
	m_iy = 490;
	m_rect.bottom = m_iy + 26;
	m_rect.top = m_iy;
	m_rect.left = m_ix + 1;
	m_rect.right = m_ix + 31;
	m_CheckRect.bottom = m_iy + 26;
	m_CheckRect.top = m_iy;
	m_CheckRect.left = m_ix + 1;
	m_CheckRect.right = m_ix + 31;
	m_Direction = UP;
	m_Bitmap = BitmapManager::GetInstance()->GetImange(45);
	m_BitmapNumber = 45;
	m_ilife = 3;
	m_bshield = false;
	m_bRespawn = true;
}
void Player::NewGameSet()
{
	MissileList->Release();
	delete MissileList;
	MissileList = new MissileManager;
	m_ix = 365;
	m_iy = 490;
	m_rect.bottom = m_iy + 26;
	m_rect.top = m_iy;
	m_rect.left = m_ix + 1;
	m_rect.right = m_ix + 31;
	m_CheckRect.bottom = m_iy + 26;
	m_CheckRect.top = m_iy;
	m_CheckRect.left = m_ix + 1;
	m_CheckRect.right = m_ix + 31;
	m_Direction = UP;
	m_Bitmap = BitmapManager::GetInstance()->GetImange(45);
	m_BitmapNumber = 45;
	m_ilife = 3;
	m_ihealth = 1;
	m_bshield = false;
	m_bRespawn = true;
}

void Player::ImageChange(int Direction)
{
	if (Direction == UP)
	{
		if (m_BitmapNumber != 45 && m_BitmapNumber != 46)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(46);
			m_BitmapNumber = 46;
		}
		else if (m_BitmapNumber == 45)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(46);
			m_BitmapNumber = 46;
		}
		else if (m_BitmapNumber == 46)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(45);
			m_BitmapNumber = 45;
		}
	}
	else if (Direction == DOWN)
	{
		if (m_BitmapNumber != 40 && m_BitmapNumber != 39)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(39);
			m_BitmapNumber = 39;
		}
		else if (m_BitmapNumber == 40)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(39);
			m_BitmapNumber = 39;
		}
		else if (m_BitmapNumber == 39)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(40);
			m_BitmapNumber = 40;
		}
	}
	else if (Direction == LEFT)
	{
		if (m_BitmapNumber != 41 && m_BitmapNumber != 42)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(41);
			m_BitmapNumber = 41;
		}
		else if (m_BitmapNumber == 42)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(41);
			m_BitmapNumber = 41;
		}
		else if (m_BitmapNumber == 41)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(42);
			m_BitmapNumber = 42;
		}
	}
	else if (Direction == RIGHT)
	{
		if (m_BitmapNumber != 44 && m_BitmapNumber != 43)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(43);
			m_BitmapNumber = 43;
		}
		else if (m_BitmapNumber == 43)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(44);
			m_BitmapNumber = 44;
		}
		else if (m_BitmapNumber == 44)
		{
			m_Bitmap = BitmapManager::GetInstance()->GetImange(43);
			m_BitmapNumber = 43;
		}
	}
}

void Player::CheckMove(int MapType, int Direction, float Moving)
{
	if (MapType == NOT)
	{
		if (Direction == UP)
		{
			if (m_CheckRect.top >= 100)
			{
				m_CheckRect.top -= (100) *Moving;
				m_CheckRect.bottom -= (100) *Moving;
			}
			m_Direction = UP;
		}
		else if (Direction == DOWN)
		{
			if (m_CheckRect.bottom <= 568)
			{
				m_CheckRect.top += (150) *Moving;
				m_CheckRect.bottom += (150) *Moving;
			}
			m_Direction = DOWN;
		}
		else if (Direction == LEFT)
		{
			if (m_CheckRect.left >= 100)
			{
				m_CheckRect.left -= (100) *Moving;
				m_CheckRect.right -= (100) *Moving;
			}
			m_Direction = LEFT;
		}
		else if (Direction == RIGHT)
		{
			if (m_CheckRect.right <= 595)
			{
				m_CheckRect.left += (150) *Moving;
				m_CheckRect.right += (150) *Moving;
			}
			m_Direction = RIGHT;
		}
	}
	if (MapType == ICE)
	{
		if (Direction == UP)
		{
			if (m_CheckRect.top >= 100)
			{
				m_CheckRect.top -= (190) *Moving;
				m_CheckRect.bottom -= (190) *Moving;
			}
			m_Direction = UP;
		}
		else if (Direction == DOWN)
		{
			if (m_CheckRect.bottom <= 568)
			{
				m_CheckRect.top += (290) *Moving;
				m_CheckRect.bottom += (290) *Moving;
			}
			m_Direction = DOWN;
		}
		else if (Direction == LEFT)
		{
			if (m_CheckRect.left >= 100)
			{
				m_CheckRect.left -= (190) *Moving;
				m_CheckRect.right -= (190) *Moving;
			}
			m_Direction = LEFT;
		}
		else if (Direction == RIGHT)
		{
			if (m_CheckRect.right <= 595)
			{
				m_CheckRect.left += (290) *Moving;
				m_CheckRect.right += (290) *Moving;
			}
			m_Direction = RIGHT;
		}
	}
}

void Player::CheckRectReset()
{
	m_CheckRect = m_rect;
}
void Player::Move(int MapState, int Direction, float Moving)
{
	if (MapState == NOT)
	{
		if (Direction == UP)
		{
			if (m_rect.top >= 100)
			{
				m_iy -= (100) *Moving;
				m_rect.top -= (100) *Moving;
				m_rect.bottom -= (100) *Moving;
			}
		}
		else if (Direction == DOWN)
		{
			if (m_rect.bottom <= 568)
			{
				m_iy += (150) *Moving;
				m_rect.top += (150) *Moving;
				m_rect.bottom += (150) *Moving;
			}

		}
		else if (Direction == LEFT)
		{
			if (m_rect.left >= 100)
			{
				m_ix -= (100) *Moving;
				m_rect.left -= (100) *Moving;
				m_rect.right -= (100) *Moving;
			}

		}
		else if (Direction == RIGHT)
		{
			if (m_rect.right <= 595)
			{
				m_ix += (150) *Moving;
				m_rect.left += (150) *Moving;
				m_rect.right += (150) *Moving;
			}

		}
	}
	else if (MapState == ICE)
	{
		if (Direction == UP)
		{
			if (m_rect.top >= 100)
			{
				m_iy -= (190) *Moving;
				m_rect.top -= (190) *Moving;
				m_rect.bottom -= (190) *Moving;
			}

		}
		else if (Direction == DOWN)
		{
			if (m_rect.bottom <= 568)
			{
				m_iy += (290) *Moving;
				m_rect.top += (290) *Moving;
				m_rect.bottom += (290) *Moving;
			}

		}
		else if (Direction == LEFT)
		{
			if (m_rect.left >= 100)
			{
				m_ix -= (190) *Moving;
				m_rect.left -= (190) *Moving;
				m_rect.right -= (190) *Moving;
			}

		}
		else if (Direction == RIGHT)
		{
			if (m_rect.right <= 595)
			{
				m_ix += (290) *Moving;
				m_rect.left += (290) *Moving;
				m_rect.right += (290) *Moving;
			}
		}
	}
}


bool Player::ContactObject(RECT ObjectRect)
{
	RECT rect;
	if (IntersectRect(&rect, &m_rect, &ObjectRect) == true)
	{
		return true;
	}
	return false;
}
void Player::Fire()
{
	MissileList->Init(m_ix, m_iy, m_Direction);
}
void Player::ShieldTime()
{
	m_shieldCurClock = clock();
	if (m_shieldCurClock - m_ShieldLastClock > 1000)
	{
		m_ShieldLastClock = clock();
		m_bshield = false;
	}
}
void Player::RespawnReset()
{
	m_bRespawn = false;
}
void Player::Break()
{
	m_ix = 365;
	m_iy = 490;
	m_rect.bottom = m_iy + 26;
	m_rect.top = m_iy;
	m_rect.left = m_ix + 1;
	m_rect.right = m_ix + 31;
	m_CheckRect.bottom = m_iy + 26;
	m_CheckRect.top = m_iy;
	m_CheckRect.left = m_ix + 1;
	m_CheckRect.right = m_ix + 31;
	m_Direction = UP;
	m_ilife--;
	m_ihealth = 1;
	m_Bitmap = BitmapManager::GetInstance()->GetImange(45);
	ShieldBitmap = BitmapManager::GetInstance()->GetImange(36);
	ShieldImageNumber = 36;
	m_BitmapNumber = 45;
	m_bshield = true;
	m_bRespawn = true;//ºÎÈ°
	m_shieldCurClock = clock();
	m_ShieldLastClock = clock();
}
void Player::Draw(HDC hdc)
{
	m_Bitmap->Draw(hdc, m_ix, m_iy);
	if (m_bshield == true)
	{
		ShieldBitmap->Draw(hdc, m_ix, m_iy);
		m_shieldChangeCurClock = clock();
		if (m_shieldChangeCurClock - m_ShieldChangeLastClock > 100)
		{
			m_ShieldChangeLastClock = clock();

			if (ShieldImageNumber == 37)
			{
				ShieldBitmap = BitmapManager::GetInstance()->GetImange(36);
				ShieldImageNumber = 36;
			}
			else if (ShieldImageNumber == 36)
			{
				ShieldBitmap = BitmapManager::GetInstance()->GetImange(37);
				ShieldImageNumber = 37;
			}
		}
	}
	MissileList->Draw(hdc);
	MissileList->ExplosionEvent();//
	MissileList->Crush();
}
void Player::MissileMove()
{
	MissileList->Move();
}
void Player::MissileChangeStateCruch(int Number, int CrushType)
{
	MissileList->ChangeStateCrush(Number);
	MissileList->Explosion(Number, CrushType);//
}

Player::~Player()
{
	MissileList->Release();
	delete MissileList;
}
