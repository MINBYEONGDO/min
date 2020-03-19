
#include "FlightGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"


FlightGameScene::FlightGameScene()
{
	m_fTitleX = 414.0f;
	m_fTitleY = 648.0f;
	srand(time(NULL));
	m_fSpeedX = 200;
	m_GameState = PLAY;//게임자체의 상태
	m_BestScore = 0;//이게 아닌데?
	m_fTimerGague = 1;
	m_TimeOutCount = 0;//타임아웃씬 유지시간 체크
	m_bFirstStart = false;
	m_player = new  Player;
	m_BulletList = new BulletManager;
	m_StarList = new StarManager;
}

void FlightGameScene::Init(HWND hWnd)
{
	m_hWnd = hWnd;
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LEFT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_RIGHT);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_UP);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_DOWN);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);
	Loading = new LoadingScene;
	Loading->Init();
	m_GameState = PLAY;
	m_Timer = new Timer;
	m_Timer->Init(1);
	m_Fever = new Fever;
	m_Fever->Init();
	m_player->Init();

	m_ScoreLabel = new JEngine::Label;
	m_ScoreLabel->Init("0", 200, 10, NULL);
	m_TimerTime = new JEngine::TimeManager;
	m_TimerTime->init(true, 100);//0.01
	m_PlayTime = new  JEngine::TimeManager;
	m_PlayTime->init(true, 1);//1
	m_BulletAddTime = new JEngine::TimeManager;
	m_BulletAddTime->init(true, 5);
	m_BulletMoveTime = new JEngine::TimeManager;
	m_BulletMoveTime->init(true, 100);


	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//FlightGameBack.bmp");
	m_TimeOut = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//TimeOver.bmp");
	m_pTimerGague = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//Fever3.bmp");
	m_bFirstStart = true;
}
bool FlightGameScene::Input(float fETime)
{
	if (Loading->GetLoading() == false)
	{
		if (m_GameState == PLAY)
		{
			if (JEngine::InputManager::GetInstance()->isKeyPress(VK_UP))
				m_player->Input(fETime, UP);
			if (JEngine::InputManager::GetInstance()->isKeyPress(VK_DOWN))
				m_player->Input(fETime, DOWN);
			if (JEngine::InputManager::GetInstance()->isKeyPress(VK_LEFT))
				m_player->Input(fETime, LEFT);
			if (JEngine::InputManager::GetInstance()->isKeyPress(VK_RIGHT))
				m_player->Input(fETime, RIGHT);
		}
	}
	return false;
}

void  FlightGameScene::Update(float fETime)
{
	if (Loading->GetLoading() == false)
	{
		m_ScoreLabel->Init((to_string(m_player->GetScore())), 200, 10, NULL);
		if (m_BulletAddTime->Update() == true)
		{
			if (m_player->GetPlayerLive() == true)
				m_BulletList->AddBullet(m_player->Getx(), m_player->Gety());//플레이어 xy값 가져가기
		}
		if (m_BulletMoveTime->Update() == true)
		{
			m_BulletList->MoveBullet(fETime);
			m_StarList->MoveStar();
		}
		if (m_TimerTime->Update() == true)
		{
			m_Timer->Update();
		}
		if (m_PlayTime->Update() == true)
		{
			m_player->TimeScore();
			m_Fever->Update(FLIGHTGAME);
			m_StarList->AddStar(FLIGHTGAME, m_Fever->GetFeverChange(), m_player->GetScore(), m_player->Getx(), m_player->Gety());
			m_Fever->FeverChangeReset();
			if (m_GameState == TIMEOUT)
				TimeOutScene();
		}
		for (int i = 0; i < 4; i++)
		{
			if (m_player->GetPlayerLive() == true)
			{
				if (m_StarList->Contact(m_player->GetPlayerRect(i)) == true)
				{
					m_player->StarScore(m_StarList->GetScore());
					m_Fever->FeverGauge();
				}
			}
		}
		if (m_GameState != STOP)
			m_StarList->ScoreChange();
		for (int i = 0; i < 4; i++)
		{
			if (m_player->GetPlayerLive() == true)
			{
				if (m_BulletList->Contact(m_player->GetPlayerRect(i)) == true)
				{
					//플레이어 죽음
					m_player->PlayerDeath();
					//별 히트 초기화
					m_StarList->ResetHitCount();
					//피버 초기화
					m_Fever->FeverReset();
					//블렛 제거
					m_BulletList->Release();
					//별 제거
					m_StarList->Release();
				}
			}
		}

		if (m_Timer->GetTimeOut() == true && m_GameState == PLAY)
			m_GameState = TIMEOUT;
	}
	else if (Loading->GetLoading() == true)
	{
		Loading->Loading();
	}
}
void FlightGameScene::TimeOutScene()
{
	if (m_TimeOutCount != 2)
		m_TimeOutCount++;
	else
	{
		m_TimeOutCount = 0;
		m_GameState = STOP;
		m_Fever->FeverReset();
		m_fTimerGague = 1;
		FileLoad(m_hWnd);
		if (m_FileScore < m_player->GetScore())
		{
			m_FileScore = m_player->GetScore();
			FileSave(m_hWnd);
		}
		m_player->ScoreReset();
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME);
	}
}

