#include "obstacle.h"

obstacle::obstacle()
{
}
void obstacle::SetBitmap(int index)
{
}
void obstacle::SetData(int Number, int type)
{
}

void obstacle::CheckifMove(int Move)
{
	if (Move > m_iNumber * 250 - 250 && m_itype == RING)
		m_bMove = true;
}
void obstacle::Draw(HDC hdc, HDC MemDC, int Number, int Move, int imageNumber)
{
	if (m_blive == true)
	{
		if (Move > m_iNumber * 250 - 250)
		{
			BitmapList[imageNumber]->Draw(hdc, MemDC, m_ix - Move, m_iy);
			m_ix = m_ix - 0.1;
		}
	}
	if (m_bMove == true)//0 3 6 12  45 78
	{
		BitmapList[imageNumber]->Draw(hdc, MemDC, m_ix - Move, m_iy);
		m_ix = m_ix - 0.1;
	}
	else if (m_ix <= -10)
		m_ix = -10;
	else //0 1
		BitmapList[imageNumber]->Draw(hdc, MemDC, m_ix - Move, m_iy);
}
void obstacle::ChangeScoreGive()
{
	m_bScore = false;
}

obstacle::~obstacle()
{
}