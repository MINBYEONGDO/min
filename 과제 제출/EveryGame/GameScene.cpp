
#include "GameScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

GameScene::GameScene()
{
	m_fTitleX = 414.0f;
	m_fTitleY = 648.0f;
	m_PaperGameScore = 0;
	m_FlightGameScore = 0;
	m_PaperScore = new JEngine::Label;
	m_FlightScore = new JEngine::Label;
	m_fSpeedX = 200;
}

GameScene::~GameScene()
{
	JEngine::ResoucesManager::GetInstance()->~ResoucesManager();
	delete m_PaperScore;
	delete m_FlightScore;
}

void GameScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	FileLoad(hWnd);
	JEngine::UIManager::GetInstance()->AddButton(320, 166, "EveryGame//OnSelect.bmp", std::bind(&GameScene::ClickEvent_PaperGame, this));
	JEngine::UIManager::GetInstance()->AddButton(320, 249, "EveryGame//OnSelect.bmp", std::bind(&GameScene::ClickEvent_FlightGame, this));
	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//GameSelect.bmp");
}
void GameScene::FileLoad(HWND hWnd)
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
	HANDLE hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);;
	if (hFile == INVALID_HANDLE_VALUE)// 파일이 없으면
	{
		FileSave(hWnd);
		hFile = CreateFile(OFN.lpstrFile, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);;
		//DWORD err = CommDlgExtendedError();
	}
	DWORD readB;
	ReadFile(hFile, &Data, sizeof(int), &readB, NULL);
	m_PaperGameScore = Data;
	ReadFile(hFile, &Data, sizeof(int), &readB, NULL);
	m_FlightGameScore = Data;
	CloseHandle(hFile);
	m_PaperScore->Init(to_string(m_PaperGameScore), 200, 200, NULL);
	m_FlightScore->Init(to_string(m_FlightGameScore), 200, 280, NULL);
}

void GameScene::FileSave(HWND hWnd)
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
	Data = 0;
	WriteFile(hFile, &Data, sizeof(int), &writeB, NULL);
	Data = 0;
	WriteFile(hFile, &Data, sizeof(int), &writeB, NULL);
	CloseHandle(hFile);
}
bool GameScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_SPACE))
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_TITLE);
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		return true;

	return false;
}

float time = 0.0f;

void GameScene::Update(float fETime)
{
	time = fETime;
}

void GameScene::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);
	m_FlightScore->Draw();
	m_PaperScore->Draw();
}

bool GameScene::ClickEvent_FlightGame()
{
	JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_FLIGHTGAME);
	return true;
}
bool GameScene::ClickEvent_PaperGame()
{
	JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_PAPERGAME);
	return true;
}
void GameScene::Release()
{
}