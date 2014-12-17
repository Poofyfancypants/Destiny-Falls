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
	m_hFiret1 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/1411_Turn5_runes1_fire1.png");
	m_hFiret2 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/1411_Turn5_runes1_fire2.png");
	m_hFiret3 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/1411_Turn5_runes1_fire3.png");
	m_hEartht1 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/1411_Turn5_runes1_earth1.png");
	m_hEartht2 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/1411_Turn5_runes1_earth2.png");
	m_hEartht3 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/1411_Turn5_runes1_earth3.png");
	m_hAirt1 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/1411_Turn5_runes1_air1.png");
	m_hAirt2 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/1411_Turn5_runes1_air2.png");
	m_hAirt3 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/1411_Turn5_runes1_air3.png");
	m_hWatert1 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/WaterRunet1.png");
	m_hWatert2 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/WaterRunet2.png");
	m_hWatert3 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/WaterRunet3.png");
	m_hHero = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Hero.png");
	m_hSword = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Sword.png");
	m_hGauntlet = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Gauntlet.jpg");
	m_hArmor = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Armor.png");

	m_hArmorBackground = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/ArmorInventory.jpg");
	m_hWeaponBackground = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/WeaponInventory.jpg");
	m_hQtImage = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/QuickTime.png");

	m_hHunterIcon = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/HunterIcon.png");
	m_hFighterIcon = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/FighterIcon.png");
	m_hHealerIcon = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/HealerIcon.png");
	m_hMageIcon = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/MageIcon.png");
	m_hHeroBackground = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/LinkBackground.jpg");
	m_hInventoryBackground = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/InventoryBackground.jpg");

	m_vSword.resize(3);
	m_vRing.resize(3);
	m_vArmor.resize(3);
	//m_vCompanion.resize(2);


}

void InventoryState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret1);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret2);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret3);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hWatert1);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hWatert2);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hWatert3);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hEartht1);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hEartht2);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hEartht3);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hAirt1);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hAirt2);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hAirt3);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hHero);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hSword);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hGauntlet);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hArmor);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFighterIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hMageIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hHunterIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hHealerIcon);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hInventoryBackground);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hHeroBackground);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hArmorBackground);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hWeaponBackground);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hQtImage);


}

