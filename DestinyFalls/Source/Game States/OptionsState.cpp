#include "stdafx.h"
#include "OptionsState.h"


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