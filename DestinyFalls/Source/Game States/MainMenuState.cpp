#include "stdafx.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "OptionsState.h"
#include "CreditState.h"
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
	PlayGame = { 50, 50, 100, 80 };

	Options = { 50, 90, 100, 120 };
	LoadGame = { 50, 130, 100, 160 };
	HowToPlay = { 50, 170, 100, 200 };
	Credit = { 50, 210, 100, 240 };
	ExitGame = { 50, 250, 100, 280 };
	
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
		m_nCursor = MenuSelections::exit;
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
			Game::GetInstance()->AddState(GameplayState::GetInstance());
			break;
		case MenuSelections::load:
			break;
		case MenuSelections::options:
			Game::GetInstance()->AddState(OptionsState::GetInstance());
			break;
		case MenuSelections::howToPlay:
			break;
		case MenuSelections::credits:
			//Game::GetInstance()->AddState(CreditState::GetInstance());
			break;
		case MenuSelections::exit:
			return false;
			break;
		default:
			break;
		}

	}


	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(PlayGame))
		{
			//Game::GetInstance()->RemoveState();
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
	pGraphics->SetClearColor();
	pGraphics->DrawRectangle(PlayGame, SGD::Color{ 255, 255, 0, 255 });
	pGraphics->DrawRectangle(Options, SGD::Color{ 255, 255, 0, 255 });
	pGraphics->DrawRectangle(LoadGame, SGD::Color{ 255, 255, 0, 255 });
	pGraphics->DrawRectangle(HowToPlay, SGD::Color{ 255, 255, 0, 255 });
	pGraphics->DrawRectangle(Credit, SGD::Color{ 255, 255, 0, 255 });
	pGraphics->DrawRectangle(ExitGame, SGD::Color{ 255, 255, 0, 255 });

	pGraphics->DrawRectangle(SGD::Rectangle{ 40, (float)(40 * m_nCursor + 60), 50, (float)(40 * m_nCursor + 70) }, SGD::Color{ 255, 0, 255, 0 });
}