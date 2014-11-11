#include "stdafx.h"
#include "CombatState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../Game Core/Game.h"
#include "GameplayState.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"

CombatState* CombatState::GetInstance()
{
	static CombatState* s_Instance;
	return s_Instance;
}

void CombatState::Enter(void)
{

}

void CombatState::Exit(void)
{

}

bool CombatState::Input(void)
{
	return true;
}

void CombatState::Update(float elapsedTime)
{

}

void CombatState::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::Rectangle rect = { 450, 450, 500, 500 };

	pGraphics->DrawRectangle(rect, SGD::Color{ 255, 255, 0, 255 });

}
