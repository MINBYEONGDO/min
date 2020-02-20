
#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
class missile
{
private:
	Bitmap* m_Bitmap;
	missile* Link;
	int m_Direction;
	RECT m_Rect;
	int m_Number;
	int m_Count;
	int m_ix;
	int m_iy;
	int ExplosionCurClock;
	int ExplosionLastClock;
	int m_iExplosion;
	int m_iCrushType;
	bool m_bCrush; //그림 안그리게 하기
	bool m_bExplosion; // 폭발 이펙트 그리게 하기
	bool m_bExplosionEnd; //폭발 이펙트 지우기 와 딜리트 유도
public:
	void Init();
	void CreateMissile(missile *Missile, int Tank_x, int Tank_y, int Tank_Direction, int Number);
	void Move();
	void Explosion(int CrushType);
	void ExplosionEvent();
	void ChangeStateCrush();
	void ReNumber(int Number);
	void Delete(missile** Node, int Number);
	void Draw(HDC hdc, missile* Node);
	void SetLink(missile* Node);
	void Release(missile* MissileList);
	inline int GetDirection(missile* Node, int Number)
	{
		missile* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_Number == Number)
				break;
			tmp = tmp->Link;
		}
		return tmp->m_Direction;
	}
	inline int GetNumber(missile *Node, int Number)
	{
		missile* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_Number == Number)
				break;
			tmp = tmp->Link;
		}
		return tmp->m_Number;
	}
	missile* GetNextLink(missile* Node)
	{
		missile* tmp;
		tmp = NULL;
		tmp = Node;
		return tmp->Link;
	}
	inline missile* Getmissile(missile* Node, int Number)
	{
		missile *tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_Number == Number)
				break;
			tmp = tmp->Link;
		}
		return tmp;
	}
	inline RECT GetMissileRect(missile* Node, int Number)
	{
		missile* tmp;
		RECT rect;
		rect.top = 0;
		rect.bottom = 0;
		rect.left = 0;
		rect.right = 0;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_Number == Number)
			{
				break;
			}
			tmp = tmp->Link;
		}
		if (tmp->m_bCrush == true)
			return rect;
		else if (tmp->m_bCrush == false)
			return tmp->m_Rect;
	}

	inline bool GetExplosion(missile* Node, int Number)
	{
		missile *tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_Number == Number)
				break;
			tmp = tmp->Link;
		}
		return tmp->m_bExplosion;
	}
	inline bool GetExplosionEnd(missile* Node, int Number)
	{
		missile *tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_Number == Number)
				break;
			tmp = tmp->Link;
		}
		return tmp->m_bExplosionEnd;
	}
	inline bool GetCrush(missile* Node, int Number)
	{
		missile *tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_Number == Number)
				break;
			tmp = tmp->Link;
		}
		return tmp->m_bCrush;
	}
	missile();
	~missile();
};
