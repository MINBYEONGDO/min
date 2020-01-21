
#include "MapManager.h"



MapManager::MapManager()
{
	MapList = NULL;
	m_Maptmp = NULL;

	int MaxMine = 0;
}
void MapManager::MapListInit(int Mode)
{
	SetMapData(Mode);
}
void MapManager::SetMapData(int Mode)
{
	Map* Maptmp = NULL;
	int Number = 0;
	int Count = 0;
	int MineCreateCount = 0;// ���ڻ��� �����ϱ� ���� ��
	int R_Mine;
	if (Mode == BEGINNER)
	{
		m_MaxMine = 10;
		for (int i = 0; i < 9; i++)//y
		{
			for (int j = 0; j < 9; j++)//x
			{
				m_Maptmp = new Map;
				if (MapList == NULL)
					MapList = m_Maptmp;
				else
					MapList->SetNext(m_Maptmp);
				m_Maptmp->Init(Mode,Number, i, j);
				Number++;
			}
		}
		if (Maptmp == NULL)
			Maptmp = MapList;
		for (int k = 0; k < m_MaxMine; k++)//�ִ����ڰ������� �ݺ�
		{
			R_Mine = rand() % 80;//�� ũ�� ��ŭ�� ���� ��
			if (MapList->CheckMine(Maptmp, R_Mine) == true)//��ġ�� �ʴ´ٸ�
				MapList->CreateMine(*Maptmp, R_Mine);
			else // ��ģ�ٸ� �ٽ� ������ ����
				k--;
		}
		for (int i = 0; i < 9; i++)//y
		{
			for (int j = 0; j < 9; j++)//x
			{
				//ij�� �������� �ƴ�¢ �����ϴ� if
				//�ֺ���ġ�ؼ� �ֺ����ڰ��� �˷��ִ� �Լ�
				//�� �Լ����� �޾ƿ°����� ��Ʈ�ʾ���� �Լ�
				if (MapList->CheckConfirmMine(Maptmp, i, j) == true)//���ڰ� �ƴҶ�
				{
					if (MapList->CheckConfirmMine(Maptmp, i - 1, j - 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i - 1, j) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i - 1, j + 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i, j - 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i, j + 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i + 1, j - 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i + 1, j) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i + 1, j + 1) == false)
					{
						Count++;
					}
					MapList->SettingNomalMap(MapList, i, j, Count);
					Count = 0;
				}
			}
		}
	}
	else if (Mode == INTERMEDIATE)
	{
		m_MaxMine = 50;
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				m_Maptmp = new Map;
				if (MapList == NULL)
					MapList = m_Maptmp;
				else
					MapList->SetNext(m_Maptmp);
				m_Maptmp->Init(Mode, Number, i, j);//�������� �ƴ����� ���?
				Number++;
			}
		}
		if (Maptmp == NULL)
			Maptmp = MapList;
		for (int k = 0; k < m_MaxMine; k++)
		{
			R_Mine = rand() % 255;//0~17 �� 18��
			if (MapList->CheckMine(Maptmp, R_Mine) == true)
				MapList->CreateMine(*Maptmp, R_Mine);
			else
				k--;
		}
		for (int i = 0; i < 16; i++)//y
		{
			for (int j = 0; j < 16; j++)//x
			{
				//ij�� �������� �ƴ�¢ �����ϴ� if
				//�ֺ���ġ�ؼ� �ֺ����ڰ��� �˷��ִ� �Լ�
				//�� �Լ����� �޾ƿ°����� ��Ʈ�ʾ���� �Լ�
				if (MapList->CheckConfirmMine(Maptmp, i, j) == true)//���ڰ� �ƴҶ�
				{
					if (MapList->CheckConfirmMine(Maptmp, i - 1, j - 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i - 1, j) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i - 1, j + 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i, j - 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i, j + 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i + 1, j - 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i + 1, j) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i + 1, j + 1) == false)
					{
						Count++;
					}
					MapList->SettingNomalMap(MapList, i, j, Count);
					Count = 0;
				}
			}
		}
	}
	else if (Mode == ADVANCED)
	{
		m_MaxMine = 80;
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				m_Maptmp = new Map;
				if (MapList == NULL)
					MapList = m_Maptmp;
				else
					MapList->SetNext(m_Maptmp);
				m_Maptmp->Init(Mode, Number, i, j);//�������� �ƴ����� ���?
				Number++;
			}
		}
		if (Maptmp == NULL)
			Maptmp = MapList;
		for (int k = 0; k < m_MaxMine; k++)
		{
			R_Mine = rand() % 624;//0~17 �� 18��
			if (MapList->CheckMine(Maptmp, R_Mine) == true)
				MapList->CreateMine(*Maptmp, R_Mine);
			else
				k--;
		}
		for (int i = 0; i < 25; i++)//y
		{
			for (int j = 0; j < 25; j++)//x
			{
				//ij�� �������� �ƴ�¢ �����ϴ� if
				//�ֺ���ġ�ؼ� �ֺ����ڰ��� �˷��ִ� �Լ�
				//�� �Լ����� �޾ƿ°����� ��Ʈ�ʾ���� �Լ�
				if (MapList->CheckConfirmMine(Maptmp, i, j) == true)//���ڰ� �ƴҶ�
				{
					if (MapList->CheckConfirmMine(Maptmp, i - 1, j - 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i - 1, j) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i - 1, j + 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i, j - 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i, j + 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i + 1, j - 1) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i + 1, j) == false)
					{
						Count++;
					}
					if (MapList->CheckConfirmMine(Maptmp, i + 1, j + 1) == false)
					{
						Count++;
					}
					MapList->SettingNomalMap(MapList, i, j, Count);
					Count = 0;
				}
			}
		}
	}
}