bool InventoryState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape) && tabLock == false || pInput->IsButtonPressed(0, 6) && m_fArcadeTimer >= 0.5f)
	{
		Game::GetInstance()->RemoveState(); //Make this Pause
		m_fArcadeTimer = 0.0f;
	}

	if (pInput->IsKeyPressed(SGD::Key::Escape) || pInput->IsButtonPressed(0, 6) && m_fArcadeTimer >= 0.5f)
	{
		tabLock = false;
		m_fArcadeTimer = 0.0f;
	}

	if (pInput->IsKeyPressed(SGD::Key::UpArrow) || pInput->GetLeftJoystick(0).y == -1)
	{
		tabLock = false;
		m_fArcadeTimer = 0.0f;
	}

	if (pInput->IsKeyPressed(SGD::Key::E) || pInput->IsKeyPressed(SGD::Key::MouseRight) || pInput->IsButtonPressed(0, 3))
	{
		Game::GetInstance()->RemoveState(); //Make this Pause
	}

	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(QTinfoButton))
			Qt = !Qt;
	}
	if (m_fArcadeTimer >= 0.5f)
	{
		if (pInput->IsKeyPressed(SGD::Key::RightArrow) && tabLock == false || pInput->GetLeftJoystick(0).x == 1 && tabLock == false)
		{
			m_ntabCursor++;
			if (m_ntabCursor == -1)
				m_ntabCursor = 3;
			else if (m_ntabCursor == 4)
				m_ntabCursor = 0;

			m_fArcadeTimer = 0.0f;
		}

		if (pInput->IsKeyPressed(SGD::Key::LeftArrow) && tabLock == false || pInput->GetLeftJoystick(0).x == -1 && tabLock == false)
		{
			m_ntabCursor--;
			if (m_ntabCursor == -1)
				m_ntabCursor = 3;
			else if (m_ntabCursor == 4)
				m_ntabCursor = 0;

			m_fArcadeTimer = 0.0f;
		}
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
		if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
		{
			tabLock = true;
			m_fArcadeTimer = 0.0f;
		}
	}

	if (tabLock)
	{
		if (m_bCompanionsTab)
		{
			if (!OnlyEquipEnter)
			{
				if (m_fArcadeTimer >= 0.5f)
				{
					if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->GetLeftJoystick(0).x == -1)
					{
						m_nCursor--;
						m_fArcadeTimer = 0.0f;
					}
					if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->GetLeftJoystick(0).x == 1)
					{
						m_nCursor++;
						m_fArcadeTimer = 0.0f;
					}
				}

				// loop check
				if (m_nCursor < 0)
					m_nCursor = 1;
				else if (m_nCursor > 1)
					m_nCursor = 0;
			}
			if (m_fArcadeTimer >= 0.5f)
			{
				if (pInput->IsKeyPressed(SGD::Key::Enter) && !OnlyEquipEnter || pInput->IsKeyPressed(SGD::Key::MouseLeft) || pInput->IsButtonPressed(0, 0))
				{
					OnlyEquipEnter = true;
					m_fArcadeTimer = 0.0f;
					return true;
				}
			}

			if (OnlyEquipEnter)
			{
				if (CompanionSelect == 30)
					CompanionSelect = 0;

				if (CompanionSelect == -1)
					CompanionSelect = 3;
				if (CompanionSelect == 4)
					CompanionSelect = 0;

				if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->GetLeftJoystick(0).x == 1 && m_fArcadeTimer >= 0.5f)
				{
					CompanionSelect++;
					m_fArcadeTimer = 0.0f;
				}
				else if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->GetLeftJoystick(0).x == -1 && m_fArcadeTimer >= 0.5f)
				{
					CompanionSelect--;
					m_fArcadeTimer = 0.0f;
				}
				if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
				{
					switch (m_nCursor)
					{
					case 0:
						// Add companion to CombatState Selection
						//m_vCompanion[0].SetC0Type((Companion::Companion_Type)(CompanionSelect));
						OnlyEquipEnter = false;
						break;
					case 1:
						// Add companion to CombatState Selection
						//m_vCompanion[1].SetC0Type((Companion::Companion_Type)(CompanionSelect));
						CompanionSelect = m_nCursor;
						OnlyEquipEnter = false;
						break;
					default:
						break;
					}
					m_fArcadeTimer = 0.0f;
				}
			}


			if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
			{
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
			if (m_fArcadeTimer >= 1.5)
			{
				if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->GetLeftJoystick(0).x == -1)
				{
					m_nCursor--;
					m_fArcadeTimer = 0.0f;
				}
				if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->GetLeftJoystick(0).x == 1)
				{
					m_nCursor++;
					m_fArcadeTimer = 0.0f;
				}
			}

			// loop check
			if (m_nCursor < 0)
				m_nCursor = 2;
			else if (m_nCursor > 2)
				m_nCursor = 0;
		}
		if (m_fArcadeTimer >= 0.5f)
		{
			if (pInput->IsKeyPressed(SGD::Key::Enter) && !pauseSelection || pInput->IsButtonPressed(0, 0) && !pauseSelection)
			{
				pauseSelection = true;
				m_fArcadeTimer = 0.0f;
				return true;
			}
		}

		if (pauseSelection)
		{

			if (equipPos == 30)
				equipPos = 0;

			if (equipPos == 12)
				equipPos = 0;
			else if (equipPos == -1)
				equipPos = 11;

			if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->GetLeftJoystick(0).x == 1 && m_fArcadeTimer >= 0.25f)
			{
				equipPos++;
				m_fArcadeTimer = 0.0f;
			}
			else if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->GetLeftJoystick(0).x == -1 && m_fArcadeTimer >= 0.25f)
			{
				equipPos--;
				m_fArcadeTimer = 0.0f;
			}
			if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
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
				m_fArcadeTimer = 0.0f;
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
		if (!pauseSelection)
		{
			equipPos = 30;

			if (m_fArcadeTimer >= 0.5f)
			{
				if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->GetLeftJoystick(0).x == -1)
				{
					m_nCursor--;
					m_fArcadeTimer = 0.0f;
				}
				if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->GetLeftJoystick(0).x == 1)
				{
					m_nCursor++;
					m_fArcadeTimer = 0.0f;
				}
			}
			// loop check
			if (m_nCursor < 0)
				m_nCursor = 2;
			else if (m_nCursor > 2)
				m_nCursor = 0;

		}
		if (m_fArcadeTimer >= 0.5f)
		{
			if (pInput->IsKeyPressed(SGD::Key::Enter) && !pauseSelection || pInput->IsButtonPressed(0, 0) && !pauseSelection)
			{
				pauseSelection = true;
				m_fArcadeTimer = 0.0f;
				return true;
			}
		}

		if (pauseSelection)
		{
			if (equipPos == 30)
				equipPos = 0;

			if (equipPos == 12)
				equipPos = 0;
			else if (equipPos == -1)
				equipPos = 11;
			if (m_fArcadeTimer >= .25f)
			{
				if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->GetLeftJoystick(0).x == 1)
				{
					equipPos++;
					m_fArcadeTimer = 0.0f;
				}
				else if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->GetLeftJoystick(0).x == -1)
				{
					equipPos--;
					m_fArcadeTimer = 0.0f;
				}
			}

			if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
			{
				switch (m_nCursor)
				{
				case 0:
					AddRunesToArmor0fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					m_fArcadeTimer = 0.0f;

					break;
				case 1:
					AddRunesToArmor1fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					m_fArcadeTimer = 0.0f;

					break;
				case 2:
					AddRunesToArmor2fromInventory(m_ptSelectedRune);
					pauseSelection = false;
					m_fArcadeTimer = 0.0f;

					break;
				default:
					break;
				}
			}
		}


		if (pInput->IsKeyPressed(SGD::Key::MouseLeft) || pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
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

		if (!pauseSelection)
		{
		equipPos = 30;

			if (m_fArcadeTimer >= 0.5f)
			{
				if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->GetLeftJoystick(0).x == -1)
				{
					m_nCursor--;
					m_fArcadeTimer = 0.0f;
				}
				if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->GetLeftJoystick(0).x == 1)
				{
					m_nCursor++;
					m_fArcadeTimer = 0.0f;
				}
			}

			// loop check
			if (m_nCursor < 0)
				m_nCursor = 2;
			else if (m_nCursor > 2)
				m_nCursor = 0;

		}
		if (m_fArcadeTimer >= 0.5f)
		{
			if (pInput->IsKeyPressed(SGD::Key::Enter) && !pauseSelection || pInput->IsButtonPressed(0, 0))
			{
				pauseSelection = true;
				m_fArcadeTimer = 0.0f;
				return true;
			}
		}

		if (pauseSelection)
		{
			if (equipPos == 30)
				equipPos = 0;

			if (equipPos == 12)
				equipPos = 0;
			else if (equipPos == -1)
				equipPos = 11;
			if (m_fArcadeTimer >= .25f)
			{
				if (pInput->IsKeyPressed(SGD::Key::RightArrow) || pInput->GetLeftJoystick(0).x == 1  )
				{
					equipPos++;
					m_fArcadeTimer = 0.0f;
				}
				else if (pInput->IsKeyPressed(SGD::Key::LeftArrow) || pInput->GetLeftJoystick(0).x == -1 )
				{
					equipPos--;
					m_fArcadeTimer = 0.0f;
				}
			}

			if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
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

				m_fArcadeTimer = 0.0f;
			}
		}


		if (pInput->IsKeyPressed(SGD::Key::MouseLeft) || pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
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



	if (pInput->IsKeyPressed(SGD::Key::MouseLeft) || pauseSelection || pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
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
	m_fArcadeTimer += elapsedTime;

	m_fTimer += elapsedTime;
	if (m_fTimer >= m_fDialogScroll)
	{
		m_nDialogSwap = !m_nDialogSwap;
		m_fTimer = 0;
	}

	for (unsigned int i = 0; i < m_vRunes.size(); i++)
	{
		m_vRunes[i].GetElement();
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

	if (m_bCompanionsTab)
	{
		pGraphics->DrawRectangle(TabCompanions, SGD::Color{ 0, 150, 150, 150 }, SGD::Color(255, 200, 92, 12));
		pGraphics->DrawRectangle(CompanionRectSide, SGD::Color(255, 117, 92, 12), SGD::Color(0, 0, 0));

		pFonts->Render("Other", "Tank", SGD::Point(210, 50), 1, SGD::Color{ 255, 0, 0, 0 });
		pFonts->Render("Other", "Cleric", SGD::Point(345, 50), 1, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawTexture(m_hFighterIcon, SGD::Point(210, 70), {}, {}, {}, { .25f, .25f });
		pGraphics->DrawTexture(m_hHealerIcon, SGD::Point(345, 70), {}, {}, {}, { .3f, .28f });

		pFonts->Render("Other", "Fighter", SGD::Point(210, 205), 1, SGD::Color{ 255, 0, 0, 0 });
		pFonts->Render("Other", "Mage", SGD::Point(345, 205), 1, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawTexture(m_hHunterIcon, SGD::Point(180, 225), {}, {}, {}, { .35f, .35f });
		pGraphics->DrawTexture(m_hMageIcon, SGD::Point(330, 225), {}, {}, {}, { .35f, .35f });

		pGraphics->DrawRectangle(ImageRect, SGD::Color{ 255, 0, 100, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawTexture(m_hHeroBackground, SGD::Point(51, 51), {}, {}, {}, { 0.3f, 1.36f });
		pGraphics->DrawTexture(m_hHero, SGD::Point(55, 100), {}, {}, {}, { 0.5f, 0.5f });

		pGraphics->DrawRectangle(TabCompanions, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 0 });
		pGraphics->DrawRectangle(CompanionRectSide, SGD::Color(255, 117, 92, 12), SGD::Color(0, 0, 0));

		pGraphics->DrawTexture(m_hInventoryBackground, SGD::Point(200, 50), {}, {}, {}, { .592f, 1.37f });
		pGraphics->DrawTexture(m_hFighterIcon, SGD::Point(210, 70), {}, {}, {}, { .25f, .25f });
		pGraphics->DrawTexture(m_hHealerIcon, SGD::Point(355, 70), {}, {}, {}, { .28f, .28f });

		pGraphics->DrawTexture(m_hHunterIcon, SGD::Point(180, 235), {}, {}, {}, { .33f, .33f });
		pGraphics->DrawTexture(m_hMageIcon, SGD::Point(345, 235), {}, {}, {}, { .31f, .33f });

		pGraphics->DrawRectangle(Comp1Rect, SGD::Color(100, 255, 255, 255), SGD::Color(0, 0, 0));
		pGraphics->DrawRectangle(Comp2Rect, SGD::Color(100, 255, 255, 255), SGD::Color(0, 0, 0));

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

		// Companion drawing to equip slot

		//if (m_vCompanion[0].GetCoType() != Companion::NonClass)
		//{
		//	pGraphics->DrawTexture(m_hInventoryBackground, SGD::Point(600, 50), {}, {}, {}, { .2f, .4f });
		//
		//	if (m_vCompanion[0].GetCoType() == Companion::Tank)
		//		pGraphics->DrawTexture(m_hFighterIcon, SGD::Point(600, 50), {}, {}, {}, { .18f, .18f });
		//	if (m_vCompanion[0].GetCoType() == Companion::Cleric)
		//		pGraphics->DrawTexture(m_hHealerIcon, SGD::Point(600, 50), {}, {}, {}, { .2f, .2f });
		//	if (m_vCompanion[0].GetCoType() == Companion::Melee)
		//		pGraphics->DrawTexture(m_hHunterIcon, SGD::Point(600, 50), {}, {}, {}, { .2f, .2f });
		//	if (m_vCompanion[0].GetCoType() == Companion::Mage)
		//		pGraphics->DrawTexture(m_hMageIcon, SGD::Point(600, 50), {}, {}, {}, { .2f, .2f });
		//}
		//
		//if (m_vCompanion[1].GetCoType() != Companion::NonClass)
		//{
		//	pGraphics->DrawTexture(m_hInventoryBackground, SGD::Point(700, 50), {}, {}, {}, { .2f, .4f });
		//
		//	if (m_vCompanion[1].GetCoType() == Companion::Tank)
		//		pGraphics->DrawTexture(m_hFighterIcon, SGD::Point(700, 50), {}, {}, {}, { .18f, .18f });
		//	if (m_vCompanion[1].GetCoType() == Companion::Cleric)
		//		pGraphics->DrawTexture(m_hHealerIcon, SGD::Point(700, 50), {}, {}, {}, { .2f, .2f });
		//	if (m_vCompanion[1].GetCoType() == Companion::Melee)
		//		pGraphics->DrawTexture(m_hHunterIcon, SGD::Point(700, 50), {}, {}, {}, { .2f, .2f });
		//	if (m_vCompanion[1].GetCoType() == Companion::Mage)
		//		pGraphics->DrawTexture(m_hMageIcon, SGD::Point(700, 50), {}, {}, {}, { .2f, .2f });
		//}


		if (m_nCursor == 0 || m_nCursor == 30)
		{
			pGraphics->DrawRectangle(Comp1Rect, SGD::Color(0, 255, 255, 255), SGD::Color(255, 200, 92, 12));
		}

		if (m_nCursor == 1)
		{
			pGraphics->DrawRectangle(Comp2Rect, SGD::Color(0, 255, 255, 255), SGD::Color(255, 200, 92, 12));
		}
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
		pGraphics->DrawTexture(m_hWeaponBackground, SGD::Point(51, 50), {}, {}, {}, { 0.58f, 1.368f });
		pGraphics->DrawTexture(m_hSword, SGD::Point(80, 60), {}, {}, {}, { 0.65f, 0.65f });
		pGraphics->DrawTexture(m_hInventoryBackground, SGD::Point(200, 50), {}, {}, {}, { .592f, 1.37f });

		pGraphics->DrawRectangle(RuneSet1, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });


		// rune squares in the inventory
		pGraphics->DrawRectangle(rect1, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect2, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect3, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect4, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect5, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect6, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });


		//Tier Strings
		pFonts->Render("Other", "Tier 1", SGD::Point(200, 175), 1, SGD::Color{ 255, 0, 0, 0 });

		pGraphics->DrawRectangle(RuneSet2, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pFonts->Render("Other", "Tier 2", SGD::Point(300, 175), 1, SGD::Color{ 255, 0, 0, 0 });

		pGraphics->DrawRectangle(RuneSet3, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pFonts->Render("Other", "Tier 3", SGD::Point(400, 175), 1, SGD::Color{ 255, 0, 0, 0 });
		for (unsigned int i = 0; i < m_vRunes.size(); i++)
		{
			if (m_vSword[0].GetElement() == Fire && m_vRunes[i].GetElement() == Fire)
			{

				if (m_vSword[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hFiret1, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
				else if (m_vSword[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hFiret2, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
				else if (m_vSword[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hFiret3, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[0].GetElement() == Water && m_vRunes[i].GetElement() == Water)
			{

				if (m_vSword[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hWatert1, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
				else if (m_vSword[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hWatert2, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
				else if (m_vSword[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hWatert3, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[0].GetElement() == Air  && m_vRunes[i].GetElement() == Air)
			{

				if (m_vSword[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hAirt1, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
				else if (m_vSword[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hAirt2, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
				else if (m_vSword[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hAirt3, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[0].GetElement() == Earth && m_vRunes[i].GetElement() == Earth)
			{

				if (m_vSword[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hEartht1, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
				else if (m_vSword[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hEartht2, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
				else if (m_vSword[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hEartht3, { Equip1.left, Equip1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[1].GetElement() == Fire && m_vRunes[i].GetElement() == Fire)
			{

				if (m_vSword[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hFiret1, { 320, 70 }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hFiret2, { 320, 70 }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hFiret3, { 320, 70 }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[1].GetElement() == Water && m_vRunes[i].GetElement() == Water)
			{

				if (m_vSword[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hWatert1, { Equip2.left, Equip2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hWatert2, { Equip2.left, Equip2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hWatert3, { Equip2.left, Equip2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[1].GetElement() == Air && m_vRunes[i].GetElement() == Air)
			{

				if (m_vSword[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hAirt1, { Equip2.left, Equip2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hAirt2, { Equip2.left, Equip2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hAirt3, { Equip2.left, Equip2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[1].GetElement() == Earth && m_vRunes[i].GetElement() == Earth)
			{

				if (m_vSword[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hEartht1, { Equip2.left, Equip2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hEartht2, { Equip2.left, Equip2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hEartht3, { Equip2.left, Equip2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[2].GetElement() == Fire && m_vRunes[i].GetElement() == Fire)
			{

				if (m_vSword[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hFiret1, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hFiret2, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hFiret3, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[2].GetElement() == Water && m_vRunes[i].GetElement() == Water)
			{

				if (m_vSword[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hWatert1, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hWatert2, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hWatert3, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[2].GetElement() == Air&& m_vRunes[i].GetElement() == Air)
			{

				if (m_vSword[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hAirt1, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hAirt2, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hAirt3, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vSword[2].GetElement() == Earth && m_vRunes[i].GetElement() == Earth)
			{

				if (m_vSword[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hEartht1, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hEartht2, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vSword[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hEartht3, { Equip3.left, Equip3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}
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

#pragma region ArmorSlot



	if (m_bArmorTab)
	{

		m_bWeaponsTab = false;
		m_bRunesTab = false;
		//outline armor tab when selected
		pGraphics->DrawRectangle(tabArmor, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 255, 0 });

		pGraphics->DrawRectangle(Fullrect, SGD::Color{ 255, 0, 255, 0 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawTexture(m_hArmorBackground, SGD::Point(51, 50), {}, {}, {}, { 0.288f, 0.682f });
		pGraphics->DrawTexture(m_hArmor, SGD::Point(52, 60), {}, {}, {}, { 0.2f, 0.3f });
		pGraphics->DrawTexture(m_hInventoryBackground, SGD::Point(200, 50), {}, {}, {}, { .592f, 1.37f });
		pGraphics->DrawRectangle(RuneSet1, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });

		// rune squares in the inventory
		pGraphics->DrawRectangle(rect1, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect2, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect3, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect4, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect5, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect6, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });

		//Tier Strings

		pFonts->Render("Other", "Tier 1", SGD::Point(200, 175), 1, SGD::Color{ 255, 0, 0, 0 });

		pGraphics->DrawRectangle(RuneSet2, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pFonts->Render("Other", "Tier 2", SGD::Point(300, 175), 1, SGD::Color{ 255, 0, 0, 0 });

		pGraphics->DrawRectangle(RuneSet3, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pFonts->Render("Other", "Tier 3", SGD::Point(400, 175), 1, SGD::Color{ 255, 0, 0, 0 });

		for (unsigned int i = 0; i < m_vRunes.size(); i++)
		{
			if (m_vArmor[0].GetElement() == Fire && m_vRunes[i].GetElement() == Fire)
			{

				if (m_vArmor[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hFiret1, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hFiret2, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hFiret3, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vArmor[0].GetElement() == Water && m_vRunes[i].GetElement() == Water)
			{

				if (m_vArmor[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hWatert1, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hWatert2, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hWatert3, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vArmor[0].GetElement() == Air && m_vRunes[i].GetElement() == Air)
			{

				if (m_vArmor[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hAirt1, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hAirt2, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hAirt3, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vArmor[0].GetElement() == Earth && m_vRunes[i].GetElement() == Earth)
			{

				if (m_vArmor[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hEartht1, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hEartht2, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hEartht3, { EquipA1.left, EquipA1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}




			if (m_vArmor[1].GetElement() == Fire && m_vRunes[i].GetElement() == Fire)
			{

				if (m_vArmor[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hFiret1, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hFiret2, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hFiret3, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vArmor[1].GetElement() == Water && m_vRunes[i].GetElement() == Water)
			{


				if (m_vArmor[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hWatert1, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hWatert2, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hWatert3, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vArmor[1].GetElement() == Air && m_vRunes[i].GetElement() == Air)
			{

				if (m_vArmor[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hAirt1, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hAirt2, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hAirt3, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vArmor[1].GetElement() == Earth && m_vRunes[i].GetElement() == Earth)
			{

				if (m_vArmor[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hEartht1, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hEartht2, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hEartht3, { EquipA2.left, EquipA2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}




			if (m_vArmor[2].GetElement() == Fire && m_vRunes[i].GetElement() == Fire)
			{

				if (m_vArmor[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hFiret1, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hFiret2, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hFiret3, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vArmor[2].GetElement() == Water && m_vRunes[i].GetElement() == Water)
			{

				if (m_vArmor[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hWatert1, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hWatert2, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hWatert3, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vArmor[2].GetElement() == Air && m_vRunes[i].GetElement() == Air)
			{

				if (m_vArmor[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hAirt1, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hAirt2, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hAirt3, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vArmor[2].GetElement() == Earth && m_vRunes[i].GetElement() == Earth)
			{

				if (m_vArmor[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hEartht1, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hEartht2, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vArmor[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hEartht3, { EquipA3.left, EquipA3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}
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
		pGraphics->DrawTexture(m_hInventoryBackground, SGD::Point(200, 50), {}, {}, {}, { .592f, 1.37f });
		pGraphics->DrawRectangle(RuneSet1, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });

		// rune squares in the inventory
		pGraphics->DrawRectangle(rect1, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect2, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect3, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect4, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect5, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });
		pGraphics->DrawRectangle(rect6, SGD::Color{ 0, 150, 150, 150 }, SGD::Color{ 255, 0, 0, 0 });

		//Tier Strings
		pFonts->Render("Other", "Tier 1", SGD::Point(200, 175), 1, SGD::Color{ 255, 0, 0, 0 });

		pGraphics->DrawRectangle(RuneSet2, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pFonts->Render("Other", "Tier 2", SGD::Point(300, 175), 1, SGD::Color{ 255, 0, 0, 0 });
		//right side line dividers
		pGraphics->DrawRectangle(RuneSet3, SGD::Color{ 255, 200, 200, 200 }, SGD::Color{ 255, 0, 0, 0 });
		pFonts->Render("Other", "Tier 3", SGD::Point(400, 175), 1, SGD::Color{ 255, 0, 0, 0 });
		for (unsigned int i = 0; i < m_vRunes.size(); i++)
		{
			if (m_vRing[0].GetElement() == Fire && m_vRunes[i].GetElement() == Fire)
			{

				if (m_vRing[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hFiret1, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hFiret2, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hFiret3, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[0].GetElement() == Water && m_vRunes[i].GetElement() == Water)
			{

				if (m_vRing[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hWatert1, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hWatert2, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hWatert3, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[0].GetElement() == Air && m_vRunes[i].GetElement() == Air)
			{

				if (m_vRing[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hAirt1, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hAirt2, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hAirt3, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[0].GetElement() == Earth && m_vRunes[i].GetElement() == Earth)
			{

				if (m_vRing[0].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hEartht1, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[0].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hEartht2, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[0].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hEartht3, { EquipG1.left, EquipG1.top }, {}, {}, {}, { 1.0f, 1.0f });
			}


			if (m_vRing[1].GetElement() == Fire && m_vRunes[i].GetElement() == Fire)
			{
				if (m_vRing[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hFiret1, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hFiret2, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hFiret3, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[1].GetElement() == Water && m_vRunes[i].GetElement() == Water)
			{
				if (m_vRing[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hWatert1, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hWatert2, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hWatert3, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[1].GetElement() == Air && m_vRunes[i].GetElement() == Air)
			{
				if (m_vRing[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hAirt1, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hAirt2, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hAirt3, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[1].GetElement() == Earth && m_vRunes[i].GetElement() == Earth)
			{

				if (m_vRing[1].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hEartht1, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[1].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hEartht2, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[1].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hEartht3, { EquipG2.left, EquipG2.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[2].GetElement() == Fire && m_vRunes[i].GetElement() == Fire)
			{

				if (m_vRing[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hFiret1, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hFiret2, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hFiret3, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[2].GetElement() == Water && m_vRunes[i].GetElement() == Water)
			{

				if (m_vRing[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hWatert1, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hWatert2, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hWatert3, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[2].GetElement() == Air && m_vRunes[i].GetElement() == Air)
			{

				if (m_vRing[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hAirt1, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hAirt2, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hAirt3, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}

			if (m_vRing[2].GetElement() == Earth && m_vRunes[i].GetElement() == Earth)
			{

				if (m_vRing[2].GetTier() == 1 && m_vRunes[i].GetTier() == 1)
					pGraphics->DrawTexture(m_hEartht1, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[2].GetTier() == 2 && m_vRunes[i].GetTier() == 2)
					pGraphics->DrawTexture(m_hEartht2, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
				if (m_vRing[2].GetTier() == 3 && m_vRunes[i].GetTier() == 3)
					pGraphics->DrawTexture(m_hEartht3, { EquipG3.left, EquipG3.top }, {}, {}, {}, { 1.0f, 1.0f });
			}
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
				pFonts->Render("Other", "Gives your weapon", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a low level Fire Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip2 || equipPos == 5)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a mid level Fire Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip3 || equipPos)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a high level Fire Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip4 || equipPos == 1)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon ", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a low level Water Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip5 || equipPos == 6)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon ", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a mid level Water Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip6 || equipPos == 9)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon ", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a high level Water Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip7 || equipPos == 3)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a low level Air Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip8 || equipPos == 7)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon ", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a mid level Air Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip9 || equipPos == 10)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a high level Air Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip10 || equipPos == 4)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon ", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a low level Earth Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip11 || equipPos == 8)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a mid level Earth Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
			if (m_bShowToolTip12 || equipPos == 11)
			{
				pGraphics->DrawRectangle(RuneToolRect, SGD::Color{ 255, 250, 250, 250 }, SGD::Color{ 1, 255, 255, 255 });
				pFonts->Render("Other", "Gives your weapon", SGD::Point(501, 51), .75f, SGD::Color{ 255, 0, 0, 0 });
				pFonts->Render("Other", "a high level Earth Ability.", SGD::Point(501, 71), .75f, SGD::Color{ 255, 0, 0, 0 });
			}
		}
#pragma endregion
		for (unsigned int i = 0; i < m_vRunes.size(); i++)
		{
			if (m_vRunes[i].GetElement() == Fire && m_vRunes[i].GetTier() == 1)
			{
				pGraphics->DrawRectangle(IventoryRect1, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hFiret1, { IventoryRect1.left, IventoryRect1.top }, {}, {}, {}, { 0.55f, 0.55f });
			}

			if (m_vRunes[i].GetElement() == Fire && m_vRunes[i].GetTier() == 2)
			{
				pGraphics->DrawRectangle(IventoryRect2, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hFiret2, { IventoryRect2.left, IventoryRect2.top }, {}, {}, {}, { 0.55f, 0.55f });
			}

			if (m_vRunes[i].GetElement() == Fire && m_vRunes[i].GetTier() == 3)
			{
				pGraphics->DrawRectangle(IventoryRect3, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hFiret3, { IventoryRect3.left, IventoryRect3.top }, {}, {}, {}, { 0.55f, 0.55f });
			}
			if (m_vRunes[i].GetElement() == Water && m_vRunes[i].GetTier() == 1)
			{
				pGraphics->DrawRectangle(IventoryRect4, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hWatert1, { IventoryRect4.left, IventoryRect4.top }, {}, {}, {}, { 0.55f, 0.55f });
			}

			if (m_vRunes[i].GetElement() == Water && m_vRunes[i].GetTier() == 2)
			{
				pGraphics->DrawRectangle(IventoryRect5, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hWatert2, { IventoryRect5.left, IventoryRect5.top }, {}, {}, {}, { 0.55f, 0.55f });
			}
			if (m_vRunes[i].GetElement() == Water && m_vRunes[i].GetTier() == 3)
			{
				pGraphics->DrawRectangle(IventoryRect6, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hWatert3, { IventoryRect6.left, IventoryRect6.top }, {}, {}, {}, { 0.55f, 0.55f });
			}
			if (m_vRunes[i].GetElement() == Air && m_vRunes[i].GetTier() == 1)
			{
				pGraphics->DrawRectangle(IventoryRect7, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hAirt1, { IventoryRect7.left, IventoryRect7.top }, {}, {}, {}, { 0.55f, 0.55f });
			}
			if (m_vRunes[i].GetElement() == Air && m_vRunes[i].GetTier() == 2)
			{
				pGraphics->DrawRectangle(IventoryRect8, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hAirt2, { IventoryRect8.left, IventoryRect8.top }, {}, {}, {}, { 0.55f, 0.55f });
			}
			if (m_vRunes[i].GetElement() == Air && m_vRunes[i].GetTier() == 3)
			{
				pGraphics->DrawRectangle(IventoryRect9, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hAirt3, { IventoryRect9.left, IventoryRect9.top }, {}, {}, {}, { 0.55f, 0.55f });
			}
			if (m_vRunes[i].GetElement() == Earth && m_vRunes[i].GetTier() == 1)
			{
				pGraphics->DrawRectangle(IventoryRect10, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hEartht1, { IventoryRect10.left, IventoryRect10.top }, {}, {}, {}, { 0.55f, 0.55f });
			}
			if (m_vRunes[i].GetElement() == Earth && m_vRunes[i].GetTier() == 2)
			{
				pGraphics->DrawRectangle(IventoryRect11, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hEartht2, { IventoryRect11.left, IventoryRect11.top }, {}, {}, {}, { 0.55f, 0.55f });
			}
			if (m_vRunes[i].GetElement() == Earth && m_vRunes[i].GetTier() == 3)
			{
				pGraphics->DrawRectangle(IventoryRect12, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
				pGraphics->DrawTexture(m_hEartht3, { IventoryRect12.left, IventoryRect12.top }, {}, {}, {}, { 0.55f, 0.55f });
			}

		}
		pGraphics->DrawTexture(m_hQtImage, SGD::Point(QTinfoButton.left, QTinfoButton.top), {}, {}, {}, { .5f, .5f });
		if (Qt)
		{
			pGraphics->DrawRectangle(SGD::Rectangle(500, 0, 900, 200), SGD::Color(255, 255, 255), SGD::Color(0, 0, 0));
			pFonts->Render("Other", "QuickTime Information", SGD::Point(600, 5), .75f, SGD::Color(0, 255, 0));
			pFonts->Render("Other", "Melee and Magic abilities are directly affected by QuickTime", SGD::Point(505, 25), 0.4f, SGD::Color(0, 0, 0));
			pFonts->Render("Other", "If You Have Runes Equipped, it Will Lengthen the QuickTime amount", SGD::Point(505, 55), 0.4f, SGD::Color(0, 0, 0));
			pFonts->Render("Other", "Filling all 3 slots per item will give you 9 QuickTime opportunites", SGD::Point(505, 95), 0.4f, SGD::Color(0, 0, 0));
			pFonts->Render("Other", "Failing QuickTime will result in a padded failure.", SGD::Point(505, 125), 0.4f, SGD::Color(0, 0, 0));
			pFonts->Render("Other", "Damage can still be done to the opponent if it is Failed", SGD::Point(505, 155), 0.4f, SGD::Color(0, 0, 0));
			pFonts->Render("Other", "Credit will be Given up to the amound of successful QuickTimes ", SGD::Point(505, 185), 0.4f, SGD::Color(0, 0, 0));
		}
#pragma endregion

		//highlight selection
		if (equipPos == 0)
			pGraphics->DrawRectangle(IventoryRect1, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 4)
			pGraphics->DrawRectangle(IventoryRect2, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 8)
			pGraphics->DrawRectangle(IventoryRect3, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 1)
			pGraphics->DrawRectangle(IventoryRect4, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 5)
			pGraphics->DrawRectangle(IventoryRect5, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 9)
			pGraphics->DrawRectangle(IventoryRect6, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 2)
			pGraphics->DrawRectangle(IventoryRect7, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 6)
			pGraphics->DrawRectangle(IventoryRect8, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 10)
			pGraphics->DrawRectangle(IventoryRect9, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 3)
			pGraphics->DrawRectangle(IventoryRect10, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 7)
			pGraphics->DrawRectangle(IventoryRect11, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
		if (equipPos == 11)
			pGraphics->DrawRectangle(IventoryRect12, SGD::Color(0, 255, 255, 0), SGD::Color(0, 0, 0));
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
	m_vArmor.clear();
	m_vSword.clear();
	m_vRing.clear();
	m_vRunes.clear();
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