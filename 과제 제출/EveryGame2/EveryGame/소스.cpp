

#include <Windows.h>
#include "EngineMain.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "FlightGameScene.h"
#include "PaperGameScene.h"
#include "time.h"
#include "defines.h"
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	//엔진 객체를 생성하고 타이틀과 윈도우 사이즈를 넣어준다.
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF); //디버깅 후 메모리릭 체크
	//_crtBreakAlloc =208; //메모리릭 위치 탐색 디버깅중
	JEngine::EngineMain engine("EveryGame", 414, 648);
	//씬을 등록한다. 첫번째 등록하는 씬이 초기화면이 된다.


	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new GameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new FlightGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new PaperGameScene);
	//엔진 시작
	return engine.StartEngine(hInstance);
}
