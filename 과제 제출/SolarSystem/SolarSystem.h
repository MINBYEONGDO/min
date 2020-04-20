
#pragma once
#include "Sun.h"
#include "PlanetManager.h"
//#include "MatrixManager.h"
class SolarSystem
{
private:
	LPDIRECT3D9    m_pD3D;
	LPDIRECT3DDEVICE9  m_pd3dDevice;
	LPDIRECT3DVERTEXBUFFER9 m_pVB;
	LPDIRECT3DINDEXBUFFER9 m_pIB;

	D3DXMATRIXA16   m_matTMAncestor; //������ ��ȯ ���
	D3DXMATRIXA16   m_matRAncestor; //������ ȸ�� ���

	D3DXMATRIXA16   m_matTMParent; //�θ��� ��ȯ ���
	D3DXMATRIXA16   m_matRParent; //�θ��� ȸ�� ���
	D3DXMATRIXA16   m_matRevParent; //�θ��� ���� ���

	D3DXMATRIXA16   m_matSChild; //�ڽ��� ������ ���
	D3DXMATRIXA16   m_matTMChild; //�ڽ��� ��ȯ ���
	D3DXMATRIXA16   m_matRChild; //�ڽ��� ȸ�� ���
	D3DXMATRIXA16   m_matRevChild; //�ڽ��� ���� ���
	Sun *m_Sun;
	PlanetManager* m_PM;
	//MatrixManager *MM;
public:
	void Init(HWND hWnd);
	void Revolution();
	void Rotation();
	void SetupCamera();
	void Animate();
	void DrawMesh(D3DXMATRIXA16* pMat);
	void Render();
	void Cleanup();
	HRESULT SolarInitD3D(HWND hWnd);
	HRESULT InitVB();
	HRESULT InitIB();
	HRESULT InitGeometry();
	SolarSystem();
	~SolarSystem();
};