void MapManager::MapReverse(int Mode, int x, int y)
{
	MapList->GetMap(MapList, y, x)->ReverseBitmap();
}
void MapManager::MapReCover(int Mode)
{
	int Max;
	if (Mode == BEGINNER)
		Max = 9;
	else if (Mode == INTERMEDIATE)
		Max = 16;
	else if (Mode == ADVANCED)
		Max = 25;
	for (int i = 0; i < Max; i++)
	{
		for (int j = 0; j < Max; j++)
		{
			MapList->GetMap(MapList, i, j)->ReCoverBitmap();
		}
	}
}

void MapManager::RightClick(int Mode, int x, int y)
{
	if (MapList->GetReverse(MapList,y,x)==false)
	{
		MapList->GetMap(MapList, y, x)->FlagBitmap();
	}
}

void MapManager::SearchMine(int Mode, int x, int y)// ���⸦ �����ؾ��ϴ±���
{
	int Max;
	if (Mode == BEGINNER)
		Max = 8;
	else if (Mode == INTERMEDIATE)
		Max = 15;
	else if (Mode == ADVANCED)
		Max = 24;
	//������ �����϶� �߰� �ϳ��� �������ϰԲ�
	if (MapList->GetReverse(MapList, y, x) == false)
	{
		if (MapList->GetState(MapList, y, x) == BLANK)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
			if (x - 1 >= 0)
			{
				SearchMine(Mode, x - 1, y);
			}
		}
		else if (MapList->GetState(MapList, y, x) != MINE)//���ڵ� �ƴϰ� ��ũ�� �ƴ� ���ں���϶�
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
		}
		if (MapList->GetMap(MapList, y, x)->GetState(MapList, y, x) == BLANK)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
			if (y - 1 >= 0)
			{
				SearchMine(Mode, x, y - 1);
			}
		}
		else if (MapList->GetMap(MapList, y, x)->GetState(MapList, y, x) != MINE)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
		}
		if (MapList->GetState(MapList, y, x) == BLANK)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
			if (x + 1 <= Max)
			{
				SearchMine(Mode, x + 1, y);
			}
		}
		else if (MapList->GetState(MapList, y, x) != MINE)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();

		}
		if (MapList->GetState(MapList, y, x) == BLANK)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
			if (y + 1 <= Max)
			{
				SearchMine(Mode, x, y + 1);
			}
		}
		else if (MapList->GetState(MapList, y, x) != MINE)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();

		}
		if (MapList->GetState(MapList, y, x) == BLANK)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
			if (x - 1 >= 0 && y - 1 >= 0)
			{
		
				SearchMine(Mode, x - 1, y - 1);
			}
		}
		else if (MapList->GetState(MapList, y, x) != MINE)//���ڵ� �ƴϰ� ��ũ�� �ƴ� ���ں���϶�
		{

			MapList->GetMap(MapList, y, x)->ReverseBitmap();
		}
		if (MapList->GetState(MapList, y, x) == BLANK)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
			if (x - 1 >= 0 && y + 1 <= Max)
			{
				SearchMine(Mode, x - 1, y + 1);
			}
		}
		else if (MapList->GetState(MapList, y, x) != MINE)//���ڵ� �ƴϰ� ��ũ�� �ƴ� ���ں���϶�
		{

			MapList->GetMap(MapList, y, x)->ReverseBitmap();
		}
		if (MapList->GetState(MapList, y, x) == BLANK)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
			if (x + 1 <= Max && y - 1 >= 0)
			{
				SearchMine(Mode, x + 1, y - 1);
			}
		}
		else if (MapList->GetState(MapList, y, x) != MINE)//���ڵ� �ƴϰ� ��ũ�� �ƴ� ���ں���϶�
		{

			MapList->GetMap(MapList, y, x)->ReverseBitmap();
		}
		if (MapList->GetState(MapList, y, x) == BLANK)
		{
			MapList->GetMap(MapList, y, x)->ReverseBitmap();
			if (x + 1 <= Max && y + 1 <= Max)
			{
				SearchMine(Mode, x + 1, y + 1);
			}
		}
		else if (MapList->GetState(MapList, y, x) != MINE)//���ڵ� �ƴϰ� ��ũ�� �ƴ� ���ں���϶�
		{

			MapList->GetMap(MapList, y, x)->ReverseBitmap();
		}
	}
}
bool MapManager::CheckMapFlag(int Mode, int xline, int yline)
{
	Map *tmp = NULL;
	if (tmp == NULL)
		tmp = MapList;
	if (MapList->GetFlag(tmp, yline, xline) == true)
	{
		return true;
	}
	else
		return false;
}
bool MapManager::CheckMineFlag(int Mode)
{
	int count = 0;
	int Max;
	if (Mode == BEGINNER)
	{
		Max = 9;
	}
	else if (Mode == INTERMEDIATE)
	{
		Max = 16;
	}
	else if (Mode == ADVANCED)
	{
		Max = 25;
	}
	for (int i = 0; i < Max; i++)
	{
		for (int j = 0; j < Max; j++)
		{
			if(MapList->GetFlag(MapList, i,j)== true &&MapList->CheckConfirmMine(MapList, i, j)== false)
				count++;
		}
	}
	if (m_MaxMine == count)
	{
		return true;
	}
	else
		return false;
}

