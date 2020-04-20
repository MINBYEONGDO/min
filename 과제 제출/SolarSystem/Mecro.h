#pragma once
#include<Windows.h>
#include<string>
#include<vector>
#include <d3d9.h>
#include <d3dx9.h>
using namespace std;

#define D3DFVF_CUSTOMVERTEX (D3DFVF_XYZ | D3DFVF_DIFFUSE)

struct CUSTOMVERTEX
{
	FLOAT x, y, z;
	DWORD color;
};

struct MYINDEX
{
	WORD _0, _1, _2;
};
