
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
	HDC MemDC[1];//��ü �׸���, �÷��̾�, ��ֹ�, ���
	HBITMAP m_BitMap[1];
	HBITMAP m_OldBitmap[1];

	//��Ÿ Ÿ�ӿ�
	DWORD  m_dwLastTime;
	DWORD  m_dwCurTime;
	float  m_fDeltaTime;
	float m_fCurJumpTime;

	//�ð�������
	float m_CurClock;
	float m_LastClock;
	bool m_bCheckTime;

	bool  m_bJump;
	bool m_bEnd;//������� �Ұ�

	   //������
	float  m_fVectorX;
	float  m_fVectorY;

	int m_imenu; //������ �޴��� ���� ����
	int m_iState; //������ ���� - menu, palyering , ��
	int m_Move; // ���ۿ��� ���� �̵��� �Ÿ�
	int m_iStage; // ���� �ʿ��Ѱ�?
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