
#include "MapManager.h"



MapManager::MapManager()
{
}

void MapManager::Init()
{
	MapSet();
	MapDataSet();
}
void MapManager::MapSet()
{
	int k = 0;
	int arr = 0;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (k % 2 == 0)
			{
				m_MapList[i][j].SetMap(12);
			}
			else if (k % 2 != 0)
			{
				m_MapList[i][j].SetMap(13);
			}
			k++;
			arr++;
		}
		k++;
	}
}
void MapManager::MapDataSet()
{
	int x = 125;
	int y = 125;
	int k = 0;
	bool  bCheckPiece;
	int Pieceteam;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (i == 0 || i == 1 || i == 6 || i == 7)
				//if (i == 0|| i == 6)// 연습용 한줄
			{
				bCheckPiece = true;
				if (i == 0 || i == 1)
					Pieceteam = 1;
				else if (i == 6 || i == 7)
					Pieceteam = 2;
				else
					Pieceteam = 0;
			}
			else
			{
				bCheckPiece = false;
				Pieceteam = 0;
			}
			m_MapList[i][j].SetMapData(x * j*0.6, y * i*0.6, 0.6, 0.6, bCheckPiece, Pieceteam, i, j);
			k++;
		}
	}
}

void MapManager::UpdataMapData(int Number, bool bresult)
{
	if (bresult == false)//이동만
	{
		m_MapList[arr_y][arr_x].MapExitPiece(Number, bresult, 0);// 이동할 위치
		m_MapList[PieceMap_y][PieceMap_x].MapExitPiece(Number, bresult, 0);//이동전 위치
		m_MapList[arr_y][arr_x].MapChangeMapTeam(Number, bresult, 0);
		m_MapList[PieceMap_y][PieceMap_x].MapChangeMapTeam(Number, bresult, 0);
	}
	else if (bresult == true)//공격만
	{
		m_MapList[arr_y][arr_x].MapExitPiece(Number, bresult, 1);// 이동할 위치
		m_MapList[PieceMap_y][PieceMap_x].MapExitPiece(Number, bresult, 0);//이동전 위치
		m_MapList[arr_y][arr_x].MapChangeMapTeam(Number, bresult, 1);
		m_MapList[PieceMap_y][PieceMap_x].MapChangeMapTeam(Number, bresult, 0);
	}
}

void MapManager::MapDraw(HDC hdc)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			m_MapList[i][j].Draw(hdc);
			if (m_MapList[i][j].CheckPieceMap() == true)
			{
				m_MapList[i][j].CheckDraw(hdc);
			}

		}
	}
}

void MapManager::SearchMap(int Map_x, int Map_y)
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_MapList[i][j].GetMap_x() == Map_x && m_MapList[i][j].GetMap_y() == Map_y)
			{
				arr_x = j;//x 좌표
				arr_y = i;//y 좌표
			}
		}
	}
}
void MapManager::SearchPieceMap(int Map_x, int Map_y)//내가 선택한 피스가 있는 맵의 위치
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_MapList[i][j].GetMap_x() == Map_x && m_MapList[i][j].GetMap_y() == Map_y)
			{
				PieceMap_x = j;//x 좌표
				PieceMap_y = i;//y 좌표
			}
		}
	}
}

