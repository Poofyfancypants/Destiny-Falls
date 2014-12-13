#include "stdafx.h"
#include "InventoryState.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "../Managers/BitmapFontManager.h"
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

	m_hHunterIcon = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/HunterIcon.png");
	m_hFighterIcon = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/FighterIcon.png");
	m_hHealerIcon = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/HealerIcon.png");
	m_hMageIcon = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/MageIcon.png");
	m_hHeroBackground = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/LinkBackground.jpg");
	m_hInventoryBackground = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/InventoryBackground.jpg");

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
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFighterIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hMageIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hHunterIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hHealerIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hInventoryBackground);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hInventoryBackground);
}

bool InventoryState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape) && tabLock == false || pInput->IsButtonDown(0, 6))
		Game::GetInstance()->RemoveState(); //Make this Pause

	if (pInput->IsKeyPressed(SGD::Key::Escape) || pInput->IsButtonDown(0, 6))
		tabLock = false;

	if (pInput->IsKeyPressed(SGD::Key::UpArrow) || pInput->IsDPadUp(0, SGD::DPad::Up))
		tabLock = false;


	if (pInput->IsKeyPressed(SGD::Key::E) || pInput->IsButtonDown(0, 6))
	{
		Game::GetInstance()->RemoveState(); //Make this Pause
	}


	if (pInput->IsKeyPressed(SGD::Key::RightArrow) && tabLock == false || pInput->IsDPadDown(0, SGD::DPad::Right))
	{
		m_ntabCursor++;
		if (m_ntabCursor == -1)
			m_ntabCursor = 3;
		else if (m_ntabCursor == 4)
			m_ntabCursor = 0;


	}

	if (pInput->IsKeyPressed(SGD::Key::LeftArrow) && tabLock == false || pInput->IsDPadDown(0, SGD::DPad::Left))
	{
		m_ntabCursor--;
		if (m_ntabCursor == -1)
			m_ntabCursor = 3;
		else if (m_ntabCursor == 4)
			m_ntabCursor = 0;


	}






	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(tabArmor))
			m_ntabCursor = 0;
		else if (pInput->GetCursorPosition().IsPointInRectangle(TabWeapons))
			m_ntabCursor = 1;
		else if (pInput->GetCursorPosition().IsPointInRectangle(TabRunes))
			m_ntabCursor = 2;
		else if (pInput->GetCursorPosition().IsPointInRectangle(TabCompanions))
			m_ntabCursor = 3;

		tabLock = true;

	}
	if (m_ntabCursor == 0)
	{
		m_bArmorTab = true;
		m_bWeaponsTab = false;
		m_bRunesTab = false;
		m_bCompanionsTab = false;
	}
	else if (m_ntabCursor == 1)
	{
		m_bWeaponsTab = true;
		m_bRunesTab = false;
		m_bArmorTab = false;
		m_bCompanionsTab = false;
	}
	else if (m_ntabCursor == 3)
	{
		m_bCompanionsTab = true;
		m_bRunesTab = false;
		m_bArmorTab = false;
		m_bWeaponsTab = false;
	}
	else if (m_ntabCursor == 2)
	{
		m_bRunesTab = true;
		m_bWeaponsTab = false;
		m_bArmorTab = false;
		m_bCompanionsTab = false;
	}

	if (tabLock == false)
	{
		if (pInput->IsKeyPressed(SGD::Key::Enter))
			tabLock = true;
	}

	if (tabLock)
	{
		if (m_bCompanionsTab)
		{
			if (!OnlyEquipEnter)
			{
				CompanionSelect = 30;
				if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->IsDPadDown(0, SGD::DPad::Left))
					m_nCursor--;
				if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->IsDPadDown(0, SGD::DPad::Right))
					m_nCursor++;

				// loop check
				if (m_nCursor < 0)
					m_nCursor = 2;
				else if (m_nCursor > 2)
					m_nCursor = 0;
			}

			if (pInput->IsKeyPressed(SGD::Key::Enter) && !OnlyEquipEnter || pInput->IsKeyPressed(SGD::Key::MouseLeft))
			{
				OnlyEquipEnter = true;
				return true;
			}

			if (OnlyEquipEnter)
			{
				if (CompanionSelect == 30)
					CompanionSelect = 0;

				if (CompanionSelect == -1)
					CompanionSelect = 3;
				if (CompanionSelect == 4)
					CompanionSelect = 0;

				if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->IsDPadDown(0, SGD::DPad::Right))
				{
					CompanionSelect++;
				}
				else if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->IsDPadDown(0, SGD::DPad::Left))
				{
					CompanionSelect--;
				}
				if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 2))
				{
					switch (m_nCursor)
					{
					case 0:
						// Add companion to CombatState Selection
						OnlyEquipEnter = false;
						break;
					case 1:
						// Add companion to CombatState Selection
						OnlyEquipEnter = false;
						break;
					case 2:
						// Add companion to CombatState Selection
						OnlyEquipEnter = false;
						break;
					default:
						break;
					}
				}
			}


				if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
				{
					OnlyEquipEnter != OnlyEquipEnter;
					if (pInput->GetCursorPosition().IsPointInRectangle(CompanionTopLeft))
					{
						CompanionSelect = 0;
					}

					if (pInput->GetCursorPosition().IsPointInRectangle(CompanionTopRight))
					{
						CompanionSelect = 1;

					}

					if (pInput->GetCursorPosition().IsPointInRectangle(CompanionBottomLeft))
					{
						CompanionSelect = 2;

					}

					if (pInput->GetCursorPosition().IsPointInRectangle(CompanionBottomRight))
					{
						CompanionSelect = 3;

					}
				}
		}
	}

	if (m_bWeaponsTab)
	{
		if (!pauseSelection)
		{
			equipPos = 30;

			if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->IsDPadDown(0, SGD::DPad::Left))
				m_nCursor--;
			if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->IsDPadDown(0, SGD::DPad::Right))
				m_nCursor++;

			// loop check
			if (m_nCursor < 0)
				m_nCursor = 2;
			else if (m_nCursor > 2)
				m_nCursor = 0;
		}

		if (pInput->IsKeyPressed(SGD::Key::Enter) && !pauseSelection)
		{
			pauseSelection = true;
			return true;
		}

		if (pauseSelection)
		{

			if (equipPos == 30)
				equipPos = 0;

			if (equipPos == 12)
				equipPos = 0;
			else if (equipPos == -1)
				equipPos = 11;

			if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->IsDPadDown(0, SGD::DPad::Right))
			{
				equipPos++;
			}
			else if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->IsDPadDown(0, SGD::DPad::Left))
			{
				equipPos--;
			}
			if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 2))
			{
				switch (m_nCursor)
				{
				case 0:
					AddRunesToSword0fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					break;
				case 1:
					AddRunesToSword1fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					break;
				case 2:
					AddRunesToSword2fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					break;
				default:
					break;
				}
			}
		}

		if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
		{

			if (pInput->GetCursorPosition().IsPointInRectangle(Equip1))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToSword0fromInventory(m_ptSelectedRune);
				}
				else
					AddRunesToInventoryfromSword0();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(Equip2))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToSword1fromInventory(m_ptSelectedRune);
				}
				else
					AddRunesToInventoryfromSword1();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(Equip3))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToSword2fromInventory(m_ptSelectedRune);
				}
				else
					AddRunesToInventoryfromSword2();
			}
		}
	}


	if (m_bArmorTab)
	{
		if (pauseSelection == false && OnlyEquipEnter)
		{
			equipPos = 30;

			/*if (equipPos == 12)
				equipPos = 0;
				else if (equipPos == -1)
				equipPos = 11;
				*/
			if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->IsDPadDown(0, SGD::DPad::Left))
			{
				m_nCursor--;
			}
			if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->IsDPadDown(0, SGD::DPad::Right))
			{
				m_nCursor++;
			}
			// loop check
			if (m_nCursor < 0)
				m_nCursor = 2;
			else if (m_nCursor > 2)
				m_nCursor = 0;

		}

		if (pInput->IsKeyPressed(SGD::Key::Enter) && !pauseSelection || pInput->IsButtonDown(0, 2) && !pauseSelection)
		{
			pauseSelection = true;
			return true;
		}
		if (pauseSelection)
		{
			if (equipPos == 30)
				equipPos = 0;

			if (equipPos == 12)
				equipPos = 0;
			else if (equipPos == -1)
				equipPos = 11;

			if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->IsDPadDown(0, SGD::DPad::Right))
			{
				equipPos++;
			}
			else if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->IsDPadDown(0, SGD::DPad::Left))
			{
				equipPos--;
			}
			if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 2))
			{
				switch (m_nCursor)
				{
				case 0:
					AddRunesToArmor0fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					break;
				case 1:
					AddRunesToArmor1fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					break;
				case 2:
					AddRunesToArmor2fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					break;
				default:
					break;
				}

			}
		}


		if (pInput->IsKeyPressed(SGD::Key::MouseLeft) || pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 2))
		{

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipA1))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToArmor0fromInventory(m_ptSelectedRune);
				}
				else
					AddRunesToInventoryfromArmor0();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipA2))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToArmor1fromInventory(m_ptSelectedRune);
				}
				else
					AddRunesToInventoryfromArmor1();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipA3))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToArmor2fromInventory(m_ptSelectedRune);
				}
				else
					AddRunesToInventoryfromArmor2();
			}
		}
	}


	if (m_bRunesTab)
	{
		if (pauseSelection == false && OnlyEquipEnter == false)
		{
			equipPos = 30;

			if (equipPos == 12)
				equipPos = 0;
			else if (equipPos == -1)
				equipPos = 11;

			if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->IsDPadDown(0, SGD::DPad::Left))
			{
				m_nCursor--;
			}
			if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->IsDPadDown(0, SGD::DPad::Right))
			{
				m_nCursor++;
			}

			// loop check
			if (m_nCursor < 0)
				m_nCursor = 2;
			else if (m_nCursor > 2)
				m_nCursor = 0;

		}

		if (pInput->IsKeyPressed(SGD::Key::Enter) && !pauseSelection || pInput->IsButtonDown(0, 2))
		{
			pauseSelection = true;
			return true;
		}
		if (pauseSelection)
		{
			if (equipPos == 30)
				equipPos = 0;

			if (equipPos == 12)
				equipPos = 0;
			else if (equipPos == -1)
				equipPos = 11;

			if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->IsDPadDown(0, SGD::DPad::Right))
			{
				equipPos++;
			}
			else if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->IsDPadDown(0, SGD::DPad::Left))
			{
				equipPos--;
			}
			if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 2))
			{
				switch (m_nCursor)
				{
				case 0:
					AddRunesToRing0fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					break;
				case 1:
					AddRunesToRing1fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					break;
				case 2:
					AddRunesToRing2fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					break;
				default:
					break;
				}

			}
		}


		if (pInput->IsKeyPressed(SGD::Key::MouseLeft) || pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 2))
		{

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipG1))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToRing0fromInventory(m_ptSelectedRune);
				}
				else
					AddRunesToInventoryfromRing0();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipG2))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToRing1fromInventory(m_ptSelectedRune);
				}
				else
					AddRunesToInventoryfromRing1();
			}

			if (pInput->GetCursorPosition().IsPointInRectangle(EquipG3))
			{
				if (m_ptSelectedRune.GetElement() != None)
				{

					AddRunesToRing2fromInventory(m_ptSelectedRune);
				}
				else
					AddRunesToInventoryfromRing1();
			}
		}
	}


