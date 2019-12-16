
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
				//if (i == 0|| i == 6)// ������ ����
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
	if (bresult == false)//�̵���
	{
		m_MapList[arr_y][arr_x].MapExitPiece(Number, bresult, 0);// �̵��� ��ġ
		m_MapList[PieceMap_y][PieceMap_x].MapExitPiece(Number, bresult, 0);//�̵��� ��ġ
		m_MapList[arr_y][arr_x].MapChangeMapTeam(Number, bresult, 0);
		m_MapList[PieceMap_y][PieceMap_x].MapChangeMapTeam(Number, bresult, 0);
	}
	else if (bresult == true)//���ݸ�
	{
		m_MapList[arr_y][arr_x].MapExitPiece(Number, bresult, 1);// �̵��� ��ġ
		m_MapList[PieceMap_y][PieceMap_x].MapExitPiece(Number, bresult, 0);//�̵��� ��ġ
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
				arr_x = j;//x ��ǥ
				arr_y = i;//y ��ǥ
			}
		}
	}
}
void MapManager::SearchPieceMap(int Map_x, int Map_y)//���� ������ �ǽ��� �ִ� ���� ��ġ
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (m_MapList[i][j].GetMap_x() == Map_x && m_MapList[i][j].GetMap_y() == Map_y)
			{
				PieceMap_x = j;//x ��ǥ
				PieceMap_y = i;//y ��ǥ
			}
		}
	}
}

bool MapManager::Searchobstruction(int Map_x, int Map_y, int Piece_x, int Piece_y, int PieceType, int playerteam, int playerTurn, int GameTurn)
{
	int i = 1;
	int Turn = 0;
	Turn = GameTurn % 2;
	if (PieceType == 0)//��
	{
		if (Map_x == Piece_x && Map_y != Piece_y)//y���� ���Ҷ�
		{
			if (Map_y < Piece_y)// y���� ����(���� ����)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)//���Ž��
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;//�������� �ٸ� ���� �� ��ǥ�ų� ����϶�
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_y > Piece_y)// y���� ����(�Ʒ��� ����)
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
		else if (Map_x != Piece_x && Map_y == Piece_y)// x���� ���Ҷ�
		{
			if (Map_x < Piece_x)//x���� ���� (���������� ����)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)// = �� �³�??
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
			else  if (Map_x > Piece_x)//x���� ���� (�������� ����)
			{
				for (int i = PieceMap_x + 1; i <= arr_x; i++)// = �� �³�??
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
	else if (PieceType == 1)//������
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
	else if (PieceType == 2)//���
	{
		if (abs(Map_x - Piece_x) == abs(Map_y - Piece_y))//�̵��� ��ǥ���� ����ġ ��ǥ�� �� ���� ���밪�� ������  x,y
		{
			if (Map_y > Piece_y)// �Ʒ��� �̵� �Ҷ�
			{
				if (Map_x > Piece_x)//���������� �̵��Ҷ�
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
				else if (Map_x < Piece_x)//�������� �̵��Ҷ�
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
			if (Map_y < Piece_y)// ���η� �̵� �Ҷ�
			{
				if (Map_x > Piece_x)//���������� �̵��Ҷ�
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
				else if (Map_x < Piece_x)//�������� �̵��Ҷ�
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
	else if (PieceType == 3)//��
	{
		if (Map_x == Piece_x && Map_y != Piece_y)//y���� ���Ҷ�
		{
			if (Map_y < Piece_y)// y���� ����(���� ����)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)//���Ž��
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
							return true;//�������� �ٸ� ���� �� ��ǥ�ų� ����϶�
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_y > Piece_y)// y���� ����(�Ʒ��� ����)
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
		else if (Map_x != Piece_x && Map_y == Piece_y)// x���� ���Ҷ�
		{
			if (Map_x < Piece_x)//x���� ���� (���������� ����)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)// = �� �³�??
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
			else  if (Map_x > Piece_x)//x���� ���� (�������� ����)
			{
				for (int i = PieceMap_x + 1; i <= arr_x; i++)// = �� �³�??
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
		if (abs(Map_x - Piece_x) == abs(Map_y - Piece_y))//�̵��� ��ǥ���� ����ġ ��ǥ�� �� ���� ���밪�� ������  x,y
		{
			if (Map_y > Piece_y)// �Ʒ��� �̵� �Ҷ�
			{
				if (Map_x > Piece_x)//���������� �̵��Ҷ�
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
				else if (Map_x < Piece_x)//�������� �̵��Ҷ�
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
			if (Map_y < Piece_y)// ���η� �̵� �Ҷ�
			{
				if (Map_x > Piece_x)//���������� �̵��Ҷ�
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
				else if (Map_x < Piece_x)//�������� �̵��Ҷ�
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
	else if (PieceType == 4)//ŷ
	{
		if (arr_y == PieceMap_y + 1 && arr_x == PieceMap_x)//&&�ڰ� ������ y���� x���� ���ϴ� �밢�� �̵�����
		{
			if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
				return true;
			else
				return false;
		}//�ʿ� �ִ� ���� ���ϸ鼭 ������ �߻��Ѵ�.�̸� �����ϱ� �����̴�.
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
	else if (PieceType == NOT)// �Ƕ��϶� define���� �ٲܰ�
		return false;
	else if (PieceType >= 5)//��
	{
		if (arr_y == PieceMap_y + 1 && (arr_x == PieceMap_x + 1 || arr_x == PieceMap_x - 1) && Turn == 1)
		{
			if (m_MapList[arr_y][arr_x].CheckPieceMap() == true)//���Ž��
			{
				if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
					return true;//�������� �ٸ� ���� �� ��ǥ�ų� ����϶�
				else
					return false;
			}
		}
		else if (arr_y == PieceMap_y - 1 && (arr_x == PieceMap_x + 1 || arr_x == PieceMap_x - 1) && Turn == 0)
		{
			if (m_MapList[arr_y][arr_x].CheckPieceMap() == true)//���Ž��
			{
				if (m_MapList[PieceMap_y][PieceMap_x].CheckTeam() != playerteam)
					return true;//�������� �ٸ� ���� �� ��ǥ�ų� ����϶�
				else
					return false;
			}
		}
		else if (arr_y <= PieceMap_y + 2 && arr_x == PieceMap_x && playerTurn == 0 && Turn == 1)
		{
			if (Map_y < Piece_y)// y���� ����(���� ����)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)//���Ž��
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() == 0)
							return true;//�������� �ٸ� ���� �� ��ǥ�ų� ����϶�
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_y > Piece_y)// y���� ����(�Ʒ��� ����)
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
			if (Map_y < Piece_y)// y���� ����(���� ����)
			{
				for (int i = PieceMap_y - 1; i >= arr_y; i--)
				{
					if (m_MapList[i][arr_x].CheckPieceMap() == true)//���Ž��
					{
						if (i == arr_y && m_MapList[PieceMap_y][PieceMap_x].CheckTeam() == 0)
							return true;//�������� ��ĭ�϶���
						else
							return false;
					}
				}
				return true;
			}
			else  if (Map_y > Piece_y)// y���� ����(�Ʒ��� ����)
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