
#include "stdafx.h"
#include "OptionsState.h"
#include "GameplayState.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "SaveandLoadState.h"
#include "../Game Objects/Player.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../Managers/BitmapFontManager.h"


PauseMenuState* PauseMenuState::GetInstance(void)
{
	static PauseMenuState s_Instance;
	return &s_Instance;
}

void PauseMenuState::Enter(void)
{

}

void PauseMenuState::Exit(void)
{

}

bool PauseMenuState::Input(void)
{
	SGD::InputManager * pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		m_nCursor = PauseSelections::exit;
	}
	if (pInput->IsKeyPressed(SGD::Key::Up))
	{
		if (m_nCursor <= 0)
			m_nCursor = PauseSelections::exit;
		else
			m_nCursor--;
	}
	else if (pInput->IsKeyPressed(SGD::Key::Down))
	{
		if (m_nCursor >= PauseSelections::exit)
			m_nCursor = PauseSelections::resume;
		else
			m_nCursor++;
	}

	if (pInput->IsKeyPressed(SGD::Key::Enter))
	{
		switch (m_nCursor)
		{
		case PauseSelections::resume:
			Game::GetInstance()->RemoveState();
			break;
		case PauseSelections::save:
			Game::GetInstance()->AddState(SaveandLoadState::GetInstance());
			break;
		case PauseSelections::options:
			Game::GetInstance()->AddState(OptionsState::GetInstance());
			break;
		case PauseSelections::exit:
			Game::GetInstance()->RemoveState();
			Game::GetInstance()->RemoveState();
			Game::GetInstance()->AddState(MainMenuState::GetInstance());
			break;
		default:
			break;
		}
	}

	//Pause game rect
	SGD::Rectangle rSaveRect = { 300.0f, 100.0f, 500.0f, 150.0f };

	//Gameplay rect
	SGD::Rectangle rResumeRect = { 300.0f, 200.0f, 500.0f, 250.0f };

	//Options rect
	SGD::Rectangle rOptionsRect = { 300.0f, 300.0f, 500.0f, 350.0f };

	//Exit rect
	SGD::Rectangle rExitRect = { 300.0f, 400.0f, 500.0f, 450.0f };
	
	//Click on buttons
	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(rSaveRect))
		{
			SaveGame();
		}
		//Clicked on Resume State button
		if (pInput->GetCursorPosition().IsPointInRectangle(rResumeRect))
		{
			Game::GetInstance()->RemoveState();
		}

		//Clicked on the Options Game button
		if (pInput->GetCursorPosition().IsPointInRectangle(rOptionsRect))
		{
			Game::GetInstance()->AddState(OptionsState::GetInstance());
		}

		//Clicked on the Exit Game button
		if (pInput->GetCursorPosition().IsPointInRectangle(rExitRect))
		{
			Game::GetInstance()->RemoveState();
			Game::GetInstance()->RemoveState();
		}
	}
	return true;
}

void PauseMenuState::Update(float elapsedTime)
{

}

void PauseMenuState::Render(void)
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	//const BitmapFont* pFont = Game::GetInstance()->GetFont();
	BitmapFontManager* pFonts = pFonts->GetInstance();

	if (((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth() <= 0)
	{
		pFonts->Render("Bernardo", Game::GetInstance()->GetString(9).c_str(), { 100, 50 }, 4, { 255, 255, 0, 0 });
	}

	pFonts->Render("Bernardo", Game::GetInstance()->GetString(7).c_str(), { 350, 115 }, 2, { 255, 0, 0, 255 });
	pFonts->Render("Bernardo", Game::GetInstance()->GetString(8).c_str(), { 330, 215 }, 2, { 255, 0, 0, 255 });
	pFonts->Render("Bernardo", Game::GetInstance()->GetString(3).c_str(), { 327, 315 }, 2, { 255, 0, 0, 150 });
	pFonts->Render("Bernardo", Game::GetInstance()->GetString(6).c_str(), { 327, 415 }, 2, { 255, 0, 0, 150 });
}

void PauseMenuState::SaveGame()
{
}
