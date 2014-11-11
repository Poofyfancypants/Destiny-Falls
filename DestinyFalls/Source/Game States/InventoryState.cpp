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

	
	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(rect1))
		{
			m_bSwordSelect = !m_bSwordSelect;

			if (m_bSwordSelect)
			{
				if (pInput->GetCursorPosition().IsPointInRectangle(swordslot1))
				{

				}
				if (pInput->GetCursorPosition().IsPointInRectangle(swordslot2))
				{

				}
				if (pInput->GetCursorPosition().IsPointInRectangle(swordslot3))
				{

				}
			}
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(rect2))
		{
			m_bArmorSelect = !m_bArmorSelect;

			if (m_bArmorSelect)
			{
				if (pInput->GetCursorPosition().IsPointInRectangle(armorslot1))
				{

				}
				if (pInput->GetCursorPosition().IsPointInRectangle(armorslot2))
				{

				}
				if (pInput->GetCursorPosition().IsPointInRectangle(armorslot3))
				{

				}
			}
		}
		else if (pInput->GetCursorPosition().IsPointInRectangle(rect3))
		{
			m_bRingSelect = !m_bRingSelect;

			if (m_bRingSelect)
			{
				if (pInput->GetCursorPosition().IsPointInRectangle(ringslot1))
				{

				}
				if (pInput->GetCursorPosition().IsPointInRectangle(ringslot2))
				{

				}
				if (pInput->GetCursorPosition().IsPointInRectangle(ringslot3))
				{

				}
			}
		}
		/*
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect1))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect2))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect3))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect4))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect5))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect6))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect7))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect8))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect9))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect10))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect11))
		{

		}
		if (pInput->GetCursorPosition().IsPointInRectangle(IventoryRect12))
		{

		}*/
	}
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
		pGraphics->DrawRectangle(swordslot2, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(swordslot3, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	}

	pGraphics->DrawRectangle(rect2, SGD::Color{ 200, 200, 200, 200 }, SGD::Color{ 255, 255, 255, 255 });
	if (m_bArmorSelect)
	{
		pGraphics->DrawRectangle(armorslot1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(armorslot2, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(armorslot3, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	}

	pGraphics->DrawRectangle(rect3, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	if (m_bRingSelect)
	{
		pGraphics->DrawRectangle(ringslot1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(ringslot2, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawRectangle(ringslot3, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	}

	pGraphics->DrawRectangle(IventoryRect1, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { 50, 200 }, {}, {}, {}, {0.5f, 0.25f});
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

void InventoryState::AddRunesToInventoryfromWorld(Runes* _addrune)
{
	m_vRunes.push_back(_addrune);
}

void InventoryState::AddRunesToSwordfromInventory(Runes* _addrune)
{
	if (m_vSword.size() > 2)
		return;

	//m_vRunes.swap(_addrune, m_vSword);
}

void InventoryState::AddRunesToRingfromInventory(Runes* _addrune)
{
	if (m_vRing.size() > 2)
		return;

	//m_vRunes.swap(_addrune, m_vRing);
}

void InventoryState::AddRunesToArmorfromInventory(Runes* _addrune)
{
	if (m_vArmor.size() > 2)
		return;

	//m_vRunes.swap(_addrune, m_vArmor);
}
