
#include "GameManager.h"



GameManager::GameManager()
{
	m_bClick = false;
	m_player = new Player[2];
	m_iTurn = 0;
	m_Piece_x = 0;
	m_Piece_y = 0;
	m_Map_x = 0;
	m_Map_y = 0;
}

void GameManager::Init(HWND hWnd)
{
	BitmapManager::GetInstance()->Init(hWnd);
	m_MapManager.Init();
	m_player[0].Init(0);
	m_player[1].Init(1);
}

void GameManager::ChangeClick()
{
	if (m_bClick == false)
		m_bClick = true;
	else if (m_bClick == true)
		m_bClick = false;
}


void GameManager::Draw(HDC hdc)
{
	m_MapManager.MapDraw(hdc);
	m_player[0].FirstDraw(hdc);
	m_player[1].FirstDraw(hdc);
}

void GameManager::Move(HWND hWnd, LPARAM lParam, int Move_x, int Move_y)
{
	m_Map_x = CheckMap_x(Move_x, Move_y);//���ӸŴ����� �̵�? ���⿡ �ֱ⿣ �ʹ� ���� �ڵ��
	m_Map_y = CheckMap_y(Move_x, Move_y);
	m_MapManager.SearchMap(m_Map_x, m_Map_y);// ��ǥ ã��
	m_MapManager.SearchPieceMap(m_Piece_x, m_Piece_y);//���� ������ �ǽ��� �ִ� �� ��ǥ
	if (m_Map_x != m_Piece_x || m_Map_y != m_Piece_y)//�ι�° ������ ���ڸ��� �ƴҶ�
	{
		if (m_MapManager.Searchobstruction(m_Map_x, m_Map_y, m_Piece_x, m_Piece_y, m_iPieceType, m_MapManager.CheckPieceTeam(m_Map_x, m_Map_y), m_player[0].CheckPieceFirstMove(m_Piece_x, m_Piece_y), m_iTurn) == true)//bool ����
		{// �̵� ��ο� ��ֹ��� �ִ��� Ȯ��
			if (m_iTurn % 2 == 1)//¦�� ��- ������ 0
			{
				if (m_MapManager.CheckPieceTeam(m_Piece_x, m_Piece_y) == 1)//���� �������� ������ �϶�
				{//�ʿ� ����->������ ���϶� ����� �ǵ������ �ǽ���ü�� �������� ������ �ʿ��� �ν��ϴ�bool�� ���� ����� ��ġ�ص� ���ϱ⿡ �̸� �����ϱ� ���ؼ� �߰��� ���ǹ��̴�
					if (m_player[1].MyPieceAttack(m_Map_x, m_Map_y) == true)
					{
						m_player[1].AttackedPieceResult(m_Map_x, m_Map_y);
						m_MapManager.UpdataMapData(0, true);
					}
					else
						m_MapManager.UpdataMapData(0, false);
					m_player[0].MoveMyPiece(0, m_Map_x, m_Map_y, m_Piece_x, m_Piece_y);//�̵�
					if (m_player[0].CheckPieceType(m_Map_x, m_Map_y) == PAWN && m_Map_y == 525)
					{
						if (MessageBox(hWnd, TEXT("���� ������ �����Ͻðڽ��ϱ�?"), TEXT("�� ����"), MB_OKCANCEL) == IDOK)
						{
							m_player[0].MyPawnPromotion(0, m_Map_x, m_Map_y, 1);
							m_iPieceType = 0;
						}
						else if (MessageBox(hWnd, TEXT("���� ���������� �����Ͻðڽ��ϱ�?"), TEXT("�� ����"), MB_OKCANCEL) == IDOK)
						{
							m_player[0].MyPawnPromotion(0, m_Map_x, m_Map_y, 2);
							m_iPieceType = 1;
						}
						else if (MessageBox(hWnd, TEXT("���� ������� �����Ͻðڽ��ϱ�?"), TEXT("�� ����"), MB_OKCANCEL) == IDOK)
						{
							m_player[0].MyPawnPromotion(0, m_Map_x, m_Map_y, 3);
							m_iPieceType = 2;
						}
						else if (MessageBox(hWnd, TEXT("���� ������ �����Ͻðڽ��ϱ�?"), TEXT("�� ����"), MB_OKCANCEL) == IDOK)
						{
							m_player[0].MyPawnPromotion(0, m_Map_x, m_Map_y, 4);
							m_iPieceType = 3;
						}
					}
					m_iTurn++;
				}
			}
		}
		if (m_MapManager.Searchobstruction(m_Map_x, m_Map_y, m_Piece_x, m_Piece_y, m_iPieceType, m_MapManager.CheckPieceTeam(m_Map_x, m_Map_y), m_player[1].CheckPieceFirstMove(m_Piece_x, m_Piece_y), m_iTurn) == true)//bool ����
		{// �̵� ��ο� ��ֹ��� �ִ��� Ȯ�� 
			if (m_iTurn % 2 == 0)// Ȧ�� ��
			{
				if (m_MapManager.CheckPieceTeam(m_Piece_x, m_Piece_y) == 2)//���� �������� ����϶�
				{
					if (m_player[0].MyPieceAttack(m_Map_x, m_Map_y) == true)
					{
						m_player[0].AttackedPieceResult(m_Map_x, m_Map_y);
						m_MapManager.UpdataMapData(1, true);
					}
					else
						m_MapManager.UpdataMapData(1, false);
					m_player[1].MoveMyPiece(1, m_Map_x, m_Map_y, m_Piece_x, m_Piece_y);//�̵�
					if (m_player[1].CheckPieceType(m_Map_x, m_Map_y) == PAWN && m_Map_y == 0)
					{//���� �̵��� ��� ���� ���̰� �������ٱ��� �̵�������
					 //InvalidateRect(hWnd, NULL, TRUE);//�׸��� /�޼����ڽ��ε� ��
						if (MessageBox(hWnd, TEXT("���� ������ �����Ͻðڽ��ϱ�?"), TEXT("�� ����"), MB_OKCANCEL) == IDOK)
						{
							m_player[1].MyPawnPromotion(1, m_Map_x, m_Map_y, 1);
							m_iPieceType = 0;
						}
						else if (MessageBox(hWnd, TEXT("���� ���������� �����Ͻðڽ��ϱ�?"), TEXT("�� ����"), MB_OKCANCEL) == IDOK)
						{
							m_player[1].MyPawnPromotion(1, m_Map_x, m_Map_y, 2);
							m_iPieceType = 1;
						}
						else if (MessageBox(hWnd, TEXT("���� ������� �����Ͻðڽ��ϱ�?"), TEXT("�� ����"), MB_OKCANCEL) == IDOK)
						{
							m_player[1].MyPawnPromotion(1, m_Map_x, m_Map_y, 3);
							m_iPieceType = 3;
						}
						else if (MessageBox(hWnd, TEXT("���� ������ �����Ͻðڽ��ϱ�?"), TEXT("�� ����"), MB_OKCANCEL) == IDOK)
						{
							m_player[1].MyPawnPromotion(1, m_Map_x, m_Map_y, 4);
							m_iPieceType = 4;
						}
					}
					m_iTurn++;

				}
			}
		}
	}
}


