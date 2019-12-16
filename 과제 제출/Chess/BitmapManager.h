
#pragma once
#include"Mecro.h"
#include"Bitmap.h"

class BitmapManager
{
private:
	Bitmap* m_parrBitMap;
	static BitmapManager* m_hThis;
	int bitmapnumber;
public:
	static BitmapManager* GetInstance()
	{
		if (m_hThis == NULL)
			m_hThis = new BitmapManager;
		return m_hThis;
	}
	Bitmap* GetImage(int index)
	{
		return &m_parrBitMap[index];
	}
	void Release();
	void Init(HWND hWnd);
	BitmapManager();
	~BitmapManager();
};