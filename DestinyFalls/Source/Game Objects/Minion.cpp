#include "stdafx.h"
#include "Minion.h"
#include "../Game States/CombatState.h"

Minion::Minion()
{
}


Minion::~Minion()
{
}

void Minion::Update(float elapsedTime)
{
	TakeTurn();
}

void Minion::Render()
{

}

bool Minion::TakeTurn()
{
	CombatState* pCombat = CombatState::GetInstance();

	return true;
}