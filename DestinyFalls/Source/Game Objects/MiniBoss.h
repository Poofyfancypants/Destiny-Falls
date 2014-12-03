#pragma once
#include "Enemy.h"
#include "Minion.h"

class MiniBoss :
	public Minion
{
public:
	MiniBoss();
	~MiniBoss();

	int GetAIType(void) const { return Mini_Boss; }
	virtual bool TakeTurn();

};

