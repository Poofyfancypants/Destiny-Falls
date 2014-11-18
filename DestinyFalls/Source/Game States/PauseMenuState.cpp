
#include "stdafx.h"
#include "MainMenuState.h"
#include "../Game Objects/Player.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "OptionsState.h"
#include "GameplayState.h"
#include "PauseMenuState.h"

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

	//Play game button
	pGraphics->DrawRectangle(
	{ 300.0f, 100.0f, 500.0f, 150.0f },
	{ 255, 0, 255, 255 },
	{ 255, 0, 0, 255 }
	);
	pGraphics->DrawString("SAVE", { 350, 115 }, { 255, 0, 0, 255 });
	//Particle button
	pGraphics->DrawRectangle(
		{300.0f, 200.0f, 500.0f, 250.0f}, 
		{ 255, 0, 255, 255 }, 
		{ 255, 0, 0, 255 }
	);
	pGraphics->DrawString("RESUME", { 330, 215 }, { 255, 0, 0, 255 });

	//Animation button
	pGraphics->DrawRectangle(
	{ 300.0f, 300.0f, 500.0f, 350.0f },
	{ 255, 150, 0, 175 },
	{ 255, 50, 0, 150 }
	);
	pGraphics->DrawString("OPTIONS", { 327, 315 }, { 255, 50, 0, 150 });

	//Animation button
	pGraphics->DrawRectangle(
	{ 300.0f, 400.0f, 500.0f, 450.0f },
	{ 255, 150, 0, 175 },
	{ 255, 50, 0, 150 }
	);
	pGraphics->DrawString("EXIT GAME", { 327, 415 }, { 255, 50, 0, 150 });
}

void PauseMenuState::SaveGame()
{
}
