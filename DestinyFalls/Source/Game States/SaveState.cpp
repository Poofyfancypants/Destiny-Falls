#include "stdafx.h"
#include "SaveState.h"
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
#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"


SaveState* SaveState::GetInstance()
{
	static SaveState s_Instance;
	return &s_Instance;
}

void SaveState::Enter()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	m_hBackground = pGraphics->LoadTexture(L"resource/graphics/MenuBackgrounds/Options.png");
	m_hButton = pGraphics->LoadTexture("resource/graphics/optionsButton.png");
	m_hButtonHighlighted = pGraphics->LoadTexture("resource/graphics/optionHighlighted.png");
	m_hNameFrame = pGraphics->LoadTexture("resource/graphics/MenuBackgrounds/saveScroll.png");

	m_bGetKey = false;
	m_bRename = false;
	LoadNames();
}

void SaveState::Exit()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	pGraphics->UnloadTexture(m_hButton);
	pGraphics->UnloadTexture(m_hButtonHighlighted);
	pGraphics->UnloadTexture(m_hBackground);
	pGraphics->UnloadTexture(m_hNameFrame);
	m_bGetKey = false;
	m_bRename = false;
	SlotName();
}

bool SaveState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape) || pInput->IsButtonPressed(0, 6))
	{
		Game::GetInstance()->RemoveState();
	}

	if (m_bRename)
	{
		if (pInput->GetCursorMovement().x || pInput->GetCursorMovement().y)
		{
			if (pInput->GetCursorPosition().IsPointInRectangle(yesRect))
				m_nRenameCursor = 0;
			else if (pInput->GetCursorPosition().IsPointInRectangle(noRect))
				m_nRenameCursor = 1;
		}
		//Arcade Timer
		if (m_fArcadeTimer >= 1.0f)
		{
			if (pInput->IsKeyPressed(SGD::Key::Left) || pInput->IsKeyPressed(SGD::Key::A) || pInput->GetLeftJoystick(0).x == -1)
			{
				m_nRenameCursor--;
				m_fArcadeTimer = 0.0f;

			}
			if (pInput->IsKeyPressed(SGD::Key::Right) || pInput->IsKeyPressed(SGD::Key::D) || pInput->GetLeftJoystick(0).x == 1)
			{
				m_nRenameCursor++;
				m_fArcadeTimer = 0.0f;
			}

			if (m_nRenameCursor > 1)
				m_nRenameCursor = 0;
			else if (m_nRenameCursor < 0)
				m_nRenameCursor = 1;
		}

		if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsKeyPressed(SGD::Key::MouseLeft) || pInput->IsButtonPressed(0, 0))
		{
			if (m_nRenameCursor == 0)
				m_bGetKey = true;
			else if (m_nRenameCursor == 1)
			{
				m_bGetKey = false;

				switch (m_nCursor)
				{
				case 0:
					Save();
					Game::GetInstance()->RemoveState();
					break;
				case 1:
					Save2();
					Game::GetInstance()->RemoveState();
					break;
				case 2:
					Save3();
					Game::GetInstance()->RemoveState();
					break;
				}
			}
			m_bRename = false;

		}

	}
	else if (m_bGetKey)
	{
		if (pInput->IsAnyKeyPressed())
		{
			if (pInput->IsKeyPressed(SGD::Key::Shift))
				return true;

			switch (m_nCursor)
			{
			case 0:
				if (pInput->IsKeyPressed(SGD::Key::Backspace) && m_sSlot1Name.length() >= 1)
					m_sSlot1Name.pop_back();
				else if (m_sSlot1Name.length() <= 15)
					m_sSlot1Name.push_back((char)pInput->GetAnyCharPressed());
				break;
			case 1:
				if (pInput->IsKeyPressed(SGD::Key::Backspace) && m_sSlot2Name.length() >= 1)
					m_sSlot2Name.pop_back();
				else if (m_sSlot2Name.length() <= 15)
					m_sSlot2Name.push_back((char)pInput->GetAnyCharPressed());
				break;
			case 2:
				if (pInput->IsKeyPressed(SGD::Key::Backspace) && m_sSlot3Name.length() >= 1)
					m_sSlot3Name.pop_back();
				else if (m_sSlot3Name.length() <= 15)
					m_sSlot3Name.push_back((char)pInput->GetAnyCharPressed());
				break;
			case 3:
				break;
			}

			if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsKeyPressed(SGD::Key::MouseLeft) || pInput->IsButtonPressed(0, 0))
			{
				m_bGetKey = false;
				switch (m_nCursor)
				{
				case 0:
					Save();
					Game::GetInstance()->RemoveState();
					break;
				case 1:
					Save2();
					Game::GetInstance()->RemoveState();
					break;
				case 2:
					Save3();
					Game::GetInstance()->RemoveState();
					break;
				}
			}
		}
	}
	else
	{
		if (m_fArcadeTimer >= 1.0f)
		{
			if (pInput->IsKeyPressed(SGD::Key::Escape) || pInput->IsButtonPressed(0, 6))
				Game::GetInstance()->RemoveState();
			m_fArcadeTimer = 0.0f;
		}


		if (pInput->GetCursorMovement().x || pInput->GetCursorMovement().y)
		{
			if (pInput->GetCursorPosition().IsPointInRectangle(saveslot1))
				m_nCursor = 0;
			else if (pInput->GetCursorPosition().IsPointInRectangle(saveslot2))
				m_nCursor = 1;
			else if (pInput->GetCursorPosition().IsPointInRectangle(saveslot3))
				m_nCursor = 2;
			else if (pInput->GetCursorPosition().IsPointInRectangle(exit))
				m_nCursor = 3;
			else
				m_nCursor = -1;
		}
		//if (m_fArcadeTimer >= 1.0f)
		{
			if (pInput->IsKeyPressed(SGD::Key::Left) || pInput->IsKeyPressed(SGD::Key::A) || pInput->GetLeftJoystick(0).x == -1)
			{
				m_nCursor--;
				if (m_nCursor < 0)
					m_nCursor = 3;

				m_fArcadeTimer = 0.0f;
			}
			else if (pInput->IsKeyPressed(SGD::Key::Right) || pInput->IsKeyPressed(SGD::Key::D) || pInput->GetLeftJoystick(0).x == 1)
			{
				m_nCursor++;
				if (m_nCursor > 3)
					m_nCursor = 0;
				m_fArcadeTimer = 0.0f;

			}
			else if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || pInput->GetLeftJoystick(0).y == -1)
			{
				m_nCursor--;
				if (m_nCursor < 0)
					m_nCursor = 3;
				m_fArcadeTimer = 0.0f;

			}
			else if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || pInput->GetLeftJoystick(0).y == 1)
			{
				m_nCursor++;
				if (m_nCursor > 3)
					m_nCursor = 0;
				m_fArcadeTimer = 0.0f;

			}
		}

		if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsKeyPressed(SGD::Key::MouseLeft) || pInput->IsButtonPressed(0, 0))
		{
			if (m_nCursor == 3)
			{
				Game::GetInstance()->RemoveState();
			}
			else if (m_nCursor != -1)
				m_bRename = true;

			m_fArcadeTimer = 0.0f;
		}
	}

	return true;
}

