#include "stdafx.h"
#include "SaveandLoadState.h"
#include "MainMenuState.h"
#include "PauseMenuState.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Player.h"
#include "../Bitmap Font/BitmapFont.h"
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
			Game::GetInstance()->RemoveState();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(loadslot2))
		{
			Load2();
			Game::GetInstance()->RemoveState();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(loadslot3))
		{
			Load3();
			Game::GetInstance()->RemoveState();
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

	const BitmapFont* pFont = Game::GetInstance()->GetFont();

	pFont->Draw("Save 1", { saveslot1.left, saveslot1.top }, 1, { 255, 225, 255, 255 });
	pFont->Draw("Save 2", { saveslot2.left, saveslot2.top }, 1, { 255, 225, 255, 255 });
	pFont->Draw("Save 3", { saveslot3.left, saveslot3.top }, 1, { 255, 225, 255, 255 });

	pFont->Draw("Load 1", { loadslot1.left, loadslot1.top }, 1, { 255, 225, 255, 255 });
	pFont->Draw("Load 2", { loadslot2.left, loadslot2.top }, 1, { 255, 225, 255, 255 });
	pFont->Draw("Load 3", { loadslot3.left, loadslot3.top }, 1, { 255, 225, 255, 255 });
	
}

void SaveandLoadState::Save()
{
	fstream fout;
	fout.open("resorce/Save/Save.txt", ios_base::out | ios_base::binary);
	if (fout.is_open())
	{
		int health = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth();
		float posx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().x;
		float posy = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().y;

		fout.write((char*)&health, sizeof(int));
		fout.write((char*)&posx, sizeof(float));
		fout.write((char*)&posy, sizeof(float));

		fout.close();
	}

}
void SaveandLoadState::Save2()
{
	fstream fout;
	fout.open("resorce/Save/Save2.txt", ios_base::out | ios_base::binary);
	if (fout.is_open())
	{
		int health = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth();
		float posx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().x;
		float posy = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().y;

		fout.write((char*)&health, sizeof(int));
		fout.write((char*)&posx, sizeof(float));
		fout.write((char*)&posy, sizeof(float));


		fout.close();
	}

}
void SaveandLoadState::Save3()
{
	fstream fout;
	fout.open("resorce/Save/Save3.txt", ios_base::out | ios_base::binary);
	if (fout.is_open())
	{
		int health = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth();
		float posx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().x;
		float posy = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().y;

		fout.write((char*)&health, sizeof(int));
		fout.write((char*)&posx, sizeof(float));
		fout.write((char*)&posy, sizeof(float));


		fout.close();
	}

}

void SaveandLoadState::Load()
{
	fstream fin;
	fin.open("resorce/Save/Save.txt", ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
		int health;
		float posx, posy;

		fin.write((char*)&health, sizeof(int));
		fin.write((char*)&posx, sizeof(float));
		fin.write((char*)&posy, sizeof(float));

		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetHealth(health);
		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetPosition(SGD::Point{posx, posy});

		fin.close();
	}
}

void SaveandLoadState::Load2()
{
	fstream fin;
	fin.open("resorce/Save/Save2.txt", ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
		int health;
		float posx, posy;

		fin.write((char*)&health, sizeof(int));
		fin.write((char*)&posx, sizeof(float));
		fin.write((char*)&posy, sizeof(float));

		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetHealth(health);
		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetPosition(SGD::Point{ posx, posy });

		fin.close();
	}
}

void SaveandLoadState::Load3()
{
	fstream fin;
	fin.open("resorce/Save/Save3.txt", ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
		int health;
		float posx, posy;

		fin.write((char*)&health, sizeof(int));
		fin.write((char*)&posx, sizeof(float));
		fin.write((char*)&posy, sizeof(float));

		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetHealth(health);
		((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetPosition(SGD::Point{ posx, posy });

		fin.close();
	}
}