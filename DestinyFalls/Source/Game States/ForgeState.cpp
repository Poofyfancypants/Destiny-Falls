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
			Game::GetInstance()->RemoveState();
	}

	return true;
}

void ForgeState::Update(float elapsedTime)
{
	
}

void ForgeState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFonts = pFonts->GetInstance();
	//pFonts->Render("Celtic", "You Win", { x, y }, 2, { 255, 255, 255, 255 });

	GameplayState::GetInstance()->Render();

	pGraphics->DrawRectangle(GameplayState::GetInstance()->InventoryButton, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 0, 255, 255, 255 });
	
	pGraphics->DrawRectangle(Fullrect, SGD::Color{ 255, 255, 255, 255 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(ImageRect, SGD::Color{ 255, 0, 100, 200 }, SGD::Color{ 255, 0, 0, 0 });


	pGraphics->DrawTexture(m_hForge, SGD::Point(55, 100), {}, {}, {}, { 0.3f, 0.5f });

	pGraphics->DrawRectangle(IventoryRect1, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { 210, 240 }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect2, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { 310, 240 }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect4, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { 260, 240 }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect5, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { 360, 240 }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect7, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { 210, 320 }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect8, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { 310, 320 }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect10, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret1, { 260, 320 }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(IventoryRect11, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hFiret2, { 360, 320 }, {}, {}, {}, { 0.1f, 0.1f });

	pGraphics->DrawRectangle(Equip1, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 0, 0, 0 });
	pGraphics->DrawRectangle(Equip2, SGD::Color{ 0, 250, 250, 250 }, SGD::Color{ 255, 0, 0, 0 });
}
