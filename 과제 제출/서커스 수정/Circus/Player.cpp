
#include "Player.h"

Player::Player()
{
	m_ix = 65;
	m_iy = 580;
	m_Rect.bottom = m_iy + 63;//충돌 영역
	m_Rect.left = m_ix;//충돌 영역
	m_Rect.right = m_ix + 66;//충돌 영역
	m_Rect.top = m_iy;//충돌 영역
	m_jump_y = 0;
	m_jump_y = m_iy;
	m_life = 3;
	m_bSurvival = true;
	imageindex = 0;
	m_istate = STOP;
	m_iScore = 0;
	Init();
}

void Player::Init()
{
	for (int i = 0; i < 4; i++)
		m_playerMotionList[i] = BitmapManager::GetInstance()->GetImage(i);
	for (int i = 0; i < 2; i++)
		m_playerMotionList[4 + i] = BitmapManager::GetInstance()->GetImage(26 + i);
}

void Player::playerMove(int Move, float Move_x)
{
	m_CurClock = clock();
	if (m_CurClock - m_LastClock > 250)
	{
		m_LastClock = clock();
		imageindex++;
		if (imageindex >= 3)
			imageindex = 0;
	}
	if (Move + Move_x >= 4670)
	{
		m_ix += Move_x;
		m_Rect.left = m_ix;//충돌 영역
		m_Rect.right = m_ix + 66;//충돌 영역
	}
	else
		m_ix = 65;
}

void Player::playerDeath()
{
	if (m_life > 0)
		m_life--;
	imageindex = 3;
	m_istate = DEATH;//나중에

}
void Player::PlayerReset()
{
	m_iScore = 0;
	m_ix = 65;
	m_iy = 580;
	m_jump_y = m_iy;
	m_istate = STOP;//나중에
	m_Rect.bottom = m_iy + 63;
	m_Rect.left = m_ix;
	m_Rect.right = m_ix + 66;
	m_Rect.top = m_iy;
}
void Player::PlayerClear()
{
	m_iScore = 0;
	m_istate = STOP;
	m_ix = 65;
	m_iy = 580;
	m_jump_y = m_iy;
	m_Rect.bottom = m_iy + 63;
	m_Rect.left = m_ix;
	m_Rect.right = m_ix + 66;
	m_Rect.top = m_iy;
	m_life = 3;
}
void Player::GameOver()
{
	m_istate = STOP;
	m_life = 3;
	m_iScore = 0;
}

void Player::playerJump()
{
	if (m_istate == STOP)
	{
		imageindex = 2;
		m_istate = JUMP;
	}
}
void Player::playerJumping(float time)
{
	m_iy = m_jump_y - sinf(time * 3.14) * 95;
	m_Rect.bottom = m_iy + 63;
	m_Rect.top = m_iy;
}
void Player::playerReachEnd()
{
	if (imageindex <= 3)
		imageindex = 4;
	m_CurClock = clock();
	if (m_CurClock - m_LastClock > 400)
	{
		m_LastClock = clock();
		imageindex++;
		if (imageindex >= 6)
			imageindex = 4;
	}
}
void Player::Draw(HDC hdc, HDC MemDC)
{
	m_playerMotionList[imageindex]->Draw(hdc, MemDC, m_ix, m_iy);
}

void Player::ChangeState(int Number)//점프후 정보 정리 이름 변경 해야 할듯
{
	if (Number == JUMP)
	{
		m_istate = STOP;
		m_iy = 580;
	}
	else if (Number == PLAYEREND)
	{
		m_istate = STOP;
		m_iy = 536;
	}
	else if (Number == DEATH)
		m_istate = STOP;
	imageindex = 0;
}

void Player::UpdateScore(int ScoreType)
{
	if (ScoreType == 0)
		m_iScore += 200;
	else if (ScoreType == 1)
		m_iScore += 500;
}
void Player::BonusScore(int Bonus)
{
	m_iScore += Bonus;
}

void Player::PlayerBitmapRelease()
{
	delete[4] m_playerMotionList;
}
Player::~Player()
{
	//delete m_playerMotionList;
}