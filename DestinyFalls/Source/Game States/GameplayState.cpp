#include "stdafx.h"
#include "../Game Core/Game.h"
#include "GameplayState.h"
#include "../../SGD Wrappers/SGD_MessageManager.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "MainMenuState.h"

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
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		Game::GetInstance()->RemoveState(); //Make this Pause
		Game::GetInstance()->AddState(MainMenuState::GetInstance());
	}

	return true;
}

void GameplayState::Update(float elapsedTime)
{

}

void GameplayState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::Rectangle rect = { 100, 100, 150, 150 };
	
	pGraphics->DrawRectangle(rect, SGD::Color{ 255, 255, 255, 0 });
}

/*static*/ void GameplayState::MessageProc(const SGD::Message* pMsg)
{
	switch (pMsg->GetMessageID())
	{

	default:
	{
			   OutputDebugStringW(L"GameplayState::MessageProc - unknown message id\n");
	}
		break;
	}

}