#pragma region click inventory



	if (pInput->IsKeyPressed(SGD::Key::MouseLeft) || pauseSelection || pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonDown(0, 2))
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


		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect1) || equipPos == 0)
		{
			m_ptSelectedRune.SetElement(Fire);
			m_ptSelectedRune.SetTier(1);

		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect2) || equipPos == 4)
		{
			m_ptSelectedRune.SetElement(Fire);
			m_ptSelectedRune.SetTier(2);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect3) || equipPos == 8)
		{
			m_ptSelectedRune.SetElement(Fire);
			m_ptSelectedRune.SetTier(3);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect4) || equipPos == 1)
		{
			m_ptSelectedRune.SetElement(Water);
			m_ptSelectedRune.SetTier(1);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect5) || equipPos == 5)
		{
			m_ptSelectedRune.SetElement(Water);
			m_ptSelectedRune.SetTier(2);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect6) || equipPos == 9)
		{
			m_ptSelectedRune.SetElement(Water);
			m_ptSelectedRune.SetTier(3);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect7) || equipPos == 2)
		{
			m_ptSelectedRune.SetElement(Air);
			m_ptSelectedRune.SetTier(1);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect8) || equipPos == 6)
		{
			m_ptSelectedRune.SetElement(Air);
			m_ptSelectedRune.SetTier(2);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect9) || equipPos == 10)
		{
			m_ptSelectedRune.SetElement(Air);
			m_ptSelectedRune.SetTier(3);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect10) || equipPos == 3)
		{
			m_ptSelectedRune.SetElement(Earth);
			m_ptSelectedRune.SetTier(1);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect11) || equipPos == 7)
		{
			m_ptSelectedRune.SetElement(Earth);
			m_ptSelectedRune.SetTier(2);
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect12) || equipPos == 11)
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
#pragma endregion