void GameManager::Click(int x, int y)
{
	m_Map_x = CheckMap_x(x, y);
	m_Map_y = CheckMap_y(x, y);
	m_Piece_x = CheckPiece_x(x, y);
	m_Piece_y = CheckPiece_y(x, y);
	m_iPieceType = CheckPieceType(x, y);//���� ��ȣ�� �Ǿ��մ°� ���߿� ������ �� �ڼ��� �����ϱ�
}

void GameManager::CheckMate(HWND hWnd)
{
	if (m_player[1].CheckPieceMate() == false)
	{
		if (MessageBox(hWnd, TEXT("������ �����մϴ�"), TEXT("��   ��"), MB_OKCANCEL) == IDOK)
		{
			SendMessage(hWnd, 100, 0, 0);
		}
	}
	else if (m_player[0].CheckPieceMate() == false)
	{
		if (MessageBox(hWnd, TEXT("������ �����մϴ�"), TEXT("��   ��"), MB_OKCANCEL) == IDOK)
		{
			SendMessage(hWnd, 100, 0, 0);
		}
	}
}
int GameManager::CheckPiece_x(int x, int y)
{
	int return_x = 0;//�ʱ�ȭ ���ϰ� ����� Ŭ���ϸ� �ٷ� �Ʒ� �ٿ��� return_x�����Ⱚ�̶� �����߻�
	return_x = m_player[0].CheckPiece_x(x, y);//�渻�� ��ġ�� Ŭ���ߴٸ�
	if (return_x != NULL)// �渻��ġ���
	{
		return return_x;//�װ��� x��
	}
	else if (return_x == NULL)//������� �ƴ� ����̳� ����̶��
	{
		return_x = m_player[1].CheckPiece_x(x, y);//������� ��ġ
		if (return_x != NULL)//��������� �´ٸ�
			return return_x;//������� x�� 
		else
			return 0;//�׳� ������̶�� 0
	}
}
int GameManager::CheckPiece_y(int x, int y)
{
	int return_y = 0;
	return_y = m_player[0].CheckPiece_y(x, y);
	if (return_y != NULL)
	{
		return return_y;
	}
	else if (return_y == NULL)
	{
		return_y = m_player[1].CheckPiece_y(x, y);
		if (return_y != NULL)
			return return_y;
		else
			return 0;
	}
}

int GameManager::CheckPieceType(int x, int y)
{
	int returnType = 0;
	returnType = m_player[0].CheckPieceType(x, y);
	if (returnType != NOT)
	{
		return returnType;
	}
	else if (returnType == NOT)
	{
		returnType = m_player[1].CheckPieceType(x, y);
		if (returnType != NOT)
			return returnType;
		else
			return NOT;
	}
}

int GameManager::CheckMap_x(int x, int y)
{
	return m_MapManager.CheckMap_x(x, y);
}
int GameManager::CheckMap_y(int x, int y)
{
	return m_MapManager.CheckMap_y(x, y);
}


GameManager::~GameManager()
{
	delete[2] m_player;
}