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

	//play combat music
	SGD::AudioManager::GetInstance()->PlayAudio(cMusic, true);

	for (unsigned int i = 0; i < rand() % 3 + 1; i++)
	{
		Object* temp;
		switch (GameplayState::GetInstance()->GetCurrentLevel())
		{
		case 1:
			temp = AddMinion(0);
			break;
		case 2:
			temp = AddMinion(1);
			break;
		case 3:
			temp = AddMinion(2);
			break;
		case 4:
			temp = AddMinion(3);
			break;
		default:
			temp = AddMinion(rand() % 4);

			break;
		}
		m_pObjects.push_back(temp);
		m_pEnemies.push_back(temp);
	}

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
	{
		ActionTimer -= elapsedTime;
		if (ActionTimer <= 0.0f)
			ActionTimer = 0.0f;

		m_fFlash += elapsedTime;

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
							if (((Player*)m_pObjects[i])->TakeTurn(elapsedTime))
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
						if (((Companion*)m_pObjects[i])->TakeTurn(elapsedTime))
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

		}

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
	/*pGraphics->DrawTexture( m_hplayer , { Playerrect.left - 20 , Playerrect.top - 10 } , { } , { } , { } , { .5 , .5 } );*/
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

	//pGraphics->DrawRectangle(Companion1rect, SGD::Color(), SGD::Color());
	//pGraphics->DrawRectangle(Companion2rect, SGD::Color(), SGD::Color());
}

Object* CombatState::AddMinion(int _region) //This is gonna get big, don't care
{
	//_region = rand() % 4;
	Minion* temp = new Minion;
	temp->SetSize({ 64, 64 });
	temp->CurrentTurn(&CurrentTurn);
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
		randHealth = rand() % 25 + 40;

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
	return temp;
}

Object* CombatState::AddCompanion()
{
	Companion* temp = new Companion;
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

bool CombatState::TakeAction(int _ActionType, Object* _this, int _target, int _spell) //Can I Add An Object* for the target
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
																		  ((Companion*)_this)->m_Block = true;
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
	RuneManager mag;

	if (_From->GetType() == iObject::OBJ_PLAYER)
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

		if (localBlock == false)
		{
			ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());

			NumQTCorrect = 0;

			Total = ((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) * 50 + (NumQTCorrect * 5)));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);

			//Cool idea to give you a better chance against harder monsters with more potential damage

			if (((Minion*)_To)->GetAIType() == Minion::Off_AI)
			{
				if (rand() % 20 > 10)
				{
					DealCounterDamage(_To, _From);
					return 0;
				}
			}

			string message = "You Slash the ";
			message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
			SetAction(message);
		}
	}
	else if (_From->GetType() == iObject::OBJ_MINION)// _From == Minion
	{

		for (size_t i = 1; i < m_pHeroes.size(); i++)
		{
			if (((Companion*)m_pHeroes[i])->GetCoType() == Companion::Companion_Type::Tank)
			{
				if (((Companion*)m_pHeroes[i])->m_Block)
				{
					BlockAttack(_From, m_pHeroes[i]);
					localBlock = ((Companion*)m_pHeroes[i])->m_Block;
					((Companion*)m_pHeroes[i])->m_Block = false;
					return 0;
				}
			}
		}

		if (localBlock == false)
		{
			Total = rand() % (10 * ((Minion*)_From)->GetMods().DamageLevel) + ((Minion*)_From)->GetMods().DamageLevel;

			if (_To->GetType() == iObject::OBJ_PLAYER)
			{
				((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
				if (rand() % 20 > 13)
				{
					DealCounterDamage(_To, _From);
					return 0;
				}
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
			Total = ((mag.DamagetoBaseElement(e1, ((Minion*)_To)->GetAffinity()) * 50 + (NumQTCorrect * 5)));

			break;
		case 1:
			ComboElements d1;

			stuff += spell2.c_str();
			d1 = mag.ElementCombination(InventoryState::GetInstance()->GetRingSlot1(), InventoryState::GetInstance()->GetRingSlot2());
			Total = ((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) * 50 + (NumQTCorrect * 5)));
			break;
		case 2:
			ComboElements d2;

			stuff += spell3.c_str();
			d2 = mag.ElementCombination(InventoryState::GetInstance()->GetRingSlot2(), InventoryState::GetInstance()->GetRingSlot3());
			Total = ((mag.DamageComboElement(d2, ((Minion*)_To)->GetAffinity()) * 50 + (NumQTCorrect * 5)));

			break;
		default:
			break;
		}

		stuff += " on the ";
		SetAction(stuff += Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);

		NumQTCorrect = 0;
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
		NumQTCorrect = 0;

		Total = ((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) * 50 + (NumQTCorrect * 5)));
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
		string message = "You Counter the ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += "'s Attack!");
	}
	else
	{
		Total = rand() % (10 * ((Minion*)_From)->GetMods().DamageLevel) + ((Minion*)_From)->GetMods().DamageLevel;
		if (_To->GetType() == iObject::OBJ_PLAYER)
			((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
		else if (_To->GetType() == iObject::OBJ_COMPANION)
			((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);

		string message = "The ";
		message += (Game::GetInstance()->GetString(((Minion*)_From)->GetName(0), ((Minion*)_From)->GetName(1)).c_str());
		SetAction(message += " Counters!");

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

		ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());

		NumQTCorrect = 0;
		//((Player*)_From)->RunQuickTime((((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + 3);

		Total = ((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) * 50 + (NumQTCorrect * 5)));
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
	}
	else if (_From->GetType() == iObject::OBJ_MINION)
	{
		Total = rand() % (10 * ((Minion*)_From)->GetMods().DamageLevel) + ((Minion*)_From)->GetMods().DamageLevel;
		((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
		string message = "Your Ally Intercepts the ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += "'s  Attack!");
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
			((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() + Total);
		else
			((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() + Total);

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