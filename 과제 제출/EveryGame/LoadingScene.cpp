
#include "LoadingScene.h"
#include "ResoucesManager.h"
#include <Windows.h>
#include "defines.h"

LoadingScene::LoadingScene()
{
}

void LoadingScene::Init()
{
	m_bLoading = true;
	m_CurClock = clock();
	m_LastClock = clock();
	m_pback = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//LoadingBack.bmp");
	m_pLoading = JEngine::ResoucesManager::GetInstance()->GetBitmap("EveryGame//Loading.bmp");
}
void LoadingScene::Loading()
{
	m_CurClock = clock();
	if (m_CurClock - m_LastClock > 1000)
		m_bLoading = false;
}
void LoadingScene::Draw()
{
	m_pback->Draw(0, 0);
	m_pLoading->Draw(120, 250);
}
LoadingScene::~LoadingScene()
{
}
