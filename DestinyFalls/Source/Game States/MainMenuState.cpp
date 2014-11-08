#include "stdafx.h"
#include "MainMenuState.h"

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

}

void MainMenuState::Render()
{

}