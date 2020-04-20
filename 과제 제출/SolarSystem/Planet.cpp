

#include "Planet.h"



Planet::Planet()
{
	Next = NULL;
	m_bExistMoon = false;
}

void Planet::Init(Planet* Node, int Number)
{
	if (Number == 0)
	{
		Node->m_PlanetNumber = 0;
		Node->m_sName = "荐己";
	}
	else if (Number == 1)
	{
		Node->m_PlanetNumber = 1;
		Node->m_sName = "陛己";
	}
	else if (Number == 2)
	{
		Node->m_PlanetNumber = 2;
		Node->m_sName = "瘤备";
		Node->m_bExistMoon = true;
		Node->m_Moon = new Moon;
		Node->m_Moon->Init();
	}
	else if (Number == 3)
	{
		Node->m_PlanetNumber = 3;
		Node->m_sName = "拳己";
	}
	else if (Number == 4)
	{
		Node->m_PlanetNumber = 4;
		Node->m_sName = "格己";
	}
	else if (Number == 5)
	{
		Node->m_PlanetNumber = 5;
		Node->m_sName = "配己";
	}
	else if (Number == 6)
	{
		Node->m_PlanetNumber = 6;
		Node->m_sName = "没空己";
	}
	else if (Number == 7)
	{
		Node->m_PlanetNumber = 7;
		Node->m_sName = "秦空己";
	}
}
void Planet::Animate(Planet* Node, int Number)
{
	D3DXVECTOR3 nomalPVec(-1, 1, 0);
	if (Number == 0)
	{
		D3DXMatrixScaling(&Node->m_matSParent, 0.3f, 0.3f, 0.3f);
		D3DXMatrixRotationY(&Node->m_matRParent, GetTickCount() / 1000.0f);
		D3DXMatrixRotationY(&Node->m_matRevParent, GetTickCount() / 80.0f);
		D3DXMatrixTranslation(&Node->m_matTMParent, 3, 0, 0);
	}
	else if (Number == 1)
	{
		D3DXMatrixScaling(&Node->m_matSParent, 0.3f, 0.3f, 0.3f);
		D3DXMatrixRotationY(&Node->m_matRParent, GetTickCount() / 2000.0f);

		D3DXMatrixRotationY(&Node->m_matRevParent, GetTickCount() / 225.0f);

		D3DXMatrixTranslation(&Node->m_matTMParent, 5.5f, 0, 0);
	}
	else if (Number == 2)
	{
		Node->m_Moon->Animate(m_Moon);
		D3DXMatrixScaling(&Node->m_matSParent, 0.5f, 0.5f, 0.5f);
		D3DXMatrixRotationY(&Node->m_matRParent, GetTickCount() / 400.0f);

		D3DXMatrixRotationY(&Node->m_matRevParent, GetTickCount() / 365.0f);

		D3DXMatrixTranslation(&Node->m_matTMParent, 7.5f, 0, 0);
	}
	else if (Number == 3)
	{
		D3DXMatrixScaling(&Node->m_matSParent, 0.5f, 0.5f, 0.5f);
		D3DXMatrixRotationY(&m_matRParent, GetTickCount() / 400.0f);

		D3DXMatrixRotationY(&Node->m_matRevParent, GetTickCount() / 500.0f);

		D3DXMatrixTranslation(&m_matTMParent, 11.5f, 0, 0);
	}
	else if (Number == 4)
	{
		D3DXMatrixScaling(&Node->m_matSParent, 0.8f, 0.8f, 0.8f);
		D3DXMatrixRotationY(&m_matRParent, GetTickCount() / 100.0f);

		D3DXMatrixRotationY(&Node->m_matRevParent, GetTickCount() / 1000.0f);

		D3DXMatrixTranslation(&m_matTMParent, 20, 0, 0);
	}
	else if (Number == 5)
	{
		D3DXMatrixScaling(&Node->m_matSParent, 0.8f, 0.8f, 0.8f);
		D3DXMatrixRotationY(&m_matRParent, GetTickCount() / 100.0f);

		D3DXMatrixRotationY(&Node->m_matRevParent, GetTickCount() / 1200.0f);

		D3DXMatrixTranslation(&m_matTMParent, 40, 0, 0);
	}
	else if (Number == 6)
	{
		D3DXMatrixScaling(&Node->m_matSParent, 1, 1, 1);

		D3DXMatrixRotationY(&m_matRParent, GetTickCount() / 600.0f);

		D3DXMatrixRotationY(&Node->m_matRevParent, GetTickCount() / 8000.0f);

		D3DXMatrixTranslation(&m_matTMParent, 50, 0, 0);
	}
	else if (Number == 7)
	{
		D3DXMatrixScaling(&Node->m_matSParent, 1, 1, 1);

		D3DXMatrixRotationY(&m_matRParent, GetTickCount() / 600.0f);

		D3DXMatrixRotationY(&Node->m_matRevParent, GetTickCount() / 10000.0f);

		D3DXMatrixTranslation(&m_matTMParent, 70, 0, 0);
	}
}
D3DXMATRIXA16 Planet::Render(Planet* Node, int Number)
{
	return Node->m_matSParent*Node->m_matRParent * Node->m_matTMParent * Node->m_matRevParent;
}
D3DXMATRIXA16 Planet::MoonRender(Planet* Node)
{
	return Node->m_Moon->Render(m_Moon);
}
void Planet::SetNext(Planet *Node)
{
	if (Next == NULL)
	{
		Next = Node;
		Next->Next = NULL;
	}
	else
	{
		Next->SetNext(Node);
	}
}
void Planet::Release(Planet *Node)
{
	while (Node != NULL)
	{
		Node = Node->Next;
		Release(Node);
		if (Node->m_bExistMoon == true)
			delete Node->m_Moon;
		delete Node;
		Node = NULL;
	}
}
Planet::~Planet()
{
}