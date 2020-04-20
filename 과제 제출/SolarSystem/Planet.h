
#pragma once
#include"Mecro.h"
#include "Moon.h"
class Planet
{
private:
protected:
	Planet* Next;
	D3DXMATRIXA16   m_matSParent; //자식의 스케일 행렬
	D3DXMATRIXA16   m_matTMParent; //부모의 변환 행렬
	D3DXMATRIXA16   m_matRParent; //부모의 회전 행렬
	D3DXMATRIXA16   m_matRevParent; //부모의 공전 행렬
	string m_sName;
	int m_PlanetNumber;
	Moon *m_Moon;
	bool m_bExistMoon;
public:
	Planet();
	~Planet();
	void Init(Planet* Node, int Number);
	void Animate(Planet* Node, int Number);
	D3DXMATRIXA16 Render(Planet* Node, int Number);
	D3DXMATRIXA16 MoonRender(Planet* Node);
	void SetNext(Planet* Node);
	void Release(Planet *Node);
	Planet* GetPlanet(Planet* Node, int Number)
	{
		Planet* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_PlanetNumber == Number)
			{
				break;
			}
			tmp = tmp->Next;
		}
		return tmp;
	}
	int GetNumber(Planet* Node, int Number)
	{
		Planet* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_PlanetNumber == Number)
			{
				break;
			}
			tmp = tmp->Next;
		}
		return tmp->m_PlanetNumber;
	}
	bool GetExistMoon(Planet* Node, int Number)
	{
		Planet* tmp;
		tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_PlanetNumber == Number)
			{
				break;
			}
			tmp = tmp->Next;
		}
		return tmp->m_bExistMoon;
	}
	Planet* GetNext()
	{
		return Next;
	}
	D3DXMATRIXA16 GetTMParent()
	{
		return m_matTMParent;
	}
	D3DXMATRIXA16 GetRParent()
	{
		return m_matRParent;
	}
	D3DXMATRIXA16 GetRevParent()
	{
		return m_matRevParent;
	}
	D3DXMATRIXA16 GetSParent()
	{
		return m_matSParent;
	}
};