#include "stdafx.h"
#include "InventoryState.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"


InventoryState* InventoryState::GetInstance()
{
	static InventoryState s_Instance;
	return &s_Instance;
}

void InventoryState::Enter()
{
	m_hFiret1 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Firet1.png");
	m_hFiret2 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Firet2.png");
	m_hFiret3 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Firet3.png");
	m_hHero = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Hero.png");
	m_hSword = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Sword.png");
	m_hGauntlet = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Gauntlet.jpg");
	m_hArmor = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Armor.png");

	/*if (m_bfirstEnter)
	{



	m_vArmor.resize(3);
	m_vArmor[0].SetElement(None);
	m_vArmor[0].SetTier(0);
	m_vArmor[1].SetElement(None);
	m_vArmor[1].SetTier(0);
	m_vArmor[2].SetElement(None);
	m_vArmor[2].SetTier(0);
	m_vRing.resize(3);

	m_vRing[0].SetElement(None);
	m_vRing[0].SetTier(0);
	m_vRing[1].SetElement(None);
	m_vRing[1].SetTier(0);
	m_vRing[2].SetElement(None);
	m_vRing[2].SetTier(0);


	Game::GetInstance()->RemoveState();
	}

	m_bfirstEnter = false;*/



	/*delete temp;
	delete temp1;
	delete temp2;
	delete temp3;
	delete temp4;
	delete temp5;
	delete temp6;
	delete temp7;
	delete temp8;*/

	m_vSword.resize(3);
	m_vRing.resize(3);
	m_vArmor.resize(3);
}

void InventoryState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret1);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret2);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret3);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hHero);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hSword);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hGauntlet);

	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hArmor);

	

}

bool InventoryState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
		Game::GetInstance()->RemoveState(); //Make this Pause

	if (pInput->IsKeyPressed(SGD::Key::E))
	{
		m_bArmorTab = true;
		Game::GetInstance()->RemoveState(); //Make this Pause
	}

	// Check tab Selection
	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(tabArmor))
		{
			m_bArmorTab = !m_bArmorTab;
			m_bWeaponsTab = false;
			m_bRunesTab = false;
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(TabWeapons))
		{
			m_bWeaponsTab = !m_bWeaponsTab;
			m_bRunesTab = false;
			m_bArmorTab = false;


		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(TabCompanions))
		{
			m_bCompanionsTab = !m_bCompanionsTab;
			m_bRunesTab = false;
			m_bArmorTab = false;
			m_bWeaponsTab = false;
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(TabRunes))
		{
			m_bRunesTab = !m_bRunesTab;
			m_bWeaponsTab = false;
			m_bArmorTab = false;
		}
	}

	if (m_bWeaponsTab)
	{
		if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
		{

			if (pInput->GetCursorPosition().IsPointInRectangle(Equip1))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToSword0fromInventory(m_ptSelectedRune);
					//m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromSword0();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(Equip2))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToSword1fromInventory(m_ptSelectedRune);
					//	m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromSword1();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(Equip3))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToSword2fromInventory(m_ptSelectedRune);
					//	m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromSword2();
			}
		}
	}

	if (m_bArmorTab)
	{
		if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
		{

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipA1))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToArmor0fromInventory(m_ptSelectedRune);
					//	m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromArmor0();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipA2))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToArmor1fromInventory(m_ptSelectedRune);
					//	m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromArmor1();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipA3))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToArmor2fromInventory(m_ptSelectedRune);
					//	m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromArmor2();
			}
		}
	}


	if (m_bRunesTab)
	{


		if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
		{

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipG1))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToRing0fromInventory(m_ptSelectedRune);
					//	m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromRing0();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipG2))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToRing1fromInventory(m_ptSelectedRune);
					//	m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromRing1();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipG3))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToRing2fromInventory(m_ptSelectedRune);
					//m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromRing1();
			}
		}
	}


