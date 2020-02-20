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
	void Init(int x, int y, int index);
	void Draw(HDC hdc);
	Interface();
	~Interface();
};

