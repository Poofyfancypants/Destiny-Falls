#include "stdafx.h"
#include "WinState.h"
#include "CreditState.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Player.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_String.h"

WinState* WinState::GetInstance()
{
	static WinState s_Instance;
	return &s_Instance;
}

void WinState::Enter()
{
	//m_hMusic = SGD::AudioManager::GetInstance()->LoadAudio(L"");
	//m_htBackground = SGD::AudioManager::GetInstance()->LoadAudio(L"");
	//SGD::AudioManager::GetInstance()->PlayAudio(m_haBackground);
}

void WinState::Exit()
{
	//SGD::AudioManager::GetInstance()->UnloadAudio(m_haBackground);
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_htBackground);
}

bool WinState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	if (pInput->IsAnyKeyPressed() )
	{
		Game::GetInstance()->ClearStates();
		Game::GetInstance()->AddState(CreditState::GetInstance());
	}
	return true;
}

void WinState::Update(float elapsedTime)
{
	Input();
}

void WinState::Render()
{
	SGD::GraphicsManager* pInput = SGD::GraphicsManager::GetInstance();

	BitmapFontManager* pFonts = pFonts->GetInstance();

	float x = Game::GetInstance()->GetScreenWidth() / 1024;
	float y = Game::GetInstance()->GetScreenHeight() / 512;
	//pGraphics->DrawTexture(m_htBackground, { 0, 0 }, {}, {}, {}, { x, y });

	pFonts->Render("Celtic", "You Win", {x, y}, 2, { 255, 255, 255, 255 });
}
