
#pragma once
#include "Mecro.h"
class Moon
{
private:
	string m_strName;
	D3DXMATRIXA16   m_matSChild; //�ڽ��� ������ ���
	D3DXMATRIXA16   m_matTMChild; //�ڽ��� ��ȯ ���
	D3DXMATRIXA16   m_matRChild; //�ڽ��� ȸ�� ���
	D3DXMATRIXA16   m_matRevChild; //�ڽ��� ���� ���
public:
	void Init();
	void Animate(Moon* moon);
	D3DXMATRIXA16  Render(Moon* moon);
	Moon();
	~Moon();
};
