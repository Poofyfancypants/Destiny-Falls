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
#include "../Game Objects/Companion.h"
#include "../Runes/RuneManager.h"
#include "../Runes/Runes.h"
#include "../Quick Time/QuickTime.h"
#include "../Game States/QuickTimeState.h"
#include "../Runes/Runes.h"

CombatState* CombatState::GetInstance()
{
	static CombatState s_Instance;
	return &s_Instance;
}

void CombatState::Enter(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	CurrentTurn = 0;
	TurnIndex = 0;

	numPots = rand() % 3;
	numRunes = rand() % 2;

	Player* player = (Player*)GameplayState::GetInstance()->GetPlayer();
	player->CurrentTurn(&CurrentTurn);
	player->SetInit(rand() % 10 + 10);
	SavePlayerPos = player->GetPosition();
	player->SetPosition({ Playerrect.left, Playerrect.bottom });
	player->AddRef();
	m_pObjects.push_back(player);
	m_pHeroes.push_back(player);

	m_hplayer = pGraphics->LoadTexture("resource/graphics/ShadowKnight.png");
	cMusic = SGD::AudioManager::GetInstance()->LoadAudio("resource/audio/combatMusic.wav");
	//minion Icons

	//play combat music
	SGD::AudioManager::GetInstance()->PlayAudio(cMusic, true);

#pragma region AddingCombatEnemies
	if (player->CombatEnemyID == 1)
	{
		for (unsigned int i = 0; i < rand() % 2 + 2; i++)
		{
			Object* temp;
			switch (GameplayState::GetInstance()->GetCurrentLevel())
			{
			case 1:
				temp = AddMinion(0, player->CombatEnemyID);
				break;
			case 2:
				temp = AddMinion(1, player->CombatEnemyID);
				break;
			case 3:
				temp = AddMinion(2, player->CombatEnemyID);
				break;
			case 4:
				temp = AddMinion(3, player->CombatEnemyID);
				break;
			default:
				temp = AddMinion(rand() % 4, player->CombatEnemyID);

				break;
			}
			m_pObjects.push_back(temp);
			m_pEnemies.push_back(temp);
		}
	}
	else if (player->CombatEnemyID == 2)
	{
		Object* temp;
		Object* temp2;
		switch (GameplayState::GetInstance()->GetCurrentLevel())
		{
		case 1:
			temp = AddMinion(0, player->CombatEnemyID);
			temp2 = AddMinion(0, 1);
			break;
		case 2:
			temp = AddMinion(1, player->CombatEnemyID);
			temp2 = AddMinion(1, 1);
			break;
		case 3:
			temp = AddMinion(2, player->CombatEnemyID);
			temp2 = AddMinion(2, 1);
			break;
		case 4:
			temp = AddMinion(3, player->CombatEnemyID);
			temp2 = AddMinion(3, 1);
			break;
		default:
			temp = AddMinion(rand() % 4, player->CombatEnemyID);
			temp2 = AddMinion(rand() % 4, 1);
			break;
		}
		m_pObjects.push_back(temp);
		m_pObjects.push_back(temp2);
		m_pEnemies.push_back(temp);
		m_pEnemies.push_back(temp2);
	}
	else if (player->CombatEnemyID == 3)
	{
		Object* temp;
		switch (GameplayState::GetInstance()->GetCurrentLevel())
		{
		case 1:
			temp = AddMinion(0, player->CombatEnemyID);
			break;
		case 2:
			temp = AddMinion(1, player->CombatEnemyID);
			break;
		case 3:
			temp = AddMinion(2, player->CombatEnemyID);
			break;
		case 4:
			temp = AddMinion(3, player->CombatEnemyID);
			break;
		default:
			temp = AddMinion(rand() % 4, player->CombatEnemyID);

			break;
		}
		m_pObjects.push_back(temp);
		m_pEnemies.push_back(temp);
	}
	else if (player->CombatEnemyID == 4)
	{
		Object* temp;
		temp = AddMinion(4, player->CombatEnemyID);

		m_pObjects.push_back(temp);
		m_pEnemies.push_back(temp);
	}
#pragma endregion
#pragma region AddingCombatCompanions

	for (unsigned int i = 1; i < 3; i++)
	{
		Object* temp = AddCompanion();
		((Companion*)temp)->SetPosIndex(i);

		if (m_pHeroes.size() == 1)
		{
			temp->SetPosition({ Companion1rect.right, Companion1rect.bottom });
		}
		else if (m_pEnemies.size() == 2)
		{
			temp->SetPosition({ Companion2rect.right, Companion2rect.bottom });
		}
		m_pObjects.push_back(temp);
		m_pHeroes.push_back(temp);
	}
#pragma endregion

	for (size_t i = 1; i < m_pObjects.size(); i++)
	{
		for (size_t j = 0; j < m_pObjects.size(); j++)
		{
			if (m_pObjects[i] != nullptr && m_pObjects[j] != nullptr)
			{
				if (m_pObjects[i]->GetInit() > m_pObjects[j]->GetInit())
				{
					swap(m_pObjects[i], m_pObjects[j]);
				}
			}
		}
	}

	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		m_pObjects[i]->SetTurnPos(i);
	}

	PlayerHB.right = PlayerHB.left + ((Player*)m_pHeroes[0])->GetHealth();
	SetActionTimer(2);
	SetAction("Combat Ensues!");

	m_CombatPos1.x = (Game::GetInstance()->GetScreenWidth() / 2 - 35);
	m_CombatPos1.y = (Game::GetInstance()->GetScreenHeight() / 2);

	m_CombatPos2.x = (Game::GetInstance()->GetScreenWidth() / 2 + 35);
	m_CombatPos2.y = (Game::GetInstance()->GetScreenHeight() / 2);

	((Player*)m_pHeroes[0])->StartCombat();

}

void CombatState::Exit(void)
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	((Player*)m_pHeroes[0])->SetPosition(SavePlayerPos);

	((Player*)m_pHeroes[0])->StopCombat();
	for (size_t i = 0; i < m_pObjects.size(); i++)
		m_pObjects[i]->Release();

	m_pObjects.clear();
	m_pEnemies.clear();
	m_pHeroes.clear();

	pGraphics->UnloadTexture(m_hplayer);

	pAudio->UnloadAudio(cMusic);
}

bool CombatState::Input(void)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		((Player*)GameplayState::GetInstance()->GetPlayer())->SetCombat(false);
		pAudio->PlayAudio(GameplayState::GetInstance()->bmusic, true);
		Game::GetInstance()->RemoveState();
	}

	return true;
}

