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
	

	pGraphics->DrawRectangle(AbilityRect, SGD::Color{ 100, 150, 150, 150 });

	pGraphics->DrawRectangle(Compation1HB, SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawRectangle(PlayerHB,	   SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawRectangle(Compation2HB, SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawRectangle(Enemy1HB, SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawRectangle(Enemy2HB, SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawRectangle(Enemy3HB, SGD::Color{ 100, 150, 150, 150 });

	pGraphics->DrawRectangle(Compation1rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Playerrect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Compation2rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Enemy1rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Enemy2rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Enemy3rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
}
