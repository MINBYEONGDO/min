
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
	int MineCreateCount = 0;// 지뢰생성 제한하기 위한 값
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
		for (int k = 0; k < m_MaxMine; k++)//최대지뢰갯수까지 반복
		{
			R_Mine = rand() % 80;//맵 크기 만큼의 랜덤 수
			if (MapList->CheckMine(Maptmp, R_Mine) == true)//겹치지 않는다면
				MapList->CreateMine(*Maptmp, R_Mine);
			else // 겹친다면 다시 랜덤수 생성
				k--;
		}
		for (int i = 0; i < 9; i++)//y
		{
			for (int j = 0; j < 9; j++)//x
			{
				//ij가 지뢰인지 아니짖 학인하는 if
				//주변서치해서 주변지뢰갯수 알려주는 함수
				//그 함수에서 받아온값으로 비트맵씌우는 함수
				if (MapList->CheckConfirmMine(Maptmp, i, j) == true)//지뢰가 아닐때
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
				m_Maptmp->Init(Mode, Number, i, j);//지뢰인지 아닌지는 어떻게?
				Number++;
			}
		}
		if (Maptmp == NULL)
			Maptmp = MapList;
		for (int k = 0; k < m_MaxMine; k++)
		{
			R_Mine = rand() % 255;//0~17 총 18개
			if (MapList->CheckMine(Maptmp, R_Mine) == true)
				MapList->CreateMine(*Maptmp, R_Mine);
			else
				k--;
		}
		for (int i = 0; i < 16; i++)//y
		{
			for (int j = 0; j < 16; j++)//x
			{
				//ij가 지뢰인지 아니짖 학인하는 if
				//주변서치해서 주변지뢰갯수 알려주는 함수
				//그 함수에서 받아온값으로 비트맵씌우는 함수
				if (MapList->CheckConfirmMine(Maptmp, i, j) == true)//지뢰가 아닐때
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
				m_Maptmp->Init(Mode, Number, i, j);//지뢰인지 아닌지는 어떻게?
				Number++;
			}
		}
		if (Maptmp == NULL)
			Maptmp = MapList;
		for (int k = 0; k < m_MaxMine; k++)
		{
			R_Mine = rand() % 624;//0~17 총 18개
			if (MapList->CheckMine(Maptmp, R_Mine) == true)
				MapList->CreateMine(*Maptmp, R_Mine);
			else
				k--;
		}
		for (int i = 0; i < 25; i++)//y
		{
			for (int j = 0; j < 25; j++)//x
			{
				//ij가 지뢰인지 아니짖 학인하는 if
				//주변서치해서 주변지뢰갯수 알려주는 함수
				//그 함수에서 받아온값으로 비트맵씌우는 함수
				if (MapList->CheckConfirmMine(Maptmp, i, j) == true)//지뢰가 아닐때
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

void MapManager::SearchMine(int Mode, int x, int y)// 여기를 변경해야하는구나
{
	int Max;
	if (Mode == BEGINNER)
		Max = 8;
	else if (Mode == INTERMEDIATE)
		Max = 15;
	else if (Mode == ADVANCED)
		Max = 24;
	//누른게 숫자일때 추가 하나만 리버스하게끔
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
		else if (MapList->GetState(MapList, y, x) != MINE)//지뢰도 아니고 블랭크도 아닌 숫자블록일때
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
		else if (MapList->GetState(MapList, y, x) != MINE)//지뢰도 아니고 블랭크도 아닌 숫자블록일때
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
		else if (MapList->GetState(MapList, y, x) != MINE)//지뢰도 아니고 블랭크도 아닌 숫자블록일때
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
		else if (MapList->GetState(MapList, y, x) != MINE)//지뢰도 아니고 블랭크도 아닌 숫자블록일때
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
		else if (MapList->GetState(MapList, y, x) != MINE)//지뢰도 아니고 블랭크도 아닌 숫자블록일때
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
{//x,y라인을 가지고 왔기때문에 별도 for문으로 반복해서 찾을필요없다.
 //if (Mode == BEGINNER)//좌표값으로  xy 라인을 찾는거기 때문에 필요
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
		return true;//빈공간
	}
	else
		return false;//지뢰 
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
	if (Mode == BEGINNER)//좌표값으로  xy 라인을 찾는거기 때문에 필요
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