void CombatState::Update(float elapsedTime)
{

	ActionTimer -= elapsedTime;
	if (ActionTimer <= 0.0f)
		ActionTimer = 0.0f;

	m_fFlash += elapsedTime;

	DrawBackground();

	if (((Player*)m_pHeroes[0])->GetHealth() > 0)
	{
		PlayerHB.right = PlayerHB.left + ((Player*)m_pHeroes[0])->GetHealth();
		((Player*)m_pHeroes[0])->Update(elapsedTime);

		for (unsigned int i = 1; i < m_pHeroes.size(); i++)
		{
			if (((Companion*)m_pHeroes[i])->GetHealth())
			{
				((Companion*)m_pHeroes[i])->Update(elapsedTime);

			}
		}
		if (((Player*)m_pHeroes[0])->GetHealth() < 25 && m_fFlash > 2)
		{
			m_bHealthWarning = true;
			m_fFlash = 0;
		}
		else
			m_bHealthWarning = false;

	}
	else
	{
		((Player*)m_pHeroes[0])->SetCombat(false);
		Game::GetInstance()->RemoveState();
		return;
	}

	if (ActionTimer <= 0.0f)
	{
		m_bShake = false;

		if (Attacker1 != -1) //System on hold
		{
			m_pHeroes[Attacker1]->SetAttacking(false); //After the time is up
		}
		if (Attacker2 != -1)
		{

		}

		for (size_t i = 0; i < m_pEnemies.size(); i++)
		{
			int numEnemies = 0;
			for (size_t i = 0; i < m_pEnemies.size(); i++)
			{
				if (((Minion*)m_pEnemies[i])->GetHealth() > 0)
				{
					numEnemies++;
					((Minion*)m_pEnemies[i])->Update(elapsedTime);
				}
			}
			if (numEnemies <= 0) //Win
			{
				((Player*)m_pHeroes[0])->SetCombat(false);
				((Player*)m_pHeroes[0])->m_nPotions += numPots;

				Game::GetInstance()->RemoveState();
				return;
			}
		}


		for (size_t i = 0; i < m_pObjects.size(); i++)
		{
			switch (m_pObjects[i]->GetType())
			{
			case Object::ObjectType::OBJ_PLAYER:
				if (((Player*)m_pObjects[i])->GetTurnPos() == CurrentTurn)
				{
					if (ActionTimer <= 0)
					{
						//Attacker1 = 0; If we can make this work it might be cool
						//Not sure why I wanted it other than that
						if (TakeTurn(((Player*)m_pObjects[i])))
						{
							CurrentTurn++;
						}
					}
				}
				break;
			case Object::ObjectType::OBJ_COMPANION:
				if (((Companion*)m_pObjects[i])->GetTurnPos() == CurrentTurn)
				{
					if (ActionTimer <= 0)
					if (TakeTurn(((Companion*)m_pObjects[i])))
						CurrentTurn++;
				}
				break;
			case Object::ObjectType::OBJ_MINION:
				if (((Minion*)m_pObjects[i])->GetTurnPos() == CurrentTurn)
				{
					if (ActionTimer <= 0)
					if (TakeTurn(((Minion*)m_pObjects[i])))
						CurrentTurn++;
				}
				break;
			}
		}
		if (CurrentTurn == m_pObjects.size() && ActionTimer <= 0)
			CurrentTurn = 0;
	}
	else
	{
		if (Attacker1 != -1)
		{
			if (m_pHeroes[Attacker1]->GetAttacking())
			{
				m_vOffset.x = ((m_pHeroes[Attacker1]->GetPosition().x + m_CombatPos1.x));
				m_vOffset.y = ((m_pHeroes[Attacker1]->GetPosition().y + m_CombatPos1.y));
				m_vOffset.Normalize();
				(Playerrect.Offset(m_vOffset / 3));
			}
		}

		for (size_t i = 0; i < m_pEnemies.size(); i++)
		{
			((Minion*)m_pEnemies[i])->Update(elapsedTime);
			((Minion*)m_pEnemies[i])->Render(i);

		}

		if (m_bShake)
		{
			//ShakeScreen(elapsedTime);
		}
		else
		{
			ResetRects();
		}
	}

}
void CombatState::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	//	pGraphics->DrawTexture(Game::GetInstance()->m_hEarth1, SGD::Point(0, 0), {}, {}, {}, { 2.0f, 2.0f });

	//Enemy Icons
	for (unsigned int i = 0; i < m_pEnemies.size(); i++)
	{
		if (((Minion*)(m_pEnemies[i]))->GetHealth() > 0)
		{
		if (((Minion*)(m_pEnemies[i]))->GetAffinity() == Water)
			pGraphics->DrawTexture(Game::GetInstance()->m_hWaterIcon, SGD::Point(m_pEnemies[i]->GetPosition().x + 40, m_pEnemies[i]->GetPosition().y - 110), {}, {}, {}, { .1f, .1f });
		if (((Minion*)(m_pEnemies[i]))->GetAffinity() == Fire)
			pGraphics->DrawTexture(Game::GetInstance()->m_hFireIcon, SGD::Point(m_pEnemies[i]->GetPosition().x + 40, m_pEnemies[i]->GetPosition().y - 110), {}, {}, {}, { .1f, .1f });
		if (((Minion*)(m_pEnemies[i]))->GetAffinity() == Air)
			pGraphics->DrawTexture(Game::GetInstance()->m_hAirIcon, SGD::Point(m_pEnemies[i]->GetPosition().x + 40, m_pEnemies[i]->GetPosition().y - 110), {}, {}, {}, { .1f, .1f });
		if (((Minion*)(m_pEnemies[i]))->GetAffinity() == Earth)
			pGraphics->DrawTexture(Game::GetInstance()->m_hEarthIcon, SGD::Point(m_pEnemies[i]->GetPosition().x + 40, m_pEnemies[i]->GetPosition().y - 110), {}, {}, {}, { .1f, .1f });
		}
	}

	pGraphics->DrawRectangle(AbilityRect, SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawRectangle(ActionRect, SGD::Color{ 100, 150, 150, 150 });
	pGraphics->DrawString(ActionMessage.c_str(), SGD::Point{ ActionRect.left + 60, ActionRect.top + 5 }, SGD::Color(255, 255, 255, 255));



	SGD::Color pHcolor;
	if (((Player*)m_pHeroes[0])->GetHealth() > 50)
		pHcolor = { 255, 0, 255, 0 };
	else if (((Player*)m_pHeroes[0])->GetHealth() > 20)
		pHcolor = { 255, 255, 255, 0 };
	else
		pHcolor = { 255, 255, 0, 0 };

	pGraphics->DrawRectangle(Playerrect, SGD::Color{ 100, 0, 0, 150 }, SGD::Color{ 255, 255, 255, 255 });
	((Player*)m_pHeroes[0])->Render();

	if (PlayerHB.right > PlayerHB.left)
		pGraphics->DrawRectangle(PlayerHB, pHcolor);

	if (m_bHealthWarning)
	{
		pGraphics->DrawRectangle(SGD::Rectangle(0, 0, Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight()), { 100, 255, 0, 0 });
	}

	for (size_t j = 0; j < m_pEnemies.size(); j++)
	{
		if (((Minion*)m_pEnemies[j])->GetHealth() > 0)
		{
			((Minion*)m_pEnemies[j])->Render(j);
		}
	}

	for (size_t j = 1; j < m_pHeroes.size(); j++)
	{
		if (((Companion*)m_pHeroes[j])->GetHealth() > 0)
		{
			((Companion*)m_pHeroes[j])->CombatRender(j);
		}
	}
	if (GameplayState::GetInstance()->GetCurrentLevel() == 0)
		HandleTutorial();
}

Object* CombatState::AddMinion(int _region, int EnemyID) //This is gonna get big, don't care
{
	Minion* temp = new Minion;
	temp->SetSize({ 64, 64 });
	temp->CurrentTurn(&CurrentTurn);

	switch (EnemyID)
	{
	case 1:
	{
			  temp->SetInit(rand() % 20);
			  temp->SetAffinity((Elements)_region);

			  if (m_pEnemies.size() == 0)
			  {
				  temp->SetPosition({ Enemy2rect.right, Enemy2rect.bottom });
			  }
			  else if (m_pEnemies.size() == 1)
			  {
				  temp->SetPosition({ Enemy1rect.right, Enemy1rect.bottom });
			  }
			  else if (m_pEnemies.size() == 2)
			  {
				  temp->SetPosition({ Enemy3rect.right, Enemy3rect.bottom });
			  }
			  int randAI = rand() % 5;
			  int randHealth = 0;

			  switch (randAI)
			  {
			  case 0: // Minion
				  randHealth = rand() % 40 + 40;
				  temp->SetMods(6, 3, _region, 0, 0);

				  switch (_region)
				  {
				  case 0:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Minion_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 1:
					  temp->SetMinionAnimation(_region, randAI);
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Minion_AI);
					  break;
				  case 2:
					  temp->SetMinionAnimation(_region, randAI);
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Minion_AI);
					  break;
				  case 3:
					  temp->SetMinionAnimation(_region, randAI);
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Minion_AI);
					  break;
				  }
				  break;
			  case 1: // Offensive
				  randHealth = rand() % 35 + 50;

				  if (randHealth > 50)
					  temp->SetMods(6, 5, _region, 2, 1);
				  else
					  temp->SetMods(6, 5, _region, 3, 1);

				  switch (_region)
				  {

				  case 0:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Off_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 1:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Off_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 2:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Off_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 3:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Off_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  }
				  break;
			  case 2: // Defensive
				  randHealth = rand() % 20 + 80;

				  if (randHealth > 90)
					  temp->SetMods(6, 2, _region, 1, 3);
				  else
					  temp->SetMods(6, 2, _region, 2, 3);

				  switch (_region)
				  {

				  case 0:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Def_AI);
					  temp->SetMinionAnimation(_region, randAI);

					  break;
				  case 1:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Def_AI);
					  temp->SetMinionAnimation(_region, randAI);


					  break;
				  case 2:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Def_AI);
					  temp->SetMinionAnimation(_region, randAI);

					  break;
				  case 3:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Def_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  }
				  break;
			  case 3: // Healing
				  randHealth = rand() % 35 + 45;

				  if (randHealth > 60)
					  temp->SetMods(6, 1, _region, 1, 2);
				  else
					  temp->SetMods(6, 1, _region, 1, 3);

				  switch (_region)
				  {
				  case 0:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Heal_AI);
					  temp->SetMinionAnimation(_region, randAI);

					  break;
				  case 1:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Heal_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 2:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Heal_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 3:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::Heal_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  }
				  break;
			  case 4: // AOE
				  randHealth = rand() % 40 + 55;

				  if (randHealth > 75)
					  temp->SetMods(6, 4, _region, 2, 1);
				  else
					  temp->SetMods(6, 4, _region, 3, 2);

				  switch (_region)
				  {
				  case 0:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::AOE_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 1:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::AOE_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 2:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::AOE_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 3:
					  temp->SetString(_region, randAI);
					  temp->SetAIType(Minion::AI_Type::AOE_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  }
				  break;
			  default:
				  break;
			  }

			  temp->SetHealth(randHealth);
	}
		break;
	case 2: //Mini Bosses
	{
				temp->SetInit(rand() % 20);
				temp->SetAffinity((Elements)_region);
				if (m_pEnemies.size() == 0)
				{
					temp->SetPosition({ Enemy1rect.right, Enemy1rect.bottom });
				}
				else if (m_pEnemies.size() == 1)
				{
					temp->SetPosition({ Enemy2rect.right, Enemy2rect.bottom });
				}
				else if (m_pEnemies.size() == 2)
				{
					temp->SetPosition({ Enemy3rect.right, Enemy3rect.bottom });
				}

				switch (_region)
				{
				case 0:
				{
						  temp->SetMods(12, 5, _region, 3, 3);
						  temp->SetString(_region, 5);
						  temp->SetAIType(Minion::AI_Type::Mini_Boss);
						  temp->SetMinionAnimation(_region, 5);
				}
					break;
				case 1:
				{
						  temp->SetMods(12, 5, _region, 3, 3);
						  temp->SetString(_region, 5);
						  temp->SetAIType(Minion::AI_Type::Mini_Boss);
						  temp->SetMinionAnimation(_region, 5);
				}
					break;
				case 2:
				{
						  temp->SetMods(12, 5, _region, 3, 3);
						  temp->SetString(_region, 5);
						  temp->SetAIType(Minion::AI_Type::Mini_Boss);
						  temp->SetMinionAnimation(_region, 5);
				}
					break;
				case 3:
				{
						  temp->SetMods(12, 5, _region, 3, 3);
						  temp->SetString(_region, 5);
						  temp->SetAIType(Minion::AI_Type::Mini_Boss);
						  temp->SetMinionAnimation(_region, 5);
				}
					break;
				default:
					break;
				}

				temp->SetHealth(150);
	}
		break;
	case 3: //Level Bosses
	{
				if (m_pEnemies.size() == 0)
				{
					temp->SetPosition({ Enemy1rect.right, Enemy1rect.bottom });
				}
				else if (m_pEnemies.size() == 1)
				{
					temp->SetPosition({ Enemy2rect.right, Enemy2rect.bottom });
				}
				else if (m_pEnemies.size() == 2)
				{
					temp->SetPosition({ Enemy3rect.right, Enemy3rect.bottom });
				}

				temp->SetInit(rand() % 20);
				temp->SetAffinity((Elements)_region);

				switch (_region)
				{
				case 0:
				{
						  temp->SetMods(12, 5, _region, 3, 3);
						  temp->SetString(4, _region);
						  temp->SetAIType(Minion::AI_Type::Level_Boss);
						  temp->SetMinionAnimation(_region, 6);
				}
					break;
				case 1:
				{
						  temp->SetMods(12, 5, _region, 3, 3);
						  temp->SetString(4, _region);
						  temp->SetAIType(Minion::AI_Type::Level_Boss);
						  temp->SetMinionAnimation(_region, 6);
				}
					break;
				case 2:
				{
						  temp->SetMods(12, 5, _region, 3, 3);
						  temp->SetString(4, _region);
						  temp->SetAIType(Minion::AI_Type::Level_Boss);
						  temp->SetMinionAnimation(_region, 6);
				}
					break;
				case 3:
				{
						  temp->SetMods(12, 5, _region, 3, 3);
						  temp->SetString(4, _region);
						  temp->SetAIType(Minion::AI_Type::Level_Boss);
						  temp->SetMinionAnimation(_region, 6);
				}
					break;
				default:
					break;
				}

				temp->SetHealth(300);

	}
		break;
	case 4: //Final Boss
	{
				temp->SetPosition({ Enemy2rect.right, Enemy2rect.bottom });
				temp->SetMods(12, 5, _region, 3, 3);
				temp->SetString(4, _region);
				temp->SetAIType(Minion::AI_Type::Final_Boss);
				temp->SetMinionAnimation(_region, 0);
				temp->SetAffinity(Earth);
				temp->SetHealth(200);
	}
		break;
	default:
		break;
	}
	return temp;
}

