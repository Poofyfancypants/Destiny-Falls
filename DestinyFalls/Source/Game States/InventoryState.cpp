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

	m_vSword.resize(3);
	m_vSword[0].SetElement(None);
	m_vSword[0].SetTier(0);
	m_vSword[1].SetElement(None);
	m_vSword[1].SetTier(0);
	m_vSword[2].SetElement(None);
	m_vSword[2].SetTier(0);

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
}

void InventoryState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret1);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret2);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret3);
}

bool InventoryState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
		Game::GetInstance()->RemoveState(); //Make this Pause

	if (pInput->IsKeyPressed(SGD::Key::E))
		Game::GetInstance()->RemoveState(); //Make this Pause


	if (pInput->IsKeyPressed(SGD::Key::MouseRight))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(rect1))
			m_bSwordSelect = !m_bSwordSelect;
		else if (pInput->GetCursorPosition().IsPointInRectangle(rect2))
			m_bArmorSelect = !m_bArmorSelect;
		else if (pInput->GetCursorPosition().IsPointInRectangle(rect3))
			m_bRingSelect = !m_bRingSelect;
	}
	if (m_bSwordSelect)
	{
		if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
		{
			if (pInput->GetCursorPosition().IsPointInRectangle(swordslot1))
			{
				if (m_ptSelectedRune != nullptr)
				{
					AddRunesToSword0fromInventory(*m_ptSelectedRune);
					m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromSword0();
			}
			if (pInput->GetCursorPosition().IsPointInRectangle(swordslot2))
			{
				if (m_ptSelectedRune != nullptr)
				{
					AddRunesToSword1fromInventory(*m_ptSelectedRune);
					m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromSword1();
			}
			if (pInput->GetCursorPosition().IsPointInRectangle(swordslot3))
			{
				if (m_ptSelectedRune != nullptr)
				{
					AddRunesToSword2fromInventory(*m_ptSelectedRune);
					m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromSword2();
			}
		}
	}

	if (m_bArmorSelect)
	{
		if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
		{
			if (pInput->GetCursorPosition().IsPointInRectangle(armorslot1))
			{
				if (m_ptSelectedRune != nullptr)
				{
					AddRunesToArmor0fromInventory(*m_ptSelectedRune);
					m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromArmor0();
			}
			if (pInput->GetCursorPosition().IsPointInRectangle(armorslot2))
			{
				if (m_ptSelectedRune != nullptr)
				{
					AddRunesToArmor1fromInventory(*m_ptSelectedRune);
					m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromArmor1();
			}
			if (pInput->GetCursorPosition().IsPointInRectangle(armorslot3))
			{
				if (m_ptSelectedRune != nullptr)
				{
					AddRunesToArmor2fromInventory(*m_ptSelectedRune);
					m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromArmor2();
			}
		}
	}

	if (m_bRingSelect)
	{
		if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
		{
			if (pInput->GetCursorPosition().IsPointInRectangle(ringslot1))
			{
				if (m_ptSelectedRune != nullptr)
				{
					AddRunesToRing0fromInventory(*m_ptSelectedRune);
					m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromRing0();
			}
			if (pInput->GetCursorPosition().IsPointInRectangle(ringslot2))
			{
				if (m_ptSelectedRune != nullptr)
				{
					AddRunesToRing1fromInventory(*m_ptSelectedRune);
					m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromRing1();
			}
			if (pInput->GetCursorPosition().IsPointInRectangle(ringslot3))
			{
				if (m_ptSelectedRune != nullptr)
				{
					AddRunesToRing2fromInventory(*m_ptSelectedRune);
					m_ptSelectedRune = nullptr;
				}
				else
					AddRunesToInventoryfromRing1();
			}
		}
	}
#pragma region click inventory

	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect1))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Fire);
			m_ptSelectedRune->SetTier(1);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect2))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Fire);
			m_ptSelectedRune->SetTier(2);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect3))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Fire);
			m_ptSelectedRune->SetTier(3);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect4))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Water);
			m_ptSelectedRune->SetTier(1);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect5))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Water);
			m_ptSelectedRune->SetTier(2);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect6))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Water);
			m_ptSelectedRune->SetTier(3);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect7))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Air);
			m_ptSelectedRune->SetTier(1);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect8))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Air);
			m_ptSelectedRune->SetTier(2);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect9))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Air);
			m_ptSelectedRune->SetTier(3);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect10))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Earth);
			m_ptSelectedRune->SetTier(1);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect11))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Earth);
			m_ptSelectedRune->SetTier(2);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect12))
		{
			m_ptSelectedRune = new Runes;
			m_ptSelectedRune->SetElement(Earth);
			m_ptSelectedRune->SetTier(3);
		}
	}
