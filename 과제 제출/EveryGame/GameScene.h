
#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "Button.h"
#include "Label.h"
class GameScene : public JEngine::Scene
{
private:
	float    m_fTitleX;
	float    m_fTitleY;

	float    m_fSpeedX;
	int m_PaperGameScore;
	int m_FlightGameScore;
	JEngine::BitMap* m_pBack;
	JEngine::Button* m_Button;
	JEngine::Label* m_PaperScore;
	JEngine::Label* m_FlightScore;
public:
	virtual void Init(HWND hWnd);
	virtual bool Input(float fETime);
	virtual void Update(float fETime);
	virtual void Draw(HDC hdc);
	virtual void Release();
	void FileLoad(HWND hWnd);
	void FileSave(HWND hWnd);
	bool ClickEvent_FlightGame();
	bool ClickEvent_PaperGame();
	int GetPaperScore()
	{
		return m_PaperGameScore;
	}
	int GetFlightScore()
	{
		return  m_FlightGameScore;
	}
	GameScene();
	~GameScene();
};