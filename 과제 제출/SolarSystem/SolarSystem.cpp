
#include "SolarSystem.h"


SolarSystem::SolarSystem()
{
	m_pD3D = NULL;
	m_pd3dDevice = NULL;
	m_pVB = NULL;
	m_pIB = NULL;
}
void SolarSystem::Init(HWND hWnd)
{
	m_Sun = new Sun;
	m_PM = new PlanetManager;
	m_PM->Init();
}

HRESULT SolarSystem::SolarInitD3D(HWND hWnd)
{
	if (NULL == (m_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;
	ZeroMemory(&d3dpp, sizeof(d3dpp));

	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.EnableAutoDepthStencil = TRUE;
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

	if (FAILED(m_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &m_pd3dDevice)))
	{
		return E_FAIL;
	}

	m_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	m_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);

	m_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}


HRESULT SolarSystem::InitVB()
{
	CUSTOMVERTEX vertices[] =
	{
	 {-1, 1, 1, 0xffff0000},
	 { 1, 1, 1, 0xff00ff00},
	 { 1, 1,-1, 0xff0000ff},
	 {-1, 1,-1, 0xffffff00},

	 {-1,-1, 1, 0xffff0000},
	 { 1,-1, 1, 0xffff0000},
	 { 1,-1,-1, 0xffff0000},
	 {-1,-1,-1, 0xffff0000},
	};

	if (FAILED(m_pd3dDevice->CreateVertexBuffer(8 * sizeof(CUSTOMVERTEX), 0, D3DFVF_CUSTOMVERTEX,
		D3DPOOL_DEFAULT, &m_pVB, NULL)))
	{
		return E_FAIL;
	}

	void* pVertices;

	if (FAILED(m_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
		return E_FAIL;

	memcpy(pVertices, vertices, sizeof(vertices));

	m_pVB->Unlock();

	return S_OK;
}

HRESULT SolarSystem::InitIB()
{
	MYINDEX indices[] =
	{
	 {0, 1, 2}, {0, 2, 3},
	 {4, 6, 5}, {4, 7, 6},
	 {0, 3, 7}, {0, 7, 4},
	 {1, 5, 6}, {1, 6, 2},
	 {3, 2, 6}, {3, 6, 7},
	 {0, 4, 5}, {0, 5, 1},
	};

	if (FAILED(m_pd3dDevice->CreateIndexBuffer(12 * sizeof(MYINDEX), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL)))
	{
		return E_FAIL;
	}

	void** pIndices;

	if (FAILED(m_pIB->Lock(0, sizeof(indices), (void**)&pIndices, 0)))
	{
		return E_FAIL;
	}

	memcpy(pIndices, indices, sizeof(indices));

	m_pIB->Unlock();

	return S_OK;
}


HRESULT SolarSystem::InitGeometry()
{
	if (FAILED(InitVB()))
		return E_FAIL;

	if (FAILED(InitIB()))
		return E_FAIL;

	return S_OK;
}
void SolarSystem::SetupCamera()
{
	D3DXMATRIXA16 matWorld;
	D3DXMatrixIdentity(&matWorld);
	m_pd3dDevice->SetTransform(D3DTS_WORLD, &matWorld);

	D3DXVECTOR3 vEyePt(0.0f, 5.0f, -20.0f);
	D3DXVECTOR3 vLookatPt(0.0f, 0.0f, 0.0f);
	D3DXVECTOR3 vUpVec(0.0f, 1.0f, 0.0f);

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &vEyePt, &vLookatPt, &vUpVec);
	m_pd3dDevice->SetTransform(D3DTS_VIEW, &matView);

	D3DXMATRIXA16 matProj;
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4, 1.0f, 1.0f, 500.0f);
	m_pd3dDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}
void SolarSystem::Animate()
{
	m_Sun->Animate();
	m_PM->Animate();
}

void SolarSystem::DrawMesh(D3DXMATRIXA16* pMat)
{
	m_pd3dDevice->SetTransform(D3DTS_WORLD, pMat);
	m_pd3dDevice->SetStreamSource(0, m_pVB, 0, sizeof(CUSTOMVERTEX));
	m_pd3dDevice->SetFVF(D3DFVF_CUSTOMVERTEX);
	m_pd3dDevice->SetIndices(m_pIB);
	m_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

void SolarSystem::Render()
{
	D3DXMATRIXA16 matWorld;//다른 클래스로 가져갈려니 오류가 발생, 가져오는건 괜찮은데 흠

	m_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0);

	Animate();

	if (SUCCEEDED(m_pd3dDevice->BeginScene()))
	{
		matWorld = m_Sun->GetAncR() * m_Sun->GetAncTM();//조상(태양)의 자전

		DrawMesh(&matWorld);
		for (int i = 0; i < m_PM->GetMaxNumber(); i++)
		{
			matWorld = m_PM->Rander(i);
			DrawMesh(&matWorld);
		}//월드 행렬을 PlanetManager클래스로 가져가서 사용이 불가능(가져간 순간  PlanetManager에서 에러 발생)
		//그래서 여기서 반복문을 사용해서 사용
		//DrwMesh도 다른 클래스로 이동하면 


		for (int i = 0; i < m_PM->GetMaxNumber(); i++)
		{
			if (m_PM->GetPlanetExistMoon(i) == true)
			{
				matWorld = m_PM->MoonRander(i)*m_PM->Rander(i);
				DrawMesh(&matWorld);
			}
		}
		m_pd3dDevice->EndScene();
	}

	m_pd3dDevice->Present(NULL, NULL, NULL, NULL);
}
void  SolarSystem::Cleanup()
{
	if (m_pIB != NULL)
		m_pIB->Release();

	if (m_pVB != NULL)
		m_pVB->Release();

	if (m_pd3dDevice != NULL)
		m_pd3dDevice->Release();

	if (m_pD3D != NULL)
		m_pD3D->Release();
}
void SolarSystem::Revolution()
{

}
void SolarSystem::Rotation()
{

}

SolarSystem::~SolarSystem()
{
	delete m_Sun;
	delete m_PM;
}