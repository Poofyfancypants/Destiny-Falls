#include "stdafx.h"
#include "OptionsState.h"
#include "../Game Core/Game.h"
#include "GameplayState.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"

OptionsState* OptionsState::GetInstance()
{
	static OptionsState* s_Instance;
	return s_Instance;
}

void OptionsState::Enter()
{
}

void OptionsState::Exit()
{
}

bool OptionsState::Input()
{

	return true;
}

void OptionsState::Update(float elapsedTime)
{

}

void OptionsState::Render()
{

}