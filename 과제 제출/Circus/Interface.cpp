
#include "Interface.h"

Interface::Interface()
{
}

void Interface::SetBitmap(int index)
{
	m_pBitmap = BitmapManager::GetInstance()->GetImage(index);
}
void Interface::Draw(HDC hdc, HDC MemDC, int x, int y)
{
	m_pBitmap->Draw(hdc, MemDC, x, y);
}

Interface::~Interface()
{
}