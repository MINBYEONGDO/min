
#pragma once
#include"Mecro.h"
#include"Tank.h"
class Enery : public Tank
{
private:
	Enery* Next;
	int m_EneryNumber;
	int m_FireCurClock;
	int m_FireLastClock;
	int m_MissileMoveCurClock;
	int m_MissileMoveLastClock;
	int m_TankType;
	bool m_blive;
	bool m_bRespawn;
	bool m_bRespawning;
public:
	virtual void Init();
	virtual void Draw(HDC hdc);
	void Init(Enery *enery, int Stage, int TankType);
	void Respawn(int Number);
	void ChangeRespwaning();
	void CheckMove(int MapType, float Moving);
	virtual void CheckRectReset();
	void Move(int MapType, float Moving);
	void ChnageDirection();
	void BitmapChange();

	void Fire();
	void MissileMove();
	void MissileChangeStateCruch(int Number, int CrushType);
	void Break();//ÆÄ±«´çÇÔ

	void Draw(HDC hdc, Enery* Node);

	void ChageNext(Enery* Node);
	void SetNext(Enery* Node);
	void Release(Enery* Node);
	void Release();
	int GetMissileMax(Enery* Node, int Number)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return tmp->MissileList->GetMax();
	}
	inline RECT GetMissileRect(Enery* Node, int Number, int MissilNumber)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return tmp->MissileList->CheckRect(MissilNumber);
	}
	inline int GetMissileDirection(Enery* Node, int Number, int MissilNumber)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return  tmp->MissileList->GetDirection(MissilNumber);
	}
	inline int GetNumber(Enery* Node, int Number)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return tmp->m_EneryNumber;
	}
	inline int GetDirection(Enery* Node, int Number)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return tmp->m_Direction;
	}
	inline RECT GetRect(Enery *Node, int Number)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return tmp->m_rect;
	}
	inline RECT GetCheckRect(Enery* Node, int Number)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return tmp->m_CheckRect;
	}
	inline bool GetLive(Enery *Node, int Number)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return tmp->m_blive;
	}
	inline bool GetRespawn(Enery *Node, int Number)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return tmp->m_bRespawn;
	}
	inline bool GetRespawning(Enery *Node, int Number)
	{
		Enery* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_EneryNumber == Number)
				break;
			tmp = tmp->Next;
		}
		return tmp->m_bRespawning;
	}
	inline Enery* GetEnery(Enery *Node, int Number)
	{
		Enery *Etmp;
		Etmp = NULL;
		Etmp = Node;
		while (Etmp != NULL)
		{
			if (Etmp->m_EneryNumber == Number)
			{
				break;
			}
			Etmp = Etmp->Next;
		}
		return Etmp;
	}

	Enery();
	~Enery();
};
