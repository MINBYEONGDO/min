

#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
class Map
{
private:
	Map* Next;
	Bitmap* m_Bitmap;
	Bitmap* m_MineBitmap;
	int m_ix;//x��ǥ��
	int m_iy;//y��ǥ��
	RECT m_rect;
	int m_Number;
	int m_iState;//Ÿ��
	int m_bReverse;
	int m_Number_x;//x��
	int m_Number_y;//y��
	bool m_bMine;
	bool m_bMineSurvival;
	bool m_bFlag;

	float m_fspX;//ũ������
	float m_fspY;//ũ������

public:
	void Init(int Mode,int Number, int Number_y, int Number_x);
	void SetNext(Map* Node);
	void CreateMine(Map tmp, int R_Mine);
	void SettingNomalMap(Map *Node, int yline, int xline, int Number);
	void Draw(HDC hdc, Map Maptmp, int  i, int j);
	bool SearchMap(Map Node, int yline, int xline);//�� �ڸ��� Ž��
	void SearchNear(Map Node, int yline, int xline);//�ֺ� Ž����
	void FlagBitmap();
	void ResetFlag();
	void ReverseBitmap();
	void ReCoverBitmap();
	//int Search_Xline(Map Node, int Number_y, int Number_x);
	inline bool CheckMine(Map *Node, int Number)//���ڻ����� ���
	{
		Map* tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_Number == Number)
			{
				if (tmp->m_bMine == true)//���ڸ�
					return false; //�̹� ������
				else if (tmp->m_bMine == false)//���ڰ� �ƴϸ�
					return true;// ���ڷ� ��������
			}
			tmp = tmp->Next;
		}
	}
	inline bool CheckConfirmMine(Map *Node, int Number_y, int Number_x)
	{//Ŭ���� ��ǥ�� �������� �ƴ��� Ȯ��
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				if (Mtmp->m_bMine == true)//���ڸ�
					return false; //���� �����̱⶧����  false
				else if (Mtmp->m_bMine == false)//���ڰ� �ƴϸ�
					return true;// ���� ������ �����ϹǷ� true
			}
			Mtmp = Mtmp->Next;
		}
	}
	inline Map* GetMap(Map *Node, int Number_y, int Number_x)
	{
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				break;
			}
			Mtmp = Mtmp->Next;
		}
		return Mtmp;
	}
	inline bool GetFlag(Map *Node, int Number_y, int Number_x)
	{
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				break;
			}
			Mtmp = Mtmp->Next;
		}
		return Mtmp->m_bFlag;
	}
	inline int GetState(Map *Node, int Number_y, int Number_x)
	{
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				break;
			}
			Mtmp = Mtmp->Next;
		}
		return Mtmp->m_iState;
	}
	inline int GetReverse(Map *Node, int Number_y, int Number_x)
	{
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				break;
			}
			Mtmp = Mtmp->Next;
		}
		return Mtmp->m_bReverse;
	}
	inline int GetX_Line(Map *Node, int Number_y, int Number_x)
	{
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				break;
			}
			Mtmp = Mtmp->Next;
		}
		return Mtmp->m_Number_x;
	}
	inline int GetY_Line(Map *Node, int Number_y, int Number_x)
	{
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				break;
			}
			Mtmp = Mtmp->Next;
		}
		return Mtmp->m_Number_y;
	}

	inline RECT GetRect(Map *Node, int Number_y, int Number_x)
	{
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				break;
			}
			Mtmp = Mtmp->Next;
		}
		return Mtmp->m_rect;
	}


	inline int GetX(Map *Node, int Number_y, int Number_x)
	{
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				break;
			}
			Mtmp = Mtmp->Next;
		}
		return Mtmp->m_ix;
	}
	inline int GetY(Map *Node, int Number_y, int Number_x)
	{
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				break;
			}
			Mtmp = Mtmp->Next;
		}
		return Mtmp->m_iy;
	}

	inline bool GetMine()
	{
		return m_bMine;
	}
	inline int GetNumber()
	{
		return m_Number;
	}
	inline int GetLine_X()
	{
		return m_Number_x;
	}
	inline int GetLine_Y()
	{
		return m_Number_y;
	}

	void Release(Map* Node);
	Map();
	~Map();
};