void FlightGameScene::FileLoad(HWND hWnd)
{
	OPENFILENAME OFN;
	char lpstrFile[MAX_PATH] = "Score.txt";
	char lpstrPath[MAX_PATH] = "";
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	GetCurrentDirectory(MAX_PATH, lpstrPath);
	OFN.lpstrInitialDir = lpstrPath;
	char buf[256];
	int Data;
	wsprintf(buf, "Score.txt");
	HANDLE hFile = CreateFile(buf, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);;
	if (hFile == INVALID_HANDLE_VALUE)// 파일이 없으면
	{
		FileSave(hWnd);
		//DWORD err = CommDlgExtendedError();
	}
	//hFile = CreateFile(buf, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD readB;
	ReadFile(hFile, &Data, sizeof(int), &readB, NULL);
	m_FileScore2 = Data;
	ReadFile(hFile, &Data, sizeof(int), &readB, NULL);
	m_FileScore = Data;
	CloseHandle(hFile);
}

void FlightGameScene::FileSave(HWND hWnd)
{
	OPENFILENAME OFN;
	char lpstrFile[MAX_PATH] = "Score.txt";
	char lpstrPath[MAX_PATH] = "";
	memset(&OFN, 0, sizeof(OPENFILENAME));
	OFN.lStructSize = sizeof(OPENFILENAME);
	OFN.hwndOwner = hWnd;
	OFN.lpstrFilter = "Every File(*.*)\0*.*\0Text File\0*.txt;*.doc\0";
	OFN.lpstrFile = lpstrFile;
	OFN.nMaxFile = 256;
	GetCurrentDirectory(MAX_PATH, lpstrPath);
	OFN.lpstrInitialDir = lpstrPath;
	char buf[256];
	int Data;
	wsprintf(buf, "Score.txt");
	HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	DWORD writeB;
	Data = m_FileScore2;
	WriteFile(hFile, &Data, sizeof(int), &writeB, NULL);
	Data = m_FileScore;
	WriteFile(hFile, &Data, sizeof(int), &writeB, NULL);
	CloseHandle(hFile);
}

void  FlightGameScene::Draw(HDC hdc)
{
	if (Loading->GetLoading() == false)
	{
		int ms = m_Timer->Getms();
		int second = m_Timer->GetSecond();
		float time;
		second = second * 100;
		time = second + ms;
		time = time / 4500;
		m_pBack->DrawBitblt(0, 0);
		m_StarList->Draw();
		m_BulletList->Draw();
		m_player->Draw();
		m_pTimerGague->DynamicDrawBitblt(20, 620, time, 1);
		m_Timer->Draw();
		m_Fever->Draw();
		m_ScoreLabel->Draw();
		if (m_GameState == TIMEOUT)
			m_TimeOut->Draw(100, 300);
	}
	else if (Loading->GetLoading() == true)
	{
		Loading->Draw();
	}
}
void FlightGameScene::Release()
{
	if (m_bFirstStart == true)
	{
		m_BulletList->Release();
		m_StarList->Release();
		delete Loading;
		delete m_ScoreLabel;
		delete m_Fever;
		delete m_Timer;
		delete m_TimerTime;
		delete m_PlayTime;
		delete m_BulletAddTime;
		delete m_BulletMoveTime;
		m_bFirstStart = false;
	}

}
FlightGameScene::~FlightGameScene()
{
	JEngine::ResoucesManager::GetInstance()->~ResoucesManager();
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::UIManager::GetInstance()->RelaaseUI();
	delete m_player;
	delete m_StarList;
	delete m_BulletList;
}