void MapManager::ResetFlag(int Mode)
{
	int Max;
	if (Mode == BEGINNER)
	{
		Max = 9;
	}
	else if (Mode == INTERMEDIATE)
	{
		Max = 16;
	}
	else if (Mode == ADVANCED)
	{
		Max = 25;
	}
	for (int i = 0; i < Max; i++)
	{
		for (int j = 0; j < Max; j++)
		{
			MapList->GetMap(MapList, i, j)->ResetFlag();
		}
	}
}
bool MapManager::CheckMine(int Mode, int xline, int yline)
{//x,y������ ������ �Ա⶧���� ���� for������ �ݺ��ؼ� ã���ʿ����.
 //if (Mode == BEGINNER)//��ǥ������  xy ������ ã�°ű� ������ �ʿ�
 //{
 // for (int i = 0; i < 9; i++)//y
 // {
 //  for (int j = 0; j < 9; j++)//x
 //  {
 //  }
 // }
	Map *tmp = NULL;
	if (tmp == NULL)
		tmp = MapList;
	if (MapList->CheckConfirmMine(tmp, yline, xline) == true)
	{
		return true;//�����
	}
	else
		return false;//���� 
}
bool MapManager::ClickMap(int Mode, int Pt_x, int Pt_y)
{
	Map* Maptmp = NULL;
	if (Maptmp == NULL)
		Maptmp = MapList;
	POINT pt;
	pt.x = Pt_x;
	pt.y = Pt_y;
	if (Mode == BEGINNER)
	{
		for (int i = 0; i < 9; i++)//y
		{
			for (int j = 0; j < 9; j++)//x
			{
				if (PtInRect(&MapList->GetRect(Maptmp, i, j), pt))
				{
					return true;
				}
			}
		}
	}
	else if (Mode == INTERMEDIATE)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (PtInRect(&MapList->GetRect(Maptmp, i, j), pt))
				{
					return true;
				}
			}
		}
	}
	else if (Mode == ADVANCED)
	{
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (PtInRect(&MapList->GetRect(Maptmp, i, j), pt))
				{
					return true;
				}
			}
		}
	}
	return false;
}
int MapManager::ClickMap_x(int Mode, int Pt_x, int Pt_y)
{
	int x;
	Map* Maptmp = NULL;
	if (Maptmp == NULL)
		Maptmp = MapList;
	POINT pt;
	pt.x = Pt_x;
	pt.y = Pt_y;
	if (Mode == BEGINNER)//��ǥ������  xy ������ ã�°ű� ������ �ʿ�
	{
		for (int i = 0; i < 9; i++)//y
		{
			for (int j = 0; j < 9; j++)//x
			{
				if (PtInRect(&MapList->GetRect(Maptmp, i, j), pt))
				{
					//x= MapList->Search_Xline(*Maptmp, i, j);
					return MapList->GetX_Line(Maptmp, i, j);
				}
			}
		}
	}
	else if (Mode == INTERMEDIATE)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (PtInRect(&MapList->GetRect(Maptmp, i, j), pt))
				{
					return MapList->GetX_Line(Maptmp, i, j);
				}
			}
		}
	}
	else if (Mode == ADVANCED)
	{
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (PtInRect(&MapList->GetRect(Maptmp, i, j), pt))
				{
					return MapList->GetX_Line(Maptmp, i, j);
				}
			}
		}
	}
	return 100;
}
int MapManager::ClickMap_y(int Mode, int Pt_x, int Pt_y)
{
	Map* Maptmp = NULL;
	if (Maptmp == NULL)
		Maptmp = MapList;
	POINT pt;
	pt.x = Pt_x;
	pt.y = Pt_y;
	if (Mode == BEGINNER)
	{
		for (int i = 0; i < 9; i++)//y
		{
			for (int j = 0; j < 9; j++)//x
			{
				if (PtInRect(&MapList->GetRect(Maptmp, i, j), pt))
				{
					return MapList->GetY_Line(Maptmp, i, j);
				}
			}
		}
	}
	else if (Mode == INTERMEDIATE)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (PtInRect(&MapList->GetRect(Maptmp, i, j), pt))
				{
					return  MapList->GetY_Line(Maptmp, i, j);
				}
			}
		}
	}
	else if (Mode == ADVANCED)
	{
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (PtInRect(&MapList->GetRect(Maptmp, i, j), pt))
				{
					return  MapList->GetY_Line(Maptmp, i, j);
				}
			}
		}
	}
	return 100;
}

void MapManager::MapDraw(HDC hdc, int Mode)
{
	Map* Maptmp = NULL;
	if (Maptmp == NULL)
		Maptmp = MapList;
	if (Mode == BEGINNER)
	{
		for (int i = 0; i < 9; i++)//y
		{
			for (int j = 0; j < 9; j++)//x
			{
				MapList->Draw(hdc, *Maptmp, i, j);
			}
		}
	}
	else if (Mode == INTERMEDIATE)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				MapList->Draw(hdc, *Maptmp, i, j);
			}
		}
	}
	else if (Mode == ADVANCED)
	{
		for (int i = 0; i < 25; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				MapList->Draw(hdc, *Maptmp, i, j);
			}
		}
	}
}
void MapManager::Release()
{
	MapList->Release(MapList);
	delete MapList;
}

MapManager::~MapManager()
{
}