Object* CombatState::AddCompanion()
{
	Companion* temp = new Companion;
	temp->SetInit(rand() % 20);

	Companion::Companion_Type coT = (Companion::Companion_Type)(/*rand() % 4 + */1);
	switch (coT)
	{
	case 1:
		temp->SetC0Type(Companion::Companion_Type::Cleric);
		temp->SetCompanionAnimation(1);
		break;
	case 2:
		temp->SetC0Type(Companion::Companion_Type::Mage);
		temp->SetCompanionAnimation(2);

		break;
	case 3:
		temp->SetC0Type(Companion::Companion_Type::Melee);
		temp->SetCompanionAnimation(3);
		break;
	case 4:
		temp->SetC0Type(Companion::Companion_Type::Tank);
		temp->SetCompanionAnimation(4);
		break;
	default:
		break;
	}
	temp->SetHealth(100);
	temp->SetSize({ 64, 64 });
	temp->CurrentTurn(&CurrentTurn);
	return temp;
}

bool CombatState::TakeAction(int _ActionType, Object* _this, int _target, int _spell)
//Can I Add An Object* for the target
//I'm thinking about the order of actions here
//Possibly get the target or attacker's type before damage type, we'll see what's most repetative
//Companions are going to possibly cause some problems
{
	Game* pGame = Game::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	SetActionTimer(GetActionTimer() + 1.5f);
	switch (_this->GetType())
	{
	case iObject::OBJ_PLAYER:
	{
								switch (_ActionType)
								{
								case CombatState::ActionType::Melee:
								{

																	   pAudio->PlayAudio(Game::GetInstance()->m_mMeleeButton);
																	  
																		   DealMeleeDamage(_this, m_pEnemies[_target]);

								}
									break;
								case CombatState::ActionType::Magic:
								{
																	   m_bCoolDown = true;
																	   DealMagicDamage(_this, m_pEnemies[_target], _spell);
																	   pAudio->PlayAudio(Game::GetInstance()->m_mMagicButton);
								}
									break;
								case CombatState::ActionType::Armor:
									break;
								default:
									break;
								}
	}
		break;
	case iObject::OBJ_COMPANION:
	{
								   switch (_ActionType)
								   {
								   case CombatState::ActionType::Melee:
								   {

																		  pAudio->PlayAudio(Game::GetInstance()->m_mMeleeButton);
																		  DealMeleeDamage(_this, m_pEnemies[_target]);

								   }
									   break;
								   case CombatState::ActionType::Magic:
								   {
																		  m_bCoolDown = true;
																		  DealMagicDamage(_this, m_pEnemies[_target], _spell);
																		  pAudio->PlayAudio(Game::GetInstance()->m_mMagicButton);
								   }
									   break;
								   case CombatState::ActionType::Armor:
								   {
																		  ((Companion*)_this)->SetBlock(true);
																		  string message = "Your Ally ";
																		  //message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
																		  SetAction(message += " Prepares to Block");
								   }
									   break;
								   case CombatState::ActionType::Heal:
								   {
																		 HealAlly(_this, m_pHeroes[_target]);
								   }
									   break;
								   default:
									   break;
								   }
	}
		break;
	case iObject::OBJ_MINION:
	{
								switch (((Minion*)_this)->GetAIType())
								{
								case 0: //Minion
								{

											string message = "The ";
											message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
											SetAction(message += " Attacks!");
											DealMeleeDamage(_this, m_pHeroes[_target]);
								}
									break;
								case 1: //Offensive
								{
											for (size_t i = 1; i < m_pHeroes.size(); i++)
											{
												if (((Companion*)m_pHeroes[i])->GetHealth() >((Player*)m_pHeroes[0])->GetHealth())
												{
													_target = i;
												}
											}
											string message = "The ";
											message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
											SetAction(message += " Attacks!");
											DealMeleeDamage(_this, m_pHeroes[_target]);
								}
									break;
								case 2: //Defensive
								{
											int numAlive = 0;
											for (size_t i = 0; i < m_pEnemies.size(); i++)
											{
												if (((Minion*)m_pEnemies[i])->GetHealth() > 0)
													numAlive++;
											}

											if (numAlive > 1)
											{
												if (rand() % 20 > 6)
												{
													((Minion*)_this)->m_Block = true;
													string message = "The ";
													message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
													SetAction(message += " Prepares to Block");
													break;
												}
											}


											string message = "The ";
											message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
											SetAction(message += " Attacks!");
											DealMeleeDamage(_this, m_pHeroes[_target]);
								}
									break;
								case 3: //Healing
								{
											int numAlive = 0;
											bool _Healed = false;
											for (size_t i = 0; i < m_pEnemies.size(); i++)
											{
												if (((Minion*)m_pEnemies[i])->GetAIType() != Minion::Heal_AI)
												{
													if ((((Minion*)m_pEnemies[i])->GetHealth() < 85) && (((Minion*)m_pEnemies[i])->GetHealth() > 0) && rand() % 20 > 5)
													{
														string message = "The ";
														message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
														SetAction(message += " Heals!");
														_Healed = true;
														HealAlly(_this, m_pEnemies[i]);
													}
												}
											}

											if (!_Healed)
											{
												_target = rand() % m_pHeroes.size();
												string message = "The ";
												message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
												SetAction(message += " Attacks!");
												DealMeleeDamage(_this, m_pHeroes[_target]);
											}

								}
									break;
								case 4: //AOE
								{
											string message = "The ";
											message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
											SetAction(message += " Uses Ground Slam!");

											if (_ActionType == ActionType::AOE)
											{
												DealAOEDamage(_this, m_pHeroes[_target]);
											}
											else if (_ActionType == ActionType::Melee)
											{
												DealMeleeDamage(_this, m_pHeroes[_target]);
											}
								}
									break;
								case 5: //Mini Boss
								{
											string message = "The ";
											message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
											SetAction(message += " Attacks!");
											DealMeleeDamage(_this, m_pHeroes[_target]);
								}
									break;
								case 6: //Level Boss
								{
											string message = "The ";
											message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
											SetAction(message += " Attacks!");
											DealMeleeDamage(_this, m_pHeroes[_target]);
								}
									break;
								case 7: //Final Boss
								{
											string message = "The ";
											message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
											SetAction(message += " Attacks!");
											DealMeleeDamage(_this, m_pHeroes[_target]);
								}
									break;
								}

	}
	default:
		break;
		return false;
	}
}

