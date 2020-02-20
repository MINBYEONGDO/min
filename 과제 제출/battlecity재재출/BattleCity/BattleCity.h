
#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
#include "MapManager.h"
#include"InterfaceManager.h"
#include "Player.h"
#include "EneryManager.h"
class BattleCity
{
private:
	HWND m_hWnd;
	HDC m_hdc;
	HDC MemDC;
	HBITMAP m_Bitmap;
	HBITMAP m_OldBitmap;

	DWORD  m_dwLastTime;
	DWORD  m_dwCurTime;
	float  m_fDeltaTime;
	float m_fCurJumpTime;

	int CurClock;
	int LastClock;
	int CreateEneryCurClock;
	int CreateEneryLastClock;
	int Space_CurClock;
	int Space_LastClock;
	int Stage_CurClock;
	int Stage_LastClock;

	MapManager* MM;
	InterfaceManager IM;
	Player *m_player;
	EneryManager *EM;
	Bitmap bitmap;
	int m_iStage;
	int m_iGameState;
public:
	void Init(HWND hWnd);
	void FileDataLoad(int x, int y, int Data);
	void Menu();
	void StageImage();
	void ClearImage();
	void DefeatImage();
	void StageClear();
	void Defeat();
	void MenuChoice(int Choice);
	void Update();
	void SetDeltaTime();
	void CreateEnery();
	void PlayerAction();
	void EneryAction();
	void MissileAction();
	void PlayerMissileActive();
	void EneryMissileActive();
	void Draw();
	void CreateHDC();
	void DeleteHDC();
	void Release();

	inline int GetGameState()
	{
		return m_iGameState;
	}
	BattleCity();
	~BattleCity();
};