
#pragma once
#include"Enery.h"
class EneryManager
{
private:
	Enery *EneryList;
	Enery *m_pEnerytmp;
	int m_iHitEneryNumber;//��� ���� ���� ��ȣ
	int m_iCrushDirection;
	int m_Max;//���� �� ��
	int m_iLiveEnery;//������ �ִ� �� ��
	int m_iRespawnEnery;//
public:
	void Init(int Stage);

	void Respawn();
	void EneryResetRespawning(int Number, RECT PlayerRect);

	void CheckMove(int MapType, int Number, float Moving);
	void CheckRectReset(int Number);
	void EneryMove(int MapType, int Number, float Moving);
	void ChangeDirection(int Number);

	void Fire();
	void MissileMove();
	void MissileChangeStateCruch(int Number, int MissileNumber, int CrushType);

	void ImageChange(int Number);
	void BreakEnery();

	bool ContactObject(int Number, RECT Missilerect);
	bool ContactObject(RECT Missilerect);

	void Draw(HDC hdc);
	void Release();
	bool GetEneryRespawning(int Number)
	{
		Enery* tmp = NULL;
		tmp = EneryList;
		return EneryList->GetRespawning(tmp, Number);
	}
	inline RECT GetEneryRect(int Number)
	{
		Enery* tmp = NULL;
		tmp = EneryList;
		return EneryList->GetRect(tmp, Number);
	}

	inline RECT GetEneryCheckRect(int Number)
	{
		Enery* tmp = NULL;
		tmp = EneryList;
		return EneryList->GetCheckRect(tmp, Number);
	}
	int GetMax()//�� ���ʹ� ��
	{
		return m_Max;
	}
	int GetLiveEnery()//��Ҵ��� �׾�����
	{
		return m_iLiveEnery;
	}
	int GetCruchDirection()//���ݹ���??//???
	{
		return m_iCrushDirection;
	}
	int GetRespawnEnery()
	{
		return m_iRespawnEnery;
	}
	int GetMissileMax(int Number)//�� ���ʹ��� �� �̻��ϼ�???
	{
		return EneryList->GetMissileMax(EneryList, Number);
	}
	inline RECT GetMissileRect(int Number, int MissileNumber)
	{
		return EneryList->GetMissileRect(EneryList, Number, MissileNumber);
	}
	inline int GetMissileDirection(int Number, int MissileNumber)
	{
		return EneryList->GetMissileDirection(EneryList, Number, MissileNumber);
	}
	EneryManager();
	~EneryManager();
};