void SaveState::Update(float elapsedTime)
{
	m_fArcadeTimer += elapsedTime;

	return;
}

void SaveState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = pFont->GetInstance();
	SGD::Color textColor = { 239, 208, 162 };

	pGraphics->DrawTexture(Game::GetInstance()->GetLoadingScreenBkGround(), { 0, 0 }, 0, {}, {}, { .78f, 1.2f });
	pGraphics->DrawTexture(Game::GetInstance()->GetGameIcon(), { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f });
	pFont->Render("Other", "Select a Slot to Save", SGD::Point(225, 100), 1.5f, SGD::Color(0, 0, 0));


	pGraphics->DrawTexture(m_hButton, SGD::Point(20, 300));
	pFont->Render("Other", m_sSlot1Name.c_str(), SGD::Point(50, 315), 1, textColor);
	pGraphics->DrawTexture(m_hButton, SGD::Point(525, 300));
	pFont->Render("Other", m_sSlot2Name.c_str(), SGD::Point(555, 315), 1, textColor);
	pGraphics->DrawTexture(m_hButton, SGD::Point(285, 470));
	pFont->Render("Other", m_sSlot3Name.c_str(), SGD::Point(315, 485), 1, textColor);
	pGraphics->DrawTexture(m_hButton, SGD::Point(630, 530), {}, {}, {}, { .5f, 1 });
	pFont->Render("Other", "Exit", SGD::Point(655, 545), 1, textColor);



	switch (m_nCursor)
	{
	case 0:
		pGraphics->DrawTexture(m_hButtonHighlighted, SGD::Point(20, 300));
		pFont->Render("Other", m_sSlot1Name.c_str(), SGD::Point(50, 315), 1, textColor);
		break;
	case 1:
		pGraphics->DrawTexture(m_hButtonHighlighted, SGD::Point(525, 300));
		pFont->Render("Other", m_sSlot2Name.c_str(), SGD::Point(555, 315), 1, textColor);
		break;
	case 2:
		pGraphics->DrawTexture(m_hButtonHighlighted, SGD::Point(285, 470));
		pFont->Render("Other", m_sSlot3Name.c_str(), SGD::Point(315, 485), 1, textColor);
		break;
	case 3:
		pGraphics->DrawTexture(m_hButtonHighlighted, SGD::Point(630, 530), {}, {}, {}, { .5f, 1 });
		pFont->Render("Other", "Exit", SGD::Point(655, 545), 1, textColor);
		break;
	}

	if (m_bRename)
	{

		pGraphics->DrawTexture(m_hNameFrame, SGD::Point(150, 190));
		pFont->Render("Other", "Do you want to rename the slot?", SGD::Point(240, 240), .9f, SGD::Color(0, 0, 0));

		if (m_nRenameCursor == 0)
			pGraphics->DrawTexture(m_hButtonHighlighted, SGD::Point(250, 300), {}, {}, {}, { .5f, 1 });
		else
			pGraphics->DrawTexture(m_hButton, SGD::Point(250, 300), {}, {}, {}, { .5f, 1 });

		if (m_nRenameCursor == 1)
			pGraphics->DrawTexture(m_hButtonHighlighted, SGD::Point(450, 300), {}, {}, {}, { .5f, 1 });
		else
			pGraphics->DrawTexture(m_hButton, SGD::Point(450, 300), {}, {}, {}, { .5f, 1 });

		pFont->Render("Other", "Yes", SGD::Point(285, 315), 1, textColor);
		pFont->Render("Other", "No", SGD::Point(485, 315), 1, textColor);
	}
	if (m_bGetKey)
	{
		switch (m_nCursor)
		{
		case 0:
			pGraphics->DrawTexture(m_hNameFrame, SGD::Point(150, 190));
			pFont->Render("Other", "Name;", SGD::Point(230, 240), 1, SGD::Color(0, 0, 0));
			pFont->Render("Other", m_sSlot1Name.c_str(), SGD::Point(325, 310), 1, SGD::Color(0, 0, 0));
			break;
		case 1:
			pGraphics->DrawTexture(m_hNameFrame, SGD::Point(150, 190));
			pFont->Render("Other", "Name;", SGD::Point(230, 240), 1, SGD::Color(0, 0, 0));
			pFont->Render("Other", m_sSlot2Name.c_str(), SGD::Point(325, 310), 1, SGD::Color(0, 0, 0));
			break;
		case 2:
			pGraphics->DrawTexture(m_hNameFrame, SGD::Point(150, 190));
			pFont->Render("Other", "Name;", SGD::Point(230, 240), 1, SGD::Color(0, 0, 0));
			pFont->Render("Other", m_sSlot3Name.c_str(), SGD::Point(325, 310), 1, SGD::Color(0, 0, 0));
			break;
		}
	}

}