#pragma region tooltips
		{
			m_bShowToolTip1 = true;
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
			m_bShowToolTip2 = true;
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
			m_bShowToolTip3 = true;
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
			m_bShowToolTip4 = true;
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
			m_bShowToolTip5 = true;
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
			m_bShowToolTip6 = true;
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
			m_bShowToolTip7 = true;
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
			m_bShowToolTip8 = true;
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
			m_bShowToolTip9 = true;
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
			m_bShowToolTip10 = true;
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
			m_bShowToolTip11 = true;
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
			m_bShowToolTip12 = true;
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
#pragma endregion 

	//leave inventory
	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(GameplayState::GetInstance()->InventoryButton))
		{

			Game::GetInstance()->RemoveState();
		}
	}


	return true;
}

void InventoryState::Update(float elapsedTime)
{
	// - Tutorial timer.
	m_fTimer += elapsedTime;
	if (m_fTimer >= m_fDialogScroll)
	{
		m_nDialogSwap = !m_nDialogSwap;
		m_fTimer = 0;
	}

}

void InventoryState::Render()
{
	GameplayState::GetInstance()->Render();


	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	pGraphics->SetClearColor();

	//Inventory button bottom right of screen
	pGraphics->DrawRectangle(GameplayState::GetInstance()->InventoryButton, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 0, 255, 255, 255 });
	pGraphics->DrawRectangle(tabArmor, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(TabWeapons, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(TabCompanions, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(TabRunes, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
	// Tab Names

	BitmapFontManager * pFonts = pFonts->GetInstance();

	pFonts->Render("Other", Game::GetInstance()->GetString(6, 1).c_str(), SGD::Point(50, 0), 1, SGD::Color{ 255, 0, 0, 0 });
	pFonts->Render("Other", Game::GetInstance()->GetString(6, 2).c_str(), SGD::Point(162, 0), 1, SGD::Color{ 255, 0, 0, 0 });
	pFonts->Render("Other", Game::GetInstance()->GetString(6, 3).c_str(), SGD::Point(274, 0), .9f, SGD::Color{ 255, 0, 0, 0 });
	pFonts->Render("Other", Game::GetInstance()->GetString(6, 4).c_str(), SGD::Point(386, 0), .9f, SGD::Color{ 255, 0, 0, 0 });



	// full inventory rect
	pGraphics->DrawRectangle(Fullrect, SGD::Color{ 255, 0, 200, 100 }, SGD::Color{ 255, 0, 0, 0 });

	if (m_bWeaponsTab == false && m_bArmorTab == false && m_bRunesTab == false)
	{
		
	}

#pragma region SwordSlots
	if (m_bWeaponsTab)
	{


		m_bArmorTab = false;
		m_bRunesTab = false;
		m_bCompanionsTab = false;

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
		pFonts->Render("InventoryFont", "Tier 1", SGD::Point(200, 175), 1, SGD::Color{ 255, 0, 0, 0 });
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
		pFonts->Render("InventoryFont", "Tier 2", SGD::Point(300, 175), 1, SGD::Color{ 255, 0, 0, 0 });


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
		pFonts->Render("InventoryFont", "Tier 3", SGD::Point(400, 175), 1, SGD::Color{ 255, 0, 0, 0 });

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

		if (m_nCursor == 0)
		{
			pGraphics->DrawRectangle(rect1, SGD::Color(0, 255, 0, 0), SGD::Color(255, 200, 0, 0));
		}
		else if (m_nCursor == 1)
		{
			pGraphics->DrawRectangle(rect2, SGD::Color(0, 255, 0, 0), SGD::Color(255, 200, 0, 0));
		}
		else if (m_nCursor == 2)
		{
			pGraphics->DrawRectangle(rect3, SGD::Color(0, 255, 0, 0), SGD::Color(255, 200, 0, 0));
		}
	}
	else
		m_bWeaponsTab = false;
#pragma endregion

	if (m_bCompanionsTab)
	{

		pGraphics->DrawRectangle(ImageRect, SGD::Color{ 255, 0, 100, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawTexture(m_hHeroBackground, SGD::Point(55, 100), {}, {}, {}, { 0.5f, 0.5f });
		pGraphics->DrawTexture(m_hHero, SGD::Point(55, 100), {}, {}, {}, { 0.5f, 0.5f });

		pGraphics->DrawRectangle(TabCompanions, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 0 });
		pGraphics->DrawRectangle(CompanionRectSide, SGD::Color(255, 117, 92, 12), SGD::Color(0, 0, 0));

		pGraphics->DrawTexture(m_hInventoryBackground, SGD::Point(200, 50), {}, {}, {}, { .592f, 1.37f });
		pGraphics->DrawTexture(m_hFighterIcon, SGD::Point(210, 70), {}, {}, {}, { .25f, .25f });
		pGraphics->DrawTexture(m_hHealerIcon, SGD::Point(355, 70), {}, {}, {}, { .28f, .28f });

		pGraphics->DrawTexture(m_hHunterIcon, SGD::Point(180, 235), {}, {}, {}, { .33f, .33f });
		pGraphics->DrawTexture(m_hMageIcon, SGD::Point(345, 235), {}, {}, {}, { .31f, .33f });



		if (CompanionSelect == 0)
		{
			pGraphics->DrawRectangle(CompanionTopLeft, { 0, 1, 1, 1 }, SGD::Color{ 255, 0, 255, 0 });
			pFonts->Render("Other", "Tank", SGD::Point(210, 51), 1, SGD::Color{ 255, 0, 255, 0 });
		}
		else
			pFonts->Render("Other", "Tank", SGD::Point(210, 51), 1, SGD::Color{ 255, 255, 255, 255 });

		if (CompanionSelect == 1)
		{
			pGraphics->DrawRectangle(CompanionTopRight, { 0, 1, 1, 1 }, SGD::Color{ 255, 0, 255, 0 });
			pFonts->Render("Other", "Healer", SGD::Point(365, 51), 1, SGD::Color{ 255, 0, 255, 0 });
		}
		else
			pFonts->Render("Other", "Healer", SGD::Point(365, 51), 1, SGD::Color{ 255, 255, 255, 255 });

		if (CompanionSelect == 2)
		{
			pGraphics->DrawRectangle(CompanionBottomLeft, { 0, 1, 1, 1 }, SGD::Color{ 255, 0, 255, 0 });
			pFonts->Render("Other", "Fighter", SGD::Point(210, 226), 1, SGD::Color{ 255, 0, 255, 0 });
		}
		else
			pFonts->Render("Other", "Fighter", SGD::Point(210, 226), 1, SGD::Color{ 255, 255, 255, 255 });

		if (CompanionSelect == 3)
		{
			pGraphics->DrawRectangle(CompanionBottomRight, { 0, 1, 1, 1 }, SGD::Color{ 255, 0, 255, 0 });
			pFonts->Render("Other", "Mage", SGD::Point(375, 226), 1, SGD::Color{ 255, 0, 255, 0 });
		}
		else
			pFonts->Render("Other", "Mage", SGD::Point(375, 226), 1, SGD::Color{ 255, 255, 255, 255 });





	}

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

		pFonts->Render("InventoryFont", "Tier 1", SGD::Point(200, 175), 1, SGD::Color{ 255, 0, 0, 0 });

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
		pFonts->Render("InventoryFont", "Tier 2", SGD::Point(300, 175), 1, SGD::Color{ 255, 0, 0, 0 });



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
		pFonts->Render("InventoryFont", "Tier 3", SGD::Point(400, 175), 1, SGD::Color{ 255, 0, 0, 0 });

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

		if (m_nCursor == 0)
		{
			pGraphics->DrawRectangle(rect1, SGD::Color(0, 255, 0, 0), SGD::Color(255, 200, 0, 0));
		}
		else if (m_nCursor == 1)
		{
			pGraphics->DrawRectangle(rect2, SGD::Color(0, 255, 0, 0), SGD::Color(255, 200, 0, 0));
		}
		else if (m_nCursor == 2)
		{
			pGraphics->DrawRectangle(rect3, SGD::Color(0, 255, 0, 0), SGD::Color(255, 200, 0, 0));
		}
	}
	else
		m_bArmorTab = false;

#pragma endregion


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
		pFonts->Render("InventoryFont", "Tier 1", SGD::Point(200, 175), 1, SGD::Color{ 255, 0, 0, 0 });

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
		pFonts->Render("InventoryFont", "Tier 2", SGD::Point(300, 175), 1, SGD::Color{ 255, 0, 0, 0 });

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
		pFonts->Render("InventoryFont", "Tier 3", SGD::Point(400, 175), 1, SGD::Color{ 255, 0, 0, 0 });

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
		if (m_nCursor == 0)
		{
			pGraphics->DrawRectangle(rect1, SGD::Color(0, 255, 0, 0), SGD::Color(255, 200, 0, 0));
		}
		else if (m_nCursor == 1)
		{
			pGraphics->DrawRectangle(rect2, SGD::Color(0, 255, 0, 0), SGD::Color(255, 200, 0, 0));
		}
		else if (m_nCursor == 2)
		{
			pGraphics->DrawRectangle(rect3, SGD::Color(0, 255, 0, 0), SGD::Color(255, 200, 0, 0));
		}
	}
	else
		m_bRunesTab = false;
#pragma endregion


#pragma region ToolTips
	if (m_bArmorTab || m_bWeaponsTab || m_bRunesTab)
	{

		if (pauseSelection)
		{
			if (m_bShowToolTip1 || equipPos == 0)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a low level\n Fire Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip2 || equipPos == 5)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a mid level\n Fire Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip3 || equipPos)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a high level\n Fire Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip4 || equipPos == 1)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a low level\n Water Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip5 || equipPos == 6)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a mid level\n Water Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip6 || equipPos == 9)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a high level\n Water Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip7 || equipPos == 3)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a low level\n Air Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip8 || equipPos == 7)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a mid level\n Air Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip9 || equipPos == 10)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a high level\n Air Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip10 || equipPos == 4)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a low level\n Earth Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip11 || equipPos == 8)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a mid level\n Earth Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip12 || equipPos == 11)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pGraphics->DrawString("Gives your weapon\n a high level\n Earth Ability.", SGD::Point(501, 51), SGD::Color{ 255, 0, 0, 0 });
			}
		}
