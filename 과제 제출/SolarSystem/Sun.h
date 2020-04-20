

#pragma once
#include "Mecro.h"

class Sun
{
private:
	D3DXMATRIXA16   m_matTMAncestor; //조상의 변환 행렬
	D3DXMATRIXA16   m_matRAncestor; //조상의 회전 행렬
	string m_sName;
public:
	Sun();
	void Init();
	void Animate();//자전
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