int CombatState::DealMeleeDamage(Object* _From, Object* _To)
{
	int Total;
	bool localBlock = false;
	m_nNumQTCorrect = 0;

	RuneManager mag;

	if (_From->GetType() == iObject::OBJ_PLAYER)
	{

		for (size_t i = 0; i < m_pEnemies.size(); i++)
		{
			if (((Minion*)m_pEnemies[i])->GetAIType() == Minion::AI_Type::Def_AI)
			{
				if (((Minion*)m_pEnemies[i])->m_Block)
				{
					//Game::GetInstance()->AddState(QuickTimeState::GetInstance());
					BlockAttack(_From, m_pEnemies[i]);
					localBlock = ((Minion*)m_pEnemies[i])->m_Block;
					((Minion*)m_pEnemies[i])->m_Block = false;
					return 0;
				}
			}
		}

		/*( ( Minion* ) m_pEnemies[ _target ] )->SetHealth( ( ( Minion* ) m_pEnemies[ _target ] )->GetHealth() -
		( mag.DamageComboElement( d1 , ( ( Minion* ) m_pEnemies[ _target ] )->GetAffinity() ) * 60 ) );
		( ( Player* ) m_pHeroes[ 0 ] )->ResetAnimation();*/

		if (localBlock == false)
		{
			ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());
			//Game::GetInstance()->AddState(QuickTimeState::GetInstance());
			Total = (((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) + m_nNumQtCorrect) * 15));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);

			//Cool idea to give you a better chance against harder monsters with more potential damage

			if (((Minion*)_To)->GetAIType() == Minion::Off_AI)
			{
				if (rand() % 20 > 1)
				{
					DealCounterDamage(_To, _From);
					return 0;
				}
			}

			string message = "You Slash the ";
			message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
			SetAction(message);
			m_bShake = true;
		}
	}
	else if (_From->GetType() == iObject::OBJ_MINION)// _From == Minion
	{
		for (size_t i = 1; i < m_pHeroes.size(); i++)
		{
			if (((Companion*)m_pHeroes[i])->GetCoType() == Companion::Companion_Type::Tank)
			{
				if (((Companion*)m_pHeroes[i])->GetBlock())
				{
					BlockAttack(_From, m_pHeroes[i]);
					localBlock = ((Companion*)m_pHeroes[i])->GetBlock();
					((Companion*)m_pHeroes[i])->SetBlock(false);
					return 0;
				}
			}
		}

		if (localBlock == false)
		{
			Total = (rand() % (10 * ((Minion*)_From)->GetMods().DamageLevel)) * ((Minion*)_From)->GetMods().DamageLevel;

			if (_To->GetType() == iObject::OBJ_PLAYER)
			{
				RuneManager::DamageReduction(InventoryState::GetInstance()->GetArmorSlot1(), ((Minion*)_From)->GetAffinity()) * Total;
				((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
				if (rand() % 20 > 13)
				{
					DealCounterDamage(_To, _From);
					return 0;
				}
				m_bShake = true;

			}
			if (_To->GetType() == iObject::OBJ_COMPANION)
			{
				((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
				if (((Companion*)_To)->GetCoType() == Companion::Melee)
				{
					if (rand() % 20 > 13)
					{
						DealCounterDamage(_To, _From);
						return 0;
					}
				}
			}
		}
	}
	else if (_From->GetType() == iObject::OBJ_COMPANION)
	{

		for (size_t i = 0; i < m_pEnemies.size(); i++)
		{
			if (((Minion*)m_pEnemies[i])->GetAIType() == Minion::AI_Type::Def_AI)
			{
				if (((Minion*)m_pEnemies[i])->m_Block)
				{
					BlockAttack(_From, m_pEnemies[i]);
					localBlock = ((Minion*)m_pEnemies[i])->m_Block;
					((Minion*)m_pEnemies[i])->m_Block = false;
					return 0;
				}
			}
		}

		if (!localBlock)
		{
			Total = rand() % 15 + 30;
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			string message = "Your Ally attacks the ";
			message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
			SetAction(message += "!");
			m_bShake = true;

		}
	}

	return Total;
}

int CombatState::DealMagicDamage(Object* _From, Object* _To, int _spell)
{
	int Total = 0;
	RuneManager mag;

	if (_From->GetType() == iObject::OBJ_PLAYER)
	{

#pragma region moreSpells
		InventoryState* pInventory = InventoryState::GetInstance();
		Runes temp1;
		temp1.SetElement(pInventory->m_vRing[0].GetElement());
		temp1.SetTier(pInventory->m_vRing[0].GetTier());

		Runes temp2;
		temp2.SetElement(pInventory->m_vRing[1].GetElement());
		temp2.SetTier(pInventory->m_vRing[1].GetTier());

		Runes temp3;
		temp3.SetElement(pInventory->m_vRing[2].GetElement());
		temp3.SetTier(pInventory->m_vRing[2].GetTier());

		string spell1;
		switch (temp1.GetElement())
		{
		case Fire:
		{
					 if (temp1.GetTier() == 1)
					 {
						 spell1 = "FireBolt1";
					 }
					 if (temp1.GetTier() == 2)
					 {
						 spell1 = "FireBolt2";
					 }
					 if (temp1.GetTier() == 3)
					 {
						 spell1 = "FireBolt3";
					 }
		}
			break;
		case Water:
		{
					  if (temp1.GetTier() == 1)
					  {
						  spell1 = "WaterBolt1";
					  }
					  if (temp1.GetTier() == 2)
					  {
						  spell1 = "WaterBolt2";
					  }
					  if (temp1.GetTier() == 3)
					  {
						  spell1 = "WaterBolt3";
					  }
		}
			break;
		case Air:
		{
					if (temp1.GetTier() == 1)
					{
						spell1 = "WindBolt1";
					}
					if (temp1.GetTier() == 2)
					{
						spell1 = "WindBolt2";
					}
					if (temp1.GetTier() == 3)
					{
						spell1 = "WindBolt3";
					}
		}
			break;
		case Earth:
		{
					  if (temp1.GetTier() == 1)
					  {
						  spell1 = "Rock Throw1";
					  }
					  if (temp1.GetTier() == 2)
					  {
						  spell1 = "Rock Throw2";
					  }
					  if (temp1.GetTier() == 3)
					  {
						  spell1 = "Rock Throw3";
					  }
		}
			break;
		case None:
			break;
		default:
			break;
		}
		string spell2;
		RuneManager rmanager;
		ComboElements firstCombo = rmanager.ElementCombination(temp1.GetElement(), temp2.GetElement());

		if (rmanager.ToString(firstCombo).length() > 0)
		{
			switch (firstCombo)
			{
			case Steam:
				spell2 = "Steam";
				break;
			case Ice:
				spell2 = "Ice";
				break;
			case Lightning:
				spell2 = "Lightning";
				break;
			case Magma:
				spell2 = "Magma";
				break;
			case Dust:
				spell2 = "Dust";
				break;
			case Mud:
				spell2 = "Mud";
				break;
			case Inferno:
				spell2 = "Inferno";
				break;
			case Wave:
				spell2 = "Wave";
				break;
			case Earthquake:
				spell2 = "Earthquake";
				break;
			case Whirlwind:
				spell2 = "Whirlwind";
				break;
			default:
				break;
			}

		}

		string spell3;

		ComboElements SecondCombo = rmanager.ElementCombination(temp2.GetElement(), temp3.GetElement());

		if (rmanager.ToString(firstCombo).length() > 0)
		{
			switch (SecondCombo)
			{
			case Steam:
				spell3 = "Steam";
				break;
			case Ice:
				spell3 = "Ice";
				break;
			case Lightning:
				spell3 = "Lightning";
				break;
			case Magma:
				spell3 = "Magma";
				break;
			case Dust:
				spell3 = "Dust";
				break;
			case Mud:
				spell3 = "Mud";
				break;
			case Inferno:
				spell3 = "Inferno";
				break;
			case Wave:
				spell3 = "Wave";
				break;
			case Earthquake:
				spell3 = "Earthquake";
				break;
			case Whirlwind:
				spell3 = "Whirlwind";
				break;
			default:
				break;
			}
		}
#pragma endregion


		SetActionTimer(GetActionTimer() + 2);
		string stuff = "You Cast ";

		switch (_spell)
		{
		case 0:
			Elements e1;

			stuff += spell1.c_str();
			e1 = InventoryState::GetInstance()->GetRingSlot1();
			Total = ((mag.DamagetoBaseElement(e1, ((Minion*)_To)->GetAffinity()) * 50 + (m_nNumQtCorrect * 5)));

			break;
		case 1:
			ComboElements d1;

			stuff += spell2.c_str();
			d1 = mag.ElementCombination(InventoryState::GetInstance()->GetRingSlot1(), InventoryState::GetInstance()->GetRingSlot2());
			Total = ((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) * 50 + (m_nNumQtCorrect * 5)));
			break;
		case 2:
			ComboElements d2;

			stuff += spell3.c_str();
			d2 = mag.ElementCombination(InventoryState::GetInstance()->GetRingSlot2(), InventoryState::GetInstance()->GetRingSlot3());
			Total = ((mag.DamageComboElement(d2, ((Minion*)_To)->GetAffinity()) * 50 + (m_nNumQtCorrect * 5)));

			break;
		default:
			break;
		}

		stuff += " on the ";
		SetAction(stuff += Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);

		m_nNumQTCorrect = 0;
		//((Player*)_From)->RunQuickTime((((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + 3);
	}
	else
	{

	}
	return Total;
}
int CombatState::DealCounterDamage(Object* _From, Object* _To)
{
	int Total = 0;
	RuneManager mag;

	if (_From->GetType() == iObject::OBJ_PLAYER)
	{
		ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());
		m_nNumQTCorrect = 0;

		Total = ((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) * 50 + (m_nNumQTCorrect * 5)));
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
		string message = "You Counter the ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += "'s Attack!");
		m_bShake = true;

	}
	else if (_From->GetType() == iObject::OBJ_MINION)
	{
		Total = rand() % (10 * ((Minion*)_From)->GetMods().DamageLevel) + ((Minion*)_From)->GetMods().DamageLevel;
		if (_To->GetType() == iObject::OBJ_PLAYER)
			((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
		else if (_To->GetType() == iObject::OBJ_COMPANION)
			((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);

		string message = "The ";
		message += (Game::GetInstance()->GetString(((Minion*)_From)->GetName(0), ((Minion*)_From)->GetName(1)).c_str());
		SetAction(message += " Counters!");
		m_bShake = true;
	}

	else if (_From->GetType() == iObject::OBJ_COMPANION)
	{
		Total = rand() % 15 + 30;
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
		string message = "Your Ally attacks the ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += "!");
		m_bShake = true;
	}

	return Total;
}
int CombatState::BlockAttack(Object* _From, Object* _To)
{
	int Total = 0;
	RuneManager mag;

	if (_From->GetType() == iObject::OBJ_PLAYER)
	{
		string message = "The ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += " Intercepts your Attack!");
		m_bShake = true;

		ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());

		m_nNumQTCorrect = 0;

		Total = ((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) * 50 + (m_nNumQTCorrect * 5)));
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
	}
	else if (_From->GetType() == iObject::OBJ_MINION)
	{
		Total = rand() % (10 * ((Minion*)_From)->GetMods().DamageLevel) + ((Minion*)_From)->GetMods().DamageLevel;
		((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
		string message = "Your Ally Intercepts the ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += "'s  Attack!");
		m_bShake = true;

	}
	else if (_From->GetType() == iObject::OBJ_COMPANION)
	{
		string message = "The ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += " Intercepts your Ally's Attack!");

		Total = rand() % 15 + 30;
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
		m_bShake = true;

	}
	return Total;
}
int CombatState::HealAlly(Object* _From, Object* _To)
{
	int Total;
	RuneManager mag;

	Total = rand() % 30 + 20;
	if (_From->GetType() == iObject::OBJ_PLAYER)
	{
		((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() + Total);
	}
	else if (_From->GetType() == iObject::OBJ_MINION)
	{
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() + Total);
	}
	else if (_From->GetType() == iObject::OBJ_COMPANION)
	{
		if (_To->GetType() == iObject::OBJ_PLAYER)
		{
			((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() + Total);

			if (((Player*)_To)->GetHealth() > ((Player*)_To)->GetMaxHealth())
				((Player*)_To)->SetHealth(((Player*)_To)->GetMaxHealth());
		}
		else
		{
			((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() + Total);
			if (((Companion*)_To)->GetHealth() > ((Companion*)_To)->GetMaxHealth())
				((Companion*)_To)->SetHealth(((Companion*)_To)->GetMaxHealth());
		}

	}

	return Total;
}
int CombatState::DealAOEDamage(Object* _From, Object* _To)
{
	int Total = 0;
	RuneManager mag;

	if (_From->GetType() == iObject::OBJ_PLAYER)
	{

	}
	else if (_From->GetType() == iObject::OBJ_MINION)
	{
		if (m_pHeroes.size() == 1) // attack player and damage self
		{
			for (size_t i = 0; i < m_pHeroes.size(); i++)
			{
				DealMeleeDamage(_From, _To);
			}
			((Minion*)_From)->SetHealth(((Minion*)_From)->GetHealth() - 10);
		}
		else if (m_pHeroes.size() > 1)
		{
			for (size_t i = 0; i < m_pHeroes.size(); i++)
			{
				DealMeleeDamage(_From, m_pHeroes[i]);
			}
		}
	}
	return Total;
}

bool CombatState::TakeTurn(Object* _this)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = BitmapFontManager::GetInstance();
	CombatState* pCombat = CombatState::GetInstance();
	SGD::Rectangle PlayerSelection{ 0, 0, 0, 0 };

	switch (_this->GetType())
	{
#pragma region PlayerTakeTurn
	case iObject::OBJ_PLAYER:
	{
								if (((Player*)_this)->GetHealth() < 0)
								{
									return false;
								}

								if (!selected)
								{
									float posX = 200.0f;
									PlayerSelection = { posX, (float)(420 + 50 * m_nCursor), posX + 40, (float)(430 + 50 * m_nCursor) };

									pGraphics->DrawString("Melee", SGD::Point{ 250, 420 }, SGD::Color(255, 255, 255, 255));

									if (CombatState::GetInstance()->GetCooldown())
									{
										pGraphics->DrawString("Magic", SGD::Point{ 250, 470 }, SGD::Color(150, 255, 255, 255));
									}
									else
									{
										pGraphics->DrawString("Magic", SGD::Point{ 250, 470 }, SGD::Color(255, 255, 255, 255));
									}

									//pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));

									pCombat->SetAction("Choose Action");
									if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
										m_nCursor--;

									if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
										m_nCursor++;

									if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
										m_nCursor--;

									if (m_nCursor < 0)
										m_nCursor = 0;
									if (m_nCursor > 1)
										m_nCursor = 1;

									if (pInput->IsKeyPressed(SGD::Key::Enter)) //First Selection >> Action
									{
										//if
										if (m_nCursor == 0)
										{
											ActionSelected = m_nCursor;
											selected = true;
											m_nCursor = 0;
											SetCooldown(false);
										}

										if (!GetCooldown() && m_nCursor == 1)
										{
											ActionSelected = m_nCursor;
											selected = true;
											m_nCursor = 0;
										}
									}
									if (PlayerSelection.left < PlayerSelection.right)
										pGraphics->DrawRectangle(PlayerSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));
								}
								else //Action selected, now pick target
								{
									if (ActionSelected == 0) //Melee
									{
										PlayerSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 150, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 110, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y + 40 };
										pCombat->SetAction("Choose Target");
										if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
										{
											m_nCursor--;
										}
										if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
										{
											m_nCursor++;
										}

										if (m_nCursor < 0)
											m_nCursor = 0;
										if (m_nCursor > pCombat->GetEnemies().size() - 1)
											m_nCursor = pCombat->GetEnemies().size() - 1;

										if (((Minion*)pCombat->GetEnemies()[m_nCursor])->GetHealth() <= 0)
											m_nCursor++;

										if (m_nCursor < 0)
											m_nCursor = 0;
										if (m_nCursor > pCombat->GetEnemies().size() - 1)
											m_nCursor = pCombat->GetEnemies().size() - 1;
										

										if (pInput->IsKeyPressed(SGD::Key::Enter)) //Second Selection >> Target
										{
											entered = true;
											((Player*)_this)->SetAttacking(true);
											Game::GetInstance()->AddState(QuickTimeState::GetInstance());
										}
										if (entered)
										{
											if (QuickTimeState::GetInstance()->GetCurrentQT()->GetIsOver())
											{
												entered = false;
												selected = false;
												QuickTimeState::GetInstance()->StopQuickTime();
												TakeAction(ActionSelected, _this, m_nCursor);
												m_nCursor = 0;
												return true;
											}
										}

										if (PlayerSelection.left < PlayerSelection.right)
											pGraphics->DrawRectangle(PlayerSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));

										((Player*)_this)->ResetAnimation();
									}
									else if (ActionSelected == 1) //Magic
									{
										if (spellSelect == -1)
										{
											pCombat->SetAction("Choose Spell");

											float posX = 250.0f + (m_nCursor * 100);
											PlayerSelection = { posX, 500, posX + 60, 510 };

											if (pInput->IsKeyPressed(SGD::Key::Left) || pInput->IsKeyPressed(SGD::Key::W))
											{
												m_nCursor--;
											}
											if (pInput->IsKeyPressed(SGD::Key::Right) || pInput->IsKeyPressed(SGD::Key::S))
											{
												m_nCursor++;
											}

#pragma region spells
											InventoryState* pInventory = InventoryState::GetInstance();
											Runes temp1;
											temp1.SetElement(pInventory->m_vRing[0].GetElement());
											temp1.SetTier(pInventory->m_vRing[0].GetTier());

											Runes temp2;
											temp2.SetElement(pInventory->m_vRing[1].GetElement());
											temp2.SetTier(pInventory->m_vRing[1].GetTier());

											Runes temp3;
											temp3.SetElement(pInventory->m_vRing[2].GetElement());
											temp3.SetTier(pInventory->m_vRing[2].GetTier());

											string spell1;
											switch (temp1.GetElement())
											{
											case Fire:
											{
														 if (temp1.GetTier() == 1)
														 {
															 spell1 = "FireBolt1";
														 }
														 if (temp1.GetTier() == 2)
														 {
															 spell1 = "FireBolt2";
														 }
														 if (temp1.GetTier() == 3)
														 {
															 spell1 = "FireBolt3";
														 }
											}
												break;
											case Water:
											{
														  if (temp1.GetTier() == 1)
														  {
															  spell1 = "WaterBolt1";
														  }
														  if (temp1.GetTier() == 2)
														  {
															  spell1 = "WaterBolt2";
														  }
														  if (temp1.GetTier() == 3)
														  {
															  spell1 = "WaterBolt3";
														  }
											}
												break;
											case Air:
											{
														if (temp1.GetTier() == 1)
														{
															spell1 = "WindBolt1";
														}
														if (temp1.GetTier() == 2)
														{
															spell1 = "WindBolt2";
														}
														if (temp1.GetTier() == 3)
														{
															spell1 = "WindBolt3";
														}
											}
												break;
											case Earth:
											{
														  if (temp1.GetTier() == 1)
														  {
															  spell1 = "Rock Throw1";
														  }
														  if (temp1.GetTier() == 2)
														  {
															  spell1 = "Rock Throw2";
														  }
														  if (temp1.GetTier() == 3)
														  {
															  spell1 = "Rock Throw3";
														  }
											}
												break;
											case None:
												break;
											default:
												break;
											}
											string spell2;
											RuneManager rmanager;
											ComboElements firstCombo = rmanager.ElementCombination(temp1.GetElement(), temp2.GetElement());

											if (rmanager.ToString(firstCombo).length() > 0)
											{
												switch (firstCombo)
												{
												case Steam:
													spell2 = "Steam";
													break;
												case Ice:
													spell2 = "Ice";
													break;
												case Lightning:
													spell2 = "Lightning";
													break;
												case Magma:
													spell2 = "Magma";
													break;
												case Dust:
													spell2 = "Dust";
													break;
												case Mud:
													spell2 = "Mud";
													break;
												case Inferno:
													spell2 = "Inferno";
													break;
												case Wave:
													spell2 = "Wave";
													break;
												case Earthquake:
													spell2 = "Earthquake";
													break;
												case Whirlwind:
													spell2 = "Whirlwind";
													break;
												default:
													break;
												}

											}

											string spell3;

											ComboElements SecondCombo = rmanager.ElementCombination(temp2.GetElement(), temp3.GetElement());

											if (rmanager.ToString(firstCombo).length() > 0)
											{
												switch (SecondCombo)
												{
												case Steam:
													spell3 = "Steam";
													break;
												case Ice:
													spell3 = "Ice";
													break;
												case Lightning:
													spell3 = "Lightning";
													break;
												case Magma:
													spell3 = "Magma";
													break;
												case Dust:
													spell3 = "Dust";
													break;
												case Mud:
													spell3 = "Mud";
													break;
												case Inferno:
													spell3 = "Inferno";
													break;
												case Wave:
													spell3 = "Wave";
													break;
												case Earthquake:
													spell3 = "Earthquake";
													break;
												case Whirlwind:
													spell3 = "Whirlwind";
													break;
												default:
													break;
												}
											}


											for (size_t i = 0; i < pInventory->m_vRing.size(); i++)
											{
												switch (i)
												{
												case 0:
													if (((Player*)_this)->GetSpell1Cool())
														pFont->Render("Bernardo", spell1.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 100, 255, 255, 255 });
													else
														pFont->Render("Bernardo", spell1.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 255, 255, 255, 255 });
													break;
												case 1:
													if (((Player*)_this)->GetSpell2Cool())
														pFont->Render("Bernardo", spell2.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 100, 255, 255, 255 });
													else
														pFont->Render("Bernardo", spell2.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 255, 255, 255, 255 });
													break;
												case 2:
													if (((Player*)_this)->GetSpell3Cool())
														pFont->Render("Bernardo", spell3.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 100, 255, 255, 255 });
													else
														pFont->Render("Bernardo", spell3.c_str(), { (float)(250 + (i * 100)), 480 }, 1, { 255, 255, 255, 255 });
													break;
												default:
													break;
												}
											}
#pragma endregion
											bool spellActive; //If no spell is active, selection needs to return as they cannot cast spells

											if (((Player*)_this)->GetSpell1Cool())
												m_nCursor++;
											else
												spellActive = true;
											if (((Player*)_this)->GetSpell2Cool())
												m_nCursor++;
											else
												spellActive = true;
											if (((Player*)_this)->GetSpell3Cool())
												m_nCursor++;
											else
												spellActive = true;

											if (m_nCursor < 0)
												m_nCursor = 0;
											if (m_nCursor > pInventory->m_vRing.size() - 1)
												m_nCursor = pInventory->m_vRing.size() - 1;

											if (pInput->IsKeyPressed(SGD::Key::Enter))
											{
												spellSelect = m_nCursor;
												m_nCursor = 0;
											}
											if (PlayerSelection.left < PlayerSelection.right && pInventory->m_vRing.size() > 0)
												pGraphics->DrawRectangle(PlayerSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0)); //
										}
										else // spellSelect is set, choose target
										{
											PlayerSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x + 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y + 40 };
											pCombat->SetAction("Choose Target");

											if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
											{
												m_nCursor--;
											}
											if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
											{
												m_nCursor++;
											}

											if (m_nCursor < 0)
												m_nCursor = 0;
											if (m_nCursor > pCombat->GetEnemies().size() - 1)
												m_nCursor = pCombat->GetEnemies().size() - 1;

											if (((Minion*)m_pEnemies[m_nCursor])->GetHealth() <= 0)
												m_nCursor++;

											if (m_nCursor < 0)
												m_nCursor = 0;
											if (m_nCursor > pCombat->GetEnemies().size() - 1)
												m_nCursor = pCombat->GetEnemies().size() - 1;

											if (pInput->IsKeyPressed(SGD::Key::Enter)) //Second Selection >> Target
											{
												selected = false;
												((Player*)_this)->SetAttacking(true);
												TakeAction(ActionSelected, _this, m_nCursor, spellSelect);
												spellSelect = -1;
												m_nCursor = 0;
												return true;
											}
											if (PlayerSelection.left < PlayerSelection.right)
												pGraphics->DrawRectangle(PlayerSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0)); //
										}
									}
								}
								return false;
								break;
