#pragma once
#include "Enemy.h"
#include "../Runes/Runes.h"
#include "../Runes/RuneManager.h"

class Minion :
	public Enemy
{
public:
	Minion();
	~Minion();

	Runes m_rAffinity;
};

