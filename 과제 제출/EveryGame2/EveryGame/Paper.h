
#pragma once
#include "GlobalDefine.h"
#include "JEngine.h"
#include "time.h"

enum Color
{
	GREEN,
	BLUE,
	RED,
	YELLOW,
};
#define ANSWER 10
#define NOTANSWER 20
#define NOTHING 30
class Paper
{
private:
	float m_fx;//��ġ�� �ʿ�
	float m_fy;
	float m_Movefx;//�̵��ӵ��� �ʿ�
	float m_Movefy;
	int m_Color;//����Ȯ��
	int m_Score;
	JEngine::BitMap* m_pBitmap;//��Ʈ��
	int m_PaperNumber;
	int m_MoveDirection;
	int m_Answer;
	bool m_bReturn;
	bool m_bMove;
	bool m_breach;
	bool m_bLive;
public:
	void Init(int Number);
	void Input(int Direction, int MoveType);
	void Move();
	void PaperReach();
	void Draw();
	int GetAnswer()
	{
		return m_Answer;
	}
	int GetNumber()
	{
		return m_PaperNumber;
	}
	int GetColor()
	{
		return m_Color;
	}
	int GetScore()
	{
		return m_Score;
	}
	bool GetMove()
	{
		return m_bMove;
	}
	bool GetLive()
	{
		return m_bLive;
	}
	bool GetReach()
	{
		return m_breach;
	}
	Paper();
	~Paper();
};