#include "Sun.h"



Sun::Sun()
{
}

void Sun::Init()
{
	m_sName = "태양";
}

void Sun::Animate()
{
	//조상의 메시는 원점에 있으므로 TM은 단위 행렬
	D3DXMatrixIdentity(&m_matTMAncestor);

	//조상 메시의 Y축 회전 행렬
	D3DXMatrixRotationY(&m_matRAncestor, GetTickCount() / 500.0f);
}
Sun::~Sun()
{
}