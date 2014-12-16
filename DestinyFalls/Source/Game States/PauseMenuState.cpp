
#include "stdafx.h"
#include "OptionsState.h"
#include "GameplayState.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "SaveState.h"
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
	m_hBackground = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/MenuBackgrounds/pauseScreen.png");
	m_hButton = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/MenuBackgrounds/pauseButton.png");
	m_hSelected = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/MenuBackgrounds/pauseSelected.png");


	m_mMenuOptions["Resume"] = SGD::Rectangle(370, 190, 485, 225);
	m_mMenuOptions["Save"] = SGD::Rectangle(370, 240, 485, 275);
	m_mMenuOptions["Options"] = SGD::Rectangle(370, 280, 485, 315);
	m_mMenuOptions["Exit"] = SGD::Rectangle(370, 320, 485, 355);
}

void PauseMenuState::Exit(void)
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hBackground);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hButton);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hSelected);
}

bool PauseMenuState::Input(void)
{
	SGD::InputManager * pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	if (m_fArcadeTimer >= 0.5f)
	{
		if (pInput->IsKeyPressed(SGD::Key::Escape) || pInput->IsButtonPressed(0, 6))
		{
			Game::GetInstance()->RemoveState();
			m_fArcadeTimer = 0.0f;
		}
		if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyDown(SGD::Key::W) || pInput->GetLeftJoystick(0).y == -1)
		{
			if (m_nCursor <= resume)
				m_nCursor = exit;
			else
				m_nCursor--;

			m_fArcadeTimer = 0.0f;
		}
		else if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyDown(SGD::Key::S) || pInput->GetLeftJoystick(0).y == 1)
		{
			if (m_nCursor >= exit)
				m_nCursor = resume;
			else
				m_nCursor++;

			m_fArcadeTimer = 0.0f;
		}
	}

	if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsKeyPressed(SGD::Key::MouseLeft) || pInput->IsButtonPressed(0, 0))
	{
		switch (m_nCursor)
		{
		case PauseSelections::resume:
			Game::GetInstance()->RemoveState();
			break;
		case PauseSelections::save:
			Game::GetInstance()->AddState(SaveState::GetInstance());
			break;
		case PauseSelections::options:
			Game::GetInstance()->AddState(OptionsState::GetInstance());
			m_pauseStage = true;
			break;
		case PauseSelections::exit:
			Game::GetInstance()->ClearStates();
			Game::GetInstance()->AddState(MainMenuState::GetInstance());
			break;
		default:
			break;
		}

	}


	if (pInput->GetCursorMovement().x || pInput->GetCursorMovement().y)
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(m_mMenuOptions["Resume"]))
			m_nCursor = resume;
		else if (pInput->GetCursorPosition().IsPointInRectangle(m_mMenuOptions["Save"]))
			m_nCursor = save;
		else if (pInput->GetCursorPosition().IsPointInRectangle(m_mMenuOptions["Options"]))
			m_nCursor = options;
		else if (pInput->GetCursorPosition().IsPointInRectangle(m_mMenuOptions["Exit"]))
			m_nCursor = exit;
		else
			m_nCursor = -1;
	}





	return true;
}

void PauseMenuState::Update(float elapsedTime)
{
	m_fArcadeTimer += elapsedTime;
}

void PauseMenuState::Render(void)
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFonts = pFonts->GetInstance();

	GameplayState::GetInstance()->Render();

	pGraphics->DrawTexture(m_hBackground, SGD::Point(300, 125), {}, {}, {}, { 1, 1.3f });
	for (size_t i = 0; i < 4; i++)
	{
		if (m_nCursor == i)
			pGraphics->DrawTexture(m_hSelected, SGD::Point(360, (float)(180 + 50 * m_nCursor)), {}, {}, {}, { .5f, .7f });
		else
			pGraphics->DrawTexture(m_hButton, SGD::Point(360, (float)(180 + 50 * i)), {}, {}, {}, { .5f, .7f });


		pFonts->Render("Dialog", Game::GetInstance()->GetString(0, i).c_str(),
		{ 380, (float)(190 + 50 * i) },
		.7f, { 247, 180, 91 });
	}

	//string cursor = ">>";
	//pFonts->Render( "Bernardo", Game::GetInstance()->GetString( 0, 8 ).c_str(), { 330, 215 }, 2, { 255, 0, 0, 255 } );
	//pFonts->Render( "Bernardo", Game::GetInstance()->GetString( 0, 3 ).c_str(), { 327, 315 }, 2, { 255, 0, 0, 150 } );
	//pFonts->Render( "Bernardo", Game::GetInstance()->GetString( 0, 6 ).c_str(), { 327, 415 }, 2, { 255, 0, 0, 150 } );

	//pFonts->Render( "Bernardo", cursor.c_str(), SGD::Point( 275, ( m_nCursor * 100 ) + 100 ), 2, { 255, 255, 255, 0 } );
	/*pGraphics->DrawRectangle( SGD::Rectangle{ 40, (float)( 40 * m_nCursor + 60 ), 50, (float)( 40 * m_nCursor + 70 ) }, SGD::Color{ 255, 0, 255, 0 } );*/
}