#pragma endregion
	}
#pragma region CompTakeTurn
	case iObject::OBJ_COMPANION:
	{
								   float posX = 200.0f;
								   SGD::Rectangle CompanionSelection{ posX, (float)(420 + 50 * m_nCursor), posX + 40, (float)(430 + 50 * m_nCursor) };

								   if (((Companion*)_this)->GetHealth() < 0)
								   {
									   return false;
								   }

								   switch (((Companion*)_this)->GetCoType())
								   {
#pragma region cleric
								   case Companion::Companion_Type::Cleric:
								   {

																			 if (selected == false) //Pick an action (melee magic or armor)
																			 {
																				 pGraphics->DrawString("Melee", SGD::Point{ 250, 420 }, SGD::Color(255, 255, 255, 255));
																				 if (false) //cooldown
																				 {
																					 pGraphics->DrawString("Heal", SGD::Point{ 250, 470 }, SGD::Color(150, 255, 255, 255));
																				 }
																				 else
																				 {
																					 pGraphics->DrawString("Heal", SGD::Point{ 250, 470 }, SGD::Color(255, 255, 255, 255));
																				 }
																				 //pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));
																				 pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));

																				 pCombat->SetAction("Choose Action");
																				 if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
																					 m_nCursor--;

																				 if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
																					 m_nCursor++;

																				 if (m_nCursor < 0)
																					 m_nCursor = 0;
																				 if (m_nCursor > 1)
																					 m_nCursor = 1;

																				 if (pInput->IsKeyPressed(SGD::Key::Enter)) //First Selection >> Action
																				 {
																					 //if
																					 if (m_nCursor == 0)
																					 {
																						 ActionSelected = m_nCursor;
																						 selected = true;
																						 m_nCursor = 0;
																					 }

																					 if (m_nCursor == 1)
																					 {
																						 ActionSelected = CombatState::ActionType::Heal;
																						 selected = true;
																						 m_nCursor = 0;
																					 }
																				 }

																			 }
																			 else//Action selected, now pick target
																			 {
																				 pCombat->SetAction("Choose Target");
																				 CompanionSelection = { ((Player*)m_pHeroes[m_nCursor])->GetPosition().x - 150, ((Player*)m_pHeroes[m_nCursor])->GetPosition().y , ((Player*)m_pHeroes[m_nCursor])->GetPosition().x - 110, ((Player*)m_pHeroes[m_nCursor])->GetPosition().y + 40 };

																				 if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
																				 {
																					 m_nCursor--;
																				 }
																				 if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
																				 {
																					 m_nCursor++;
																				 }

																				 if (ActionSelected == CombatState::ActionType::Heal)
																				 {
																					 if (m_nCursor < 0)
																						 m_nCursor = 0;
																					 if (m_nCursor > m_pHeroes.size() - 1)
																						 m_nCursor = m_pHeroes.size() - 1;

																					 if (m_nCursor < 0)
																						 m_nCursor = 0;
																					 if (m_nCursor > m_pHeroes.size() - 1)
																						 m_nCursor = m_pHeroes.size() - 1;

																					 if (((Player*)m_pHeroes[m_nCursor])->GetHealth() <= 0)
																						 m_nCursor++;

																					 if (m_nCursor < 0)
																						 m_nCursor = 0;
																					 if (m_nCursor > m_pHeroes.size() - 1)
																						 m_nCursor = m_pHeroes.size() - 1;

																				 }
																				 else
																				 {
																					 if (m_nCursor < 0)
																						 m_nCursor = 0;
																					 if (m_nCursor > m_pEnemies.size() - 1)
																						 m_nCursor = m_pEnemies.size() - 1;

																					 if (((Minion*)pCombat->GetEnemies()[m_nCursor])->GetHealth() <= 0)
																						 m_nCursor++;

																					 if (m_nCursor < 0)
																						 m_nCursor = 0;
																					 if (m_nCursor > m_pEnemies.size() - 1)
																						 m_nCursor = m_pEnemies.size() - 1;

																					 CompanionSelection = { ((Minion*)m_pEnemies[m_nCursor])->GetPosition().x - 150, ((Minion*)m_pEnemies[m_nCursor])->GetPosition().y, ((Minion*)m_pEnemies[m_nCursor])->GetPosition().x -110, ((Minion*)m_pEnemies[m_nCursor])->GetPosition().y + 40 };
																				 }


																				 if (pInput->IsKeyPressed(SGD::Key::Enter)) //Second Selection >> Target
																				 {
																					 selected = false;
																					 ((Companion*)_this)->SetAttacking(true);

																					 TakeAction(ActionSelected, _this, m_nCursor);
																					 m_nCursor = 0;
																					 return true;
																				 }
																				 ((Companion*)_this)->SetAnimation(true);
																				 ((Companion*)_this)->ResetAnimation();

																				 if (CompanionSelection.left < CompanionSelection.right)
																					 pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));
																			 }


																			 return false;
								   }
									   break;
