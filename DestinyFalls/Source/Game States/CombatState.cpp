#include "stdafx.h"
#include "CombatState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../Game Core/Game.h"
#include "GameplayState.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"

CombatState* CombatState::GetInstance()
{
	static CombatState s_Instance;
	return &s_Instance;
}

void CombatState::Enter(void)
{

}

void CombatState::Exit(void)
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

}

bool CombatState::Input(void)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		Game::GetInstance()->RemoveState();
	}

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
