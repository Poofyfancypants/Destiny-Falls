#include "stdafx.h"
#include "SaveandLoadState.h"
#include "MainMenuState.h"
#include "PauseMenuState.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Player.h"
#include "../Managers/BitmapFontManager.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include <fstream>
#include "GameplayState.h"


SaveandLoadState* SaveandLoadState::GetInstance()
{
	static SaveandLoadState s_Instance;
	return &s_Instance;
}

void SaveandLoadState::Enter()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

}

void SaveandLoadState::Exit()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();


}

bool SaveandLoadState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		Game::GetInstance()->RemoveState();
	}

	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(saveslot1))
		{
			Save();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(saveslot2))
		{
			Save2();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(saveslot3))
		{
			Save3();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(loadslot1))
		{
			Load();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(loadslot2))
		{
			Load2();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(loadslot3))
		{
			Load3();
		}

	}


	return true;
}

void SaveandLoadState::Update(float elapsedTime)
{
	return;
}

void SaveandLoadState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	pGraphics->SetClearColor();

	pGraphics->DrawTexture(m_hBackground, { 100, 0 }, 0, {}, {}, { 0.5f, 0.5f });

	BitmapFontManager* pFonts = pFonts->GetInstance();
	pFonts->Render("Bernardo", "Save 1", { saveslot1.left, saveslot1.top }, 1, { 255, 225, 0, 0 });
	pFonts->Render("Bernardo", "Save 2", { saveslot2.left, saveslot2.top }, 1, { 255, 225, 0, 0 });
	pFonts->Render("Bernardo", "Save 3", { saveslot3.left, saveslot3.top }, 1, { 255, 225, 0, 0 });		 
	pFonts->Render("Bernardo", "Load 1", { loadslot1.left, loadslot1.top }, 1, { 255, 225, 0, 0 });
	pFonts->Render("Bernardo", "Load 2", { loadslot2.left, loadslot2.top }, 1, { 255, 225, 0, 0 });
	pFonts->Render("Bernardo", "Load 3", { loadslot3.left, loadslot3.top }, 1, { 255, 225, 0, 0 });
	

}

void SaveandLoadState::Save()
{
	fstream fout;
fout.open("resource/Save/Save.txt", ios_base::out | ios_base::binary);

	if (fout.is_open())
	{
		int health = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth();
		float posx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().x;
		float posy = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().y;
		int currLevel = GameplayState::GetInstance()->GetCurrentLevel();

		fout.write((char*)&health, sizeof(int));
		fout.write((char*)&posx, sizeof(float));
		fout.write((char*)&posy, sizeof(float));
		fout.write((char*)&currLevel, sizeof(int));

		fout.close();
	}

}
void SaveandLoadState::Save2()
{
	fstream fout;
	fout.open("resource/Save/Save2.txt", ios_base::out | ios_base::binary);
	if (fout.is_open())
	{
		int health = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth();
		float posx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().x;
		float posy = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().y;
		int currlevel = GameplayState::GetInstance()->GetChangeLevel();

		fout.write((char*)&health, sizeof(int));
		fout.write((char*)&posx, sizeof(float));
		fout.write((char*)&posy, sizeof(float));
		fout.write((char*)&currlevel, sizeof(int));

		fout.close();
	}

}
void SaveandLoadState::Save3()
{
	fstream fout;
	fout.open("resource/Save/Save3.txt", ios_base::out | ios_base::binary);
	if (fout.is_open())
	{
		int health = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth();
		float posx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().x;
		float posy = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().y;
		int currlevel = GameplayState::GetInstance()->GetChangeLevel();

		fout.write((char*)&health, sizeof(int));
		fout.write((char*)&posx, sizeof(float));
		fout.write((char*)&posy, sizeof(float));
		fout.write((char*)&currlevel, sizeof(int));

		fout.close();
	}

}

void SaveandLoadState::Load()
{
	fstream fin;
	fin.open("resource/Save/Save.txt", ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
		int health, currLevel;
		float posx, posy;

		fin.read((char*)&health, sizeof(int));
		fin.read((char*)&posx, sizeof(float));
		fin.read((char*)&posy, sizeof(float));
		fin.read((char*)&currLevel, sizeof(int));

		Game::GetInstance()->RemoveState();
		Game::GetInstance()->AddState(GameplayState::GetInstance());

		GameplayState::GetInstance()->SetLevel(currLevel);
		GameplayState::GetInstance()->LoadNewLevel();

		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetHealth(health);
		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetPosition(SGD::Point{posx, posy});

		fin.close();
	}
}

void SaveandLoadState::Load2()
{
	fstream fin;
	fin.open("resource/Save/Save2.txt", ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
		int health, currLevel;
		float posx, posy;

		fin.read((char*)&health, sizeof(int));
		fin.read((char*)&posx, sizeof(float));
		fin.read((char*)&posy, sizeof(float));
		fin.read((char*)&currLevel, sizeof(int));

		Game::GetInstance()->RemoveState();
		Game::GetInstance()->AddState(GameplayState::GetInstance());


		GameplayState::GetInstance()->SetLevel(currLevel);
		GameplayState::GetInstance()->LoadNewLevel();

		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetHealth(health);
		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetPosition(SGD::Point{ posx, posy });

		fin.close();
	}
}

void SaveandLoadState::Load3()
{
	fstream fin;
	fin.open("resource/Save/Save3.txt", ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
		int health, currLevel;
		float posx, posy;

		fin.read((char*)&health, sizeof(int));
		fin.read((char*)&posx, sizeof(float));
		fin.read((char*)&posy, sizeof(float));
		fin.read((char*)&currLevel, sizeof(int));

		Game::GetInstance()->RemoveState();
		Game::GetInstance()->AddState(GameplayState::GetInstance());


		GameplayState::GetInstance()->SetLevel(currLevel);
		GameplayState::GetInstance()->LoadNewLevel();

		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetHealth(health);
		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetPosition(SGD::Point{ posx, posy });

		fin.close();
	}
}