#pragma endregion
#pragma region Melee
								   case Companion::Companion_Type::Melee:
								   {
																			if (selected == false) //Pick an action (melee magic or armor)
																			{
																				pGraphics->DrawString("Melee", SGD::Point{ 250, 420 }, SGD::Color(255, 255, 255, 255));
																				if (false)
																				{
																					pGraphics->DrawString("Fury", SGD::Point{ 250, 470 }, SGD::Color(150, 255, 255, 255)); //AOE attack
																				}
																				else
																				{
																					pGraphics->DrawString("Fury", SGD::Point{ 250, 470 }, SGD::Color(255, 255, 255, 255));
																				}
																				//pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));
																				pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));

																				pCombat->SetAction("Choose Action");
																				if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
																					m_nCursor--;

																				if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
																					m_nCursor++;

																				if (m_nCursor < 0)
																					m_nCursor = 0;
																				if (m_nCursor > 1)
																					m_nCursor = 1;

																				if (pInput->IsKeyPressed(SGD::Key::Enter)) //First Selection >> Action
																				{
																					//if
																					if (m_nCursor == 0)
																					{
																						ActionSelected = m_nCursor;
																						selected = true;
																						m_nCursor = 0;
																						CombatState::GetInstance()->SetCooldown(false);
																					}

																					if (!CombatState::GetInstance()->GetCooldown() && m_nCursor == 1)
																					{
																						ActionSelected = m_nCursor;
																						selected = true;
																						m_nCursor = 0;
																					}
																				}

																			}
																			else //Action selected, now pick target
																			{
																				pCombat->SetAction("Choose Target");
																				if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
																				{
																					m_nCursor--;
																				}
																				if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
																				{
																					m_nCursor++;
																				}
																				if (m_nCursor < 0)
																					m_nCursor = 0;
																				if (m_nCursor > m_pEnemies.size() - 1)
																					m_nCursor = m_pEnemies.size() - 1;


																				if (pInput->IsKeyPressed(SGD::Key::Enter)) //Second Selection >> Target
																				{
																					selected = false;
																					((Companion*)_this)->SetAttacking(true);
																					TakeAction(ActionSelected, _this, m_nCursor);
																					m_nCursor = 0;
																					return true;
																				}
																				((Companion*)_this)->SetAnimation(true);


																				((Companion*)_this)->ResetAnimation();
																			}


																			return false;
								   }
									   break;