#pragma endregion

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





		//highlight selection
		if (equipPos == 0)
		{
			pGraphics->DrawRectangle(IventoryRect1, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 4)
		{
			pGraphics->DrawRectangle(IventoryRect2, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 8)
		{
			pGraphics->DrawRectangle(IventoryRect3, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 1)
		{
			pGraphics->DrawRectangle(IventoryRect4, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 5)
		{
			pGraphics->DrawRectangle(IventoryRect5, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 9)
		{
			pGraphics->DrawRectangle(IventoryRect6, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 2)
		{
			pGraphics->DrawRectangle(IventoryRect7, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 6)
		{
			pGraphics->DrawRectangle(IventoryRect8, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 10)
		{
			pGraphics->DrawRectangle(IventoryRect9, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 3)
		{
			pGraphics->DrawRectangle(IventoryRect10, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 7)
		{
			pGraphics->DrawRectangle(IventoryRect11, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}
		if (equipPos == 11)
		{
			pGraphics->DrawRectangle(IventoryRect12, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		}


	}


	// - Tutorial
	if (GameplayState::GetInstance()->GetCurrentLevel() == 0)
		HandleTutorial();


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

void InventoryState::HandleTutorial()
{
	BitmapFontManager* pFont = BitmapFontManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	// - Location of the Dialog Box at the bottom of the screen.
	SGD::Rectangle DialogBoxOne;
	SGD::Point portraitPosition;

	DialogBoxOne.left = 25;
	DialogBoxOne.top = Game::GetInstance()->GetScreenHeight() - 125;
	DialogBoxOne.right = Game::GetInstance()->GetScreenWidth() - 25;
	DialogBoxOne.bottom = Game::GetInstance()->GetScreenHeight() - 25;
	SGD::Point TextPositionOne;
	SGD::Point TextPositionTwo;
	TextPositionOne.y = DialogBoxOne.top + 20;
	TextPositionTwo.y = DialogBoxOne.top + 50;

	if (m_nDialogSwap)
	{
		if (Game::GetInstance()->GetIcelandic())
		{
			TextPositionOne.x = DialogBoxOne.left + 90;
			TextPositionTwo.x = DialogBoxOne.left + 180;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 100;
			TextPositionTwo.x = DialogBoxOne.left + 140;
		}

		portraitPosition.x = DialogBoxOne.left - 10;
		portraitPosition.y = DialogBoxOne.top - 30;

		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(GameplayState::GetInstance()->GetPortrait(), portraitPosition);
		pGraphics->DrawTexture(GameplayState::GetInstance()->GetPotionIMG(), SGD::Point(DialogBoxOne.left + 10, DialogBoxOne.top + 20));
		pFont->Render("Dialog", Game::GetInstance()->GetString(8, 4).c_str(), TextPositionOne, 0.7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(8, 5).c_str(), TextPositionTwo, 0.7f, SGD::Color(0, 0, 0));

	}
	else
	{
		if (Game::GetInstance()->GetIcelandic())
		{
			TextPositionOne.x = DialogBoxOne.left + 115;
			TextPositionTwo.x = DialogBoxOne.left + 50;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 150;
			TextPositionTwo.x = DialogBoxOne.left + 130;
		}

		portraitPosition.x = DialogBoxOne.left - 10;
		portraitPosition.y = DialogBoxOne.top - 30;

		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(GameplayState::GetInstance()->GetPortrait(), portraitPosition);

		pFont->Render("Dialog", Game::GetInstance()->GetString(10, 4).c_str(), TextPositionOne, 0.7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(10, 5).c_str(), TextPositionTwo, 0.7f, SGD::Color(0, 0, 0));

	}
}