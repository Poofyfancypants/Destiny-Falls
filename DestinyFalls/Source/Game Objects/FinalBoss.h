#pragma once
#include "Enemy.h"
#include "Minion.h"

class FinalBoss :
	public Minion
{
public:
	FinalBoss();
	~FinalBoss();

	int GetAIType(void) const { return Final_Boss; }
	virtual bool TakeTurn();

};

