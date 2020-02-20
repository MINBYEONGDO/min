
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
			tmp->Respawn(i);//방향은 나중에?
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
				break; //충돌하는게 있다면 진행하지 않고 종료
			}
		}
	}
	if (IntersectRect(&rect, &recttmp, &PlayerRect) == true)
	{
		bcheck = true;
	}
	if (bcheck == false)//다른 에너미와 충돌지 않았다면 넘버에 맞는 에너미의 리스포닝 값 변경해서 에너미끼리 충돌할수 있도록 변경
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
			tmp->Move(MapType, Moving);//방향은 나중에?
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

bool EneryManager::ContactObject(int Number, RECT MissileRect)//에너미끼리 충돌?
{
	RECT rect;
	RECT recttmp;
	recttmp = EneryList->GetRect(EneryList, Number);
	if (EneryList->GetDirection(EneryList, Number) == UP)
	{
		recttmp.top -= 2;//intersectRect는 값이 같아도 포함이기에 충돌영역을 수정했다.???
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
bool EneryManager::ContactObject(RECT MissileRect)//접근 대상이 플레이어와 미사일
{
	RECT rect;
	for (int i = 0; i < m_Max; i++)
	{
		if (IntersectRect(&rect, &EneryList->GetRect(EneryList, i), &MissileRect) == true)
		{
			m_iHitEneryNumber = i;//미사일용
			m_iCrushDirection = EneryList->GetDirection(EneryList, i);//플레이어용
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
		enerytmp = enerytmp->GetEnery(enerytmp, i + 1);//좀더 깔끔하게 안되나?
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
