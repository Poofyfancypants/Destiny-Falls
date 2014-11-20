#include "stdafx.h"
#include "CombatState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "CombatState.h"
#include "GameplayState.h"
#include "GameplayState.h"
#include "InventoryState.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Minion.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"
#include "../Runes/RuneManager.h"
#include "../Runes/Runes.h"

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
	player->AddRef();
	m_pObjects.push_back(player);
	TurnIndex++;

	m_hplayer = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/ShadowKnight.png");
	m_henemy = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/Rock.png");
	m_henemy2 = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/Plant.png");

	//for (unsigned int i = 0; i < rand() % 3 + 1; i++)
	//{
	//	Object* temp = AddMinion();
	//	m_pObjects.push_back(temp);
	//	Enemies[i] = temp;
	//	m_nNumEnemies++;
	//	TurnIndex++;
	//}

		Object* temp = AddMinion();
		m_pObjects.push_back(temp);
		Enemies[0] = temp;
		m_nNumEnemies++;
		TurnIndex++;

		Object* temp1 = AddMinion1();
		m_pObjects.push_back(temp1);
		Enemies[1] = temp1;
		m_nNumEnemies++;
		TurnIndex++;
	


	PlayerHB.right = PlayerHB.left + ((Player*)m_pObjects[0])->GetHealth();


}

void CombatState::Exit(void)
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->UnloadTexture(m_hplayer);
	pGraphics->UnloadTexture(m_henemy);
	pGraphics->UnloadTexture(m_henemy2);

	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		//if (m_pObjects[i]->GetType() != Object::ObjectType::OBJ_PLAYER)
		{
			m_pObjects[i]->Release();
		}
	}
	m_pObjects.clear();
}

bool CombatState::Input(void)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		//((Player*)GameplayState::GetInstance()->GetPlayer())->SetHealth(((Player*)GameplayState::GetInstance()->GetPlayer())->GetHealth() - 20);
		((Player*)GameplayState::GetInstance()->GetPlayer())->SetCombat(false);
		Game::GetInstance()->RemoveState();
	}

	return true;
}

void CombatState::Update(float elapsedTime)
{
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		if (((Player*)m_pObjects[0])->GetHealth() > 0)
		{

		}
		else
		{
			((Player*)m_pObjects[0])->SetCombat(false);
		}

		for (size_t i = 0; i < 3; i++)
		{
			{

			}
		}


		switch (m_pObjects[i]->GetType())
		{
		case Object::ObjectType::OBJ_PLAYER:
		{
											   if (((Player*)m_pObjects[i])->GetTurnPos() == CurrentTurn)
											   {
												   if (((Player*)m_pObjects[i])->TakeTurn(elapsedTime))
												   {
													   CurrentTurn++; //Put this back in the check once player combat input is complete
												   }

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
	}
	CurrentTurn = 0;
}

void CombatState::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->DrawRectangle(AbilityRect, SGD::Color{ 100, 150, 150, 150 });

	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		if (i == 0)
		{
			pGraphics->DrawRectangle(Playerrect, SGD::Color{ 100, 0, 0, 150 }, SGD::Color{ 255, 255, 255, 255 });
			pGraphics->DrawTexture(m_hplayer, { Playerrect.left- 20, Playerrect.top -10 }, {}, {}, {}, { .5, .5 });
			pGraphics->DrawRectangle(PlayerHB, SGD::Color{ 100, 0, 255, 0 });
		}
		if (i == 1)
		{
			pGraphics->DrawRectangle(Enemy1rect, SGD::Color{ 100, 150, 0, 0 }, SGD::Color{ 255, 255, 255, 255 });
			pGraphics->DrawTexture(m_henemy, { Enemy1rect.left, Enemy1rect.top }, {}, {}, {}, {.5, .5});
			pGraphics->DrawRectangle(Enemy1HB, SGD::Color{ 100, 0, 255, 0 });
		}
		if (i == 2)
		{
			pGraphics->DrawRectangle(Enemy2rect, SGD::Color{ 100, 150, 0, 0 }, SGD::Color{ 255, 255, 255, 255 });
			pGraphics->DrawTexture(m_henemy2, { Enemy2rect.left, Enemy2rect.top }, {}, {}, {}, { .5, .5 });
			pGraphics->DrawRectangle(Enemy2HB, SGD::Color{ 100, 0, 255, 0 });
		}
		if (i == 3)
		{
			pGraphics->DrawRectangle(Enemy3rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
			pGraphics->DrawRectangle(Enemy3HB, SGD::Color{ 100, 0, 255, 0 });
		}
		if (i == 4)
		{
			pGraphics->DrawRectangle(Compation1HB, SGD::Color{ 100, 150, 150, 150 });
			pGraphics->DrawRectangle(Compation1rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
		}
		if (i == 5)
		{
			pGraphics->DrawRectangle(Compation2rect, SGD::Color{ 100, 150, 150, 150 }, SGD::Color{ 255, 255, 255, 255 });
			pGraphics->DrawRectangle(Compation2HB, SGD::Color{ 100, 150, 150, 150 });
		}
	}
}

Object* CombatState::AddMinion()
{
	Minion* temp = new Minion;
	temp->SetImage(m_henemy);
	temp->SetSize({ 64, 64 });
	temp->CurrentTurn(&CurrentTurn);
	temp->SetTurnPos(TurnIndex);
	temp->SetAffinity(Earth);
	return temp;
}

Object* CombatState::AddMinion1()
{
	Minion* temp = new Minion;
	temp->SetImage(m_henemy2);
	temp->SetSize({ 64, 64 });
	temp->CurrentTurn(&CurrentTurn);
	temp->SetTurnPos(TurnIndex);
	temp->SetAffinity(None);
	return temp;
}

bool CombatState::DealDamage(int _DamType, Object* _this, int _target)
{
	RuneManager* mag = new RuneManager;

	Game::GetInstance()->AddState(InventoryState::GetInstance());

	switch (_DamType)
	{
	case CombatState::DamType::Melee:
	{
										if (m_pObjects[_target]->GetType() == iObject::OBJ_PLAYER)
										{
											((Player*)m_pObjects[_target])->SetHealth(((Player*)m_pObjects[_target])->GetHealth() - 20);
										}
										if (m_pObjects[_target]->GetType() == iObject::OBJ_MINION)
										{
											((Minion*)m_pObjects[_target])->SetHealth(((Minion*)m_pObjects[_target])->GetHealth() - 
												(mag->DamageComboElement(
												mag->ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), 
												InventoryState::GetInstance()->GetSwordSlot2()), ((Minion*)m_pObjects[_target])->GetAffinity()) * 10));
										}
	}
		break;
	case CombatState::DamType::Magic:
	{
										m_bCoolDown = true;
										if (m_pObjects[_target]->GetType() == iObject::OBJ_PLAYER)
										{
											((Player*)m_pObjects[_target])->SetHealth(((Player*)m_pObjects[_target])->GetHealth() - 20);
										}
										if (m_pObjects[_target]->GetType() == iObject::OBJ_MINION)
										{
											((Minion*)m_pObjects[_target])->SetHealth(((Minion*)m_pObjects[_target])->GetHealth() -
												(mag->DamageComboElement(
												mag->ElementCombination(InventoryState::GetInstance()->GetRingSlot1(),
												InventoryState::GetInstance()->GetRingSlot2()), ((Minion*)m_pObjects[_target])->GetAffinity()) * 10));
										}
	}
		break;
	case CombatState::DamType::Armor:
	{

	}
		break;
	default:
		break;
	}

	delete mag;

	return false;
}