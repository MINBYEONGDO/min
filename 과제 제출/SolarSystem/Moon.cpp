#include "Moon.h"

Moon::Moon()
{
}
void Moon::Init()
{
	m_strName = "달";
}
void Moon::Animate(Moon* moon)
{
	D3DXMatrixScaling(&moon->m_matSChild, 0.3f, 0.3f, 0.3f);

	D3DXMatrixRotationY(&moon->m_matRChild, GetTickCount() / 500.0f);

	//특정 vector를 축으로 하는 행렬
	D3DXMatrixRotationZ(&moon->m_matRevChild, GetTickCount() / 1000.0f);
	//부모 메시는 원점으로 부터 (3, 3, 3)의 거리에 있다.
	D3DXMatrixTranslation(&moon->m_matTMChild, 1.5f, 1.5f, 1.5f);
}
D3DXMATRIXA16  Moon::Render(Moon* moon)
{
	return moon->m_matSChild*moon->m_matRChild*moon->m_matTMChild * moon->m_matRevChild;
}

Moon::~Moon()
{
}