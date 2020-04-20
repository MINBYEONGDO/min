

#include <d3d9.h>
#include <d3dx9.h>
#include "SolarSystem.h"

SolarSystem static g_SSystem;

LRESULT WINAPI MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_DESTROY:
		g_SSystem.Cleanup();
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR, INT)
{
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, MsgProc,
	 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL,
	 TEXT("D3D Hierarchy"), NULL };

	RegisterClassEx(&wc);

	HWND hWnd = CreateWindow(TEXT("D3D Hierarchy"), TEXT("D3D Hierarchy"), WS_OVERLAPPEDWINDOW,
		100, 100, 500, 500, GetDesktopWindow(), NULL, wc.hInstance, NULL);
	g_SSystem.Init(hWnd);
	if (SUCCEEDED(g_SSystem.SolarInitD3D(hWnd)))
	{
		if (SUCCEEDED(g_SSystem.InitGeometry()))
		{
			g_SSystem.SetupCamera();

			ShowWindow(hWnd, SW_SHOWDEFAULT);
			UpdateWindow(hWnd);

			MSG msg;
			ZeroMemory(&msg, sizeof(msg));

			while (msg.message != WM_QUIT)
			{
				if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
				{
					TranslateMessage(&msg);
					DispatchMessage(&msg);
				}
				else
				{
					g_SSystem.Render();
				}
			}
		}
	}

	UnregisterClass(TEXT("D3D Hierarchy"), wc.hInstance);
	return 0;
}