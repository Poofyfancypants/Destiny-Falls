#include "stdafx.h"
#include "CombatState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../Game Core/Game.h"
#include "GameplayState.h"
#include "CombatState.h"
#include "GameplayState.h"
#include "../Game Objects/Minion.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"

CombatState* CombatState::GetInstance()
{
	static CombatState s_Instance;
	return &s_Instance;
}

void CombatState::Enter(void)
{
	CurrentTurn = 0;
	TurnIndex = 0;

	Player* player = (Player*)GameplayState::GetInstance()->GetPlayer();
	player->SetCombat(true);
	player->CurrentTurn(&CurrentTurn);
	player->SetTurnPos(TurnIndex);
	m_pObjects.push_back(player);
	TurnIndex++;

	for (unsigned int i = 0; i < 3; i++)
	{
		Object* temp = AddMinion();
		m_pObjects.push_back(temp);
		m_nNumEnemies++;
		TurnIndex++;
	}
}

void CombatState::Exit(void)
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		if (m_pObjects[i]->GetType() != Object::ObjectType::OBJ_PLAYER)
		{
			m_pObjects[i]->Release();
		}
	}
}

bool CombatState::Input(void)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		((Player*)GameplayState::GetInstance()->GetPlayer())->SetHealth(((Player*)GameplayState::GetInstance()->GetPlayer())->GetHealth() - 20);
		((Player*)GameplayState::GetInstance()->GetPlayer())->SetCombat(false);
		Game::GetInstance()->RemoveState();
	}

	return true;
}
void CombatState::Update(float elapsedTime)
{

	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		switch (m_pObjects[i]->GetType())
		{
		case Object::ObjectType::OBJ_PLAYER:
		{
											   if (((Player*)m_pObjects[i])->GetTurnPos() == CurrentTurn)
											   {
												   ((Player*)m_pObjects[i])->TakeTurn();
												   CurrentTurn++;
											   }
		}
			break;
		case Object::ObjectType::OBJ_MINION:
		{
											   if (((Minion*)m_pObjects[i])->GetTurnPos() == CurrentTurn)
											   {
												   ((Minion*)m_pObjects[i])->TakeTurn();
												   CurrentTurn++;
											   }
		}
			break;
		}
		//CurrentTurn++;
	}
}

void CombatState::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->DrawRectangle(AbilityRect, SGD::Color{ 100, 150, 150, 150 });

	pGraphics->DrawRectangle(Compation1HB, SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawRectangle(PlayerHB, SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawRectangle(Compation2HB, SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawRectangle(Enemy1HB, SGD::Color{ 100, 0, 255, 0 });
	pGraphics->DrawRectangle(Enemy2HB, SGD::Color{ 100, 0, 255, 0 });
	pGraphics->DrawRectangle(Enemy3HB, SGD::Color{ 100, 0, 255, 0 });

	pGraphics->DrawRectangle(Compation1rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Playerrect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Compation2rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Enemy1rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Enemy2rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawRectangle(Enemy3rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
}

Object* CombatState::AddMinion()
{
	Minion* temp = new Minion;
	temp->SetImage(m_henemy);
	temp->SetSize({ 64, 64 });
	temp->CurrentTurn(&CurrentTurn);
	temp->SetTurnPos(TurnIndex);
	return temp;
}