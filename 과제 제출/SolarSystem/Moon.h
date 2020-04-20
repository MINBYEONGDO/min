
#pragma once
#include "Mecro.h"
class Moon
{
private:
	string m_strName;
	D3DXMATRIXA16   m_matSChild; //자식의 스케일 행렬
	D3DXMATRIXA16   m_matTMChild; //자식의 변환 행렬
	D3DXMATRIXA16   m_matRChild; //자식의 회전 행렬
	D3DXMATRIXA16   m_matRevChild; //자식의 공전 행렬
public:
	void Init();
	void Animate(Moon* moon);
	D3DXMATRIXA16  Render(Moon* moon);
	Moon();
	~Moon();
};
