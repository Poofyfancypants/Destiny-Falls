#include "stdafx.h"
#include "Companion.h"
#include "../Game States/CombatState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

Companion::Companion()
{
}


Companion::~Companion()
{
}

void Companion::Update(float elapsedTime)
{

}

void Companion::Render(int _posIndex)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

}

bool Companion::TakeTurn()
{
	CombatState* pCombat = CombatState::GetInstance();


	return true;
}
