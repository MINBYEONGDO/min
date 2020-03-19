
#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Player.h"
#include "BulletManager.h"
#include "TimeManager.h"
#include "Label.h"
class Timer
{
private:
	int m_ms;
	int m_Second;
	bool m_bTimeOut;
	JEngine::Label* m_msLabel;
	JEngine::Label* m_SecLabel;
public:
	Timer();
	void Init(int Number);
	void Update();
	void Draw();
	int Getms()
	{
		return m_ms;
	}
	int GetSecond()
	{
		return m_Second;
	}
	bool GetTimeOut()
	{
		return m_bTimeOut;
	}
	~Timer();
};