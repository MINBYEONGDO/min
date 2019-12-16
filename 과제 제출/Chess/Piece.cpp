
#include "Piece.h"



Piece::Piece()
{
	Next = NULL;
}
void Piece::Init(Piece *m_Piecetmp, int PlayerNumber, int Number, int x, int y, float spX, float spY)
{//비트맵 입히기
	if (PlayerNumber == 0)
	{
		if (Number == 0)//ROOK
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(3);
		}
		else if (Number == 1)//KNIGHT
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(1);
		}
		else if (Number == 2)//BISHOP
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(2);
		}
		else if (Number == 3)//QUEEN
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(5);
		}
		else if (Number == 4)//KING
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(4);
		}
		else if (Number == 5)//BISHOP
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(2);
		}
		else if (Number == 6)//KNIGHT
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(1);
		}
		else if (Number == 7)//ROOK
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(3);
		}
		else//PAWN
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(0);
		}
	}
	if (PlayerNumber == 1)
	{
		if (Number == 0)//ROOK
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(9);
		}
		else if (Number == 1)//KNIGHT
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(7);
		}
		else if (Number == 2)//BISHOP
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(8);
		}
		else if (Number == 3)//QUEEN
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(11);
		}
		else if (Number == 4)//KING
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(10);
		}
		else if (Number == 5)//BISHOP
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(8);
		}
		else if (Number == 6)//KNIGHT
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(7);
		}
		else if (Number == 7)//ROOK
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(9);
		}
		else//PAWN
		{
			m_Piecetmp->m_pBitmap = BitmapManager::GetInstance()->GetImage(6);
		}
	}
}

void Piece::PawnPromotion(Piece *Node, int playerteamNumber, int x, int y, int number, int Number)
{
	Piece *piecetmp;
	if (Node->GetNumber(*Node, number) == number)
	{
		if (Number == 1)
		{
			piecetmp = Next;
			Next = (new Rook((Rook*)Node));
			if (playerteamNumber == 0)
				Next->m_pBitmap = BitmapManager::GetInstance()->GetImage(3);
			else if (playerteamNumber == 1)
				Next->m_pBitmap = BitmapManager::GetInstance()->GetImage(9);
			delete piecetmp;
		}
		else if (Number == 2)
		{
			piecetmp = Next;
			Next = (new Knight((Knight*)Node));
			if (playerteamNumber == 0)
				Next->m_pBitmap = BitmapManager::GetInstance()->GetImage(1);
			else if (playerteamNumber == 1)
				Next->m_pBitmap = BitmapManager::GetInstance()->GetImage(7);
			delete piecetmp;
		}
		else if (Number == 3)
		{
			piecetmp = Next;
			Next = (new Bishop((Bishop*)Node));
			if (playerteamNumber == 0)
				Next->m_pBitmap = BitmapManager::GetInstance()->GetImage(2);
			else if (playerteamNumber == 1)
				Next->m_pBitmap = BitmapManager::GetInstance()->GetImage(8);
			delete piecetmp;
		}
		else if (Number == 4)
		{
			piecetmp = Next;
			Next = (new Queen((Queen*)Node));
			Next->m_PieceType = QUEEN;
			if (playerteamNumber == 0)
				Next->m_pBitmap = BitmapManager::GetInstance()->GetImage(5);
			else if (playerteamNumber == 1)
				Next->m_pBitmap = BitmapManager::GetInstance()->GetImage(11);
			delete piecetmp;
		}
	}
	else
	{
		if (Node->Next->GetNumber(*Node, number) == number)
		{
			piecetmp = Node->Next;
			Node->PawnPromotion(piecetmp, playerteamNumber, x, y, number, Number);
		}
		else
		{
			piecetmp = Node->Next;
			Node->Next->PawnPromotion(piecetmp, playerteamNumber, x, y, number, Number);
		}
	}
}

void Piece::Draw(HDC hdc, Piece tmp, int number)
{
	Piece *piecetmp;
	if (tmp.GetNumber(tmp, number) == number)
		tmp.m_pBitmap->PieceDraw(hdc, m_ix, m_iy, m_fspX, m_fspY);
	else
	{
		piecetmp = tmp.Next;
		tmp.Next->Draw(hdc, *piecetmp, number);
	}

}

void Piece::Move(Piece tmp, int x, int y, int number, int playernumber)
{
	Piece *piecetmp;
	if (tmp.GetNumber(tmp, number) == number)
	{
		m_ix = x;
		m_iy = y;
		m_Rect.top = y;
		m_Rect.left = x;
		m_Rect.bottom = y + 75;
		m_Rect.right = x + 75;
	}
	else
	{
		piecetmp = tmp.Next;
		tmp.Next->Move(*piecetmp, x, y, number, playernumber);
	}

}

void Piece::MoveManager(Piece *tmp, int playernumber, int x, int y, int number)
{
	Piece *piecetmp;
	if (tmp->GetNumber(*tmp, number) == number)
	{
		tmp->Move(*tmp, x, y, number, playernumber);
	}
	else
	{
		piecetmp = tmp->Next;
		tmp->Next->MoveManager(piecetmp, playernumber, x, y, number);
	}
}

void Piece::PieceDeath(Piece *Node, int x, int y, int number)
{
	Piece *piecetmp;
	if (Node->GetNumber(*Node, number) == number)
	{
		m_bSurvival = false;
	}
	else
	{
		piecetmp = Node->Next;
		Node->Next->PieceDeath(piecetmp, x, y, number);
	}
}

void Piece::SetNext(Piece* Node)
{
	if (Next == NULL)
	{
		Next = Node;
		Next->Next = NULL;
	}
	else
	{
		Next->SetNext(Node);
	}
}
void Piece::Release(Piece *Node)
{
	while (Node != NULL)
	{
			Node = Node->Next;
			Release(Node);
			delete Node;
			Node = NULL;
	}
}

Piece::~Piece()
{
}