void SaveState::SlotName()
{
	fstream fout;
	fout.open("resource/Save/Names.txt", ios_base::out | ios_base::binary);
	if (fout.is_open())
	{
		int len = m_sSlot1Name.length() + 1;
		fout.write((char*)&len, sizeof(len));
		fout.write(m_sSlot1Name.c_str(), len);

		len = m_sSlot2Name.length() + 1;
		fout.write((char*)&len, sizeof(len));
		fout.write(m_sSlot2Name.c_str(), len);

		len = m_sSlot3Name.length() + 1;
		fout.write((char*)&len, sizeof(len));
		fout.write(m_sSlot3Name.c_str(), len);

		fout.close();
	}

}

void SaveState::LoadNames()
{
	fstream fin;
	fin.open("resource/Save/Names.txt", ios_base::in | ios_base::binary);
	char* name;
	int nameLength;
	if (fin.is_open())
	{

		fin.read((char*)&nameLength, sizeof(int));
		name = new char[nameLength];
		fin.read(name, nameLength);
		m_sSlot1Name = name;
		delete[] name;

		fin.read((char*)&nameLength, sizeof(int));
		name = new char[nameLength];
		fin.read(name, nameLength);
		m_sSlot2Name = name;
		delete[] name;

		fin.read((char*)&nameLength, sizeof(int));
		name = new char[nameLength];
		fin.read(name, nameLength);
		m_sSlot3Name = name;
		delete[] name;

		fin.close();
	}
}

