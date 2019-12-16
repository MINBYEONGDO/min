
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
	m_Map_x = CheckMap_x(Move_x, Move_y);//게임매니저로 이동? 여기에 있기엔 너무 많은 코드들
	m_Map_y = CheckMap_y(Move_x, Move_y);
	m_MapManager.SearchMap(m_Map_x, m_Map_y);// 좌표 찾기
	m_MapManager.SearchPieceMap(m_Piece_x, m_Piece_y);//내가 선택한 피스가 있는 맵 좌표
	if (m_Map_x != m_Piece_x || m_Map_y != m_Piece_y)//두번째 선택이 제자리가 아닐때
	{
		if (m_MapManager.Searchobstruction(m_Map_x, m_Map_y, m_Piece_x, m_Piece_y, m_iPieceType, m_MapManager.CheckPieceTeam(m_Map_x, m_Map_y), m_player[0].CheckPieceFirstMove(m_Piece_x, m_Piece_y), m_iTurn) == true)//bool 값임
		{// 이동 경로에 장애물이 있는지 확인
			if (m_iTurn % 2 == 1)//짝수 턴- 시작이 0
			{
				if (m_MapManager.CheckPieceTeam(m_Piece_x, m_Piece_y) == 1)//현재 지정말이 검은색 일때
				{//필요 이유->검은색 턴일때 흰색을 건드렸을때 피스자체는 움직이지 않으나 맵에서 인식하는bool에 값은 흰색을 터치해도 변하기에 이를 방지하기 위해서 추가한 조건문이다
					if (m_player[1].MyPieceAttack(m_Map_x, m_Map_y) == true)
					{
						m_player[1].AttackedPieceResult(m_Map_x, m_Map_y);
						m_MapManager.UpdataMapData(0, true);
					}
					else
						m_MapManager.UpdataMapData(0, false);
					m_player[0].MoveMyPiece(0, m_Map_x, m_Map_y, m_Piece_x, m_Piece_y);//이동
					if (m_player[0].CheckPieceType(m_Map_x, m_Map_y) == PAWN && m_Map_y == 525)
					{
						if (MessageBox(hWnd, TEXT("폰을 룩으로 진급하시겠습니까?"), TEXT("폰 진급"), MB_OKCANCEL) == IDOK)
						{
							m_player[0].MyPawnPromotion(0, m_Map_x, m_Map_y, 1);
							m_iPieceType = 0;
						}
						else if (MessageBox(hWnd, TEXT("폰을 나이츠으로 진급하시겠습니까?"), TEXT("폰 진급"), MB_OKCANCEL) == IDOK)
						{
							m_player[0].MyPawnPromotion(0, m_Map_x, m_Map_y, 2);
							m_iPieceType = 1;
						}
						else if (MessageBox(hWnd, TEXT("폰을 비숍으로 진급하시겠습니까?"), TEXT("폰 진급"), MB_OKCANCEL) == IDOK)
						{
							m_player[0].MyPawnPromotion(0, m_Map_x, m_Map_y, 3);
							m_iPieceType = 2;
						}
						else if (MessageBox(hWnd, TEXT("폰을 퀸으로 진급하시겠습니까?"), TEXT("폰 진급"), MB_OKCANCEL) == IDOK)
						{
							m_player[0].MyPawnPromotion(0, m_Map_x, m_Map_y, 4);
							m_iPieceType = 3;
						}
					}
					m_iTurn++;
				}
			}
		}
		if (m_MapManager.Searchobstruction(m_Map_x, m_Map_y, m_Piece_x, m_Piece_y, m_iPieceType, m_MapManager.CheckPieceTeam(m_Map_x, m_Map_y), m_player[1].CheckPieceFirstMove(m_Piece_x, m_Piece_y), m_iTurn) == true)//bool 값임
		{// 이동 경로에 장애물이 있는지 확인 
			if (m_iTurn % 2 == 0)// 홀수 턴
			{
				if (m_MapManager.CheckPieceTeam(m_Piece_x, m_Piece_y) == 2)//현재 지정말이 흰색일때
				{
					if (m_player[0].MyPieceAttack(m_Map_x, m_Map_y) == true)
					{
						m_player[0].AttackedPieceResult(m_Map_x, m_Map_y);
						m_MapManager.UpdataMapData(1, true);
					}
					else
						m_MapManager.UpdataMapData(1, false);
					m_player[1].MoveMyPiece(1, m_Map_x, m_Map_y, m_Piece_x, m_Piece_y);//이동
					if (m_player[1].CheckPieceType(m_Map_x, m_Map_y) == PAWN && m_Map_y == 0)
					{//현재 이동한 흰색 말이 폰이고 마지막줄까지 이동했을때
					 //InvalidateRect(hWnd, NULL, TRUE);//그리기 /메세지박스인데 흠
						if (MessageBox(hWnd, TEXT("폰을 룩으로 진급하시겠습니까?"), TEXT("폰 진급"), MB_OKCANCEL) == IDOK)
						{
							m_player[1].MyPawnPromotion(1, m_Map_x, m_Map_y, 1);
							m_iPieceType = 0;
						}
						else if (MessageBox(hWnd, TEXT("폰을 나이츠으로 진급하시겠습니까?"), TEXT("폰 진급"), MB_OKCANCEL) == IDOK)
						{
							m_player[1].MyPawnPromotion(1, m_Map_x, m_Map_y, 2);
							m_iPieceType = 1;
						}
						else if (MessageBox(hWnd, TEXT("폰을 비숍으로 진급하시겠습니까?"), TEXT("폰 진급"), MB_OKCANCEL) == IDOK)
						{
							m_player[1].MyPawnPromotion(1, m_Map_x, m_Map_y, 3);
							m_iPieceType = 3;
						}
						else if (MessageBox(hWnd, TEXT("폰을 퀸으로 진급하시겠습니까?"), TEXT("폰 진급"), MB_OKCANCEL) == IDOK)
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
	m_iPieceType = CheckPieceType(x, y);//현재 번호로 되어잇는거 나중에 종류로 더 자세히 구분하기
}

void GameManager::CheckMate(HWND hWnd)
{
	if (m_player[1].CheckPieceMate() == false)
	{
		if (MessageBox(hWnd, TEXT("게임을 종료합니다"), TEXT("승   리"), MB_OKCANCEL) == IDOK)
		{
			SendMessage(hWnd, 100, 0, 0);
		}
	}
	else if (m_player[0].CheckPieceMate() == false)
	{
		if (MessageBox(hWnd, TEXT("게임을 종료합니다"), TEXT("승   리"), MB_OKCANCEL) == IDOK)
		{
			SendMessage(hWnd, 100, 0, 0);
		}
	}
}
int GameManager::CheckPiece_x(int x, int y)
{
	int return_x = 0;//초기화 안하고 빈곳간 클릭하면 바로 아래 줄에서 return_x쓰레기값이라 에러발생
	return_x = m_player[0].CheckPiece_x(x, y);//흑말들 위치를 클릭했다면
	if (return_x != NULL)// 흑말위치라면
	{
		return return_x;//그곳의 x값
	}
	else if (return_x == NULL)//흑색들이 아닌 빈곳이나 흰색이라면
	{
		return_x = m_player[1].CheckPiece_x(x, y);//흰색말들 위치
		if (return_x != NULL)//흰색진영이 맞다면
			return return_x;//흰색말의 x값 
		else
			return 0;//그냥 빈공간이라면 0
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