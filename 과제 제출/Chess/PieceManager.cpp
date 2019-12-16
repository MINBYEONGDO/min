
#include "PieceManager.h"



PieceManager::PieceManager()
{
	m_PieceList = NULL;
	m_Piecetmp = NULL;
}


void PieceManager::Init(int number)// 줄이기 전후비교 하기
{
	int x = 75;
	int y = 75;
	int startx;
	int starty;
	if (number == 0)
	{
		startx = 0;
		starty = 0;
	}
	if (number == 1)//배열을 시작이 록 나이츠 비숍 ~~~ 폰 순이라서 거꾸로 생성하게됨
	{
		startx = 0;
		starty = 525;
	}
	for (int i = 0; i < 16; i++)
	{
		if (i < 8)
		{
			if (i == 0)
			{
				m_Piecetmp = new Rook(i, x*i, starty, 0.6, 0.6);
			}
			else if (i == 1)
			{
				m_Piecetmp = new Knight(i, x*i, starty, 0.6, 0.6);
			}
			else if (i == 2)
			{
				m_Piecetmp = new Bishop(i, x*i, starty, 0.6, 0.6);
			}
			else if (i == 3)
			{
				m_Piecetmp = new Queen(i, x*i, starty, 0.6, 0.6);
			}
			else if (i == 4)
			{
				m_Piecetmp = new King(i, x*i, starty, 0.6, 0.6);
			}
			else if (i == 5)
			{
				m_Piecetmp = new Bishop(i, x*i, starty, 0.6, 0.6);
			}
			else if (i == 6)
			{
				m_Piecetmp = new Knight(i, x*i, starty, 0.6, 0.6);
			}
			else if (i == 7)
			{
				m_Piecetmp = new Rook(i, x*i, starty, 0.6, 0.6);
			}
			if (m_PieceList == NULL)
				m_PieceList = m_Piecetmp;
			else
				m_PieceList->SetNext(m_Piecetmp);
			m_PieceList->Init(m_Piecetmp, number, i, x*i, starty, 0.6, 0.6);
		}
		else if (i >= 8 && number == 0)
		{
			m_Piecetmp = new Pawn(i, x*(i - 8), starty + y, 0.6, 0.6);
			if (m_PieceList == NULL)
				m_PieceList = m_Piecetmp;
			else
				m_PieceList->SetNext(m_Piecetmp);
			m_PieceList->Init(m_Piecetmp, number, i, x*(i - 8), starty + y * 1, 0.6, 0.6);
		}
		else if (i >= 8 && number == 1)
		{
			m_Piecetmp = new Pawn(i, x*(i - 8), starty - y * 1, 0.6, 0.6);
			if (m_PieceList == NULL)
				m_PieceList = m_Piecetmp;
			else
				m_PieceList->SetNext(m_Piecetmp);
			m_PieceList->Init(m_Piecetmp, number, i, x*(i - 8), starty - y * 1, 0.6, 0.6);//여기보면 거꾸로뜻을 알수잇다
		}
	}
}

void PieceManager::PieceSet()
{

}

void PieceManager::FirstDraw(HDC hdc)
{
	Piece *piecetmp = NULL;
	if (piecetmp == NULL)
	{
		piecetmp = m_PieceList;
	}
	for (int i = 0; i < 16; i++)
	{
		if (m_PieceList->GetSurvival(piecetmp, i) == true)
			m_PieceList->Draw(hdc, *piecetmp, i);
	}
}
void PieceManager::AttackedPieceResult(int x, int y)
{
	Piece *piecetmp = NULL;
	POINT pt;
	pt.x = x;
	pt.y = y;
	if (piecetmp == NULL)
	{
		piecetmp = m_PieceList;
	}
	for (int i = 0; i < 16; i++)//?
	{
		if (PtInRect(&m_PieceList->GetRect(piecetmp, i), pt))
		{
			m_PieceList->PieceDeath(piecetmp, x, y, i);
		}
	}
}