void SaveState::Save()
{
	int health = (int)((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth();
	float posx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().x;
	float posy = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().y;
	int currLevel = GameplayState::GetInstance()->GetCurrentLevel();
	float checkx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetCheckpoint().x;
	float checky = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetCheckpoint().y;

	TiXmlDocument doc;

	TiXmlDeclaration* pDel = new TiXmlDeclaration{ "1.0", "utf-8", "" };

	doc.LinkEndChild(pDel);

	TiXmlElement* pRoot = new TiXmlElement{ "Save1" };

	doc.LinkEndChild(pRoot);

	TiXmlElement* pPlayer = new TiXmlElement{ "player_info" };

	pRoot->LinkEndChild(pPlayer);

	pPlayer->SetAttribute("Health", health);
	pPlayer->SetDoubleAttribute("PosX", posx);
	pPlayer->SetDoubleAttribute("PosY", posy);
	pPlayer->SetAttribute("CurrLevel", currLevel);
	pPlayer->SetDoubleAttribute("CheckpointX", checkx);
	pPlayer->SetDoubleAttribute("CheckpointY", checky);

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vSword.size(); i++)
	{
		TiXmlElement* pSword = new TiXmlElement{ "Sword" };

		pPlayer->LinkEndChild(pSword);

		pSword->SetAttribute("Element", (int)(InventoryState::GetInstance()->m_vSword[i].GetElement()));
		pSword->SetAttribute("Tier", InventoryState::GetInstance()->m_vSword[i].GetTier());
	}

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vArmor.size(); i++)
	{
		TiXmlElement* pArmor = new TiXmlElement{ "Armor" };

		pPlayer->LinkEndChild(pArmor);

		pArmor->SetAttribute("Element", (int)(InventoryState::GetInstance()->m_vArmor[i].GetElement()));
		pArmor->SetAttribute("Tier", InventoryState::GetInstance()->m_vArmor[i].GetTier());
	}

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vRing.size(); i++)
	{
		TiXmlElement* pRing = new TiXmlElement{ "Ring" };

		pPlayer->LinkEndChild(pRing);

		pRing->SetAttribute("Element", (int)(InventoryState::GetInstance()->m_vRing[i].GetElement()));
		pRing->SetAttribute("Tier", InventoryState::GetInstance()->m_vRing[i].GetTier());
	}

	TiXmlElement* pInv = new TiXmlElement{ "Inventory" };
	pPlayer->LinkEndChild(pInv);
	pInv->SetAttribute("Size", InventoryState::GetInstance()->m_vRunes.size());

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vRunes.size(); i++)
	{
		TiXmlElement* pInv1 = new TiXmlElement{ "Rune" };
		pInv->LinkEndChild(pInv1);

		pInv1->SetAttribute("Element", (int)(InventoryState::GetInstance()->m_vRunes[i].GetElement()));
		pInv1->SetAttribute("Tier", InventoryState::GetInstance()->m_vRunes[i].GetTier());
	}


	doc.SaveFile("resource/Save/Save.xml");

}

void SaveState::Save2()
{
	int health = (int)((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth();
	float posx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().x;
	float posy = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().y;
	int currLevel = GameplayState::GetInstance()->GetCurrentLevel();
	float checkx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetCheckpoint().x;
	float checky = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetCheckpoint().y;

	TiXmlDocument doc;

	TiXmlDeclaration* pDel = new TiXmlDeclaration{ "1.0", "utf-8", "" };

	doc.LinkEndChild(pDel);

	TiXmlElement* pRoot = new TiXmlElement{ "Save2" };

	doc.LinkEndChild(pRoot);

	TiXmlElement* pPlayer = new TiXmlElement{ "player_info" };

	pRoot->LinkEndChild(pPlayer);

	pPlayer->SetAttribute("Health", health);
	pPlayer->SetDoubleAttribute("PosX", posx);
	pPlayer->SetDoubleAttribute("PosY", posy);
	pPlayer->SetAttribute("CurrLevel", currLevel);
	pPlayer->SetDoubleAttribute("CheckpointX", checkx);
	pPlayer->SetDoubleAttribute("CheckpointY", checky);

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vSword.size(); i++)
	{
		TiXmlElement* pSword = new TiXmlElement{ "Sword" };

		pPlayer->LinkEndChild(pSword);

		pSword->SetAttribute("Element", InventoryState::GetInstance()->m_vSword[i].GetElement());
		pSword->SetAttribute("Tier", InventoryState::GetInstance()->m_vSword[i].GetTier());
	}

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vArmor.size(); i++)
	{
		TiXmlElement* pArmor = new TiXmlElement{ "Armor" };

		pPlayer->LinkEndChild(pArmor);

		pArmor->SetAttribute("Element", InventoryState::GetInstance()->m_vArmor[i].GetElement());
		pArmor->SetAttribute("Tier", InventoryState::GetInstance()->m_vArmor[i].GetTier());
	}

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vRing.size(); i++)
	{
		TiXmlElement* pRing = new TiXmlElement{ "Ring" };

		pPlayer->LinkEndChild(pRing);

		pRing->SetAttribute("Element", InventoryState::GetInstance()->m_vRing[i].GetElement());
		pRing->SetAttribute("Tier", InventoryState::GetInstance()->m_vRing[i].GetTier());
	}

	TiXmlElement* pInv = new TiXmlElement{ "Inventory" };
	pPlayer->LinkEndChild(pInv);
	pInv->SetAttribute("Size", InventoryState::GetInstance()->m_vRunes.size());

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vRunes.size(); i++)
	{
		TiXmlElement* pInv1 = new TiXmlElement{ "Rune" };
		pInv->LinkEndChild(pInv1);

		pInv1->SetAttribute("Element", InventoryState::GetInstance()->m_vRunes[i].GetElement());
		pInv1->SetAttribute("Tier", InventoryState::GetInstance()->m_vRunes[i].GetTier());
	}


	doc.SaveFile("resource/Save/Save2.xml");

}

