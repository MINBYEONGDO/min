

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
	//���� ��ü�� �����ϰ� Ÿ��Ʋ�� ������ ����� �־��ش�.
	_CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF); //����� �� �޸𸮸� üũ
	//_crtBreakAlloc =208; //�޸𸮸� ��ġ Ž�� �������
	JEngine::EngineMain engine("EveryGame", 414, 648);
	//���� ����Ѵ�. ù��° ����ϴ� ���� �ʱ�ȭ���� �ȴ�.


	JEngine::SceneManager::GetInstance()->RegistScene(new TitleScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new GameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new FlightGameScene);
	JEngine::SceneManager::GetInstance()->RegistScene(new PaperGameScene);
	//���� ����
	return engine.StartEngine(hInstance);
}
