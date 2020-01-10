
#pragma once
#include"Mecro.h"
#include "BitmapManager.h"
class obstacle
{
private:
protected:
	float m_ix;
	float m_iy;
	int m_iNumber;
	int m_itype;
	bool m_bMove;
	bool m_blive;
	bool m_bimageChange;
	bool m_bScore;
	Bitmap *BitmapList[8];

public:
	virtual void SetBitmap(int index);
	virtual void SetData(int Number, int type);
	void CheckifMove(int Move);
	void ChangeScoreGive();
	void Draw(HDC hdc, HDC MemDC, int Number, int Move, int imageNumber);
	float inline Getx()
	{
		return m_ix;
	}
	float inline Gety()
	{
		return m_iy;
	}
	bool inline GetScroeGive()
	{
		return m_bScore;
	}
	obstacle();
	~obstacle();
};

class Ring : public obstacle
{
private:
	RECT m_Rect;
public:
	Ring()
	{
	}
	void SetData(int Number, int type)
	{
		m_ix = 250 + Number * 250;
		m_iy = 460;
		m_iNumber = Number;
		m_itype = RING;
		m_bMove = false;
		m_blive = false;
		m_bimageChange = false;
		m_bScore = true;
		m_Rect.bottom = m_iy + 128;//面倒 康开
		m_Rect.left = m_ix + 29;//面倒 康开
		m_Rect.right = m_ix + 31;//面倒 康开
		m_Rect.top = m_iy + 126;//面倒 康开

	}
	void MoveRect(float Move)
	{
		m_Rect.left = m_ix + 29 - Move;
		m_Rect.right = m_ix + 31 - Move;
	}
	void UpdateRect(float Move)
	{
		m_Rect.left -= Move;
		m_Rect.right -= Move;
	}
	void SetBitmap(int index)
	{
		for (int i = 0; i < 8; i++)
			BitmapList[i] = BitmapManager::GetInstance()->GetImage(index + i);
	}
	RECT inline GetRect()
	{
		return m_Rect;
	}
	int inline Getx()
	{
		return m_ix;
	}
	int inline Gety()
	{
		return m_iy;
	}
	int inline GetRectRight()
	{
		return m_Rect.right;
	}
	~Ring()
	{}
};

class Front : public obstacle
{
private:
	RECT m_Rect1;
	RECT m_Rect2;
public:
	Front()
	{
	}
	void SetData(int Number, int type)
	{
		m_ix = 450 + Number * 500;
		m_iy = 595;
		m_iNumber = Number;
		m_bMove = false;
		m_blive = false;
		m_itype = FRONT;
		m_bimageChange = false;
		m_bScore = true;

		m_Rect1.bottom = m_iy + 25;//面倒 康开
		m_Rect1.left = m_ix + 15;//面倒 康开
		m_Rect1.right = m_ix + 31;//面倒 康开
		m_Rect1.top = m_iy + 10;//面倒 康开

		m_Rect2.bottom = m_iy + 50;//面倒 康开
		m_Rect2.left = m_ix + 10;//面倒 康开
		m_Rect2.right = m_ix + 40;//面倒 康开
		m_Rect2.top = m_iy + 25;//面倒 康开
	}
	void UpdateRect(float Move)
	{
		m_Rect1.left -= Move;
		m_Rect1.right -= Move;

		m_Rect2.left -= Move;
		m_Rect2.right -= Move;
	}
	void MoveRect(float Move)
	{
		m_Rect1.left = m_ix + 25 - Move;
		m_Rect1.right = m_ix + 31 - Move;

		m_Rect2.left = m_ix - Move;
		m_Rect2.right = m_ix + 50 - Move;
	}
	void SetBitmap(int index)
	{
		for (int i = 0; i < 2; i++)
			BitmapList[i] = BitmapManager::GetInstance()->GetImage(index + i);
	}
	RECT inline GetRect1()
	{
		return m_Rect1;
	}
	RECT inline GetRect2()
	{
		return m_Rect2;
	}
	int inline GetRectRight1()
	{
		return m_Rect1.right;
	}
	int inline GetRectRight2()
	{
		return m_Rect2.right;
	}
	int inline Getx()
	{
		return m_ix;
	}
	int inline Gety()
	{
		return m_iy;
	}
	~Front()
	{}
};

class Money : public obstacle
{
private:
	RECT m_Rect;//面倒 康开
public:
	Money()
	{
	}
	void SetData(int Number, int type)
	{
		m_ix = 260 + Number * 250;
		m_iy = 480;//455;
		m_iNumber = Number;
		m_itype = MONEY;
		m_bMove = false;
		m_blive = true;
		m_bimageChange = false;
		m_bScore = true;
		m_Rect.bottom = m_iy + 30;//面倒 康开
		m_Rect.left = m_ix;//面倒 康开
		m_Rect.right = m_ix + 30;//面倒 康开
		m_Rect.top = m_iy;//面倒 康开
	}
	void ChangeState()
	{
		if (m_blive == true)
			m_blive = false;
		else if (m_blive == false)
			m_blive = true;
	}
	void MoveRect(float Move)
	{
		m_Rect.left = m_ix - Move;
		m_Rect.right = m_ix+30- Move;
	}
	void UpdateRect(int Move)
	{
		m_Rect.bottom;
		m_Rect.left -= Move;
		m_Rect.right -= Move;
		m_Rect.top;
	}
	void SetBitmap(float index)
	{
		BitmapList[0] = BitmapManager::GetInstance()->GetImage(index);
	}
	RECT inline GetRect()
	{
		return m_Rect;
	}
	bool inline CheckLive()
	{
		return m_blive;
	}
	int inline GetNumber()
	{
		return m_iNumber;
	}
	~Money()
	{}
};
class End : public obstacle
{
private:
	RECT m_Rect;//面倒 康开
public:
	End()
	{
	}
	void SetData(int Number, int type)
	{
		m_ix = 5000;
		m_iy = 600;
		m_iNumber = Number;
		m_itype = RING;
		m_bMove = false;
		m_blive = false;
		m_bimageChange = false;
		m_bScore = true;
		m_Rect.bottom = 600 + 49;//面倒 康开
		m_Rect.left = 5000;//面倒 康开
		m_Rect.right = 5000 + 76;//面倒 康开
		m_Rect.top = 600;//面倒 康开
	}
	void UpdateRect(int Move)
	{
		m_Rect.bottom;
		m_Rect.left -= Move;
		m_Rect.right -= Move;
		m_Rect.top;
	}
	void SetBitmap(float index)
	{
		BitmapList[0] = BitmapManager::GetInstance()->GetImage(index);
	}
	RECT inline GetRect()
	{
		return m_Rect;
	}
	~End()
	{}
};