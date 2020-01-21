#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
class Interface
{
private:
	int m_ix;
	int m_iy;
	Bitmap* m_Bitmap;
public:
	void Draw(HDC hdc, int Mode);
	Interface();
	~Interface();
};

