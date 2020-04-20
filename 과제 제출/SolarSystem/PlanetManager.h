
#pragma once
#include "Mecro.h"
#include "Planet.h"
class PlanetManager
{
private:
	Planet* m_PlanetList;
	Planet* m_Planettmp;
	int m_MaxNumber;
public:
	void Init();
	void Animate();
	D3DXMATRIXA16 Rander(int Number);
	D3DXMATRIXA16 MoonRander(int Number);
	int GetMaxNumber()
	{
		return m_MaxNumber;
	}
	bool GetPlanetExistMoon(int Number)
	{
		Planet* tmp;
		tmp = NULL;
		int itmp;
		for (int i = 0; i < 3; i++)
		{
			if (i == Number)
			{
				tmp = m_PlanetList->GetPlanet(m_PlanetList, i);
				if (tmp->GetExistMoon(m_PlanetList, i) == true)
				{
					return tmp->GetExistMoon(m_PlanetList, i);
					break;
				}
			}
			itmp = i - 1;
		}
		return tmp->GetExistMoon(m_PlanetList, itmp);
	}
	PlanetManager();
	~PlanetManager();
};