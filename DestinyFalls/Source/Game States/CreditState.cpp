#include "stdafx.h"
#include "CreditState.h"
#include "../Game Objects/Player.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_String.h"

CreditState* CreditState::GetInstance()
{
	static CreditState s_Instance;
	return &s_Instance;
}

void CreditState::Enter()
{
	//m_hMusic = SGD::AudioManager::GetInstance()->LoadAudio(L"");
	//m_htBackground = SGD::AudioManager::GetInstance()->LoadAudio(L"");
	//SGD::AudioManager::GetInstance()->PlayAudio(m_haBackground);

	m_particle.ReadXML("resource/XML/Test2.xml");

}

void CreditState::Exit()
{
	SGD::AudioManager::GetInstance()->UnloadAudio(m_haBackground);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_htBackground);
}

bool CreditState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	if (pInput->IsKeyPressed(SGD::Key::Escape) /*|| Timer <= 0.0f*/)
	{

		Game::GetInstance()->RemoveState();
	}
	return true;
}

void CreditState::Update(float elapsedTime)
{
	//varHeight += 50.0f * elapsedTime;
	Timer -= 1 * elapsedTime;
}

void CreditState::Render()
{
	SGD::GraphicsManager* pInput = SGD::GraphicsManager::GetInstance();

	float x = Game::GetInstance()->GetScreenWidth() / 1024;
	float y = Game::GetInstance()->GetScreenHeight() / 512;
	//pGraphics->DrawTexture(m_htBackground, { 0, 0 }, {}, {}, {}, { x, y });

	SGD::GraphicsManager::GetInstance()->DrawString("John OLeske\n\nSean Hathaway\n\nCaris Frazier\n\n Gregory Bey\n\n", { 100, 100 }, { 255, 255, 255 });
	SGD::GraphicsManager::GetInstance()->DrawString("esc to Exit", { 690, 575 }, { 255, 255, 255 });

	m_particle.Render();

}