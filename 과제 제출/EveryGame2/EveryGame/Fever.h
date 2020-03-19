
#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "TimeManager.h"
#include "Label.h"
#include "Timer.h"
class Fever
{
private:
	int m_FeverState;
	float m_Fevergauge;
	int m_FeverTimeCount;
	bool m_bFever;
	bool m_bFeverChange;
	bool m_DrawEffect;
	JEngine::BitMap* m_pFever1;
	JEngine::BitMap* m_pFever2;
	JEngine::BitMap* m_pFever3;
	JEngine::BitMap* m_pFeverEffect;
public:
	void Init();
	void Update(int GameType);
	void FeverTime();
	void Draw();
	void FeverGauge();
	void FeverGaugeDisCount();
	void FeverReset();
	void FeverChangeReset();
	bool GetFeverChange()
	{
		return m_bFeverChange;
	}
	int GetFeverState()
	{
		return m_FeverState;//피버상태에 따른 점수값추가및 피버 증가량에 영향을 줌
	}
	Fever();
	~Fever();
};


