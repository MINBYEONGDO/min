
#pragma once
#include"Mecro.h"
#include"BitmapManager.h"
class Piece
{
private:
protected:
	Bitmap* m_pBitmap;
	Piece* Next;
	int m_index;//�ʿ��Ѱ�? �Ⱦ��°Ͱ����� ����
	int m_PieceType;
	int m_ix;//���� x��
	int m_iy;//���� y��
	float m_fspX;//ũ������
	float m_fspY;//ũ������
	RECT m_Rect;//��ǥȮ�ο� ���ʱ�
	bool m_bSurvival;//���� ��Ҵ��� �׾����� Ȯ�ο�
	int m_bFirstmove;//���� ó���� �����ϼ� �մ� ��찡 �ϳ��� �ձ⿡
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

public://��Ȯ�� �밢������ ���� 1ĭ ����ĭ�̹Ƿ� �̵��� ĭ�� �� ��ġ�� ���� ��ǥ�� ���� ���� x,y ������ ����
	// �����Ѵ� 1ĭ1ĭ �밢�� �̵��ÿ� �� 75�� ���̳��� ���� ���÷� ��� �մ�.
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
	void Move(Piece tmp, int x, int y, int number, int playernumber)//�� �����̵�
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
			if (y > m_iy + 74 && y <= m_iy + 75 && x == m_ix)//1ĭ�����̵�
			{
				//m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (y < m_iy - 74 && y >= m_iy - 75 && x == m_ix)//1ĭ�����̵�
			{
				//m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x < m_ix - 74 && x >= m_ix - 75 && y == m_iy)//1ĭ�����̵�
			{
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x > m_ix + 74 && x <= m_ix + 75 && y == m_iy)//1ĭ�����̵�
			{
				m_ix = x;
				int  a;
				int b;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x - m_ix == 75 && y - m_iy == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x - m_ix == 75 && (-1)*(y - m_iy) == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == 75 && y - m_iy == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == 75 && (-1)*(y - m_iy) == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == 75 && y - m_iy == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == 75 && (-1)*(y - m_iy) == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == 75 && y - m_iy == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == 75 && (-1)*(y - m_iy) == 75)//1ĭ�밢���̵�
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
			if (y > m_iy + 74 && y <= m_iy + 75 && x == m_ix)//1ĭ�����̵�
			{
				//m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (y < m_iy - 74 && y >= m_iy - 75 && x == m_ix)//1ĭ�����̵�
			{
				//m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x < m_ix - 74 && x >= m_ix - 75 && y == m_iy)//1ĭ�����̵�
			{
				m_ix = x;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x > m_ix + 74 && x <= m_ix + 75 && y == m_iy)//1ĭ�����̵�
			{
				m_ix = x;
				int  a;
				int b;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			if (x - m_ix == 75 && y - m_iy == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			if (x - m_ix == 75 && (-1)*(y - m_iy) == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == 75 && y - m_iy == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x - m_ix) == 75 && (-1)*(y - m_iy) == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == 75 && y - m_iy == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if (x + m_ix == 75 && (-1)*(y - m_iy) == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == 75 && y - m_iy == 75)//1ĭ�밢���̵�
			{
				m_ix = x;
				m_iy = y;
				m_Rect.top = y;
				m_Rect.left = x;
				m_Rect.bottom = y + 75;
				m_Rect.right = x + 75;
			}
			else if ((-1)*(x + m_ix) == 75 && (-1)*(y - m_iy) == 75)//1ĭ�밢���̵�
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