
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

	D3DXMATRIXA16   m_matTMAncestor; //조상의 변환 행렬
	D3DXMATRIXA16   m_matRAncestor; //조상의 회전 행렬

	D3DXMATRIXA16   m_matTMParent; //부모의 변환 행렬
	D3DXMATRIXA16   m_matRParent; //부모의 회전 행렬
	D3DXMATRIXA16   m_matRevParent; //부모의 공전 행렬

	D3DXMATRIXA16   m_matSChild; //자식의 스케일 행렬
	D3DXMATRIXA16   m_matTMChild; //자식의 변환 행렬
	D3DXMATRIXA16   m_matRChild; //자식의 회전 행렬
	D3DXMATRIXA16   m_matRevChild; //자식의 공전 행렬
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