#pragma endregion

	

	return true;
}

void InventoryState::Update(float elapsedTime)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();



}

void InventoryState::Render()
{
	GameplayState::GetInstance()->Render();

	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->DrawRectangle(rect, SGD::Color{ 200, 100, 100, 100 }, SGD::Color{ 255, 255, 255, 255 });

	pGraphics->DrawRectangle(rect1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	if (m_bSwordSelect)
	{
		pGraphics->DrawRectangle(swordslot1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		if (m_vSword[0].GetElement() == Fire)
		{
			if (m_vSword[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 75, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vSword[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 75, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vSword[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 75, 125 }, {}, {}, {}, { 0.17f, 0.10f });
		}
		pGraphics->DrawRectangle(swordslot2, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		if (m_vSword[1].GetElement() == Fire)
		{
			if (m_vSword[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 125, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vSword[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 125, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vSword[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 125, 125 }, {}, {}, {}, { 0.17f, 0.10f });
		}
		pGraphics->DrawRectangle(swordslot3, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		if (m_vSword[2].GetElement() == Fire)
		{
			if (m_vSword[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 175, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vSword[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 175, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vSword[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 175, 125 }, {}, {}, {}, { 0.17f, 0.10f });
		}
	}

	pGraphics->DrawRectangle(rect2, SGD::Color{ 200, 200, 200, 200 }, SGD::Color{ 255, 255, 255, 255 });
	if (m_bArmorSelect)
	{
		pGraphics->DrawRectangle(armorslot1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		if (m_vArmor[0].GetElement() == Fire)
		{
			if (m_vArmor[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 275, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vArmor[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 275, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vArmor[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 275, 125 }, {}, {}, {}, { 0.17f, 0.10f });
		}
		pGraphics->DrawRectangle(armorslot2, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		if (m_vArmor[1].GetElement() == Fire)
		{
			if (m_vArmor[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 325, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vArmor[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 325, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vArmor[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 325, 125 }, {}, {}, {}, { 0.17f, 0.10f });
		}
		pGraphics->DrawRectangle(armorslot3, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		if (m_vArmor[2].GetElement() == Fire)
		{
			if (m_vArmor[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 375, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vArmor[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 375, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vArmor[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 375, 125 }, {}, {}, {}, { 0.17f, 0.10f });
		}
	}

	pGraphics->DrawRectangle(rect3, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	if (m_bRingSelect)
	{
		pGraphics->DrawRectangle(ringslot1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		if (m_vRing[0].GetElement() == Fire)
		{
			if (m_vRing[0].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 475, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vRing[0].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 475, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vRing[0].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 475, 125 }, {}, {}, {}, { 0.17f, 0.10f });
		}
		pGraphics->DrawRectangle(ringslot2, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		if (m_vRing[1].GetElement() == Fire)
		{
			if (m_vRing[1].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 525, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vRing[1].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 525, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vRing[1].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 525, 125 }, {}, {}, {}, { 0.17f, 0.10f });
		}
		pGraphics->DrawRectangle(ringslot3, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		if (m_vRing[2].GetElement() == Fire)
		{
			if (m_vRing[2].GetTier() == 1)
				pGraphics->DrawTexture(m_hFiret1, { 575, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vRing[2].GetTier() == 2)
				pGraphics->DrawTexture(m_hFiret2, { 575, 125 }, {}, {}, {}, { 0.17f, 0.10f });
			if (m_vRing[2].GetTier() == 3)
				pGraphics->DrawTexture(m_hFiret3, { 575, 125 }, {}, {}, {}, { 0.17f, 0.10f });
		}
	}

	pGraphics->DrawRectangle(IventoryRect1, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { 50, 200 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect2, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { 50, 317 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect3, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret3, { 50, 434 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect4, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { 200, 200 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect5, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { 200, 317 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect6, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret3, { 200, 434 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect7, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { 350, 200 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect8, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { 350, 317 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect9, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret3, { 350, 434 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect10, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { 500, 200 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect11, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { 500, 317 }, {}, {}, {}, { 0.5f, 0.25f });

	pGraphics->DrawRectangle(IventoryRect12, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret3, { 500, 434 }, {}, {}, {}, { 0.5f, 0.25f });

}

//Add
void InventoryState::AddRunesToInventoryfromWorld(Runes* _addrune)
{
	m_vRunes.push_back(*_addrune);
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

//Remove
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