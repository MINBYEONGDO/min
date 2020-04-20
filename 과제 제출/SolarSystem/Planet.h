
#pragma once
#include"Mecro.h"
#include "Moon.h"
class Planet
{
private:
protected:
	Planet* Next;
	D3DXMATRIXA16   m_matSParent; //�ڽ��� ������ ���
	D3DXMATRIXA16   m_matTMParent; //�θ��� ��ȯ ���
	D3DXMATRIXA16   m_matRParent; //�θ��� ȸ�� ���
	D3DXMATRIXA16   m_matRevParent; //�θ��� ���� ���
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