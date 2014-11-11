#include "stdafx.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "../Managers/TileManager.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
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
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();


}

bool MainMenuState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		Exit();
		return false;
	}
	if (pInput->IsKeyPressed(SGD::Key::Up))
	{
		if (m_nCursor <= 0)
			m_nCursor = MenuSelections::exit;
		else
			m_nCursor--;
	}
	else if (pInput->IsKeyPressed(SGD::Key::Down))
	{
		if (m_nCursor >= MenuSelections::exit)
			m_nCursor = MenuSelections::play;
		else
			m_nCursor++;
	}

	if (pInput->IsKeyPressed(SGD::Key::Enter))
	{
		switch (m_nCursor)
		{
		case MenuSelections::play:
			break;
		case MenuSelections::load:
			break;
		case MenuSelections::options:
			break;
		case MenuSelections::howToPlay:
			break;
		case MenuSelections::credits:
			break;
		case MenuSelections::exit:
			break;
		default:
			break;
		}

	}


	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(PlayGame))
		{
			Game::GetInstance()->RemoveState();
			Game::GetInstance()->AddState(GameplayState::GetInstance());
		}
	}


	return true;
}

void MainMenuState::Update(float elapsedTime)
{
	return;
}

void MainMenuState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->DrawRectangle(PlayGame, SGD::Color{ 255, 255, 0, 255 });
}