
#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
#include"Interface.h"
class InterfaceManager
{
private:
	int m_iChoice_y;
	int m_iChoiceNumber;
	Interface StageIcon;
	Interface EneryIcon;
	Interface PlayerLife;
public:
	void Init(int stage);
	void Menu(HDC MemDC);
	void Stage(HDC MemDC, int Number);
	void Clear(HDC MemDC);
	void Defeat(HDC MemDC);
	void MoveChoice(HDC MemDC, int Choice);
	void GameInterface(int life, int stage);
	void Draw(HDC hdc, int life, int stage, int EneryMax);
	inline int GetChoiceNumber()
	{
		return m_iChoiceNumber;
	}
	InterfaceManager();
	~InterfaceManager();
};