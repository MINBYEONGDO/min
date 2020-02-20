
#include "InterfaceManager.h"



InterfaceManager::InterfaceManager()
{
	m_iChoice_y = 300;
	m_iChoiceNumber = 0;
}
void InterfaceManager::Init(int stage)
{
	EneryIcon.Init(605, 250, 28);
	PlayerLife.Init(605, 400, 29);
	StageIcon.Init(605, 500, 30);
}
void InterfaceManager::Draw(HDC hdc, int life, int stage, int EneryMax)
{
	PlayerLife.Draw(hdc);
	bool checkline = false;
	int xline = 0;//count와 같은 용도로 사용하면서 x단위 값을 변화시켜준다. 일을 두개한다. 변수 줄일려고
	int yline = 0;
	for (int i = 0; i < EneryMax; i++)
	{
		if (xline % 4 == 0)
		{
			yline++;
			xline = 0;
		}
		EneryIcon.Init(605 + xline * 20, 300 + yline * 20, 28);
		EneryIcon.Draw(hdc);
		xline++;
	}
	char buf[120];
	wsprintf(buf, "%d", life);
	TextOut(hdc, 615, 400, buf, 1);
	StageIcon.Draw(hdc);
	wsprintf(buf, "%d", stage);
	TextOut(hdc, 615, 520, buf, 1);
}
void InterfaceManager::Menu(HDC MemDC)
{
	TextOut(MemDC, 345, 100, "BattleCity", 10);//350//345
	TextOut(MemDC, 344, 300, "PlayGame", 8);//350
	TextOut(MemDC, 345, 330, "EndGame", 7);
	TextOut(MemDC, 320, m_iChoice_y, "▷", 2);
}

void InterfaceManager::Stage(HDC MemDC, int Number)
{
	char buf[256];
	wsprintf(buf, "Stage %d", Number);
	TextOut(MemDC, 345, 100, buf, 7);//350//345
}
void InterfaceManager::Clear(HDC MemDC)
{
	TextOut(MemDC, 345, 100, "CLEAR", 5);//350//345
}
void InterfaceManager::Defeat(HDC MemDC)
{
	TextOut(MemDC, 345, 100, "DEFEAT", 6);//350//345
}
void InterfaceManager::MoveChoice(HDC MemDC, int Choice)
{
	if (Choice == UP)
	{
		m_iChoice_y = 300;
		m_iChoiceNumber = 0;
	}
	else if (Choice == DOWN)
	{
		m_iChoice_y = 330;
		m_iChoiceNumber = 1;
	}
}

void InterfaceManager::GameInterface(int life, int stage)
{
	//적 수 -> 나중에
	//내 목숨
	//스테이지
}

InterfaceManager::~InterfaceManager()
{
}
