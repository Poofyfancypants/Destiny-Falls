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
	//m_hFiret1 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"../../../../Firet1.png");
	//m_hFiret2 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"../../../../Firet2.png");
	//m_hFiret3 = SGD::GraphicsManager::GetInstance()->LoadTexture(L"../../../../Firet3.png");
}

void InventoryState::Exit()
{
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret1);
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret2);
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hFiret3);
}

bool InventoryState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		Game::GetInstance()->RemoveState(); //Make this Pause
		Game::GetInstance()->AddState(GameplayState::GetInstance());
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

	SGD::Rectangle rect = { 100, 100, 900, 700 };
	pGraphics->DrawRectangle(rect, SGD::Color{ 200, 100, 100, 100 }, SGD::Color{ 255, 255, 255, 255 });

	SGD::Rectangle rect1 = { 100, 100, 350, 300 };
	pGraphics->DrawRectangle(rect1, SGD::Color{ 200, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });

	SGD::Rectangle rect2 = { 350, 100, 600, 300 };
	pGraphics->DrawRectangle(rect2, SGD::Color{ 200, 200, 200, 200 }, SGD::Color{ 255, 255, 255, 255 });

	SGD::Rectangle rect3 = { 600, 100, 900, 300 };
	pGraphics->DrawRectangle(rect3, SGD::Color{ 200, 250, 250, 250 }, SGD::Color{ 255, 255, 255, 255 });

	for (float i = 0; i < 4; i++)
	{
		for (float j = 0; j < 3; j++)
		{
			SGD::Rectangle rect4 = { 100 + (200 * i), 300 + (133 * j), 300 + (200 * i), 433 + (133 * j) };
			pGraphics->DrawRectangle(rect4, SGD::Color{ 100, 255, 255, 255 }, SGD::Color{ 255, 255, 255, 255 });
		}
	}
}

void InventoryState::AddRunesToInventory(Runes* _addrune)
{
	m_vRunes.push_back(_addrune);
}

void InventoryState::AddRunesToSword(Runes* _addrune)
{
	if (m_vSword.size() > 2)
		return;

	m_vSword.push_back(_addrune);
}

void InventoryState::AddRunesToRing(Runes* _addrune)
{
	if (m_vRing.size() > 2)
		return;

	m_vRing.push_back(_addrune);
}

void InventoryState::AddRunesToArmor(Runes* _addrune)
{
	if (m_vArmor.size() > 2)
		return;

	m_vArmor.push_back(_addrune);
}
