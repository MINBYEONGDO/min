
#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Player.h"
#include "BulletManager.h"
#include "StarManager.h"
#include "TimeManager.h"
#include "Label.h"
#include "Timer.h"
#include "Fever.h"
#include "LoadingScene.h"
class FlightGameScene : public JEngine::Scene
{
private:
	HWND m_hWnd;
	int m_GameState;
	int m_TimeOutCount;
	int m_BestScore;
	int m_FileScore;
	int m_FileScore2;
	float    m_fTitleX;
	float    m_fTitleY;
	float    m_fSpeedX;
	Timer* m_Timer;
	JEngine::BitMap* m_pTimerGague;
	float m_fTimerGague;
	JEngine::BitMap* m_pBack;
	JEngine::BitMap* m_TimeOut;
	JEngine::Label* m_ScoreLabel;
	JEngine::Label* m_MinLabel;
	JEngine::Label* m_SecLabel;
	JEngine::TimeManager* m_BulletAddTime;
	JEngine::TimeManager* m_BulletMoveTime;
	JEngine::TimeManager* m_PlayTime;
	JEngine::TimeManager* m_TimerTime;
	Player* m_player;
	BulletManager* m_BulletList;
	StarManager* m_StarList;
	Fever* m_Fever;
	bool m_bFirstStart;
	LoadingScene *Loading;
public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	void FileLoad(HWND hWnd);
	void FileSave(HWND hWnd);
	void TimeOutScene();
	FlightGameScene();
	~FlightGameScene();
};