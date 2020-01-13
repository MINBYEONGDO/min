

#pragma once
#include"Mecro.h"
#include"Interface.h"
class InterfaceManager
{
private:
	Interface m_StarList[3];
	Interface m_back;
	Interface m_backNormal[3];// deco noraml1 normal2
	Interface m_Life;
	Interface m_Imiter;
	int cycle;
public:
	void Init();
	void SetBitmap();
	void StartMenu(HDC hdc, HDC MemDC);
	void DrawTitle(HDC hdc, HDC MemDC);
	void MenuChoice(HDC hdc, HDC MemDC, int choice);
	void StageDisplay(HDC hdc, HDC MemDC);
	void CircusBack(HDC hdc, HDC MemDC, int Move, int Clock);
	void StatePlate(HDC hdc, HDC MemDC, int Life, int Score, int BonusScore, int Stage);
	InterfaceManager();
	~InterfaceManager();
};