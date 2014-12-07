#include "stdafx.h"
#include "ForgeState.h"
#include "InventoryState.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "../Game Core/Game.h"
#include "../Managers/BitmapFontManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"


ForgeState* ForgeState::GetInstance()
{
	static ForgeState s_Instance;
	return &s_Instance;
}

void ForgeState::Enter()
{
	m_hForge = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Anvil.png");
	m_hFiret1 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Firet1.png");
	m_hFiret2 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Firet2.png");
	m_hFiret3 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/Firet3.png");
}

void ForgeState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hForge);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret1);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret2);
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret3);
}

bool ForgeState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
		Game::GetInstance()->RemoveState();

	if (pInput->IsKeyPressed(SGD::Key::F))
		Game::GetInstance()->RemoveState();

	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(GameplayState::GetInstance()->InventoryButton))
		{
			Game::GetInstance()->RemoveState();
			Game::GetInstance()->AddState(InventoryState::GetInstance());
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(GameplayState::GetInstance()->ForgeButton))
			Game::GetInstance()->RemoveState();
	}

	if (pInput->IsKeyPressed(SGD::Key::MouseLeft))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(ForgeButton))
		{
			m_bForge = true;
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(rect1))
		{
			if (m_ptSelectedRune.GetElement() != None)
			{
				m_rSlot1 = m_ptSelectedRune;
			}
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(rect2))
		{
			if (m_ptSelectedRune.GetElement() != None)
			{
				m_rSlot2 = m_ptSelectedRune;
			}
		}

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
	}

	if (pInput->IsKeyPressed(SGD::Key::MouseRight))
	{
		if (pInput->GetCursorPosition().IsPointInRectangle(rect1))
		{
			InventoryState::GetInstance()->AddRunesToInventoryfromWorld(m_rSlot1);
		}
		if (pInput->GetCursorPosition().IsPointInRectangle(rect2))
		{
			InventoryState::GetInstance()->AddRunesToInventoryfromWorld(m_rSlot2);
		}
	}



	return true;
}

void ForgeState::Update(float elapsedTime)
{
	if (m_bForge)
	{

	}
}

void ForgeState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFonts = pFonts->GetInstance();
	//pFonts->Render("Celtic", "You Win", { x, y }, 2, { 255, 255, 255, 255 });

	GameplayState::GetInstance()->Render();

	//pGraphics->DrawRectangle(GameplayState::GetInstance()->InventoryButton, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 0, 255, 255, 255 });

	pGraphics->DrawRectangle(Fullrect, SGD::Color{ 255, 255, 255, 255 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(rect1, SGD::Color{ 255, 0, 100, 200 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(rect2, SGD::Color{ 255, 200, 100, 0 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(ImageRect, SGD::Color{ 255, 0, 100, 200 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(ResultBox, SGD::Color{ 255, 0, 100, 200 }, SGD::Color{ 255, 0, 0, 0 });

	pGraphics->DrawTexture(m_hForge, SGD::Point{ ImageRect.left, ImageRect.top }, {}, {}, {}, { 0.3f, 0.3f });


	pGraphics->DrawRectangle(IventoryRect1, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { IventoryRect1.left, IventoryRect1.top }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect2, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { IventoryRect2.left, IventoryRect2.top }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect4, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { IventoryRect4.left, IventoryRect4.top }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect5, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { IventoryRect5.left, IventoryRect5.top }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect7, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { IventoryRect7.left, IventoryRect7.top }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect8, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { IventoryRect8.left, IventoryRect8.top }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect10, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { IventoryRect10.left, IventoryRect10.top }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect11, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { IventoryRect11.left, IventoryRect11.top }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(Equip1, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(Equip2, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 0, 0, 0 });
}
