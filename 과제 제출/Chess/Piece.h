
#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
class Piece
{
private:
protected:
	Bitmap* m_pBitmap;
	Piece* Next;
	int m_index;//필요한가? 안쓰는것같은데 순서
	int m_PieceType;
	int m_ix;//시작 x값
	int m_iy;//시작 y값
	float m_fspX;//크기조절
	float m_fspY;//크기조절
	RECT m_Rect;//좌표확인용 랭탱글
	bool m_bSurvival;//말이 살았는지 죽었는지 확인용
	int m_bFirstmove;//폰이 처음에 움직일수 잇는 경우가 하나더 잇기에
public:
	void Init(Piece *m_Piecetmp, int playernumber, int Number, int x, int y, float spX, float spY);
	void PawnPromotion(Piece *Node, int playerteamNumber, int x, int y, int number, int Number);
	void Draw(HDC hdc, Piece tmp, int number);
	void SetNext(Piece* Node);
	virtual void Move(Piece tmp, int x, int y, int number, int playernumber);
	void MoveManager(Piece *Node, int playernumber, int x, int y, int number);
	void PieceDeath(Piece *Node, int x, int y, int number);
	void Release(Piece *Node);
	inline Piece* GetPieceNext(Piece *Node, int number)
	{
		Piece *Ptmp;
		Ptmp = NULL;
		Ptmp = Node;
		while (Ptmp != NULL)
		{
			if (Ptmp->m_index == number)
			{
				break;
			}
			Ptmp = Ptmp->Next;
		}
		return Ptmp;
	}
	inline RECT GetRect(Piece *Node, int number)
	{
		Piece *Ptmp;
		Ptmp = NULL;
		Ptmp = Node;
		while (Ptmp != NULL)
		{
			if (Ptmp->m_index == number)
			{
				break;
			}
			Ptmp = Ptmp->Next;
		}
		return Ptmp->m_Rect;
	}
	inline int GetPiece_x(Piece *Node, int number)
	{
		Piece *Ptmp;
		Ptmp = NULL;
		Ptmp = Node;
		while (Ptmp != NULL)
		{
			if (Ptmp->m_index == number)
			{
				break;
			}
			Ptmp = Ptmp->Next;
		}
		return Ptmp->m_ix;
	}
	inline int GetPiece_y(Piece *Node, int number)
	{
		Piece *Ptmp;
		Ptmp = NULL;
		Ptmp = Node;
		while (Ptmp != NULL)
		{
			if (Ptmp->m_index == number)
			{
				break;
			}
			Ptmp = Ptmp->Next;
		}
		return Ptmp->m_iy;
	}
	inline int GetNumber(Piece Node, int number)
	{
		return m_index;
	}
	inline int GetPieceType(Piece *Node, int number)
	{
		Piece *Ptmp;
		Ptmp = NULL;
		Ptmp = Node;
		while (Ptmp != NULL)
		{
			if (Ptmp->m_index == number)
			{
				break;
			}
			Ptmp = Ptmp->Next;
		}
		return Ptmp->m_PieceType;
	}
	inline int GetPieceFirstMove(Piece *Node, int number)
	{
		Piece *Ptmp;
		Ptmp = NULL;
		Ptmp = Node;
		while (Ptmp != NULL)
		{
			if (Ptmp->m_index == number)
			{
				break;
			}
			Ptmp = Ptmp->Next;
		}
		return Ptmp->m_bFirstmove;
	}
	inline bool GetSurvival(Piece *Node, int number)
	{
		Piece *Ptmp;
		Ptmp = NULL;
		Ptmp = Node;
		while (Ptmp != NULL)
		{
			if (Ptmp->m_index == number)
			{
				break;
			}
			Ptmp = Ptmp->Next;
		}
		return Ptmp->m_bSurvival;
	}
	Piece();
	~Piece();

};

