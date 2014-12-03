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

CombatState* CombatState::GetInstance()
{
	static CombatState s_Instance;
	return &s_Instance;
}

void CombatState::Enter(void)
{
	CurrentTurn = 0;
	TurnIndex = 0;

	numPots = rand() % 3;
	numRunes = rand() % 2;

	Player* player = (Player*)GameplayState::GetInstance()->GetPlayer();
	player->SetCombat(true);
	player->CurrentTurn(&CurrentTurn);
	player->SetInit(rand() % 10 + 10);

	player->AddRef();
	m_pObjects.push_back(player);
	m_pHeroes.push_back(player);

	m_hplayer = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/ShadowKnight.png");
	m_hMinion = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/enemy1.png");
	m_hRockGolem = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/Rock.png");
	m_hPlantMonster = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/Plant.png");
	cMusic = SGD::AudioManager::GetInstance()->LoadAudio("resource/audio/combatMusic.wav");

	//play combat music
	SGD::AudioManager::GetInstance()->PlayAudio(cMusic, true);

	for (unsigned int i = 0; i < rand() % 3 + 1; i++)
	{
		Object* temp = AddMinion();
		m_pObjects.push_back(temp);
		m_pEnemies.push_back(temp);
	}

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

	PlayerHB.right = PlayerHB.left + ((Player*)m_pObjects[0])->GetHealth();
	SetActionTimer(2);
	SetAction("Combat Ensues!");
}

void CombatState::Exit(void)
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	for (size_t i = 0; i < m_pObjects.size(); i++)
		m_pObjects[i]->Release();

	m_pObjects.clear();
	m_pEnemies.clear();
	m_pHeroes.clear();

	pGraphics->UnloadTexture(m_hplayer);
	pGraphics->UnloadTexture(m_hMinion);
	pGraphics->UnloadTexture(m_hRockGolem);
	pGraphics->UnloadTexture(m_hPlantMonster);

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

	if (ActionTimer <= 0.0f)
	{

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
		if (((Player*)m_pHeroes[0])->GetHealth() > 0)
		{
			PlayerHB.right = PlayerHB.left + ((Player*)m_pHeroes[0])->GetHealth();

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

		for (size_t i = 0; i < m_pObjects.size(); i++)
		{
			switch (m_pObjects[i]->GetType())
			{
			case Object::ObjectType::OBJ_PLAYER:
				if (((Player*)m_pObjects[i])->GetTurnPos() == CurrentTurn)
				{
					if (ActionTimer <= 0)
					if (((Player*)m_pObjects[i])->TakeTurn(elapsedTime))
						CurrentTurn++;
				}
				break;
			case Object::ObjectType::OBJ_COMPANION:
				if (((Companion*)m_pObjects[i])->GetTurnPos() == CurrentTurn)
				{
					if (ActionTimer <= 0)
					if (((Companion*)m_pObjects[i])->TakeTurn())
						CurrentTurn++;
				}
				break;
			case Object::ObjectType::OBJ_MINION:
				if (((Minion*)m_pObjects[i])->GetTurnPos() == CurrentTurn)
				{
					if (ActionTimer <= 0)
					if (((Minion*)m_pObjects[i])->TakeTurn())
						CurrentTurn++;
				}
				break;
			}
		}

		if (CurrentTurn == m_pObjects.size() && ActionTimer <= 0)
			CurrentTurn = 0;
	}
}

void CombatState::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

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
	pGraphics->DrawTexture(m_hplayer, { Playerrect.left - 20, Playerrect.top - 10 }, {}, {}, {}, { .5, .5 });
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
		if (((Companion*)m_pEnemies[j])->GetHealth() > 0)
		{
			((Companion*)m_pEnemies[j])->Render(j);
		}
	}
}

