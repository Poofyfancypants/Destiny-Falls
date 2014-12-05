#include "stdafx.h"
#include "DeathState.h"
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


DeathState* DeathState::GetInstance(void)
{
	static DeathState s_Instance;
	return &s_Instance;
}

void DeathState::Enter(void)
{

}

void DeathState::Exit(void)
{

}

bool DeathState::Input(void)
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
		case PauseSelections::exit:
			Game::GetInstance()->ClearStates();
			Game::GetInstance()->AddState(MainMenuState::GetInstance());
			break;
		default:
			break;
		}

	}

	//Gameplay rect
	SGD::Rectangle rResumeRect = { 300.0f, 200.0f, 500.0f, 250.0f };

	//Exit rect
	SGD::Rectangle rExitRect = { 300.0f, 400.0f, 500.0f, 450.0f };

	//Click on buttons
	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		//Clicked on Resume State button
		if (pInput->GetCursorPosition().IsPointInRectangle(rResumeRect))
		{
			Game::GetInstance()->RemoveState();
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

void DeathState::Update(float elapsedTime)
{

}

void DeathState::Render(void)
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	//const BitmapFont* pFont = Game::GetInstance()->GetFont();
	BitmapFontManager* pFonts = pFonts->GetInstance();

	pFonts->Render("Bernardo", Game::GetInstance()->GetString(0, 9).c_str(), { 150, 50 }, 4, { 255, 255, 0, 0 });

	string cursor = ">>";
	pFonts->Render("Bernardo", Game::GetInstance()->GetString(0, 7).c_str(), { 350, 200 }, 2, { 255, 0, 0, 255 });
	pFonts->Render("Bernardo", Game::GetInstance()->GetString(0, 8).c_str(), { 350, 350 }, 2, { 255, 0, 0, 255 });
	pFonts->Render("Bernardo", Game::GetInstance()->GetString(0, 6).c_str(), { 350, 500 }, 2, { 255, 0, 0, 150 });

	pFonts->Render("Bernardo", cursor.c_str(), SGD::Point(250, (m_nCursor * 150) + 200), 2, { 255, 255, 255, 0 });
}