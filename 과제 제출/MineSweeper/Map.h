

#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
class Map
{
private:
	Map* Next;
	Bitmap* m_Bitmap;
	Bitmap* m_MineBitmap;
	int m_ix;//x좌표값
	int m_iy;//y좌표값
	RECT m_rect;
	int m_Number;
	int m_iState;//타입
	int m_bReverse;
	int m_Number_x;//x열
	int m_Number_y;//y열
	bool m_bMine;
	bool m_bMineSurvival;
	bool m_bFlag;

	float m_fspX;//크기조절
	float m_fspY;//크기조절

public:
	void Init(int Mode,int Number, int Number_y, int Number_x);
	void SetNext(Map* Node);
	void CreateMine(Map tmp, int R_Mine);
	void SettingNomalMap(Map *Node, int yline, int xline, int Number);
	void Draw(HDC hdc, Map Maptmp, int  i, int j);
	bool SearchMap(Map Node, int yline, int xline);//한 자리만 탐색
	void SearchNear(Map Node, int yline, int xline);//주변 탐색만
	void FlagBitmap();
	void ResetFlag();
	void ReverseBitmap();
	void ReCoverBitmap();
	//int Search_Xline(Map Node, int Number_y, int Number_x);
	inline bool CheckMine(Map *Node, int Number)//지뢰생성시 사용
	{
		Map* tmp = NULL;
		tmp = Node;
		while (tmp != NULL)
		{
			if (tmp->m_Number == Number)
			{
				if (tmp->m_bMine == true)//지뢰면
					return false; //이미 생성함
				else if (tmp->m_bMine == false)//지뢰가 아니면
					return true;// 지뢰로 생성가능
			}
			tmp = tmp->Next;
		}
	}
	inline bool CheckConfirmMine(Map *Node, int Number_y, int Number_x)
	{//클릭한 좌표가 지뢰인지 아닌지 확인
		Map *Mtmp;
		Mtmp = NULL;
		Mtmp = Node;
		while (Mtmp != NULL)
		{
			if (Mtmp->m_Number_x == Number_x && Mtmp->m_Number_y == Number_y)
			{
				if (Mtmp->m_bMine == true)//지뢰면
					return false; //게임 오버이기때문에  false
				else if (Mtmp->m_bMine == false)//지뢰가 아니면
					return true;// 게임 진행이 가능하므로 true
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
