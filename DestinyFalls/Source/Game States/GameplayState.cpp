#include "stdafx.h"
#include "../Game Core/Game.h"
#include "GameplayState.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"
#include "MainMenuState.h"
#include "InventoryState.h"
#include "../Messages/MessageID.h"
#include "../../SGD Wrappers/SGD_MessageManager.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

#include "../../SGD Wrappers/SGD_EventManager.h"
#include "MainMenuState.h"


GameplayState* GameplayState::GetInstance()
{
	static GameplayState s_Instance;
	return &s_Instance;
}

void GameplayState::Enter()
{
	
	m_pObjects = new ObjectManager;
	m_pMap = new TileManager;

	m_pPlayer = CreatePlayer();
	m_pObjects->AddObject(m_pPlayer, PLAYER_BUCKET);

	// - Manage The map
	m_pMap->LoadLevel("testMap.xml");

	for (unsigned int i = 0; i < 1; i++)
	{
		Object* tempEnemy = nullptr;
		tempEnemy = CreateEnemy();
		m_pObjects->AddObject(tempEnemy, ENEMY_BUCKET);
		tempEnemy->Release();
	}
}

void GameplayState::Exit()
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	pGraphics->UnloadTexture(m_hBackImage);

	m_pObjects->RemoveAll();
	delete m_pObjects;
	m_pObjects = nullptr;
	


}

bool GameplayState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		Game::GetInstance()->RemoveState(); //Make this Pause
		Game::GetInstance()->AddState(MainMenuState::GetInstance());
	}

	if (pInput->IsKeyPressed(SGD::Key::E))
	{
		//Game::GetInstance()->RemoveState(); //Make this Pause
		Game::GetInstance()->AddState(InventoryState::GetInstance());
	}

	return true;
}

void GameplayState::Update(float elapsedTime)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	SGD::MessageManager::GetInstance()->Update();

	m_pObjects->UpdateAll(elapsedTime);
	m_pObjects->RenderAll();
}

void GameplayState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::Rectangle rect = { 100, 100, 150, 150 };
	m_pMap->DrawLevel();
	
	pGraphics->DrawRectangle(rect, SGD::Color{ 255, 255, 255, 0 });

	m_pObjects->RenderAll();
}

Object* GameplayState::CreatePlayer()
{
	Player* temp = new Player;
	temp->SetSize({ 64, 64 });
	temp->SetPosition(SGD::Point(150, 150));
	return temp;
}

Object* GameplayState::CreateEnemy()
{
	Enemy* temp = new Enemy;
	temp->SetSize({ 64, 64 });
	temp->SetPosition(SGD::Point(250, 300));
	return temp;
}