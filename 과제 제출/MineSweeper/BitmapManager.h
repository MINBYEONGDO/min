#pragma once
#include"Mecro.h"
#include"Bitmap.h"
class BitmapManager
{
private:
	Bitmap* m_parrBitmap;
	static BitmapManager* m_hThis;
	int BitmapNumber;
public:
	static BitmapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitmapManager;
		return m_hThis;
	}
	Bitmap* GetImage(int index)
	{
		return &m_parrBitmap[index];
	}
	void Release();
	void Init(HWND hWnd, HDC hdc);
	BitmapManager();
	~BitmapManager();
};