#pragma region click inventory

	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		m_bShowToolTip1 = false;
		m_bShowToolTip2 = false;
		m_bShowToolTip3 = false;
		m_bShowToolTip4 = false;
		m_bShowToolTip5 = false;
		m_bShowToolTip6 = false;
		m_bShowToolTip7 = false;
		m_bShowToolTip8 = false;
		m_bShowToolTip9 = false;
		m_bShowToolTip10 = false;
		m_bShowToolTip11 = false;
		m_bShowToolTip12 = false;

		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect1))
		{
			m_ptSelectedRune.SetElement(Fire);
			m_ptSelectedRune.SetTier(1);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect2))
		{
			m_ptSelectedRune.SetElement(Fire);
			m_ptSelectedRune.SetTier(2);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect3))
		{
			m_ptSelectedRune.SetElement(Fire);
			m_ptSelectedRune.SetTier(3);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect4))
		{
			m_ptSelectedRune.SetElement(Water);
			m_ptSelectedRune.SetTier(1);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect5))
		{
			m_ptSelectedRune.SetElement(Water);
			m_ptSelectedRune.SetTier(2);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect6))
		{
			m_ptSelectedRune.SetElement(Water);
			m_ptSelectedRune.SetTier(3);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect7))
		{
			m_ptSelectedRune.SetElement(Air);
			m_ptSelectedRune.SetTier(1);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect8))
		{
			m_ptSelectedRune.SetElement(Air);
			m_ptSelectedRune.SetTier(2);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect9))
		{
			m_ptSelectedRune.SetElement(Air);
			m_ptSelectedRune.SetTier(3);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect10))
		{
			m_ptSelectedRune.SetElement(Earth);
			m_ptSelectedRune.SetTier(1);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect11))
		{
			m_ptSelectedRune.SetElement(Earth);
			m_ptSelectedRune.SetTier(2);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect12))
		{
			m_ptSelectedRune.SetElement(Earth);
			m_ptSelectedRune.SetTier(3);
		}
	}
	// remove runes from the equipped slot
	if (pInput->IsKeyPressed(SGD::Key::MouseRight))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(Equip1))
		{
			AddRunesToInventoryfromSword0();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(Equip2))
		{
			AddRunesToInventoryfromSword1();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(Equip3))
		{
			AddRunesToInventoryfromSword2();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(EquipA1))
		{
			AddRunesToInventoryfromArmor0();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(EquipA2))
		{
			AddRunesToInventoryfromArmor1();

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(EquipA3))
		{
			AddRunesToInventoryfromArmor2();

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(EquipG1))
		{
			AddRunesToInventoryfromRing0();
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(EquipG2))
		{
			AddRunesToInventoryfromRing1();

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(EquipG3))
		{
			AddRunesToInventoryfromRing2();

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect1))
		{
			m_bShowToolTip1 = !m_bShowToolTip1;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect2))
		{
			m_bShowToolTip2 = !m_bShowToolTip2;
			m_bShowToolTip1 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect3))
		{
			m_bShowToolTip3 = !m_bShowToolTip3;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect4))
		{
			m_bShowToolTip4 = !m_bShowToolTip4;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect5))
		{
			m_bShowToolTip5 = !m_bShowToolTip5;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect6))
		{
			m_bShowToolTip6 = !m_bShowToolTip6;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect7))
		{
			m_bShowToolTip7 = !m_bShowToolTip7;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect8))
		{
			m_bShowToolTip8 = !m_bShowToolTip8;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect9))
		{
			m_bShowToolTip9 = !m_bShowToolTip9;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect10))
		{
			m_bShowToolTip10 = !m_bShowToolTip10;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip11 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect11))
		{
			m_bShowToolTip11 = !m_bShowToolTip11;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip12 = false;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect12))
		{
			m_bShowToolTip12 = !m_bShowToolTip12;
			m_bShowToolTip1 = false;
			m_bShowToolTip2 = false;
			m_bShowToolTip3 = false;
			m_bShowToolTip4 = false;
			m_bShowToolTip5 = false;
			m_bShowToolTip6 = false;
			m_bShowToolTip7 = false;
			m_bShowToolTip8 = false;
			m_bShowToolTip9 = false;
			m_bShowToolTip10 = false;
			m_bShowToolTip11 = false;
		}
	}
	//leave inventory
	if (pInput->GetCursorPosition().IsPointInRectangle(GameplayState::GetInstance()->InventoryButton))
	{

		Game::GetInstance()->RemoveState();
	}


#pragma endregion



	return true;
}

void InventoryState::Update(float elapsedTime)
{

}

