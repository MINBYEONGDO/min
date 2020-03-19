#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Timer.h"
class LoadingScene
{
private:
	int m_Second;
	bool m_bLoading;
	int m_CurClock;
	int m_LastClock;
	JEngine::BitMap *m_pback;
	JEngine::BitMap *m_pLoading;
public:
	void Loading();
	void Init();
	void Draw();
	bool GetLoading()
	{
		return m_bLoading;
	}
	LoadingScene();
	~LoadingScene();
};