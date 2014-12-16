#include "stdafx.h"
#include "../Game Core/Game.h"
#include "HowToPlayState.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

HowToPlayState* HowToPlayState::GetInstance()
{
	static HowToPlayState s_Instance;
	return &s_Instance;
}
void HowToPlayState::Enter()
{

}

void HowToPlayState::Exit()
{

}

bool HowToPlayState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	if (pInput->IsKeyPressed(SGD::Key::Escape) || pInput->IsButtonPressed(0,6))
	{
		Game::GetInstance()->RemoveState();
	}
	return true;
}

void HowToPlayState::Update(float elapsedTime)
{

}

void HowToPlayState::Render()
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	pGraphics->SetClearColor();

	pGraphics->DrawTexture(m_hBackground, { 0,0 }, 0, {}, {}, { 1.6f, 1.2f });

	SGD::GraphicsManager::GetInstance()->DrawString("esc to Exit", { 690, 575 }, { 255, 0, 0 });

}