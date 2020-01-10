
#include "InterfaceManager.h"

InterfaceManager::InterfaceManager()
{
	cycle = 0;
}

void InterfaceManager::Init()
{
	SetBitmap();
}

void InterfaceManager::SetBitmap()
{
	for (int i = 0; i < 3; i++)//타이틀 별
		m_StarList[i].SetBitmap(i + 6);
	m_back.SetBitmap(18);
	for (int i = 0; i < 3; i++)
		m_backNormal[i].SetBitmap(i + 19);
	m_Life.SetBitmap(25);
	m_Imiter.SetBitmap(24);
}
void InterfaceManager::StartMenu(HDC  hdc, HDC MemDC)
{
	SetTextAlign(MemDC, TA_CENTER);
	TextOut(MemDC, 215, 100, TEXT("CIRCUS_TROUPE"), 13);
	TextOut(MemDC, 215, 600, TEXT("1 Player_Start"), 14);
	TextOut(MemDC, 215, 620, TEXT("2 Game_End"), 10);
}
void InterfaceManager::DrawTitle(HDC hdc, HDC MemDC)
{
	int j = 0 + cycle;
	for (int i = 0; i < 18; i++)
	{
		m_StarList[j].Draw(hdc, MemDC, 50 + i * 20, 70);
		if (j != 2)
			j++;
		else if (j == 2)
			j = 0;
	}
	for (int i = 0; i < 18; i++)
	{
		m_StarList[j].Draw(hdc, MemDC, 50 + i * 20, 250);
		if (j != 2)
			j++;
		else if (j == 2)
			j = 0;
	}
	for (int i = 0; i < 8; i++)
	{
		m_StarList[j].Draw(hdc, MemDC, 35, 90 + i * 20);
		if (j != 2)
			j++;
		else if (j == 2)
			j = 0;
	}
	for (int i = 0; i < 8; i++)
	{
		m_StarList[j].Draw(hdc, MemDC, 405, 90 + i * 20);
		if (j != 2)
			j++;
		else if (j == 2)
			j = 0;
	}
	cycle++;
	if (cycle == 3)
		cycle = 0;

}
void InterfaceManager::MenuChoice(HDC hdc, HDC MemDC, int choice)
{
	if (choice == 1)
	{
		TextOut(MemDC, 130, 620, TEXT("    "), 4);
		TextOut(MemDC, 130, 600, TEXT("☆"), 2);
	}

	else if (choice == 2)
	{
		TextOut(MemDC, 130, 600, TEXT("    "), 4);
		TextOut(MemDC, 130, 620, TEXT("☆"), 2);
	}
}

void InterfaceManager::CircusBack(HDC hdc, HDC MemDC, int Move, int Clock)
{
	char ch[10];
	for (int i = 0; i < 8; i++)
		m_back.Draw(hdc, MemDC, 0 + (i * 65), 500);//650*
	for (int i = 0; i <= 101; i++)
	{
		if (i % 7 == 4)
			m_backNormal[0].Draw(hdc, MemDC, 0 + (i * 64) - Move, 434);//
		else
			if (Clock % 2 == 0)
				m_backNormal[1].Draw(hdc, MemDC, 0 + (i * 64) - Move, 436);//
			else
				m_backNormal[2].Draw(hdc, MemDC, 0 + (i * 64) - Move, 436);
	}
	for (int i = 0; i <= 10; i++)
	{
		wsprintf(ch, "%d", 100 - i * 10);
		m_Imiter.Draw(hdc, MemDC, (500 * i) - Move, 650);
		TextOut(MemDC, (500 * i) + 30 - Move, 656, ch, strlen(ch));
	}
}


void InterfaceManager::StatePlate(HDC hdc, HDC MemDC, int Life, int Score, int BonusScore, int Stage)
{
	char buf[256];
	for (int i = 0; i < 18; i++)
		m_StarList[1].Draw(hdc, MemDC, 40 + i * 20, 200);
	for (int i = 0; i < 18; i++)
		m_StarList[1].Draw(hdc, MemDC, 40 + i * 20, 300);
	for (int i = 0; i < 6; i++)
		m_StarList[0].Draw(hdc, MemDC, 25, 200 + i * 20);
	for (int i = 0; i < 6; i++)
		m_StarList[2].Draw(hdc, MemDC, 395, 200 + i * 20);
	TextOut(MemDC, 50, 260, TEXT("LIFE"), 4);
	for (int i = 0; i < Life; i++)
		m_Life.Draw(hdc, MemDC, 50 + i * 20, 285);//드로우중 트루 폴스 쓰는거 찾기

	TextOut(MemDC, 50, 220, TEXT("Score"), 5);
	wsprintf(buf, TEXT("%d"), Score);
	TextOut(MemDC, 50, 240, buf, strlen(buf));

	TextOut(MemDC, 270, 260, TEXT("Stage"), 5);
	wsprintf(buf, TEXT("%d"), Stage);
	TextOut(MemDC, 270, 280, buf, strlen(buf));
	TextOut(MemDC, 270, 220, TEXT("▶KEY 설명"), 10);
	TextOut(MemDC, 270, 240, TEXT("←,↑,→, SPACE"), 15);

	TextOut(MemDC, 150, 260, TEXT("BonusScore"), 10);
	wsprintf(buf, TEXT("%d"), BonusScore);
	TextOut(MemDC, 150, 280, buf, strlen(buf));

}

void InterfaceManager::StageDisplay(HDC hdc, HDC MemDC)
{
	TextOut(MemDC, 190, 300, TEXT("S t a g e 1"), 11);
}

InterfaceManager::~InterfaceManager()
{
}