bool MapManager::Searchobstruction(int Map_x, int Map_y, int Piece_x, int Piece_y, int PieceType, int playerteam, int playerTurn, int GameTurn)
{
	int i = 1;
	int Turn = 0;
	Turn = GameTurn % 2;
	if (PieceType == 0)//룩
	{
		if (Map_x == Piece_x && Map_y != Piece_y)//y값이 변할때
		{
			if (Map_y < Piece_y)// y값이 감소(위로 향함)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)//경로탐색
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;//도착지가 다른 팀의 말 좌표거나 빈곳일때
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_y > Piece_y)// y값이 증가(아래로 향함)
			{
				for (int i = PieceMap_y + 1; i <= arr_y; i++)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;
						else
							return false;
					}

				}
				return true;
			}
		}
		else if (Map_x != Piece_x && Map_y == Piece_y)// x값이 변할때
		{
			if (Map_x < Piece_x)//x값이 증가 (오른쪽으로 향함)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)// = 이 맞나??
				{
					if (m_MapList[arr_y][i].CheckPieceMap() == true)
					{
						if (i == arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_x > Piece_x)//x값이 감소 (왼쪽으로 향함)
			{
				for (int i = PieceMap_x + 1; i <= arr_x; i++)// = 이 맞나??
				{
					if (m_MapList[arr_y][i].CheckPieceMap() == true)
					{
						if (i == arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;
						else
							return false;
					}
				}
				return true;
			}
		}
	}
	else if (PieceType == 1)//나이츠
	{
		if (arr_y == PieceMap_y + 2 && arr_x == PieceMap_x + 1)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y + 2 && arr_x == PieceMap_x - 1)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y - 2 && arr_x == PieceMap_x + 1)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y - 2 && arr_x == PieceMap_x - 1)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y + 1 && arr_x == PieceMap_x + 2)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y - 1 && arr_x == PieceMap_x + 2)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y + 1 && arr_x == PieceMap_x - 2)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y - 1 && arr_x == PieceMap_x - 2)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else
			return false;
	}
	else if (PieceType == 2)//비숍
	{
		if (abs(Map_x - Piece_x) == abs(Map_y - Piece_y))//이동할 좌표에서 현위치 좌표를 뺀 값의 절대값이 같을때  x,y
		{
			if (Map_y > Piece_y)// 아래로 이동 할때
			{
				if (Map_x > Piece_x)//오른쪽으로 이동할때
				{
					while (1)
					{
						if (PieceMap_x + i == arr_x)
						{
							if (arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						else if (m_MapList[PieceMap_y + i][PieceMap_x + i].CheckPieceMap() == true)
						{
							return false;
						}
						i++;
					}
				}
				else if (Map_x < Piece_x)//왼쪽으로 이동할때
				{
					while (1)
					{
						if (PieceMap_x - i == arr_x)
						{
							if (arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						else if (m_MapList[PieceMap_y + i][PieceMap_x - i].CheckPieceMap() == true)
						{
							return false;
						}
						i++;
					}
				}
			}
			if (Map_y < Piece_y)// 위로로 이동 할때
			{
				if (Map_x > Piece_x)//오른쪽으로 이동할때
				{
					while (1)
					{
						if (PieceMap_x + i == arr_x)
						{
							if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						else if (m_MapList[PieceMap_y - i][PieceMap_x + i].CheckPieceMap() == true)
						{
							return false;
						}
						i++;
					}
				}
				else if (Map_x < Piece_x)//왼쪽으로 이동할때
				{
					while (1)
					{
						if (PieceMap_x - i == arr_x)
						{
							if (arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						else if (m_MapList[PieceMap_y - i][PieceMap_x - i].CheckPieceMap() == true)
						{
							if (i == arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						i++;
					}
				}
			}
			return true;
		}
	}
	else if (PieceType == 3)//퀸
	{
		if (Map_x == Piece_x && Map_y != Piece_y)//y값이 변할때
		{
			if (Map_y < Piece_y)// y값이 감소(위로 향함)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)//경로탐색
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;//도착지가 다른 팀의 말 좌표거나 빈곳일때
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_y > Piece_y)// y값이 증가(아래로 향함)
			{
				for (int i = PieceMap_y + 1; i <= arr_y; i++)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;
						else
							return false;
					}

				}
				return true;
			}
		}
		else if (Map_x != Piece_x && Map_y == Piece_y)// x값이 변할때
		{
			if (Map_x < Piece_x)//x값이 증가 (오른쪽으로 향함)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)// = 이 맞나??
				{
					if (m_MapList[arr_y][i].CheckPieceMap() == true)
					{
						if (i == arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_x > Piece_x)//x값이 감소 (왼쪽으로 향함)
			{
				for (int i = PieceMap_x + 1; i <= arr_x; i++)// = 이 맞나??
				{
					if (m_MapList[arr_y][i].CheckPieceMap() == true)
					{
						if (i == arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;
						else
							return false;
					}
				}
				return true;
			}
		}
		if (abs(Map_x - Piece_x) == abs(Map_y - Piece_y))//이동할 좌표에서 현위치 좌표를 뺀 값의 절대값이 같을때  x,y
		{
			if (Map_y > Piece_y)// 아래로 이동 할때
			{
				if (Map_x > Piece_x)//오른쪽으로 이동할때
				{
					while (1)
					{
						if (PieceMap_x + i == arr_x)
						{
							if (arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						else if (m_MapList[PieceMap_y + i][PieceMap_x + i].CheckPieceMap() == true)
						{
							return false;
						}
						i++;
					}
				}
				else if (Map_x < Piece_x)//왼쪽으로 이동할때
				{
					while (1)
					{
						if (PieceMap_x - i == arr_x)
						{
							if (arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						else if (m_MapList[PieceMap_y + i][PieceMap_x - i].CheckPieceMap() == true)
						{
							return false;
						}
						i++;
					}
				}
			}
			if (Map_y < Piece_y)// 위로로 이동 할때
			{
				if (Map_x > Piece_x)//오른쪽으로 이동할때
				{
					while (1)
					{
						if (PieceMap_x + i == arr_x)
						{
							if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						else if (m_MapList[PieceMap_y - i][PieceMap_x + i].CheckPieceMap() == true)
						{
							return false;
						}
						i++;
					}
				}
				else if (Map_x < Piece_x)//왼쪽으로 이동할때
				{
					while (1)
					{
						if (PieceMap_x - i == arr_x)
						{
							if (arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						else if (m_MapList[PieceMap_y - i][PieceMap_x - i].CheckPieceMap() == true)
						{
							if (i == arr_x && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
								return true;
							else
								return false;
						}
						i++;
					}
				}
			}
			return true;
		}
	}
	else if (PieceType == 4)//킹
	{
		if (arr_y == PieceMap_y + 1 && arr_x == PieceMap_x)//&&뒤가 없으면 y값과 x값이 변하는 대각선 이동에도
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}//맵에 있는 값만 변하면서 문제가 발생한다.이를 방지하기 위함이다.
		else if (arr_y == PieceMap_y - 1 && arr_x == PieceMap_x)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_x == PieceMap_x + 1 && arr_y == PieceMap_y)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_x == PieceMap_x - 1 && arr_y == PieceMap_y)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y + 1 && arr_x == PieceMap_x + 1)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y + 1 && arr_x == PieceMap_x - 1)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y - 1 && arr_x == PieceMap_x + 1)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
		else if (arr_y == PieceMap_y - 1 && arr_x == PieceMap_x - 1)
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}
	}
	else if (PieceType == NOT)// 맨땅일때 define으로 바꿀것
		return false;
	else if (PieceType >= 5)//폰
	{
		if (arr_y == PieceMap_y + 1 && (arr_x == PieceMap_x + 1 || arr_x == PieceMap_x - 1) && Turn == 1)
		{
			if (m_MapList[arr_y][arr_x].CheckPieceMap() == true)//경로탐색
			{
				if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
					return true;//도착지가 다른 팀의 말 좌표거나 빈곳일때
				else
					return false;
			}
		}
		else if (arr_y == PieceMap_y - 1 && (arr_x == PieceMap_x + 1 || arr_x == PieceMap_x - 1) && Turn == 0)
		{
			if (m_MapList[arr_y][arr_x].CheckPieceMap() == true)//경로탐색
			{
				if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
					return true;//도착지가 다른 팀의 말 좌표거나 빈곳일때
				else
					return false;
			}
		}
		else if (arr_y <= PieceMap_y + 2 && arr_x == PieceMap_x && playerTurn == 0 && Turn == 1)
		{
			if (Map_y < Piece_y)// y값이 감소(위로 향함)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)//경로탐색
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() == 0)
							return true;//도착지가 다른 팀의 말 좌표거나 빈곳일때
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_y > Piece_y)// y값이 증가(아래로 향함)
			{
				for (int i = PieceMap_y + 1; i <= arr_y; i++)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() == 0)
							return true;
						else
							return false;
					}

				}
				return true;
			}
		}
		else if (arr_y == PieceMap_y + 1 && arr_x == PieceMap_x && Turn == 1)
		{
			if (m_MapList[arr_y][arr_x].CheckTeam() == 0)
				return true;
			else
				return false;
		}
		else if (arr_y >= PieceMap_y - 2 && arr_x == PieceMap_x && playerTurn == 0 && Turn == 0)
		{
			if (Map_y < Piece_y)// y값이 감소(위로 향함)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)//경로탐색
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() == 0)
							return true;//도착지가 빈칸일때만
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_y > Piece_y)// y값이 증가(아래로 향함)
			{
				for (int i = PieceMap_y + 1; i <= arr_y; i++)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() == 0)
							return true;
						else
							return false;
					}

				}
				return true;
			}
		}
		else if (arr_y == PieceMap_y - 1 && arr_x == PieceMap_x && Turn == 0)
		{
			if (m_MapList[arr_y][arr_x].CheckTeam() == 0)
				return true;
			else
				return false;
		}
		else
			return false;
	}
}

int MapManager::CheckMap_x(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			if (PtInRect(&m_MapList[i][j].GetRect(), pt))
			{
				return m_MapList[i][j].GetMap_x();
			}
	}
	return 0;
}
int MapManager::CheckMap_y(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			if (PtInRect(&m_MapList[i][j].GetRect(), pt))
			{
				return m_MapList[i][j].GetMap_y();
			}
	}
	return 0;
}
int  MapManager::CheckPieceTeam(int x, int y)
{
	POINT pt;
	pt.x = x;
	pt.y = y;
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			if (PtInRect(&m_MapList[i][j].GetRect(), pt))
			{
				return m_MapList[i][j].CheckTeam();
			}
	}
	return 0;
}
MapManager::~MapManager()
{
}