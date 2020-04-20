#include "Moon.h"

Moon::Moon()
{
}
void Moon::Init()
{
	m_strName = "��";
}
void Moon::Animate(Moon* moon)
{
	D3DXMatrixScaling(&moon->m_matSChild, 0.3f, 0.3f, 0.3f);

	D3DXMatrixRotationY(&moon->m_matRChild, GetTickCount() / 500.0f);

	//Ư�� vector�� ������ �ϴ� ���
	D3DXMatrixRotationZ(&moon->m_matRevChild, GetTickCount() / 1000.0f);
	//�θ� �޽ô� �������� ���� (3, 3, 3)�� �Ÿ��� �ִ�.
	D3DXMatrixTranslation(&moon->m_matTMChild, 1.5f, 1.5f, 1.5f);
}
D3DXMATRIXA16  Moon::Render(Moon* moon)
{
	return moon->m_matSChild*moon->m_matRChild*moon->m_matTMChild * moon->m_matRevChild;
}

Moon::~Moon()
{
}