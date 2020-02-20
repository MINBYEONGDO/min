
#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
class Map
{
private:
	int m_ix;
	int m_iy;
	int m_MapNumber;
	RECT m_Rect;
	int m_MapType;
	Bitmap* m_Bitmap;
	bool m_bIce;
	bool m_bExist;//�����ϴ���
	bool m_bBreak;//�ν�������?�ν�������
	bool m_bContectMissile;//�̽��ϰ� �浹�ϴ� ������� ����
	bool m_bContect;//����
	bool m_End;
public:
	void Init(int xline, int yline);
	void FileDataLoad(int MapData);
	void BreakBlock(int Direciton, int tank);
	void DrawMap(HDC hdc);
	inline int GetX()
	{
		return m_ix;
	}
	inline int GetY()
	{
		return m_iy;
	}
	inline RECT GetRect()
	{
		return m_Rect;
	}
	inline bool GetExistBlock()
	{
		return m_bExist;
	}
	inline int GetMapType()
	{
		return m_MapType;
	}
	inline bool GetBreakBlock()
	{
		return m_bBreak;
	}
	inline bool GetContect()
	{
		return m_bContect;
	}
	inline bool GetIce()
	{
		return m_bIce;
	}
	inline bool GetContectMissile()
	{
		return m_bContectMissile;
	}
	bool GetEnd()
	{
		return m_End;
	}
	Map();
	~Map();
};