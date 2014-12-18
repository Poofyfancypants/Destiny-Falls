#include "stdafx.h"
#include "WinState.h"
#include "CreditState.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Player.h"
#include "GameplayState.h"
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

	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	pAudio->PlayAudio(Game::GetInstance()->m_mWinMusic, false);
}

void WinState::Exit()
{
	//SGD::AudioManager::GetInstance()->UnloadAudio(m_haBackground);
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_htBackground);
}

bool WinState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsKeyPressed(SGD::Key::Escape) || pInput->IsButtonDown(0, 0))
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

	float width = Game::GetInstance()->GetScreenWidth();

	//pGraphics->DrawTexture(m_htBackground, { 0, 0 }, {}, {}, {}, { x, y });

	pFonts->Render("Other", "You Win", { { (width - (10 * 32)) / 2, 250 } }, 2, { 255, 255, 255, 255 });

	pFonts->Render("Other", "You have claimed your revenge", { { (width - (13 * 32)) / 2, 350 } }, 1, { 255, 255, 255, 255 });
	pFonts->Render("Other", "Now all thats left is to rebuild the Moon Lit Isle", { { (width - (14 * 32)) / 2, 375 } }, 1, { 255, 255, 255, 255 });
	pFonts->Render("Other", "But with your powerful allies and the natives of the Isle ", { { (width - (16 * 32)) / 2, 400 } }, 1, { 255, 255, 255, 255 });
	pFonts->Render("Other", "This should not be a challenge for the Champion of the Moon", { { (width - (18 * 32)) / 2, 425 } }, 1, { 255, 255, 255, 255 });
}
