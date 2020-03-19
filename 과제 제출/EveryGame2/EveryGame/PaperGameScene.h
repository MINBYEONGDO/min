
#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "StarManager.h"
#include "TimeManager.h"
#include "Label.h"
#include "Timer.h"
#include "Fever.h"
#include "PaperManager.h"
#include "LoadingScene.h"
class PaperGameScene : public JEngine::Scene
{
private:
	HWND m_hWnd;
	int m_GameState;
	int m_TimeOutCount;
	int m_FileScore;
	int m_FileScore2;
	int m_Score;
	float    m_fTitleX;
	float    m_fTitleY;
	float    m_fSpeedX;
	Timer* m_Timer;
	float m_bFirstStart;
	JEngine::BitMap* m_pTimerGague;
	float m_fTimerGague;

	LoadingScene *Loading;

	JEngine::BitMap* m_pBack;
	JEngine::BitMap* m_TimeOut;
	JEngine::Label* m_ScoreLabel;
	JEngine::Label* m_MinLabel;
	JEngine::Label* m_SecLabel;
	JEngine::TimeManager* m_PlayTime;
	JEngine::TimeManager *m_TimerTime;
	StarManager* m_StarList;
	Fever* m_Fever;
	PaperManager* m_PaperList;
public:
	void FileLoad(HWND hWnd);
	void FileSave(HWND hWnd);
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	void PaperReach();
	void PaperNotAnswer();
	void TimeOutScene();
	virtual void Release();
	PaperGameScene();
	~PaperGameScene();
};
