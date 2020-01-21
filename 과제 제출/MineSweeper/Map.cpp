
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
		m_ix = Number_x * 26 + 13;//��Ȯ�� ���� ���߿�
		m_iy = Number_y * 26 + 24;//���ϵ���
		m_rect.top = m_iy;
		m_rect.bottom = m_iy + 26;
		m_rect.left = m_ix;
		m_rect.right = m_ix + 26;
	}
	else if (Mode == INTERMEDIATE)
	{
		m_ix = Number_x * 26 + 23;//��Ȯ�� ���� ���߿�
		m_iy = Number_y * 26 + 43;//���ϵ���
		m_rect.top = m_iy;
		m_rect.bottom = m_iy + 26;
		m_rect.left = m_ix;
		m_rect.right = m_ix + 26;
	}
	else if (Mode == ADVANCED)
	{
		m_ix = Number_x * 26+36 ;//��Ȯ�� ���� ���߿�
		m_iy = Number_y * 26+68 ;//���ϵ���
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
void Map::SearchNear(Map Node, int yline, int xline)//�ֺ� Ž����
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
	if (m_bFlag == false)//���ϸ� Ȯ����� ���̸� m_MineBitmap���� �ٲ�� ������ ���ǹ� �߰�
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
	}//����������� �ݺ��ؼ� �׸�
}//���� ���۴� �ƴѰ� ���⵵ �� ����


 //int Map::Search_Xline(Map Node, int Number_y, int Number_x)
 //{//�̰� �� Ʋ�ȴ°�?
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
	while (Node != NULL)//Node�� ���빰�� �ִٸ�
	{
		Node = Node->Next;//Next�� �̵�
		Release(Node);//��� - ���ѹݺ��ϴ� ����Next�� �ƹ��͵� ���ٸ� ��,�������� �ٴٸ���
		delete Node;//�ű⼭���� delete���� ù�κ��� �������� �������� �ֵ���
		Node = NULL;
	}
}
Map::~Map()
{
}