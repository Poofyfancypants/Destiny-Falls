#include "stdafx.h"
#include "OptionsState.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_String.h"
#include "../Game Core/Game.h"
#include "GameplayState.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"
#include <fstream>
#include <ostream>

OptionsState* OptionsState::GetInstance()
{
	static OptionsState s_Instance;
	return &s_Instance;
}

void OptionsState::Enter()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	std::ifstream load;
	load.open("Options.txt");
	if (load.is_open())
	{
		load >> m_nMusic >> m_nEffects >> m_nScreen;
		pAudio->SetMasterVolume(SGD::AudioGroup::Music, m_nMusic);
		pAudio->SetMasterVolume(SGD::AudioGroup::SoundEffects, m_nEffects);

		if (m_nScreen != 0)
			m_bWindowed = true;
		else
			m_bWindowed = false;

		load.close();
	}
}

void OptionsState::Exit()
{
	SGD::AudioManager *pAudio = SGD::AudioManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	if (pAudio->GetMasterVolume(SGD::AudioGroup::Music) <= 255 && pAudio->GetMasterVolume(SGD::AudioGroup::Music) >= 0)
		m_nMusic = pAudio->GetMasterVolume(SGD::AudioGroup::Music);

	if (pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects) <= 255 && pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects) >= 0)
		m_nEffects = pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects);

	std::ofstream save;
	save.open("Options.txt");
	if (save.is_open())
		save << m_nMusic << " " << m_nEffects << " " << m_bWindowed;


}

bool OptionsState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
		Game::GetInstance()->RemoveState();

	//If Nothing is selected
	if (m_bSelect == false)
	{
		if (pInput->IsKeyPressed(SGD::Key::Enter) == true)
		{
			m_bSelect = true;
		}
		if (pInput->IsKeyPressed(SGD::Key::Down) == true)
		{
			++m_nCursor;
			if (m_nCursor > 2)
				m_nCursor = 0;
		}
		else if (pInput->IsKeyPressed(SGD::Key::Up) == true)
		{
			--m_nCursor;
			if (m_nCursor < 0)
				m_nCursor = 2;
		}
	}
	//If something is selected
	else
	{
		//Unselect?
		if (pInput->IsKeyPressed(SGD::Key::Enter) == true)
			m_bSelect = false;

		if (m_nCursor == 0) // Music
		{
			if (pInput->IsKeyPressed(SGD::Key::Right) == true)
			{
				pAudio->SetMasterVolume(SGD::AudioGroup::Music, pAudio->GetMasterVolume(SGD::AudioGroup::Music) + 10);
			}
			else if (pInput->IsKeyPressed(SGD::Key::Left) == true)
			{
				pAudio->SetMasterVolume(SGD::AudioGroup::Music, pAudio->GetMasterVolume(SGD::AudioGroup::Music) - 10);
			}
		}
		else if (m_nCursor == 1)	// SFX
		{
			if (pInput->IsKeyPressed(SGD::Key::Right) == true)
			{
				pAudio->SetMasterVolume(SGD::AudioGroup::SoundEffects, pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects) + 10);
				//pAudio->PlayAudio(m_hEffectSound, false);
			}
			else if (pInput->IsKeyPressed(SGD::Key::Left) == true)
			{
				pAudio->SetMasterVolume(SGD::AudioGroup::SoundEffects, pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects) - 10);
				//pAudio->PlayAudio(m_hEffectSound, false);
				//Play a sound effect here
			}
		}
		else if (m_nCursor == 2) //Full Screen toggle
		{
			if (pInput->IsKeyPressed(SGD::Key::Right) == true)
			{
				m_bWindowed = !m_bWindowed;
			}
			else if (pInput->IsKeyPressed(SGD::Key::Left) == true)
			{
				m_bWindowed = !m_bWindowed;
			}

			if (pInput->IsKeyPressed(SGD::Key::Enter))
			{
				SGD::GraphicsManager::GetInstance()->Resize({ Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() }, m_bWindowed);
			}
		}
	}

	return true;
}

void OptionsState::Update(float elapsedTime)
{

}

void OptionsState::Render()
{
	SGD::AudioManager *pAudio = SGD::AudioManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::OStringStream volumes;
	volumes << pAudio->GetMasterVolume(SGD::AudioGroup::Music) / 10 << "\n\n\n"
		<< pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects) / 10 << "\n\n\n"
		<< (m_bWindowed ? "Windowed" : "Fullscreen");

	//pFont->Draw(volumes.str().c_str(), { (width - (4 * 32)), 300 }, 1.0f, { 255, 255, 255, 255 });
	pGraphics->DrawString(volumes.str().c_str(), { (9 * 32) - 2, 302 }, { 255, 0, 0, 0 });
	pGraphics->DrawString(volumes.str().c_str(), { (9 * 32), 300 }, {});

	pGraphics->DrawString("Music Vol", { ((7 * 32) / 2) - 2, 302 }, { 255, 0, 0, 0 });
	pGraphics->DrawString("Music Vol", { (7 * 32) / 2, 300 }, {});

	pGraphics->DrawString("SFX Vol", { ((7 * 32) / 2) - 2, 366 }, { 255, 0, 0, 0 });
	pGraphics->DrawString("SFX Vol", { (7 * 32) / 2, 364 }, {});

	pGraphics->DrawString("Fullscreen", { ((7 * 32) / 2) - 2, 430 }, { 255, 0, 0, 0 });
	pGraphics->DrawString("Fullscreen", { (7 * 32) / 2, 428 }, {});


	int offset;
	if (!m_bSelect)
		offset = 0;
	else
		offset = 200;

	pGraphics->DrawString("			=", { (4 * 32) / 2.0f + offset - 2, (300.0f + 64 * m_nCursor) + 2 }, { 255, 0, 0, 0 });
	pGraphics->DrawString("			=", { (4 * 32) / 2.0f + offset, 300.0f + 64 * m_nCursor }, {});

	//How to Exit
	SGD::GraphicsManager::GetInstance()->DrawString("esc to Exit", { 670, 520 }, { 255, 255, 255 });

	//How to Select
	SGD::GraphicsManager::GetInstance()->DrawString("ENTER to select", { 30, 520 }, { 255, 255, 255 });

}