
#include "StarManager.h"
#include "defines.h"

StarManager::StarManager()
{
	m_vecStar.clear();
	m_MaxStar = 8;
	m_CurStar = 0;
	m_HitStar = 0;
	m_LiveStar = 0;
}


void StarManager::AddStar(int GameType, bool Fever, int Score, int playerx, int playery)
{
	if (GameType == FLIGHTGAME)
	{
	
		if (Fever == true && m_LiveStar != 8)
		{
			
			while (1)
			{
				Star *Stmp = new Star;
				Stmp->Init(FLIGHTGAME, m_CurStar, m_HitStar, Score, playerx, playery);
				m_vecStar.push_back(Stmp);
				
				m_CurStar++;
				m_LiveStar++;
				if (m_LiveStar >= 8)
					break;
			}

		}
		else if (m_LiveStar != 8 && Fever == false)
		{
			Star *Stmp = new Star;
			Stmp->Init(FLIGHTGAME, m_CurStar, m_HitStar, Score, playerx, playery);
			m_vecStar.push_back(Stmp);
			m_CurStar++;
			m_LiveStar++;
		}
	}
	else if (GameType == PAPERGAME)
	{
		if (Fever == true && m_LiveStar < 1)
		{
			Star *Stmp = new Star;
			Stmp->Init(PAPERGAME, m_CurStar, m_HitStar, Score, playerx, playery);
			m_vecStar.push_back(Stmp);
			m_CurStar++;
			m_LiveStar++;
		}
		else if (Fever == false)
		{
			Star *Stmp = new Star;
			Stmp->Init(PAPERGAME, m_CurStar, m_HitStar, Score, playerx, playery);
			m_vecStar.push_back(Stmp);
			m_CurStar++;
			m_LiveStar++;
		}
	}
}
void StarManager::Draw()
{
	for (auto iter = m_vecStar.begin(); iter != m_vecStar.end(); iter++)
	{
		(*iter)->Draw();
	}
}
void StarManager::MoveStar()
{
	for (auto iter = m_vecStar.begin(); iter != m_vecStar.end(); iter++)
	{
		(*iter)->Move();
	}
	for (int i = 0; i < m_CurStar; i++)
	{
		if (m_vecStar[i]->GetLive() == true && m_vecStar[i]->SideOut() == false)
		{
			StarDelete(m_vecStar[i]->GetNumber());
		}
	}
}

int StarManager::SearchLiveStarNumber()
{
	for (auto iter = m_vecStar.begin(); iter != m_vecStar.end(); iter++)
	{
		if ((*iter)->GetLive() == true)
		{
			return (*iter)->GetNumber();
		}
	}
}
void StarManager::StarDelete(int Number)
{
	int itmp;
	for (auto iter = m_vecStar.begin(); iter != m_vecStar.end(); iter++)
	{
		
		if ((*iter)->GetNumber() == Number)
		{
			(*iter)->Out();
			m_LiveStar--;
		}
	}
}

bool StarManager::Contact(RECT player)
{
	RECT rect;
	for (auto iter = m_vecStar.begin(); iter != m_vecStar.end(); iter++)
	{
		if (IntersectRect(&rect, &player, &(*iter)->GetRect()) == true && (*iter)->GetLive() == true)
		{
			m_Score = (*iter)->GetScore();
			StarDelete((*iter)->GetNumber());
			m_HitStar++;
			return true;
		}
	}
	return false;
}
void StarManager::HitIncrease()
{
	m_HitStar++;
}
void StarManager::ResetHitCount()
{
	m_HitStar = 0;
}
void StarManager::ScoreChange()
{
	for (auto iter = m_vecStar.begin(); iter != m_vecStar.end(); iter++)
	{
		(*iter)->BitmapChange(m_HitStar);
	}
}
void StarManager::Release()
{
	for (auto iter = m_vecStar.begin(); iter != m_vecStar.end(); iter++)
	{
		SAFE_DELETE((*iter));
	}
	m_vecStar.clear();
	m_vecStar.shrink_to_fit();
	m_CurStar = 0;
	m_LiveStar = 0;
}

StarManager::~StarManager()
{
	for (auto iter = m_vecStar.begin(); iter != m_vecStar.end(); iter++)
	{
		if (iter == m_vecStar.end() - 1)
			(*iter)->Release();
		delete (*iter);
	}
	m_vecStar.clear();
}
