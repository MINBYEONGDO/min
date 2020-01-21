#pragma once
#include"Mecro.h"
class Player
{
private:
	int m_iFlag;
public:
	void Init(int Mode);
	void FlagDown();
	void FlagUp(int Mode);
	inline int GetFlag()
	{
		return m_iFlag;
	}
	Player();
	~Player();
};

