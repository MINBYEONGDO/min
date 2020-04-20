

#pragma once
#include "Mecro.h"

class Sun
{
private:
	D3DXMATRIXA16   m_matTMAncestor; //������ ��ȯ ���
	D3DXMATRIXA16   m_matRAncestor; //������ ȸ�� ���
	string m_sName;
public:
	Sun();
	void Init();
	void Animate();//����
	D3DXMATRIXA16 GetAncTM()
	{
		return m_matTMAncestor;
	}
	D3DXMATRIXA16 GetAncR()
	{
		return m_matRAncestor;
	}
	~Sun();
};
