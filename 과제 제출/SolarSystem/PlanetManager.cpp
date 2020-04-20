
#include "PlanetManager.h"



PlanetManager::PlanetManager()
{
	m_PlanetList = NULL;
	m_Planettmp = NULL;
	m_MaxNumber = 0;

}
void PlanetManager::Init()
{
	for (int i = 0; i < 8; i++)
	{
		m_Planettmp = new Planet;

		if (m_PlanetList == NULL)
			m_PlanetList = m_Planettmp;
		else
			m_PlanetList->SetNext(m_Planettmp);
		m_PlanetList->Init(m_Planettmp, i);
		m_MaxNumber++;
	}
}
void PlanetManager::Animate()
{
	Planet* tmp;
	tmp = NULL;
	for (int i = 0; i < 8; i++)
	{
		tmp = m_PlanetList->GetPlanet(m_PlanetList, i);
		tmp->Animate(tmp, i);
	}
}
D3DXMATRIXA16 PlanetManager::Rander(int Number)
{
	Planet* tmp;
	D3DXMATRIXA16 Mtmp;
	tmp = NULL;
	for (int i = 0; i < 8; i++)
	{
		if (i == Number)
		{
			tmp = m_PlanetList->GetPlanet(m_PlanetList, i);
			Mtmp = tmp->Render(tmp, i);
			break;
		}
	}
	return Mtmp;
}
D3DXMATRIXA16 PlanetManager::MoonRander(int Number)
{
	Planet* tmp;
	D3DXMATRIXA16 Mtmp;
	tmp = NULL;
	for (int i = 0; i < 8; i++)
	{
		if (i == Number)
		{
			tmp = m_PlanetList->GetPlanet(m_PlanetList, i);
			if (tmp->GetExistMoon(m_PlanetList, i) == true)
			{
				Mtmp = tmp->MoonRender(tmp);
				break;
			}
		}
	}
	return Mtmp;
}
PlanetManager::~PlanetManager()
{
	m_PlanetList->Release(m_PlanetList);
	delete m_PlanetList;
}