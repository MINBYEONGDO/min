
#include "PaperGameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

PaperGameScene::PaperGameScene()
{
	m_fTitleX = 414.0f;
	m_fTitleY = 648.0f;
	srand(time(NULL));
	m_fSpeedX = 200;
	m_GameState = PLAY;//게임자체의 상태
	m_Score = 0;
	m_FileScore = 0;
	m_FileScore2 = 0;
	m_fTimerGague = 1;
	m_TimeOutCount = 0;//타임아웃씬 유지시간 체크
	m_bFirstStart = false;
	m_PaperList = new PaperManager;
	m_StarList = new StarManager;
}
void PaperGameScene::Init(HWND hWnd)
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

	m_ScoreLabel = new JEngine::Label;
	m_ScoreLabel->Init("0", 200, 10, NULL);
	m_GameState = PLAY;
	m_Score = 0;
	m_TimerTime = new JEngine::TimeManager;
	m_TimerTime->init(true, 100);
	m_PlayTime = new  JEngine::TimeManager;
	m_PlayTime->init(true, 1);//1 

	m_Timer = new Timer;//제한 시간 45초
	m_Timer->Init(1);

	m_Fever = new Fever;
	m_Fever->Init();

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//ColoredPaperBack.bmp");
	m_TimeOut = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//TimeOver.bmp");
	m_pTimerGague = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//Fever3.bmp");
	m_PaperList->AddPaper();
	m_bFirstStart = true;
}

void PaperGameScene::FileLoad(HWND hWnd)
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
	m_FileScore = Data;
	ReadFile(hFile, &Data, sizeof(int), &readB, NULL);
	m_FileScore2 = Data;
	CloseHandle(hFile);
}

