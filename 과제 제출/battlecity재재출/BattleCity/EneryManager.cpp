
#include "EneryManager.h"



EneryManager::EneryManager()
{
	EneryList = NULL;
	m_pEnerytmp = NULL;
	m_iHitEneryNumber = 10;
	m_iCrushDirection = 10;
	m_iRespawnEnery = 0;
}
void EneryManager::Init(int Stage)
{
	m_Max = Stage * 2;
	//m_Max = 1;
	m_iRespawnEnery = 0;
	m_iLiveEnery = m_Max;
	for (int i = 0; i < m_Max; i++)
	{
		m_pEnerytmp = new Enery;
		if (EneryList == NULL)
		{
			EneryList = m_pEnerytmp;
		}
		else
			EneryList->SetNext(m_pEnerytmp);
		if (i == m_Max - 1 && Stage == 5)
		{
			EneryList->Init(m_pEnerytmp, i, BOSS);
		}
		else
			EneryList->Init(m_pEnerytmp, i, NOMAL);
	}
}
void EneryManager::Respawn()
{
	Enery* tmp;
	tmp = NULL;
	tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		if (tmp->GetRespawn(tmp, i) == false && tmp->GetLive(tmp, i) == true)
		{
			tmp->Respawn(i);//������ ���߿�?
			m_iRespawnEnery++;
			break;
		}
		tmp = tmp->GetEnery(tmp, i + 1);
	}
}

void EneryManager::EneryResetRespawning(int Number, RECT PlayerRect)
{
	Enery* tmp;
	RECT rect;
	RECT recttmp;
	RECT recttmp2;
	bool bcheck = false;
	tmp = NULL;
	tmp = EneryList;
	recttmp = EneryList->GetRect(EneryList, Number);
	for (int i = 0; i < m_iRespawnEnery; i++)
	{
		recttmp2 = EneryList->GetRect(EneryList, i);
		if (i != Number)
		{
			if (IntersectRect(&rect, &recttmp, &recttmp2) == true)
			{
				bcheck = true;
				break; //�浹�ϴ°� �ִٸ� �������� �ʰ� ����
			}
		}
	}
	if (IntersectRect(&rect, &recttmp, &PlayerRect) == true)
	{
		bcheck = true;
	}
	if (bcheck == false)//�ٸ� ���ʹ̿� �浹�� �ʾҴٸ� �ѹ��� �´� ���ʹ��� �������� �� �����ؼ� ���ʹ̳��� �浹�Ҽ� �ֵ��� ����
	{
		for (int i = 0; i < m_iRespawnEnery; i++)
		{
			if (tmp->GetNumber(tmp, i) == Number)
			{
				tmp->ChangeRespwaning();
			}
			tmp = tmp->GetEnery(tmp, i + 1);
		}
	}
}
void EneryManager::EneryMove(int MapType, int Number, float Moving)
{
	Enery* tmp;
	tmp = NULL;
	tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		if (tmp->GetNumber(tmp, i) == Number)
		{
			tmp->Move(MapType, Moving);//������ ���߿�?
		}
		tmp = tmp->GetEnery(tmp, i + 1);
	}
}
void EneryManager::CheckRectReset(int Number)
{
	Enery* tmp;
	tmp = NULL;
	tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		if (tmp->GetNumber(tmp, i) == Number)
		{
			tmp->CheckRectReset();
		}
		tmp = tmp->GetEnery(tmp, i + 1);
	}
}
void EneryManager::CheckMove(int MapType, int Number, float Moving)
{
	Enery* tmp;
	tmp = NULL;
	tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		if (tmp->GetNumber(tmp, i) == Number)
		{
			tmp->CheckMove(MapType, Moving);
		}
		tmp = tmp->GetEnery(tmp, i + 1);
	}
}
void EneryManager::ChangeDirection(int Number)
{
	Enery* tmp;
	tmp = NULL;
	tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		if (tmp->GetNumber(tmp, i) == Number)
		{
			tmp->ChnageDirection();
		}
		tmp = tmp->GetEnery(tmp, i + 1);
	}
}
void EneryManager::ImageChange(int Number)
{
	Enery* tmp;
	tmp = NULL;
	tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		if (tmp->GetNumber(tmp, i) == Number)
		{
			tmp->BitmapChange();
		}
		tmp = tmp->GetEnery(tmp, i + 1);
	}
}
void EneryManager::Fire()
{
	Enery* tmp;
	tmp = NULL;
	tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		tmp = tmp->GetEnery(tmp, i);
		tmp->Fire();
	}
}
void EneryManager::MissileMove()
{
	Enery* tmp;
	tmp = NULL;
	tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		tmp = tmp->GetEnery(tmp, i);
		tmp->MissileMove();
	}
}
void EneryManager::MissileChangeStateCruch(int Number, int MissileNumber, int CrushType)
{
	Enery* tmp;
	tmp = NULL;
	tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		if (tmp->GetNumber(tmp, i) == Number)
		{
			tmp->MissileChangeStateCruch(MissileNumber, CrushType);
		}
		tmp = tmp->GetEnery(tmp, i + 1);
	}
}

bool EneryManager::ContactObject(int Number, RECT MissileRect)//���ʹ̳��� �浹?
{
	RECT rect;
	RECT recttmp;
	recttmp = EneryList->GetRect(EneryList, Number);
	if (EneryList->GetDirection(EneryList, Number) == UP)
	{
		recttmp.top -= 2;//intersectRect�� ���� ���Ƶ� �����̱⿡ �浹������ �����ߴ�.???
		recttmp.bottom -= 2;
	}
	else if (EneryList->GetDirection(EneryList, Number) == DOWN)
	{
		recttmp.top += 2;
		recttmp.bottom += 2;
	}
	else if (EneryList->GetDirection(EneryList, Number) == LEFT)
	{
		recttmp.left -= 2;
		recttmp.right -= 2;
	}
	else if (EneryList->GetDirection(EneryList, Number) == RIGHT)
	{
		recttmp.left += 2;
		recttmp.right += 2;
	}
	if (IntersectRect(&rect, &recttmp, &MissileRect) == true)
	{
		if (EneryList->GetRespawning(EneryList, Number) == false)
			return true;
	}
	return false;
}
bool EneryManager::ContactObject(RECT MissileRect)//���� ����� �÷��̾�� �̻���
{
	RECT rect;
	for (int i = 0; i < m_Max; i++)
	{
		if (IntersectRect(&rect, &EneryList->GetRect(EneryList, i), &MissileRect) == true)
		{
			m_iHitEneryNumber = i;//�̻��Ͽ�
			m_iCrushDirection = EneryList->GetDirection(EneryList, i);//�÷��̾��
			return true;
		}
	}
	return false;
}


void EneryManager::BreakEnery()
{
	Enery* tmp = NULL;
	if (tmp == NULL)
		tmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		if (i == m_iHitEneryNumber)
		{
			tmp->Break();
			if (tmp->GetLive(tmp, i) == false)
				m_iLiveEnery--;
		}
		tmp = tmp->GetEnery(tmp, i + 1);
	}
}

void EneryManager::Draw(HDC hdc)
{
	Enery* enerytmp = NULL;
	if (enerytmp == NULL)
		enerytmp = EneryList;
	for (int i = 0; i < m_Max; i++)
	{
		enerytmp->Draw(hdc, enerytmp);
		enerytmp = enerytmp->GetEnery(enerytmp, i + 1);//���� ����ϰ� �ȵǳ�?
	}
}
void EneryManager::Release()
{
	EneryList->Release(EneryList);
	EneryList->Release();
	delete EneryList;
}
EneryManager::~EneryManager()
{
}
