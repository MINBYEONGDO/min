#include "Interface.h"



Interface::Interface()
{
	m_ix = 0;
	m_iy = 0;
	m_Bitmap = BitmapManager::GetInstance()->GetImage(0);
}

void Interface::Draw(HDC hdc,int Mode)
{
	if(Mode== BEGINNER)
		m_Bitmap->Draw(hdc, m_ix , m_iy,0.301,0.555);
	else if(Mode == INTERMEDIATE)
	{
		m_Bitmap->Draw(hdc, m_ix, m_iy, 0.534, 0.99);
	}
	else if (Mode == ADVANCED)
	{
		m_Bitmap->Draw(hdc, m_ix, m_iy, 0.835, 1.55);
	}
}
Interface::~Interface()
{
}
