
#pragma once
#include "Mecro.h"
#include "BitmapManager.h"
#include "InterfaceManager.h"
#include "Player.h"
#include "obstacleManager.h"
class Circus
{
private:
	InterfaceManager IM;
	obstacleManager oM;
	Player* m_player;

	HWND  m_hWnd;
	HDC hdc;
	HDC MemDC[1];//전체 그리기, 플레이어, 장애물, 배경
	HBITMAP m_BitMap[1];
	HBITMAP m_OldBitmap[1];

	//델타 타임용
	DWORD  m_dwLastTime;
	DWORD  m_dwCurTime;
	float  m_fDeltaTime;
	float m_fCurJumpTime;

	//시간측정용
	float m_CurClock;
	float m_LastClock;
	bool m_bCheckTime;

	bool  m_bJump;
	bool m_bEnd;//끝내기용 불값

	   //물리적
	float  m_fVectorX;
	float  m_fVectorY;

	int m_imenu; //선택한 메뉴에 관한 변수
	int m_iState; //게임의 상태 - menu, palyering , 등
	int m_Move; // 시작에서 부터 이동한 거리
	int m_iStage; // 굳이 필요한가?
	int m_iTimeBonus;
public:
	void Init(HWND hWnd);
	void CreateHDC1();
	void CreateHDC2();
	void DeleteHDC1();
	void DeleteHDC2();
	void MenuChoice();
	void StageDisplay();
	void Update();
	void PlayGame();
	void PlayerMove();
	void PlayerJump();
	void PlayerDeath();
	void EndEvent(int number);
	void DataRelease();
	void Release();
	bool inline GetbEnd()
	{
		return m_bEnd;
	}
	Circus();
	~Circus();
};