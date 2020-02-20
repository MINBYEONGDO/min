#include "Interface.h"



Interface::Interface()
{
}

void Interface::Init(int x, int y,int index)
{
	m_ix = x;
	m_iy = y;
	m_Bitmap = BitmapManager::GetInstance()->GetImange(index);
}
void Interface::Draw(HDC hdc)
{
	m_Bitmap->Draw(hdc, m_ix, m_iy);
}
Interface::~Interface()
{
}
