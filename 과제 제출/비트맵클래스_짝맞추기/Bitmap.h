
#pragma once
#include<Windows.h>
enum Card
{
	DOG,
	TIGER,
	DUCK,
	ELEPHAT,
	COW,
	HORSE,
	CAT,
	MONKEY,
	FLOG,
	CHICKEN,
	BACKCARD,
};
class Bitmap
{
private:
	HDC  MemDC;
	HBITMAP m_pMyBitMap;
	HBITMAP m_pOldBitMap;
	SIZE m_size;
	int m_CardNumber;//ī�� �ѹ���
	int m_CardType;// ���� ī�� ����
	bool m_bCardState;//���߾��°� �ƴѰ��� ���ؼ�
	bool m_bCardBack;//�ո� �޸�
protected:
public:
	Bitmap();
	Bitmap(HDC hdc, HINSTANCE hInst, int CardType);

	void Init(HDC hdc, HINSTANCE hInst);
	void Draw(HDC hdc, int x, int y, bool k, int spX = 1, int spY = 1);
	void ReverseCard();
	void CardStateChange();
	void SetCardNumber(int Number);
	void ResetCard();
	inline int GetNumber()
	{
		return m_CardNumber;
	}
	inline int GetCardType()
	{
		return m_CardType;
	}
	inline bool GetState()
	{
		return m_bCardState;
	}
	inline bool GetBack()
	{
		return m_bCardBack;
	}
	~Bitmap();
};