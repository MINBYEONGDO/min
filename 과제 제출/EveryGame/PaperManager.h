
#pragma once
#include "SingleTon.h"
#include "Paper.h"
class PaperManager
{
private:
	vector<Paper*> m_vecPaper;
	int m_CurPaper;
	int m_MaxPaper;
	int m_LivePaper;
	int m_iAnswerCount;//연속정답횟수 -별 생성을 위해서
	int m_CheckAnswer;
	bool m_bFirstCount;//한번만 적용하기 위해서 지속적으로 적용되는걸 막기위함, 한번 눌렸을뿐인데 여러번 키가 누른걸로 적용되는걸 막기위함
	bool m_bReach;
public:
	void AddPaper();
	void Input(float fETime, int Direction);
	void Draw();
	void MovePaper();
	void StateReset();
	void PaperReach();
	void Release();
	bool GetPaperMove()
	{
		for (auto iter = m_vecPaper.begin(); iter != m_vecPaper.end(); iter++)
		{
			if ((*iter)->GetLive() == true)
			{
				return (*iter)->GetMove();
			}
		}
	}
	int GetAnswer()
	{
		return m_CheckAnswer;
	}
	int GetAnswerCount()
	{
		return m_iAnswerCount;

	}
	int GetLivePaper()
	{
		return m_LivePaper;
	}
	bool GetReach()
	{
		return m_bReach;
	}
	int GetPaperScore()
	{
		for (auto iter = m_vecPaper.begin(); iter != m_vecPaper.end(); iter++)
		{
			if ((*iter)->GetLive() == true)
			{
				return (*iter)->GetScore();
			}
		}
	}
	PaperManager();
	~PaperManager();
};