#include "Sun.h"



Sun::Sun()
{
}

void Sun::Init()
{
	m_sName = "�¾�";
}

void Sun::Animate()
{
	//������ �޽ô� ������ �����Ƿ� TM�� ���� ���
	D3DXMatrixIdentity(&m_matTMAncestor);

	//���� �޽��� Y�� ȸ�� ���
	D3DXMatrixRotationY(&m_matRAncestor, GetTickCount() / 500.0f);
}
Sun::~Sun()
{
}