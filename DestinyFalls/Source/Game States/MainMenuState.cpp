#include "stdafx.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "OptionsState.h"
#include "CreditState.h"
#include "HowToPlayState.h"
#include "SaveandLoadState.h"#include "../Managers/ParticleManager.h"#include "../Managers/TileManager.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../Game States/AnimationTestState.h"
#include "../Bitmap Font/BitmapFont.h"

MainMenuState* MainMenuState::GetInstance()
{
	static MainMenuState s_Instance;
	return &s_Instance;
}

void MainMenuState::Enter()
{
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	//pGraphics->LoadTexture()

	PlayGame = { 50, 50, 100, 80 };
	LoadGame = { 50, 90, 100, 120 };
	Options = { 50, 130, 100, 160 };
	HowToPlay = { 50, 170, 100, 200 };
	Credit = { 50, 210, 100, 240 };
	ExitGame = { 50, 250, 100, 280 };

	TestAnimationSystem = { 300, 150, 350, 200 };

	int nMusic, nEffects, nScreen;
	std::ifstream load;
	load.open("Options.txt");
	if (load.is_open())
	{
		load >> nMusic >> nEffects >> nScreen;
		pAudio->SetMasterVolume(SGD::AudioGroup::Music, nMusic);
		pAudio->SetMasterVolume(SGD::AudioGroup::SoundEffects, nEffects);
		load.close();

		bool windowed;
		if (nScreen != 0)
		{
			windowed = true;
		}
		else
			windowed = false;
		pGraphics->Resize({ Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() }, windowed);
	}


	InventoryState::GetInstance()->m_vSword.resize(3);
	InventoryState::GetInstance()->SetSwordSlot1(None, 0);
	InventoryState::GetInstance()->SetSwordSlot2(None, 0);
	InventoryState::GetInstance()->SetSwordSlot3(None, 0);
	InventoryState::GetInstance()->m_vArmor.resize(3);
	InventoryState::GetInstance()->SetArmorSlot1(None, 0);
	InventoryState::GetInstance()->SetArmorSlot2(None, 0);
	InventoryState::GetInstance()->SetArmorSlot3(None, 0);
	InventoryState::GetInstance()->m_vRing.resize(3);
	InventoryState::GetInstance()->SetRingSlot1(None, 0);
	InventoryState::GetInstance()->SetRingSlot2(None, 0);
	InventoryState::GetInstance()->SetRingSlot3(None, 0);

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
			Game::GetInstance()->AddState(SaveandLoadState::GetInstance());
			break;
		case MenuSelections::options:
			Game::GetInstance()->AddState(OptionsState::GetInstance());
			break;
		case MenuSelections::howToPlay:
			Game::GetInstance()->AddState(HowToPlayState::GetInstance());
			break;
		case MenuSelections::credits:
			Game::GetInstance()->AddState(CreditState::GetInstance());
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

	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(TestAnimationSystem))
		{
			//Game::GetInstance()->RemoveState();
			Game::GetInstance()->AddState(AnimationTestState::GetInstance());
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
	pGraphics->DrawRectangle(TestAnimationSystem, SGD::Color{ 255, 0, 255, 255 });

	const BitmapFont* pFont = Game::GetInstance()->GetFont();

	//pGraphics->DrawRectangle(PlayGame, SGD::Color{ 255, 255, 0, 255 });
	//pGraphics->DrawRectangle(Options, SGD::Color{ 255, 255, 0, 255 });
	//pGraphics->DrawRectangle(LoadGame, SGD::Color{ 255, 255, 0, 255 });
	//pGraphics->DrawRectangle(HowToPlay, SGD::Color{ 255, 255, 0, 255 });
	//pGraphics->DrawRectangle(Credit, SGD::Color{ 255, 255, 0, 255 });
	//pGraphics->DrawRectangle(ExitGame, SGD::Color{ 255, 255, 0, 255 });

	pFont->Draw(Game::GetInstance()->GetString(0,1).c_str(), { PlayGame.left, PlayGame.top }, 1, { 255, 225, 255, 255 });
	pFont->Draw(Game::GetInstance()->GetString(0,2).c_str(), { LoadGame.left, LoadGame.top }, 1, { 255, 225, 255, 255 });
	pFont->Draw(Game::GetInstance()->GetString(0,3).c_str(), { Options.left, Options.top }, 1, { 255, 225, 255, 255 });
	pFont->Draw(Game::GetInstance()->GetString(0,4).c_str(), { HowToPlay.left, HowToPlay.top }, 1, { 255, 225, 255, 255 });
	pFont->Draw(Game::GetInstance()->GetString(0,5).c_str(), { Credit.left, Credit.top }, 1, { 255, 225, 255, 255 });
	pFont->Draw(Game::GetInstance()->GetString(0,6).c_str(), { ExitGame.left, ExitGame.top }, 1, { 255, 225, 255, 255 });


	pGraphics->DrawRectangle(SGD::Rectangle{ 40, (float)(40 * m_nCursor + 60), 50, (float)(40 * m_nCursor + 70) }, SGD::Color{ 255, 0, 255, 0 });
}