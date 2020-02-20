
#include "MissileManager.h"

MissileManager::MissileManager()
{
	MissileList = NULL;
	m_Max = 0;
	m_pMissiletmp = NULL;
}
void MissileManager::Init(int Tank_x, int Tank_y, int Tank_Direction)
{
	m_pMissiletmp = new missile;
	if (MissileList == NULL)
	{
		MissileList = m_pMissiletmp;
	}
	else
		MissileList->SetLink(m_pMissiletmp);
	MissileList->CreateMissile(m_pMissiletmp, Tank_x, Tank_y, Tank_Direction, m_Max);
	m_Max++;
}
void MissileManager::Crush()
{
	missile* tmp = NULL;
	missile* tmp1 = NULL;
	if (tmp == NULL)
		tmp = MissileList;
	for (int i = 0; i < m_Max; i++)
	{
		if (tmp->GetExplosionEnd(tmp, i) == true)
		{
			if (tmp->GetCrush(tmp, i) == true)
			{
				if (i == 0)
				{
					tmp1 = tmp->Getmissile(tmp, i);
					tmp->Delete((&tmp1), 0);
					MissileList = tmp1;
				}
				else
				{
					tmp1 = tmp->Getmissile(tmp, i - 1);
					tmp->Delete((&tmp1), i);
				}
				tmp = tmp1;
				ReNumber();
				m_Max--;
			}
		}
	}
}
void MissileManager::Explosion(int Number, int CrushType)
{
	missile* tmp = NULL;
	if (tmp == NULL)
		tmp = MissileList;
	for (int i = 0; i < m_Max; i++)
	{
		if (Number == i)
		{
			tmp->Explosion(CrushType);
		}
		tmp = tmp->GetNextLink(tmp);
	}
}
void MissileManager::ExplosionEvent()
{
	missile* tmp = NULL;
	if (tmp == NULL)
		tmp = MissileList;
	for (int i = 0; i < m_Max; i++)
	{
		tmp->ExplosionEvent();
		tmp = tmp->GetNextLink(tmp);
	}
}
void MissileManager::ChangeStateCrush(int Number)//��Ͽ� �ε�������
{
	missile* tmp = NULL;
	if (tmp == NULL)
		tmp = MissileList;
	for (int i = 0; i < m_Max; i++)
	{
		if (Number == i)
		{
			tmp->ChangeStateCrush();
		}
		tmp = tmp->GetNextLink(tmp);
	}
}

void MissileManager::Draw(HDC hdc)
{
	int Number = 0;
	missile* tmp = NULL;
	if (tmp == NULL)
		tmp = MissileList;
	for (int i = 0; i < m_Max; i++)
	{
		tmp->Draw(hdc, tmp);
		tmp = tmp->Getmissile(tmp, i + 1);//���� ����ϰ� �ȵǳ�?
		if (tmp == NULL)
			break;
	}
}

void MissileManager::ReNumber()//�ݺ����� �̿��ؼ� �ϳ��ϳ� Ȯ���ϴ� ���
{
	missile* tmp = NULL;
	if (tmp == NULL)
		tmp = MissileList;
	for (int i = 0; i < m_Max - 1; i++)
	{
		tmp->ReNumber(i);
		tmp = tmp->GetNextLink(tmp);
	}
}

RECT MissileManager::CheckRect(int Number)
{
	missile* tmp = NULL;
	if (tmp == NULL)
		tmp = MissileList;
	//tmp = tmp->Getmissile(tmp, Number);
	return tmp->GetMissileRect(tmp, Number);
}

int MissileManager::GetDirection(int Number)//�ݺ����� ã�°� �ϳ��ϳ� ã�°� �ƴ϶� ���ǿ� �´� �ϳ��� ã�� ���
{
	missile* tmp = NULL;
	if (tmp == NULL)
		tmp = MissileList;
	//tmp = tmp->Getmissile(tmp, Number);
	return tmp->GetDirection(tmp, Number);
}

void MissileManager::Move()
{
	missile* tmp = NULL;
	if (tmp == NULL)
		tmp = MissileList;
	for (int i = 0; i < m_Max; i++)
	{
		tmp->Move();
		tmp = tmp->Getmissile(tmp, i + 1);//���� ����ϰ� �ȵǳ�?
	}
}

void MissileManager::Release()
{
	MissileList->Release(MissileList);
	delete MissileList;
}
MissileManager::~MissileManager()
{
}