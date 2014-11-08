#include "stdafx.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"

MainMenuState* MainMenuState::GetInstance()
{
	static MainMenuState s_Instance;
	return &s_Instance;
}

void MainMenuState::Enter()
{
	PlayGame = { 50, 50, 100, 100 };
}

void MainMenuState::Exit()
{

}

bool MainMenuState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	return true;
}

void MainMenuState::Update(float elapsedTime)
{
	Game::GetInstance()->AddState(GameplayState::GetInstance());
}

void MainMenuState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->DrawRectangle(PlayGame, SGD::Color{ 255, 255, 0, 255 });
}