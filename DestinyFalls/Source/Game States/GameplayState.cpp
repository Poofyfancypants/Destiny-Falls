#include "stdafx.h"
#include "GameplayState.h"

GameplayState* GameplayState::GetInstance()
{
	static GameplayState s_Instance;
	return &s_Instance;
}

void GameplayState::Enter()
{

}

void GameplayState::Exit()
{

}

bool GameplayState::Input()
{
	return true;
}

void GameplayState::Update(float elapsedTime)
{

}

void GameplayState::Render()
{

}