void InventoryState::Render()
{
	//	GameplayState::GetInstance()->Render();

	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	//Inventory button bottom right of screen
	pGraphics->DrawRectangle(GameplayState::GetInstance()->InventoryButton, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 0, 255, 255, 255 });
	pGraphics->DrawRectangle(tabArmor, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(TabWeapons, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(TabCompanions, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(TabRunes, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
	// Tab Names
	pGraphics->DrawString("Armor", SGD::Point(50, 0), SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawString("Sword", SGD::Point(162, 0), SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawString("Gauntlet", SGD::Point(274, 0), SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawString("Companion", SGD::Point(386, 0), SGD::Color{ 255, 0, 0, 0 });

	// full inventory rect
	pGraphics->DrawRectangle(Fullrect, SGD::Color{ 255, 0, 200, 100 }, SGD::Color{ 255, 0, 0, 0 });

	if (m_bWeaponsTab == false && m_bArmorTab == false && m_bRunesTab == false)
	{
		pGraphics->DrawRectangle(ImageRect, SGD::Color{ 255, 0, 100, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawTexture(m_hHero, SGD::Point(55, 100), {}, {}, {}, { 0.5f, 0.5f });
	}

#pragma region SwordSlots
	if (m_bWeaponsTab)
	{
		m_bArmorTab = false;
		m_bRunesTab = false;
		//change tab color when selected
		pGraphics->DrawRectangle(TabWeapons, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 255, 0, 0 });


		//changes color of inv image background
		pGraphics->DrawRectangle(Fullrect, SGD::Color{ 255, 255, 0, 0 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawTexture(m_hSword, SGD::Point(70, 60), {}, {}, {}, { 0.65f, 0.65f });
		pGraphics->DrawRectangle(RuneSet1, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });


		// rune squares in the inventory
		pGraphics->DrawRectangle(rect1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect2, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect3, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect4, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect5, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect6, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });


		//Tier Strings
		pGraphics->DrawString("Tier1", SGD::Point(200, 175), SGD::Color{ 255, 0, 0, 0 });

		if (m_vSword[0].GetElement() == Fire)
		{

			if (m_vSword[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			else if (m_vSword[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			else if (m_vSword[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vSword[0].GetElement() == Water)
		{

			if (m_vSword[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			else if (m_vSword[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			else if (m_vSword[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vSword[0].GetElement() == Air)
		{

			if (m_vSword[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			else if (m_vSword[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			else if (m_vSword[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vSword[0].GetElement() == Earth)
		{

			if (m_vSword[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			else if (m_vSword[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			else if (m_vSword[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}


		pGraphics->DrawRectangle(RuneSet2, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawString("Tier2", SGD::Point(300, 175), SGD::Color{ 255, 0, 0, 0 });


		if (m_vSword[1].GetElement() == Fire)
		{

			if (m_vSword[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vSword[1].GetElement() == Water)
		{

			if (m_vSword[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vSword[1].GetElement() == Air)
		{

			if (m_vSword[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vSword[1].GetElement() == Earth)
		{

			if (m_vSword[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}


		pGraphics->DrawRectangle(RuneSet3, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawString("Tier3", SGD::Point(400, 175), SGD::Color{ 255, 0, 0, 0 });

		if (m_vSword[2].GetElement() == Fire)
		{

			if (m_vSword[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vSword[2].GetElement() == Water)
		{

			if (m_vSword[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vSword[2].GetElement() == Air)
		{

			if (m_vSword[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vSword[2].GetElement() == Earth)
		{

			if (m_vSword[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vSword[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}
	}
	else
		m_bWeaponsTab = false;
#pragma endregion


#pragma region ArmorSlot

	if (m_bArmorTab)
	{

		m_bWeaponsTab = false;
		m_bRunesTab = false;
		//outline armor tab when selected
		pGraphics->DrawRectangle(tabArmor, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 255, 0 });

		pGraphics->DrawRectangle(Fullrect, SGD::Color{ 255, 0, 255, 0 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawTexture(m_hArmor, SGD::Point(52, 60), {}, {}, {}, { 0.2f, 0.3f });
		pGraphics->DrawRectangle(RuneSet1, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });

		// rune squares in the inventory
		pGraphics->DrawRectangle(rect1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect2, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect3, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect4, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect5, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect6, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });

		//Tier Strings
		pGraphics->DrawString("Tier1", SGD::Point(200, 175), SGD::Color{ 255, 0, 0, 0 });

		if (m_vArmor[0].GetElement() == Fire)
		{

			if (m_vArmor[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vArmor[0].GetElement() == Water)
		{

			if (m_vArmor[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vArmor[0].GetElement() == Air)
		{

			if (m_vArmor[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vArmor[0].GetElement() == Earth)
		{

			if (m_vArmor[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}
		pGraphics->DrawRectangle(RuneSet2, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawString("Tier2", SGD::Point(300, 175), SGD::Color{ 255, 0, 0, 0 });



		if (m_vArmor[1].GetElement() == Fire)
		{

			if (m_vArmor[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vArmor[1].GetElement() == Water)
		{


			if (m_vArmor[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vArmor[1].GetElement() == Air)
		{

			if (m_vArmor[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vArmor[1].GetElement() == Earth)
		{

			if (m_vArmor[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}


		pGraphics->DrawRectangle(RuneSet3, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawString("Tier3", SGD::Point(400, 175), SGD::Color{ 255, 0, 0, 0 });

		if (m_vArmor[2].GetElement() == Fire)
		{

			if (m_vArmor[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vArmor[2].GetElement() == Water)
		{

			if (m_vArmor[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vArmor[2].GetElement() == Air)
		{

			if (m_vArmor[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vArmor[2].GetElement() == Earth)
		{

			if (m_vArmor[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vArmor[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}
	}
	else
		m_bArmorTab = false;

#pragma endregion


	//pGraphics->DrawRectangle(rect3, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
#pragma region RingSlot

	if (m_bRunesTab)
	{

		m_bWeaponsTab = false;
		m_bArmorTab = false;
		//outline tab
		pGraphics->DrawRectangle(TabRunes, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 255 });

		pGraphics->DrawRectangle(Fullrect, SGD::Color{ 255, 0, 0, 255 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawTexture(m_hGauntlet, SGD::Point(51, 50), {}, {}, {}, { 0.287f, 0.341f });
		pGraphics->DrawRectangle(RuneSet1, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });

		// rune squares in the inventory
		pGraphics->DrawRectangle(rect1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect2, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect3, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect4, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect5, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect6, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });

		//Tier Strings
		pGraphics->DrawString("Tier1", SGD::Point(200, 175), SGD::Color{ 255, 0, 0, 0 });

		if (m_vRing[0].GetElement() == Fire)
		{

			if (m_vRing[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vRing[0].GetElement() == Water)
		{

			if (m_vRing[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vRing[0].GetElement() == Air)
		{

			if (m_vRing[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vRing[0].GetElement() == Earth)
		{

			if (m_vRing[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 220, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}
		pGraphics->DrawRectangle(RuneSet2, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawString("Tier2", SGD::Point(300, 175), SGD::Color{ 255, 0, 0, 0 });


		if (m_vRing[1].GetElement() == Fire)
		{

			if (m_vRing[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vRing[1].GetElement() == Water)
		{

			if (m_vRing[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vRing[1].GetElement() == Air)
		{

			if (m_vRing[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vRing[1].GetElement() == Earth)
		{

			if (m_vRing[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}


		//right side line dividers
		pGraphics->DrawRectangle(RuneSet3, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawString("Tier3", SGD::Point(400, 175), SGD::Color{ 255, 0, 0, 0 });

		if (m_vRing[2].GetElement() == Fire)
		{

			if (m_vRing[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vRing[2].GetElement() == Water)
		{

			if (m_vRing[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vRing[2].GetElement() == Air)
		{

			if (m_vRing[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}

		if (m_vRing[2].GetElement() == Earth)
		{

			if (m_vRing[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
			if (m_vRing[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 420, 70 }, {}, {}, {}, { 0.2f, 0.18f });
		}
	}
	else
		m_bRunesTab = false;
#pragma endregion
	if (m_bArmorTab || m_bWeaponsTab || m_bRunesTab)
	{
		if (m_bShowToolTip1)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a low level\n Fire Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}
		if (m_bShowToolTip2)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a mid level\n Fire Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip3)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a high level\n Fire Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip4)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a low level\n Water Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip5)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a mid level\n Water Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip6)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a high level\n Water Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip7)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a low level\n Air Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip8)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a mid level\n Air Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip9)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a high level\n Air Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip10)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a low level\n Earth Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip11)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a mid level\n Earth Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}if (m_bShowToolTip12)
		{
			pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
			pGraphics->DrawString("Gives your weapon\n a high level\n Earth Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
		}


		pGraphics->DrawRectangle(IventoryRect1, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret1, { 210, 240 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect2, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret2, { 310, 240 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect3, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret3, { 410, 240 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect4, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret1, { 260, 240 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect5, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret2, { 360, 240 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect6, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret3, { 460, 240 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect7, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret1, { 210, 320 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect8, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret2, { 310, 320 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect9, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret3, { 410, 320 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect10, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret1, { 260, 320 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect11, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret2, { 360, 320 }, {}, {}, {}, { 0.1f, 0.1f });


		pGraphics->DrawRectangle(IventoryRect12, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hFiret3, { 460, 320 }, {}, {}, {}, { 0.1f, 0.1f });
		//sword
		pGraphics->DrawRectangle(Equip1, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(Equip2, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(Equip3, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		//armor
		pGraphics->DrawRectangle(EquipA1, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(EquipA2, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(EquipA3, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		//gauntlet
		pGraphics->DrawRectangle(EquipG1, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(EquipG2, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(EquipG3, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });



	}

}

#pragma region Add
void InventoryState::AddRunesToInventoryfromWorld(Runes _addrune)
{

	m_vRunes.push_back(_addrune);
}


void InventoryState::AddRunesToSword0fromInventory(Runes _addrune)
{

	m_vSword[0].SetElement(_addrune.GetElement());
	m_vSword[0].SetTier(_addrune.GetTier());
}


void InventoryState::AddRunesToSword1fromInventory(Runes _addrune)
{

	m_vSword[1].SetElement(_addrune.GetElement());
	m_vSword[1].SetTier(_addrune.GetTier());
}


void InventoryState::AddRunesToSword2fromInventory(Runes _addrune)
{

	m_vSword[2].SetElement(_addrune.GetElement());
	m_vSword[2].SetTier(_addrune.GetTier());
}


void InventoryState::AddRunesToRing0fromInventory(Runes _addrune)
{

	m_vRing[0].SetElement(_addrune.GetElement());
	m_vRing[0].SetTier(_addrune.GetTier());
}


void InventoryState::AddRunesToRing1fromInventory(Runes _addrune)
{

	m_vRing[1].SetElement(_addrune.GetElement());
	m_vRing[1].SetTier(_addrune.GetTier());
}


void InventoryState::AddRunesToRing2fromInventory(Runes _addrune)
{

	m_vRing[2].SetElement(_addrune.GetElement());
	m_vRing[2].SetTier(_addrune.GetTier());
}


void InventoryState::AddRunesToArmor0fromInventory(Runes _addrune)
{

	m_vArmor[0].SetElement(_addrune.GetElement());
	m_vArmor[0].SetTier(_addrune.GetTier());
}


void InventoryState::AddRunesToArmor1fromInventory(Runes _addrune)
{

	m_vArmor[1].SetElement(_addrune.GetElement());
	m_vArmor[1].SetTier(_addrune.GetTier());
}


void InventoryState::AddRunesToArmor2fromInventory(Runes _addrune)
{

	m_vArmor[2].SetElement(_addrune.GetElement());
	m_vArmor[2].SetTier(_addrune.GetTier());
}

#pragma endregion

#pragma region Remove
void InventoryState::AddRunesToInventoryfromSword0()
{

	m_vSword[0].SetElement(None);
	m_vSword[0].SetTier(0);
}

void InventoryState::AddRunesToInventoryfromSword1()
{

	m_vSword[1].SetElement(None);
	m_vSword[1].SetTier(0);
}

void InventoryState::AddRunesToInventoryfromSword2()
{

	m_vSword[2].SetElement(None);
	m_vSword[2].SetTier(0);
}

void InventoryState::AddRunesToInventoryfromRing0()
{

	m_vRing[0].SetElement(None);
	m_vRing[0].SetTier(0);
}

void InventoryState::AddRunesToInventoryfromRing1()
{

	m_vRing[1].SetElement(None);
	m_vRing[1].SetTier(0);
}

void InventoryState::AddRunesToInventoryfromRing2()
{

	m_vRing[2].SetElement(None);
	m_vRing[2].SetTier(0);
}

void InventoryState::AddRunesToInventoryfromArmor0()
{

	m_vArmor[0].SetElement(None);
	m_vArmor[0].SetTier(0);
}

void InventoryState::AddRunesToInventoryfromArmor1()
{

	m_vArmor[1].SetElement(None);
	m_vArmor[1].SetTier(0);
}

void InventoryState::AddRunesToInventoryfromArmor2()
{

	m_vArmor[2].SetElement(None);
	m_vArmor[2].SetTier(0);
}

#pragma endregion

void InventoryState::ClearInventory()
{

	//for (unsigned int i = 0; i < m_vSword.size(); i++)
	//{
	////	if (m_vSword[i]->GetElement() == 4)
	//	{
	//	delete m_vSword[i];
	//	}
	//}

	//for (unsigned int i = 0; i < m_vArmor.size(); i++)
	//{
	////	if (m_vArmor[i]->GetElement() == 4)
	//		delete m_vArmor[i];
	//}

	//for (unsigned int i = 0; i < m_vRing.size(); i++)
	//{
	//	//if (m_vRing[i]->GetElement() == 4)
	//		delete m_vRing[i];
	//}

	m_vArmor.clear();
	m_vSword.clear();
	m_vRing.clear();

} 