Object* CombatState::AddMinion(int _region) //This is gonna get big, don't care
{
	Minion* temp = new Minion;
	temp->SetSize({ 64, 64 });
	temp->CurrentTurn(&CurrentTurn);
	temp->SetInit(rand() % 20);

	int randAI = rand() % 3;

	switch (randAI)
	{
	case 0:

		switch (_region)
		{
		case 0:
			temp->SetAffinity(Earth);
			temp->SetAIType(Minion::AI_Type::Minion_AI);
			temp->SetCombatImage(m_hMinion);
			temp->SetString(1);
			temp->SetMinionAnimation( _region , randAI );
			
			break;
		case 1:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 2:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 3:
			temp->SetMinionAnimation( _region , randAI );

			break;
		}
		break;
	case 1:

		switch (_region)
		{
		case 0:
			temp->SetAffinity(Earth);
			temp->SetCombatImage(m_hPlantMonster);
			temp->SetAIType(Minion::AI_Type::Off_AI);
			temp->SetString(2);
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 1:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 2:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 3:
			temp->SetMinionAnimation( _region , randAI );

			break;
		}
		break;
	case 2:

		switch (_region)
		{
		case 0:
			temp->SetAffinity(Earth);
			temp->SetCombatImage(m_hRockGolem);
			temp->SetAIType(Minion::AI_Type::Def_AI);
			temp->SetString(3);
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 1:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 2:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 3:
			temp->SetMinionAnimation( _region , randAI );

			break;
		}
		break;
	case 3:
		switch (_region)
		{
		case 0:
			temp->SetAffinity(Earth);
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 1:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 2:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 3:
			temp->SetMinionAnimation( _region , randAI );

			break;
		}
		break;
	case 4:
		switch (_region)
		{
		case 0:
			temp->SetAffinity( Earth );			
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 1:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 2:
			temp->SetMinionAnimation( _region , randAI );

			break;
		case 3:
			temp->SetMinionAnimation( _region , randAI );

			break;
		}
		break;
	default:
		break;
	}
	return temp;
}

bool CombatState::DealDamage(int _DamType, Object* _this, int _target)
//I'm thinking about the order of actions here
//Possibly get the target or attacker's type before damage type, we'll see what's most repetative
//Companions are going to possibly cause some problems
{
	RuneManager mag;
	Game* pGame = Game::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	//Game::GetInstance()->AddState(InventoryState::GetInstance());

	switch (_DamType)
	{
	case CombatState::DamType::Melee:
	{
										if (_this->GetType() == iObject::OBJ_PLAYER)
										{
											pAudio->PlayAudio(Game::GetInstance()->m_mMeleeButton);
											ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());

											((Minion*)m_pEnemies[_target])->SetHealth(((Minion*)m_pEnemies[_target])->GetHealth() -
												(mag.DamageComboElement(d1, ((Minion*)m_pEnemies[_target])->GetAffinity()) * 10));

											SetActionTimer(GetActionTimer() + 3);
											string message = "You Slash the ";
											message += pGame->GetString(1, ((Minion*)m_pEnemies[_target])->GetName()).c_str();
											SetAction(message);
										}
										else if (_this->GetType() == iObject::OBJ_MINION)
										{

											SetActionTimer(GetActionTimer() + 3);
											switch (((Minion*)_this)->GetAIType())
											{
											case 0: //Minion
											{	((Player*)m_pHeroes[_target])->SetHealth(((Player*)m_pHeroes[_target])->GetHealth() - 5);
											string message = "The ";
											message += (pGame->GetString(1, ((Minion*)_this)->GetName()).c_str());
											SetAction(message += " Attacks!");
											}
												break;
											case 1: //Offensive
											{((Player*)m_pHeroes[_target])->SetHealth(((Player*)m_pHeroes[_target])->GetHealth() - 10);
											string message = "The ";
											message += (pGame->GetString(1, ((Minion*)_this)->GetName()).c_str());
											SetAction(message += " Attacks!");
											}
												break;
											case 2: //Defensive
											{((Player*)m_pHeroes[_target])->SetHealth(((Player*)m_pHeroes[_target])->GetHealth() - 3);
											string message = "The ";
											message += (pGame->GetString(1, ((Minion*)_this)->GetName()).c_str());
											SetAction(message += " Attacks!");
											}
												break;
											default:
												break;
											}

										}
	}
		break;
	case CombatState::DamType::Magic:
	{
										m_bCoolDown = true;
										if (_this->GetType() == iObject::OBJ_PLAYER)
										{
											pAudio->PlayAudio(Game::GetInstance()->m_mMagicButton);
											ComboElements d2 = mag.ElementCombination(InventoryState::GetInstance()->GetRingSlot1(), InventoryState::GetInstance()->GetRingSlot2());
											((Minion*)m_pObjects[_target])->SetHealth(((Minion*)m_pObjects[_target])->GetHealth() -
												(mag.DamageComboElement(d2, ((Minion*)m_pObjects[_target])->GetAffinity()) * 10));
											SetActionTimer(GetActionTimer() + 3);
											string stuff = "You Magify the ";
											SetAction(stuff += Game::GetInstance()->GetString(1, ((Minion*)m_pEnemies[_target])->GetName()).c_str());
										}
										if (_this->GetType() == iObject::OBJ_MINION)
										{
											((Player*)m_pObjects[_target])->SetHealth(((Player*)m_pObjects[_target])->GetHealth() - 20);
										}
	}
		break;
	case CombatState::DamType::Armor:
		break;
	default:
		break;
	}

	return false;
}