class Rook : public Piece
{
private:

protected:

public:
	void Move(Piece tmp, int x, int y, int number, int playernumber)
	{
		if (playernumber == 0)
		{
			if (m_ix != x && m_iy == y)
			{
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (m_iy != y && m_ix == x)
			{
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
		}
		else if (playernumber == 1)
		{
			if (m_ix != x && m_iy == y)
			{
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (m_iy != y && m_ix == x)
			{
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
		}
	}
	Rook()
	{}
	Rook(Rook *i)
	{
		m_ix = i->m_ix;
		m_iy = i->m_iy;
		m_fspX = i->m_fspX;
		m_fspY = i->m_fspY;
		m_Rect = { i->m_ix,i->m_iy,i->m_ix + 75,i->m_iy + 75 };
		m_index = i->m_index;
		Next = i->Next;
		m_bFirstmove = 1;
		m_PieceType = ROOK;
		m_bSurvival = true;
	}
	Rook(int Number, int x, int y, float spX, float  spY)
	{
		m_ix = x;
		m_iy = y;
		m_fspX = spX;
		m_fspY = spY;
		m_Rect = { x,y,x + 75,y + 75 };
		m_index = Number;
		m_bFirstmove = 0;
		m_PieceType = ROOK;
		m_bSurvival = true;
	}
	~Rook()
	{}
};


class Knight : public Piece
{
private:

protected:

public:
	void Move(Piece tmp, int x, int y, int number, int playernumber)
	{
		if (playernumber == 0)
		{
			if (m_iy + 75 < y&& m_iy + 151 > y)
			{
				if (m_ix - 75 == x)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
				else if (m_ix + 75 == x)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}

			}
			else if (m_iy - 75 > y&& m_iy - 151 < y)
			{
				if (m_ix - 75 == x)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
				else if (m_ix + 75 == x)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
			}
			else if (m_ix + 75 < x&& m_ix + 151 > x)
			{
				if (m_iy - 75 == y)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
				else if (m_iy + 75 == y)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
			}
			else if (m_ix - 75 > x&& m_ix - 151 < x)
			{
				if (m_iy - 75 == y)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
				else if (m_iy + 75 == y)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
			}
		}
		else if (playernumber == 1)
		{
			if (m_iy + 75 < y&& m_iy + 151 > y)
			{
				if (m_ix - 75 == x)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
				else if (m_ix + 75 == x)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}

			}
			else if (m_iy - 75 > y&& m_iy - 151 < y)
			{
				if (m_ix - 75 == x)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
				else if (m_ix + 75 == x)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
			}
			else if (m_ix + 75 < x&& m_ix + 151 > x)
			{
				if (m_iy - 75 == y)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
				else if (m_iy + 75 == y)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
			}
			else if (m_ix - 75 > x&& m_ix - 151 < x)
			{
				if (m_iy - 75 == y)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
				else if (m_iy + 75 == y)
				{
					m_iy = y;
					m_ix = x;
					m_Rect.top = y;
					m_Rect.left = x;
					m_Rect.bottom = y + 75;
					m_Rect.right = x + 75;
				}
			}
		}
		m_bFirstmove = 1;
	}
	Knight()
	{}
	Knight(Knight *i)
	{
		m_ix = i->m_ix;
		m_iy = i->m_iy;
		m_fspX = i->m_fspX;
		m_fspY = i->m_fspY;
		m_Rect = { i->m_ix,i->m_iy,i->m_ix + 75,i->m_iy + 75 };
		m_index = i->m_index;
		Next = i->Next;
		m_bFirstmove = 1;
		m_PieceType = KNIGHT;
		m_bSurvival = true;
	}
	Knight(int Number, int x, int y, float spX, float  spY)
	{
		m_ix = x;
		m_iy = y;
		m_fspX = spX;
		m_fspY = spY;
		m_Rect = { x,y,x + 75,y + 75 };
		m_index = Number;
		m_PieceType = KNIGHT;
		m_bFirstmove = 0;
		m_bSurvival = true;
	}
	~Knight()
	{}
};

class Bishop : public Piece
{
private:

protected:

public://정확한 대각선으로 가로 1칸 세로칸이므로 이동할 칸과 현 위치의 말의 좌표의 값을 빼면 x,y 각각의 차가
	// 동일한다 1칸1칸 대각선 이동시에 각 75가 차이나는 것을 예시로 들수 잇다.
	void Move(Piece tmp, int x, int y, int number, int playernumber)
	{
		if (playernumber == 0)
		{
			if (x - m_ix == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
		}
		else if (playernumber == 1)
		{
			if (x - m_ix == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
		}
		m_bFirstmove = 1;
	}
	Bishop()
	{}
	Bishop(Bishop *i)
	{
		m_ix = i->m_ix;
		m_iy = i->m_iy;
		m_fspX = i->m_fspX;
		m_fspY = i->m_fspY;
		m_Rect = { i->m_ix,i->m_iy,i->m_ix + 75,i->m_iy + 75 };
		m_index = i->m_index;
		Next = i->Next;
		m_bFirstmove = 1;
		m_PieceType = BISHOP;
		m_bSurvival = true;
	}
	Bishop(int Number, int x, int y, float spX, float  spY)
	{
		m_ix = x;
		m_iy = y;
		m_fspX = spX;
		m_fspY = spY;
		m_Rect = { x,y,x + 75,y + 75 };
		m_index = Number;
		m_PieceType = BISHOP;
		m_bFirstmove = 0;
		m_bSurvival = true;
	}
	~Bishop()
	{}
};

class Queen : public Piece
{
private:

protected:

public:
	void Move(Piece tmp, int x, int y, int number, int playernumber)//퀸 직선이동
	{
		if (playernumber == 0)
		{
			if (m_ix != x && m_iy == y)
			{
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (m_iy != y && m_ix == x)
			{
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x - m_ix == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
		}
		else if (playernumber == 1)
		{
			if (m_ix != x && m_iy == y)
			{
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (m_iy != y && m_ix == x)
			{
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x - m_ix == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == y - m_iy)
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
		}
		m_bFirstmove = 1;
	}
	Queen()
	{}
	Queen(Queen *i)
	{
		m_ix = i->m_ix;
		m_iy = i->m_iy;
		m_fspX = i->m_fspX;
		m_fspY = i->m_fspY;
		m_Rect = { i->m_ix,i->m_iy,i->m_ix + 75,i->m_iy + 75 };
		m_index = i->m_index;
		Next = i->Next;
		m_bFirstmove = 1;
		m_PieceType = QUEEN;
		m_bSurvival = true;
	}
	Queen(int Number, int x, int y, float spX, float  spY)
	{
		m_ix = x;
		m_iy = y;
		m_fspX = spX;
		m_fspY = spY;
		m_Rect = { x,y,x + 75,y + 75 };
		m_index = Number;
		m_PieceType = QUEEN;
		m_bFirstmove = 0;
		m_bSurvival = true;
	}
	~Queen()
	{}
};

class King : public Piece
{
private:

protected:

public:
	void Move(Piece tmp, int x, int y, int number, int playernumber)
	{
		if (playernumber == 0)
		{
			if (y > m_iy + 74 && y <= m_iy + 75 && x == m_ix)//1칸세로이동
			{
				//m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (y < m_iy - 74 && y >= m_iy - 75 && x == m_ix)//1칸세로이동
			{
				//m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x < m_ix - 74 && x >= m_ix - 75 && y == m_iy)//1칸가로이동
			{
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x > m_ix + 74 && x <= m_ix + 75 && y == m_iy)//1칸가로이동
			{
				m_ix = x;
				int  a;
				int b;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x - m_ix == 75 && y - m_iy == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x - m_ix == 75 && (-1)*(y - m_iy) == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == 75 && y - m_iy == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == 75 && (-1)*(y - m_iy) == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == 75 && y - m_iy == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == 75 && (-1)*(y - m_iy) == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == 75 && y - m_iy == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == 75 && (-1)*(y - m_iy) == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
		}
		else if (playernumber == 1)
		{
			if (y > m_iy + 74 && y <= m_iy + 75 && x == m_ix)//1칸세로이동
			{
				//m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (y < m_iy - 74 && y >= m_iy - 75 && x == m_ix)//1칸세로이동
			{
				//m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x < m_ix - 74 && x >= m_ix - 75 && y == m_iy)//1칸가로이동
			{
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x > m_ix + 74 && x <= m_ix + 75 && y == m_iy)//1칸가로이동
			{
				m_ix = x;
				int  a;
				int b;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			if (x - m_ix == 75 && y - m_iy == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			if (x - m_ix == 75 && (-1)*(y - m_iy) == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == 75 && y - m_iy == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == 75 && (-1)*(y - m_iy) == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == 75 && y - m_iy == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == 75 && (-1)*(y - m_iy) == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == 75 && y - m_iy == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == 75 && (-1)*(y - m_iy) == 75)//1칸대각선이동
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;

			}
		}
		m_bFirstmove = 1;
	}
	King()
	{}
	King(int Number, int x, int y, float spX, float  spY)
	{
		m_ix = x;
		m_iy = y;
		m_fspX = spX;
		m_fspY = spY;
		m_Rect = { x,y,x + 75,y + 75 };
		m_index = Number;
		m_PieceType = KING;
		m_bFirstmove = 0;
		m_bSurvival = true;
	}
	~King()
	{}
};

class Pawn : public Piece
{
private:
protected:

public:
	void Move(Piece tmp, int x, int y, int number, int playernumber)
	{
		if (playernumber == 0)
		{
			if ((y > m_iy + 74 && y <= m_iy + 75) && (x - 74 < m_ix || x + 75 > m_ix))
			{
				m_iy = y;
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
				m_bFirstmove = 1;
			}
			else if (y > m_iy + 74 && y <= m_iy + 150 && x == m_ix && m_bFirstmove == 0)
			{
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
				m_bFirstmove = 1;
			}
			else if (y > m_iy + 74 && y <= m_iy + 75 && x == m_ix)
			{
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
				m_bFirstmove = 1;
			}
		}
		else if (playernumber == 1)
		{
			if ((y < m_iy - 74 && y >= m_iy - 75) && (x - 74 < m_ix || x + 75 > m_ix))
			{
				m_iy = y;
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
				m_bFirstmove = 1;
			}
			else if (y < m_iy - 74 && y >= m_iy - 150 && x == m_ix && m_bFirstmove == 0)
			{
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
				m_bFirstmove = 1;
			}
			else if (y < m_iy - 74 && y >= m_iy - 75 && x == m_ix)
			{
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
				m_bFirstmove = 1;
			}
		}
	}
	Pawn()
	{}
	Pawn(int Number, int x, int y, float spX, float  spY)
	{
		m_ix = x;
		m_iy = y;
		m_fspX = spX;
		m_fspY = spY;
		m_Rect = { x,y,x + 75,y + 75 };
		m_index = Number;
		m_PieceType = PAWN;
		m_bFirstmove = 0;
		m_bSurvival = true;
	}
	~Pawn()
	{}
};