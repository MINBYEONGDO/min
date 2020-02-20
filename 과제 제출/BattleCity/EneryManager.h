
#pragma once
#include"Enery.h"
class EneryManager
{
private:
	Enery *EneryList;
	Enery *m_pEnerytmp;
	int m_iHitEneryNumber;//방금 맞은 적의 번호
	int m_iCrushDirection;
	int m_Max;//적의 총 수
	int m_iLiveEnery;//생존해 있는 적 수
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
	int GetMax()//총 에너미 수
	{
		return m_Max;
	}
	int GetLiveEnery()//살았는지 죽었는지
	{
		return m_iLiveEnery;
	}
	int GetCruchDirection()//공격방향??//???
	{
		return m_iCrushDirection;
	}
	int GetRespawnEnery()
	{
		return m_iRespawnEnery;
	}
	int GetMissileMax(int Number)//그 에너미의 총 미사일수???
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