#pragma endregion
#pragma region Mage
								   case Companion::Companion_Type::Mage:
								   {
																		   pGraphics->DrawString("Melee", SGD::Point{ 250, 420 }, SGD::Color(255, 255, 255, 255));
																		   if (CombatState::GetInstance()->GetCooldown())
																		   {
																			   pGraphics->DrawString("Magic", SGD::Point{ 250, 470 }, SGD::Color(150, 255, 255, 255));
																		   }
																		   else
																		   {
																			   pGraphics->DrawString("Magic", SGD::Point{ 250, 470 }, SGD::Color(255, 255, 255, 255));
																		   }
																		   //pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));
																		   pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));


																		   if (selected == false) //Pick an action (melee magic or armor)
																		   {
																			   pCombat->SetAction("Choose Action");
																			   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
																				   m_nCursor--;

																			   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
																				   m_nCursor++;

																			   if (m_nCursor < 0)
																				   m_nCursor = 0;
																			   if (m_nCursor > 1)
																				   m_nCursor = 1;

																			   if (pInput->IsKeyPressed(SGD::Key::Enter)) //First Selection >> Action
																			   {
																				   //if
																				   if (m_nCursor == 0)
																				   {
																					   ActionSelected = m_nCursor;
																					   selected = true;
																					   m_nCursor = 0;
																					   CombatState::GetInstance()->SetCooldown(false);
																				   }

																				   if (!CombatState::GetInstance()->GetCooldown() && m_nCursor == 1)
																				   {
																					   ActionSelected = m_nCursor;
																					   selected = true;
																					   m_nCursor = 0;
																				   }
																			   }

																		   }
																		   else //Action selected, now pick target
																		   {
																			   pCombat->SetAction("Choose Target");
																			   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
																			   {
																				   m_nCursor--;
																			   }
																			   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
																			   {
																				   m_nCursor++;
																			   }
																			   if (m_nCursor < 0)
																				   m_nCursor = 0;
																			   if (m_nCursor > pCombat->GetEnemies().size() - 1)
																				   m_nCursor = pCombat->GetEnemies().size() - 1;


																			   if (pInput->IsKeyPressed(SGD::Key::Enter)) //Second Selection >> Target
																			   {
																				   selected = false;
																				   ((Companion*)_this)->SetAttacking(true);

																				   TakeAction(ActionSelected, _this, m_nCursor);
																				   m_nCursor = 0;
																				   return true;
																			   }
																			   ((Companion*)_this)->SetAnimation(true);


																			   ((Companion*)_this)->ResetAnimation();
																		   }


																		   return false;
								   }
									   break;
#pragma endregion
#pragma region Tank
								   case Companion::Companion_Type::Tank:
								   {
																		   pGraphics->DrawString("Melee", SGD::Point{ 250, 420 }, SGD::Color(255, 255, 255, 255));

																		   pGraphics->DrawString("Block", SGD::Point{ 250, 470 }, SGD::Color(255, 255, 255, 255));

																		   //pGraphics->DrawString("Armor", SGD::Point{ 250, 520 }, SGD::Color(255, 255, 255, 255));
																		   pGraphics->DrawRectangle(CompanionSelection, SGD::Color(255, 0, 255, 0), SGD::Color(255, 0, 255, 0));

																		   if (selected == false) //Pick an action (melee magic or armor)
																		   {
																			   pCombat->SetAction("Choose Action");
																			   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
																				   m_nCursor--;

																			   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
																				   m_nCursor++;

																			   if (m_nCursor < 0)
																				   m_nCursor = 0;
																			   if (m_nCursor > 1)
																				   m_nCursor = 1;

																			   if (pInput->IsKeyPressed(SGD::Key::Enter)) //First Selection >> Action
																			   {
																				   //if
																				   if (m_nCursor == 0)
																				   {
																					   ActionSelected = m_nCursor;
																					   selected = true;
																					   m_nCursor = 0;
																					   CombatState::GetInstance()->SetCooldown(false);
																				   }

																				   if (m_nCursor == 1)
																				   {
																					   ActionSelected = 2;
																					   selected = true;
																					   m_nCursor = 0;
																				   }
																			   }

																		   }
																		   else //Action selected, now pick target
																		   {
																			   if (ActionSelected == 2)
																			   {
																				   ((Companion*)_this)->SetBlock(true);
																				   selected = false;
																				   TakeAction(ActionSelected, _this, m_nCursor);
																				   m_nCursor = 0;
																				   return true;
																			   }

																			   pCombat->SetAction("Choose Target");
																			   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W))
																			   {
																				   m_nCursor--;
																			   }
																			   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S))
																			   {
																				   m_nCursor++;
																			   }
																			   if (m_nCursor < 0)
																				   m_nCursor = 0;
																			   if (m_nCursor > pCombat->GetEnemies().size() - 1)
																				   m_nCursor = pCombat->GetEnemies().size() - 1;


																			   if (pInput->IsKeyPressed(SGD::Key::Enter)) //Second Selection >> Target
																			   {
																				   selected = false;
																				   ((Companion*)_this)->SetAttacking(true);

																				   TakeAction(ActionSelected, _this, m_nCursor);
																				   m_nCursor = 0;
																				   return true;
																			   }
																			   ((Companion*)_this)->SetAnimation(true);


																			   ((Companion*)_this)->ResetAnimation();
																		   }


																		   return false;
								   }
									   break;
#pragma endregion
								   default:
									   break;
								   }


								   ((Companion*)_this)->SetAnimation(true);
								   ((Companion*)_this)->ResetAnimation();

								   return true;
	}
		break;
#pragma endregion
#pragma region MinionTakeTurn
	case iObject::OBJ_MINION:
	{
								int target = 0;

								switch (((Minion*)_this)->GetAIType())
								{
								case Minion::AI_Type::Minion_AI:
									if (((Minion*)_this)->GetHealth() > 0)
									{
										target = rand() % pCombat->GetHeroes().size();
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::Melee, _this, target);
										((Minion*)_this)->SetAnimation(true);

										((Minion*)_this)->ResetAnimation();
									}
									break;
								case Minion::AI_Type::Off_AI:
									if (((Minion*)_this)->GetHealth() > 0)
									{
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::Melee, _this, target);
										((Minion*)_this)->SetAnimation(true);

										((Minion*)_this)->ResetAnimation();
									}
									break;
								case Minion::AI_Type::Def_AI:
									if (((Minion*)_this)->GetHealth() > 0)
									{
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::Melee, _this, target);
										((Minion*)_this)->SetAnimation(true);

										((Minion*)_this)->ResetAnimation();
									}
									break;
								case Minion::AI_Type::Heal_AI:
									if (((Minion*)_this)->GetHealth() > 0)
									{
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::Melee, _this, target);
										((Minion*)_this)->SetAnimation(true);

										((Minion*)_this)->ResetAnimation();
									}
									break;
								case Minion::AI_Type::AOE_AI:
									if (((Minion*)_this)->GetHealth() > 0)
									{
										int AI = rand() % 20;
										if (AI <= 15) //AOE attack
											TakeAction(CombatState::ActionType::AOE, _this, target);
										else
											TakeAction(CombatState::ActionType::Melee, _this, target);

										((Minion*)_this)->SetAnimation(true);
										((Minion*)_this)->ResetAnimation();

									}
									break;
								case Minion::AI_Type::Mini_Boss:
									switch (((Minion*)_this)->GetAffinity())
									{
									case Elements::Earth:
										if (((Minion*)_this)->GetHealth() > 0)
										{
											target = rand() % pCombat->GetHeroes().size();
											pCombat->SetActionTimer(1);
											TakeAction(CombatState::ActionType::Melee, _this, target);
											((Minion*)_this)->SetAnimation(true);

											((Minion*)_this)->ResetAnimation();
										}
										break;
									case Elements::Water:
										if (((Minion*)_this)->GetHealth() > 0)
										{
											target = rand() % pCombat->GetHeroes().size();
											pCombat->SetActionTimer(1);
											TakeAction(CombatState::ActionType::Melee, _this, target);
											((Minion*)_this)->SetAnimation(true);

											((Minion*)_this)->ResetAnimation();
										}
										break;
									case Elements::Air:
										if (((Minion*)_this)->GetHealth() > 0)
										{
											target = rand() % pCombat->GetHeroes().size();
											pCombat->SetActionTimer(1);
											TakeAction(CombatState::ActionType::Melee, _this, target);
											((Minion*)_this)->SetAnimation(true);

											((Minion*)_this)->ResetAnimation();
										}
										break;
									case Elements::Fire:
										break;
									default:
										if (((Minion*)_this)->GetHealth() > 0)
										{
											target = rand() % pCombat->GetHeroes().size();
											pCombat->SetActionTimer(1);
											TakeAction(CombatState::ActionType::Melee, _this, target);
											((Minion*)_this)->SetAnimation(true);

											((Minion*)_this)->ResetAnimation();
										}
										break;
									}
									break;
								case Minion::AI_Type::Level_Boss:
									switch (((Minion*)_this)->GetAffinity())
									{
									case Elements::Earth:
										target = rand() % pCombat->GetHeroes().size();
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::Melee, _this, target);
										((Minion*)_this)->ResetAnimation();
										break;
									case Elements::Water:
										break;
									case Elements::Air:
										break;
									case Elements::Fire:
										target = rand() % pCombat->GetHeroes().size();
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::AOE, _this, target);
										((Minion*)_this)->ResetAnimation();
										break;
									default:
										break;
									}
									break;
								case Minion::AI_Type::Final_Boss:
									if (((Minion*)_this)->GetHealth() > 0)
									{
										if (((Minion*)_this)->GetHealth() >= 100 && ((Minion*)_this)->GetHealth() < 150)
										{
											((Minion*)_this)->SetAffinity(Water);
										}
										if (((Minion*)_this)->GetHealth() >= 75 && ((Minion*)_this)->GetHealth() < 100)
										{
											((Minion*)_this)->SetAffinity(Air);
										}
										if (((Minion*)_this)->GetHealth() >= 50 && ((Minion*)_this)->GetHealth() < 75)
										{
											((Minion*)_this)->SetAffinity(Fire);
										}
										if (((Minion*)_this)->GetHealth() >= 0 && ((Minion*)_this)->GetHealth() < 50)
										{
											((Minion*)_this)->SetAffinity(((Elements)(rand()%4)));
										}

										target = rand() % pCombat->GetHeroes().size();
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::Melee, _this, target);
										((Minion*)_this)->SetAnimation(true);

										((Minion*)_this)->ResetAnimation();
									}
									break;
								default:
									break;
								}

								return true;
	}