void SaveState::Save3()
{
	int health = (int)((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetHealth();
	float posx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().x;
	float posy = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetPosition().y;
	int currLevel = GameplayState::GetInstance()->GetCurrentLevel();
	float checkx = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetCheckpoint().x;
	float checky = ((Player*)(GameplayState::GetInstance()->GetPlayer()))->GetCheckpoint().y;

	TiXmlDocument doc;

	TiXmlDeclaration* pDel = new TiXmlDeclaration{ "1.0", "utf-8", "" };

	doc.LinkEndChild(pDel);

	TiXmlElement* pRoot = new TiXmlElement{ "Save3" };

	doc.LinkEndChild(pRoot);

	TiXmlElement* pPlayer = new TiXmlElement{ "player_info" };

	pRoot->LinkEndChild(pPlayer);

	pPlayer->SetAttribute("Health", health);
	pPlayer->SetDoubleAttribute("PosX", posx);
	pPlayer->SetDoubleAttribute("PosY", posy);
	pPlayer->SetAttribute("CurrLevel", currLevel);
	pPlayer->SetDoubleAttribute("CheckpointX", checkx);
	pPlayer->SetDoubleAttribute("CheckpointY", checky);

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vSword.size(); i++)
	{
		TiXmlElement* pSword = new TiXmlElement{ "Sword" };

		pPlayer->LinkEndChild(pSword);

		pSword->SetAttribute("Element", InventoryState::GetInstance()->m_vSword[i].GetElement());
		pSword->SetAttribute("Tier", InventoryState::GetInstance()->m_vSword[i].GetTier());
	}

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vArmor.size(); i++)
	{
		TiXmlElement* pArmor = new TiXmlElement{ "Armor" };

		pPlayer->LinkEndChild(pArmor);

		pArmor->SetAttribute("Element", InventoryState::GetInstance()->m_vArmor[i].GetElement());
		pArmor->SetAttribute("Tier", InventoryState::GetInstance()->m_vArmor[i].GetTier());
	}

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vRing.size(); i++)
	{
		TiXmlElement* pRing = new TiXmlElement{ "Ring" };

		pPlayer->LinkEndChild(pRing);

		pRing->SetAttribute("Element", InventoryState::GetInstance()->m_vRing[i].GetElement());
		pRing->SetAttribute("Tier", InventoryState::GetInstance()->m_vRing[i].GetTier());
	}

	TiXmlElement* pInv = new TiXmlElement{ "Inventory" };
	pPlayer->LinkEndChild(pInv);
	pInv->SetAttribute("Size", InventoryState::GetInstance()->m_vRunes.size());

	for (unsigned int i = 0; i < InventoryState::GetInstance()->m_vRunes.size(); i++)
	{
		TiXmlElement* pInv1 = new TiXmlElement{ "Rune" };
		pInv->LinkEndChild(pInv1);

		pInv1->SetAttribute("Element", InventoryState::GetInstance()->m_vRunes[i].GetElement());
		pInv1->SetAttribute("Tier", InventoryState::GetInstance()->m_vRunes[i].GetTier());
	}

	doc.SaveFile("resource/Save/Save3.xml");
}



