#include "stdafx.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "../Game Core/Game.h"
MainMenuState* MainMenuState::GetInstance()
{
	static MainMenuState s_Instance;
	return &s_Instance;
}

void MainMenuState::Enter()
{
	
}

void MainMenuState::Exit()
{

}

bool MainMenuState::Input()
{
	return true;
}

void MainMenuState::Update(float elapsedTime)
{
	Game::GetInstance()->AddState(GameplayState::GetInstance());
}

void MainMenuState::Render()
{

}