void PaperGameScene::FileSave(HWND hWnd)
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
	Data = m_FileScore;
	WriteFile(hFile, &Data, sizeof(int), &writeB, NULL);
	Data = m_FileScore2;
	WriteFile(hFile, &Data, sizeof(int), &writeB, NULL);
	CloseHandle(hFile);
}
bool PaperGameScene::Input(float fETime)
{
	if (Loading->GetLoading() == false)
	{
		if (m_GameState == PLAY)
		{
			if (m_PaperList->GetPaperMove() == false)// 속도가 빨라서 확인은 안되지만 시간을 늘려놓으면 이동중 키입력을 막고있음
			{
				if (JEngine::InputManager::GetInstance()->isKeyPress(VK_UP))
					m_PaperList->Input(fETime, UP);
				if (JEngine::InputManager::GetInstance()->isKeyPress(VK_DOWN))
					m_PaperList->Input(fETime, DOWN);
				if (JEngine::InputManager::GetInstance()->isKeyPress(VK_LEFT))
					m_PaperList->Input(fETime, LEFT);
				if (JEngine::InputManager::GetInstance()->isKeyPress(VK_RIGHT))
					m_PaperList->Input(fETime, RIGHT);
			}
		}
	}
	return false;
}
void PaperGameScene::PaperReach()
{

	if (m_PaperList->GetReach() == true)// 종이가 최고점에 도달했을때 --> 결국 정답일때 아님이게?//연속적으로 적용되는걸 막음
	{
		if (m_Fever->GetFeverState() == NON && m_StarList->GetLiveStar() == 0)//피버가 아닐때의 점수
		{
			m_Score += m_PaperList->GetPaperScore();
		}
		else if (m_StarList->GetLiveStar() != 0)//없으면 생성되자 마자 사라짐
		{
			if (m_Fever->GetFeverState() == NON || m_Fever->GetFeverState() == NOMAL)//피버가 아닐때의 점수
			{
				m_Score += m_StarList->GetStarScore();
			}
			//피버 일때
			else if (m_Fever->GetFeverState() == SUPER)
			{
				m_Score += m_StarList->GetStarScore() * 2;
			}
			else if (m_Fever->GetFeverState() == ULTRA)
			{
				m_Score += m_StarList->GetStarScore() * 3;
			}
			m_Fever->FeverGauge();
			m_StarList->StarDelete(m_StarList->SearchLiveStarNumber());
			//별히트 제거 해야함
			m_StarList->HitIncrease();
		}
		if (m_Fever->GetFeverState() != NON && m_StarList->GetLiveStar() == 0)//피버이면서 스타가 없을때
		{
			m_StarList->AddStar(PAPERGAME, m_Fever->GetFeverChange(), m_Score, 155, 297);//별하나 생성
		}
		if (m_PaperList->GetAnswerCount() == 5 && m_Fever->GetFeverState() == NON)//5연속으로 정답일때
		{
			m_StarList->AddStar(PAPERGAME, m_Fever->GetFeverChange(), m_Score, 155, 297);//별하나 생성
			m_PaperList->StateReset();//카운터 초기화
		}
		m_Fever->FeverGauge();//종이가 최고점에 도달했을때 게이지 추가
		m_PaperList->PaperReach();//색종이가 최고점에 도달했을때 종이 삭제 추가를  실행하는 함수
	}
}
void PaperGameScene::PaperNotAnswer()
{
	if (m_PaperList->GetAnswer() == 20)//오답일때
	{
		//피버 감소
		if (m_Fever->GetFeverState() == NON)
			m_Fever->FeverGaugeDisCount();
		//만약 피버상태라면 피버상태 초기화
		else if (m_Fever->GetFeverState() != NON && m_Fever->GetFeverState() != ULTRA)
			m_Fever->FeverReset();
		//스택 초기화
		m_PaperList->StateReset();
		//별제거
		if (m_StarList->GetLiveStar() != 0)
		{
			m_StarList->StarDelete(m_StarList->SearchLiveStarNumber());
		}
		m_StarList->ResetHitCount();
		//별히트제거
		if (m_Fever->GetFeverState() == ULTRA)
			m_StarList->AddStar(PAPERGAME, m_Fever->GetFeverChange(), m_Score, 155, 297);//별하나 생성
			  //울트라 피버일때는 오답이라도 피버게이지가 초기화 되지 않음/ 별히트는 초기화
			  //그런데 이코드가 없으면 오답후 바로 별이 생성되지 않음
			  //그래서 추가함
	}
}
void PaperGameScene::Update(float fETime)
{
	if (Loading->GetLoading() == false)
	{
		m_ScoreLabel->Init(to_string(m_Score), 200, 10, NULL);
		if (m_TimerTime->Update() == true)
		{
			m_PaperList->MovePaper();
			m_Timer->Update();//스탑워치 변화
		}
		if (m_PlayTime->Update() == true)
		{
			//m_PaperList->MovePaper();
			m_Fever->Update(PAPERGAME);//피버상태 변화
			if (m_GameState == TIMEOUT)
				TimeOutScene();
		}
		if (m_Fever->GetFeverState() != NON && m_StarList->GetLiveStar() == 0)//피버이면서 스타가 없을때
		{//피버가 되자말자 바로 별생성을 하기 위해서 이 코드가 없으면 피버가 되도 첫 종이에는 별이 생성되지 않는다.
			m_StarList->AddStar(PAPERGAME, m_Fever->GetFeverChange(), m_Score, 155, 297);//별하나 생성
		}
		PaperReach();
		PaperNotAnswer();
		//if (m_PaperList->GetAnswer() == 10)//정답일때
		//{
		// //별 사라지게 하기
		// if (m_StarList->GetStar() != 0 && m_PaperList->GetAnswerCount() == 1)//없으면 생성되자 마자 사라짐
		// {
		//  m_Fever->FeverGauge();
		//  m_StarList->StarDelete(0);
		//  //별히트 제거 해야함
		//  m_StarList->ResetHitCount();
		// }
		// //점수 추가
		//}//여러번 적용되고 도착위치에 도달했을때의 조건문과 겹치기 때문에 제거
		if (m_Timer->GetTimeOut() == true && m_GameState == PLAY)
			m_GameState = TIMEOUT;
	}
	else if (Loading->GetLoading() == true)
	{
		Loading->Loading();
	}
}
void PaperGameScene::Draw(HDC hdc)//타이머 드로우 함수 따로 만들어서 보기 편하게 만들기
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
		m_pTimerGague->DynamicDrawBitblt(20, 620, time, 1);
		m_Timer->Draw();
		m_PaperList->Draw();
		m_StarList->Draw();
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

void PaperGameScene::TimeOutScene()
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
		if (m_FileScore < m_Score)
		{
			m_FileScore = m_Score;
			FileSave(m_hWnd);
		}

		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME);
	}
}
void PaperGameScene::Release()
{
	if (m_bFirstStart == true)
	{
		m_StarList->Release();
		m_PaperList->Release();

		delete Loading;
		delete m_ScoreLabel;
		delete m_Timer;//제한 시간 45초
		delete m_Fever;
		delete m_TimerTime;
		delete m_PlayTime;
		m_bFirstStart = false;
	}
}

PaperGameScene::~PaperGameScene()
{
	if (m_bFirstStart == true)
	{
		JEngine::ResoucesManager::GetInstance()->~ResoucesManager();
		JEngine::InputManager::GetInstance()->Clear();
	}
	delete m_StarList;
	delete m_PaperList;
	JEngine::ResoucesManager::GetInstance()->DestroyInstance();
	JEngine::TimeManager::GetInstance()->DestroyInstance();
	JEngine::InputManager::GetInstance()->DestroyInstance();
	JEngine::UIManager::GetInstance()->DestroyInstance();
}