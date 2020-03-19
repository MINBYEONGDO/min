

#pragma once
#include "SingleTon.h"
#include "Star.h"
class StarManager
{
private:
	vector<Star*> m_vecStar;
	int m_CurStar;
	int m_MaxStar;
	int m_Score;
	int m_HitStar;
	int m_LiveStar;
public:

	void AddStar(int GameType, bool Fever, int Score, int playerx, int playery);
	void Draw();
	void MoveStar();
	void StarDelete(int Number);
	bool Contact(RECT player);
	void HitIncrease();
	void ScoreChange();
	int SearchLiveStarNumber();
	void ResetHitCount();
	void Release();
	int GetStar()//현재 별이 몇개가 있는지 혹은 존재하는지 
	{
		return m_CurStar;
	}
	int GetLiveStar()
	{
		return m_LiveStar;
	}
	int GetStarScore()
	{
		for (auto iter = m_vecStar.begin(); iter != m_vecStar.end(); iter++)
		{
			if ((*iter)->GetLive() == true)
			{
				return (*iter)->GetScore();
			}
		}
	}

	int GetScore()
	{
		return m_Score;
	}
	StarManager();
	~StarManager();
};