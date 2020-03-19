
#include "TitleScene.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "UIManager.h"
#include "POINT.h"
#include "ResoucesManager.h"
#include "defines.h"


TitleScene::TitleScene()
{
	m_fTitleX = 414.0f;
	m_fTitleY = 648.0f;

	m_fSpeedX = 200;
}

TitleScene::~TitleScene()
{
	JEngine::ResoucesManager::GetInstance()->~ResoucesManager();
	JEngine::InputManager::GetInstance()->Clear();
}

void TitleScene::Init(HWND hWnd)
{
	JEngine::InputManager::GetInstance()->Clear();
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_SPACE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_ESCAPE);
	JEngine::InputManager::GetInstance()->RegistKeyCode(VK_LBUTTON);

	m_pBack = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//Loadingback.bmp");
	m_pTitle = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//Title.bmp");

	m_pTitle->SetAnchor(JEngine::ANCHOR_RB);
}

bool TitleScene::Input(float fETime)
{
	if (JEngine::InputManager::GetInstance()->isKeyUp(VK_SPACE))
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME);
	else if (JEngine::InputManager::GetInstance()->isKeyDown(VK_LBUTTON))
		JEngine::SceneManager::GetInstance()->LoadScene(SCENE_INDEX_GAME);
	else if (JEngine::InputManager::GetInstance()->isKeyUp(VK_ESCAPE))
		return true;
	return false;
}

void TitleScene::Update(float fETime)
{

}

void TitleScene::Draw(HDC hdc)
{
	m_pBack->DrawBitblt(0, 0);
	m_pTitle->Draw((int)m_fTitleX, (int)m_fTitleY);
}

void TitleScene::Release()
{

}

bool TitleScene::OnClick()
{
	return true;
}
