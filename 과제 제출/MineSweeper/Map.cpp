
#include "Map.h"



Map::Map()
{
	Next = NULL;
	m_fspX = 1;
	m_fspY = 1;
	m_Number = 0;
	m_iState = BLANK;
}

void Map::SetNext(Map* Node)
{
	if (Next == NULL)
	{
		Next = Node;
		Next->Next = NULL;
	}
	else
		Next->SetNext(Node);

}
void Map::Init(int Mode, int Number, int Number_y, int Number_x)
{
	if (Mode == BEGINNER)
	{
		m_ix = Number_x * 26 + 13;//정확한 값은 나중에
		m_iy = Number_y * 26 + 24;//이하동문
		m_rect.top = m_iy;
		m_rect.bottom = m_iy + 26;
		m_rect.left = m_ix;
		m_rect.right = m_ix + 26;
	}
	else if (Mode == INTERMEDIATE)
	{
		m_ix = Number_x * 26 + 23;//정확한 값은 나중에
		m_iy = Number_y * 26 + 43;//이하동문
		m_rect.top = m_iy;
		m_rect.bottom = m_iy + 26;
		m_rect.left = m_ix;
		m_rect.right = m_ix + 26;
	}
	else if (Mode == ADVANCED)
	{
		m_ix = Number_x * 26+36 ;//정확한 값은 나중에
		m_iy = Number_y * 26+68 ;//이하동문
		m_rect.top = m_iy;
		m_rect.bottom = m_iy + 26;
		m_rect.left = m_ix;
		m_rect.right = m_ix + 26;
	}
	m_Number = Number;
	m_Number_x = Number_x;
	m_Number_y = Number_y;
	m_Bitmap = BitmapManager::GetInstance()->GetImage(1);
	m_bReverse = false;
	m_bMine = false;
	m_bMineSurvival = false;
	m_bFlag = false;
}

void Map::CreateMine(Map tmp, int R_Mine)
{
	Map *Maptmp;
	if (tmp.GetNumber() == R_Mine)
	{
		m_bMine = true;
		m_bMineSurvival = true;
		//m_Bitmap = BitmapManager::GetInstance()->GetImage(12);
		m_MineBitmap = BitmapManager::GetInstance()->GetImage(12);
		m_iState = MINE;
	}
	else
	{
		Maptmp = tmp.Next;
		tmp.Next->CreateMine(*Maptmp, R_Mine);
	}
}
void Map::SettingNomalMap(Map *Node, int  yline, int xline, int count)
{
	Map *Maptmp;
	if (Node->GetLine_X() == xline && Node->GetLine_Y() == yline)
	{
		m_MineBitmap = BitmapManager::GetInstance()->GetImage(count + 2);
		m_iState = BLANK + count;
	}
	else
	{
		Maptmp = Node->Next;
		Node->Next->SettingNomalMap(Maptmp, yline, xline, count);
	}
}
bool Map::SearchMap(Map Node, int yline, int xline)
{
	Map *Maptmp;
	if (Node.GetLine_X() == xline && Node.GetLine_Y() == yline)
	{
		if (Node.GetMine() == true)
		{
			return true;
		}
	}
	else
	{
		if (Node.Next == NULL)
			return false;
		Maptmp = Node.Next;
		Node.Next->SearchMap(*Maptmp, yline, xline);
	}
}
void Map::SearchNear(Map Node, int yline, int xline)//주변 탐색만
{
	int Count = 0;
	if (Node.SearchMap(Node, yline - 1, xline - 1) == true)
	{
		Count++;
	}
	if (Node.SearchMap(Node, yline - 1, xline) == true)
	{
		Count++;
	}
	if (Node.SearchMap(Node, yline - 1, xline + 1) == true)
	{
		Count++;
	}
	if (Node.SearchMap(Node, yline, xline - 1) == true)
	{
		Count++;
	}
	if (Node.SearchMap(Node, yline, xline + 1) == true)
	{
		Count++;
	}
	if (Node.SearchMap(Node, yline + 1, xline - 1) == true)
	{
		Count++;
	}
	if (Node.SearchMap(Node, yline + 1, xline) == true)
	{
		Count++;
	}
	if (Node.SearchMap(Node, yline + 1, xline + 1) == true)
	{
		Count++;
	}
}
void Map::FlagBitmap()
{
	if (m_bFlag == true)
	{
		m_bFlag = false;
		m_Bitmap = BitmapManager::GetInstance()->GetImage(1);
	}
	else if (m_bFlag == false)
	{
		m_Bitmap = BitmapManager::GetInstance()->GetImage(11);
		m_bFlag = true;
	}
}
void Map::ResetFlag()
{
	m_bFlag = false;
}
void Map::ReverseBitmap()
{
	if (m_bFlag == false)//안하면 확장범위 안이면 m_MineBitmap으로 바뀌기 때문에 조건문 추가
	{
		m_Bitmap = m_MineBitmap;
		m_bReverse = true;
	}
}
void Map::ReCoverBitmap()
{
	m_bReverse = false;
	//if(m_bMine != true)
		m_Bitmap = BitmapManager::GetInstance()->GetImage(1);
//	else
//		m_Bitmap = BitmapManager::GetInstance()->GetImage(12);
}
void Map::Draw(HDC hdc, Map tmp, int  yline, int xline)
{
	Map *Maptmp;
	if (tmp.GetLine_X() == xline && tmp.GetLine_Y() == yline)
		tmp.m_Bitmap->Draw(hdc, m_ix, m_iy, m_fspX, m_fspY);
	else
	{
		Maptmp = tmp.Next;
		tmp.Next->Draw(hdc, *Maptmp, yline, xline);
	}//재귀형식으로 반복해서 그림
}//더블 버퍼는 아닌것 같기도 함 지금


 //int Map::Search_Xline(Map Node, int Number_y, int Number_x)
 //{//이건 왜 틀렸는가?
 // Map *tmp = NULL;
 // if (Node.GetLine_X() == Number_x && Node.GetLine_Y() == Number_y)
 // {
 //  return Node.GetLine_X();
 // }
 // else
 // {
 //  tmp = Node.Next;
 //  Node.Next->Search_Xline(*tmp, Number_y, Number_x);
 // }
 //}

void Map::Release(Map* Node)
{
	while (Node != NULL)//Node에 내용물이 있다면
	{
		Node = Node->Next;//Next로 이동
		Release(Node);//재귀 - 무한반복하다 다음Next에 아무것도 없다면 즉,마지막에 다다르면
		delete Node;//거기서부터 delete시작 첫부분이 마지막에 지워질수 있도록
		Node = NULL;
	}
}
Map::~Map()
{
}