void PieceManager::PawnPromotion(int playerteamNumber, int x, int y, int Number)
{
	Piece *piecetmp = NULL;
	//piecetmp = new Piece;
	piecetmp = NULL;

	POINT pt;
	pt.x = x;
	pt.y = y;
	if (piecetmp == NULL)
	{
		piecetmp = m_PieceList;
	}
	for (int i = 0; i < 16; i++)//?
	{
		if (PtInRect(&m_PieceList->GetRect(piecetmp, i), pt))
		{
			m_PieceList->PawnPromotion(piecetmp, playerteamNumber, x, y, i, Number);
			break;
		}
	}
}


int PieceManager::GetPieceRect_x(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	Piece *piecetmp = NULL;
	if (piecetmp == NULL)
	{
		piecetmp = m_PieceList;
	}
	for (int i = 0; i < 16; i++)
	{
		if (PtInRect(&m_PieceList->GetRect(piecetmp, i), pt) && m_PieceList->GetSurvival(m_PieceList, i) == true)
		{
			return m_PieceList->GetPiece_x(piecetmp, i);
		}
	}
	return 0;
}
int PieceManager::GetPieceRect_y(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	Piece *piecetmp = NULL;
	if (piecetmp == NULL)
	{
		piecetmp = m_PieceList;
	}
	for (int i = 0; i < 16; i++)
	{
		if (PtInRect(&m_PieceList->GetRect(piecetmp, i), pt) && m_PieceList->GetSurvival(m_PieceList, i) == true)
		{
			return m_PieceList->GetPiece_y(piecetmp, i);
		}
	}
	return 0;
}
int PieceManager::GetPieceType(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	Piece *piecetmp = NULL;
	if (piecetmp == NULL)
	{
		piecetmp = m_PieceList;
	}
	for (int i = 0; i < 16; i++)
	{
		if (PtInRect(&m_PieceList->GetRect(piecetmp, i), pt) && m_PieceList->GetSurvival(m_PieceList, i) == true)
		{
			return m_PieceList->GetPieceType(piecetmp, i);
		}
	}
	return NOT;
}

int PieceManager::GetPieceFirstMove(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	Piece *piecetmp = NULL;
	if (piecetmp == NULL)
	{
		piecetmp = m_PieceList;
	}
	for (int i = 0; i < 16; i++)
	{
		if (PtInRect(&m_PieceList->GetRect(piecetmp, i), pt) && m_PieceList->GetSurvival(m_PieceList, i) == true)
		{
			return m_PieceList->GetPieceFirstMove(piecetmp, i);
		}
	}
	return NOT;
}
bool PieceManager::PieceAttack(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	Piece *piecetmp = NULL;
	if (piecetmp == NULL)
	{
		piecetmp = m_PieceList;
	}
	for (int i = 0; i < 16; i++)
	{
		if (PtInRect(&m_PieceList->GetRect(piecetmp, i), pt) && m_PieceList->GetSurvival(m_PieceList, i) == true)//
		{
			return true;
		}
	}
	return false;
}
bool PieceManager::CheckSurvival()
{
	return m_PieceList->GetSurvival(m_PieceList, 4);
}
void PieceManager::Move(int playernumber, int Map_x, int Map_y, int Piece_x, int Piece_y)
{
	POINT pt;
	pt.x = Piece_x;
	pt.y = Piece_y;
	Piece *piecetmp = NULL;
	if (piecetmp == NULL)
	{
		piecetmp = m_PieceList;
	}
	for (int i = 0; i < 16; i++)//?
	{
		if ((m_PieceList->GetPiece_x(piecetmp, i) == Piece_x) && (m_PieceList->GetPiece_y(piecetmp, i) == Piece_y) && m_PieceList->GetSurvival(piecetmp, i) == true)//이렇게 단순히 추가만 해도 되나?
		{
			m_PieceList->MoveManager(piecetmp, playernumber, Map_x, Map_y, i);
			break;//맞나?
		}
	}
}
PieceManager::~PieceManager()
{
	m_PieceList->Release(m_PieceList);
	delete m_PieceList;
}