#pragma endregion
	}
}

void CombatState::ShakeScreen(float elapsedTime)
{
	int randY = 0;
	int randX = 0;

	randX = rand() % 10 - 5;
	randY = rand() % 10 - 5;


	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		SGD::Rectangle tempShakeRect = { ((float)randX / 10.0f), ((float)randY / 10.0f), ((float)randX / 10.0f), ((float)randY / 10.0f) };

		if (m_pObjects[i]->GetType() == iObject::OBJ_PLAYER)
		{
			tempShakeRect.left += Playerrect.left;
			tempShakeRect.top += Playerrect.top;
			tempShakeRect.right += Playerrect.right;
			tempShakeRect.bottom += Playerrect.bottom;

			((Player*)m_pObjects[i])->SetRect(tempShakeRect);
		}
		else if (m_pObjects[i]->GetType() == iObject::OBJ_COMPANION)
		{
			tempShakeRect.left += Companion1rect.left;
			tempShakeRect.top += Companion1rect.top;
			tempShakeRect.right += Companion1rect.right;
			tempShakeRect.bottom += Companion1rect.bottom;

			((Companion*)m_pObjects[i])->SetCompanionRect1(tempShakeRect);

			tempShakeRect = { ((float)randX / 10.0f), ((float)randY / 10.0f), ((float)randX / 10.0f), ((float)randY / 10.0f) };

			tempShakeRect.left += Companion2rect.left;
			tempShakeRect.top += Companion2rect.top;
			tempShakeRect.right += Companion2rect.right;
			tempShakeRect.bottom += Companion2rect.bottom;

			((Companion*)m_pObjects[i])->SetCompanionRect2(tempShakeRect);
		}
		else if (m_pObjects[i]->GetType() == iObject::OBJ_MINION)
		{
			tempShakeRect.left += Enemy1rect.left;
			tempShakeRect.top += Enemy1rect.top;
			tempShakeRect.right += Enemy1rect.right;
			tempShakeRect.bottom += Enemy1rect.bottom;

			((Minion*)m_pObjects[i])->SetMinionRect1(tempShakeRect);

			tempShakeRect = { ((float)randX / 10.0f), ((float)randY / 10.0f), ((float)randX / 10.0f), ((float)randY / 10.0f) };

			tempShakeRect.left += Enemy2rect.left;
			tempShakeRect.top += Enemy2rect.top;
			tempShakeRect.right += Enemy2rect.right;
			tempShakeRect.bottom += Enemy2rect.bottom;

			((Minion*)m_pObjects[i])->SetMinionRect2(tempShakeRect);

			tempShakeRect = { ((float)randX / 10.0f), ((float)randY / 10.0f), ((float)randX / 10.0f), ((float)randY / 10.0f) };

			tempShakeRect.left += Enemy3rect.left;
			tempShakeRect.top += Enemy3rect.top;
			tempShakeRect.right += Enemy3rect.right;
			tempShakeRect.bottom += Enemy3rect.bottom;

			((Minion*)m_pObjects[i])->SetMinionRect3(tempShakeRect);
		}
	}
}
void CombatState::ResetRects()
{
	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		if (m_pObjects[i]->GetType() == iObject::OBJ_PLAYER)
		{
			((Player*)m_pObjects[i])->SetRect(Playerrect);
		}
		else if (m_pObjects[i]->GetType() == iObject::OBJ_COMPANION)
		{
			((Companion*)m_pObjects[i])->SetCompanionRect1(Companion1rect);
			((Companion*)m_pObjects[i])->SetCompanionRect2(Companion2rect);
		}
		else if (m_pObjects[i]->GetType() == iObject::OBJ_MINION)
		{
			((Minion*)m_pObjects[i])->SetMinionRect1(Enemy1rect);
			((Minion*)m_pObjects[i])->SetMinionRect2(Enemy2rect);
			((Minion*)m_pObjects[i])->SetMinionRect3(Enemy3rect);
		}
	}
}

void CombatState::HandleTutorial()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager *pFont = BitmapFontManager::GetInstance();

	SGD::Point ptWorldCam = GameplayState::GetInstance()->GetWorldCam();

	SGD::Point heroPosition;
	SGD::Point portraitPosition;
	// - Location of the Dialog Box at the bottom of the screen.

	SGD::Rectangle DialogBoxOne;
	DialogBoxOne.left = 25;
	DialogBoxOne.top = Game::GetInstance()->GetScreenHeight() - 105;
	DialogBoxOne.right = Game::GetInstance()->GetScreenWidth() - 25;
	DialogBoxOne.bottom = Game::GetInstance()->GetScreenHeight() - 5;

	// - Location to print the strings within the dialog Box
	SGD::Point TextPositionOne;
	SGD::Point TextPositionTwo;

	TextPositionOne.x = DialogBoxOne.left + 40;
	TextPositionOne.y = DialogBoxOne.top + 20;
	TextPositionTwo.x = DialogBoxOne.left + 20;
	TextPositionTwo.y = DialogBoxOne.top + 50;

	portraitPosition.x = DialogBoxOne.left - 10;
	portraitPosition.y = DialogBoxOne.top - 30;

	if (CurrentTurn == m_pHeroes[0]->GetTurnPos())
	{
		if (Game::GetInstance()->GetIcelandic())
		{
			TextPositionOne.x = DialogBoxOne.left + 100;
			TextPositionTwo.x = DialogBoxOne.left + 150;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 120;
			TextPositionTwo.x = DialogBoxOne.left + 125;
		}

		heroPosition = { (float)((3 * 32) - ptWorldCam.x), (float)((8 * 32) - ptWorldCam.y) };

		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(GameplayState::GetInstance()->GetPortrait(), portraitPosition);
		pFont->Render("Dialog", Game::GetInstance()->GetString(9, 5).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(9, 6).c_str(), TextPositionTwo, .7f, SGD::Color(0, 0, 0));

	}
	else if (CurrentTurn == m_pHeroes[1]->GetTurnPos() || CurrentTurn == m_pHeroes[2]->GetTurnPos())
	{
		if (Game::GetInstance()->GetIcelandic())
		{
			TextPositionOne.x = DialogBoxOne.left + 50;
			TextPositionTwo.x = DialogBoxOne.left + 240;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 100;
			TextPositionTwo.x = DialogBoxOne.left + 200;
		}

		heroPosition = { (float)((3 * 32) - ptWorldCam.x), (float)((8 * 32) - ptWorldCam.y) };

		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(GameplayState::GetInstance()->GetPortrait(), portraitPosition);
		pFont->Render("Dialog", Game::GetInstance()->GetString(9, 9).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(10, 1).c_str(), TextPositionTwo, .7f, SGD::Color(0, 0, 0));

	}
	else
	{
		if (Game::GetInstance()->GetIcelandic())
		{
			TextPositionOne.x = DialogBoxOne.left + 80;
			TextPositionTwo.x = DialogBoxOne.left + 200;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 150;
			TextPositionTwo.x = DialogBoxOne.left + 200;
		}

		heroPosition = { (float)((3 * 32) - ptWorldCam.x), (float)((8 * 32) - ptWorldCam.y) };

		pGraphics->DrawRectangle(DialogBoxOne, SGD::Color(220, 215, 143), SGD::Color(0, 0, 0));
		pGraphics->DrawTexture(GameplayState::GetInstance()->GetPortrait(), portraitPosition);
		pFont->Render("Dialog", Game::GetInstance()->GetString(10, 2).c_str(), TextPositionOne, .7f, SGD::Color(0, 0, 0));
		pFont->Render("Dialog", Game::GetInstance()->GetString(10, 3).c_str(), TextPositionTwo, .7f, SGD::Color(0, 0, 0));
	}
}

void CombatState::DrawBackground()
{
	switch (GameplayState::GetInstance()->GetCurrentLevel())
	{
	case 1:
		SGD::GraphicsManager::GetInstance()->DrawTexture(Game::GetInstance()->m_hEarth1, { 0, 0 }, {}, {}, {255,255,255,255}, { 2.0f, 2.4f });
		break;
	case 2:
		SGD::GraphicsManager::GetInstance()->DrawTexture(Game::GetInstance()->m_hIce2, { 0, 0 }, {}, {}, { 255, 255, 255, 255 }, { 2.0f, 2.2f });
		break;
	case 3:
		SGD::GraphicsManager::GetInstance()->DrawTexture(Game::GetInstance()->m_hAir2, { 0, 0 }, {}, {}, { 255, 255, 255, 255 }, { 2.0f, 2.2f });
		break;
	case 4:
		SGD::GraphicsManager::GetInstance()->DrawTexture(Game::GetInstance()->m_hFire1, { 0, 0 }, {}, {}, { 255, 255, 255, 255 }, { 2.0f, 2.3f });
		break;
	case 5:
		SGD::GraphicsManager::GetInstance()->DrawTexture(Game::GetInstance()->m_hFinal1, { 0, 0 }, {}, {}, { 255, 255, 255, 255 }, { 2.0f, 2.2f });
		break;
	default:
		SGD::GraphicsManager::GetInstance()->DrawTexture(Game::GetInstance()->m_hEarth2, { 0, 0 }, {}, {}, { 255, 255, 255, 255 }, { 2.0f, 2.5f });
		break;
	}
}