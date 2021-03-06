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
	InventoryState* pInventory = InventoryState::GetInstance();
	m_hTurnIndicator = pGraphics->LoadTexture("resource/graphics/TurnIndicator.png");
	m_hTargetSelector = pGraphics->LoadTexture("resource/graphics/Selection_Arrow.png");

	CurrentTurn = 0;
	TurnIndex = 0;

	numPots = rand() % 3;
	numRunes = rand() % 2;

	Player* player = (Player*)GameplayState::GetInstance()->GetPlayer();
	player->CurrentTurn(&CurrentTurn);
	player->SetInit(rand() % 15 + 5);
	player->SetAttckSpd(8);
	SavePlayerPos = player->GetPosition();
	player->SetPosition({ Playerrect.left, Playerrect.top });
	player->AddRef();
	player->SetDeathAnimationTimer();
	//player->SetHealth( 2 );
	m_pObjects.push_back(player);
	m_pHeroes.push_back(player);

#pragma region spells
	//pInventory = InventoryState::GetInstance();

	Rune1.SetElement(pInventory->m_vRing[0].GetElement());
	Rune1.SetTier(pInventory->m_vRing[0].GetTier());
	Rune2.SetElement(pInventory->m_vRing[1].GetElement());
	Rune2.SetTier(pInventory->m_vRing[1].GetTier());
	Rune3.SetElement(pInventory->m_vRing[2].GetElement());
	Rune3.SetTier(pInventory->m_vRing[2].GetTier());

	string spell1;
	switch (Rune1.GetElement())
	{
	case Fire:
	{
				 if (Rune1.GetTier() == 1)
					 spell1 = "Fire Ball(1)";
				 if (Rune1.GetTier() == 2)
					 spell1 = "Fire Ball(2)";
				 if (Rune1.GetTier() == 3)
					 spell1 = "Fire Ball(3)";
	}
		break;
	case Water:
	{
				  if (Rune1.GetTier() == 1)
					  spell1 = "Water Blast(1)";
				  if (Rune1.GetTier() == 2)
					  spell1 = "Water Blast(2)";
				  if (Rune1.GetTier() == 3)
					  spell1 = "Water Blast(3)";
	}
		break;
	case Air:
	{
				if (Rune1.GetTier() == 1)
					spell1 = "Wind Gust(1)";
				if (Rune1.GetTier() == 2)
					spell1 = "Wind Gust(2)";
				if (Rune1.GetTier() == 3)
					spell1 = "Wind Gust(3)";
	}
		break;
	case Earth:
	{
				  if (Rune1.GetTier() == 1)
					  spell1 = "Rock Throw(1)";
				  if (Rune1.GetTier() == 2)
					  spell1 = "Rock Throw(2)";
				  if (Rune1.GetTier() == 3)
					  spell1 = "Rock Throw(3)";
	}
		break;
	case None:
		break;
	default:
		break;
	}
	string spell2;
	RuneManager rmanager;
	ComboElements firstCombo = rmanager.ElementCombination(Rune1.GetElement(), Rune2.GetElement());

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

	ComboElements SecondCombo = rmanager.ElementCombination(Rune2.GetElement(), Rune3.GetElement());

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

	if (pInventory->m_vRing[0].GetElement() != Elements::None)
		((Player*)m_pHeroes[0])->SetSpell1Cool(0);
	else
		((Player*)m_pHeroes[0])->SetSpell1Cool(-1);

	if (pInventory->m_vRing[1].GetElement() != Elements::None)
		((Player*)m_pHeroes[0])->SetSpell2Cool(0);
	else
		((Player*)m_pHeroes[0])->SetSpell2Cool(-1);

	if (pInventory->m_vRing[2].GetElement() != Elements::None)
		((Player*)m_pHeroes[0])->SetSpell3Cool(0);
	else
		((Player*)m_pHeroes[0])->SetSpell3Cool(-1);

#pragma endregion

	m_hplayer = pGraphics->LoadTexture("resource/graphics/ShadowKnight.png");
	cMusic = SGD::AudioManager::GetInstance()->LoadAudio("resource/audio/combatMusic.wav");
	cHealingAbility = SGD::AudioManager::GetInstance()->LoadAudio("resource/audio/HealAbility.wav");
	m_hButton = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/MenuBackgrounds/pauseButton.png");
	//minion Icons

	//play combat music
	SGD::AudioManager::GetInstance()->PlayAudio(cMusic, true);

#pragma region AddingCombatEnemies
	//Possibly get combinations of enemy minion affinities per region
	if (player->CombatEnemyID == 1)
	{
		int randEnemies = (rand() % 2) + 2;
		for (int i = 0; i < randEnemies; i++)
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
			temp = AddMinion(0, 1);
			m_pObjects.push_back(temp);
			m_pEnemies.push_back(temp);
			temp2 = AddMinion(0, player->CombatEnemyID);
			m_pObjects.push_back(temp2);
			m_pEnemies.push_back(temp2);
			break;
		case 2:
			temp = AddMinion(1, 1);
			m_pObjects.push_back(temp);
			m_pEnemies.push_back(temp);
			temp2 = AddMinion(1, player->CombatEnemyID);
			m_pObjects.push_back(temp2);
			m_pEnemies.push_back(temp2);
			break;
		case 3:
			temp = AddMinion(2, 1);
			m_pObjects.push_back(temp);
			m_pEnemies.push_back(temp);
			temp2 = AddMinion(2, player->CombatEnemyID);
			m_pObjects.push_back(temp2);
			m_pEnemies.push_back(temp2);
			break;
		case 4:
			temp = AddMinion(3, 1);
			m_pObjects.push_back(temp);
			m_pEnemies.push_back(temp);
			temp2 = AddMinion(3, player->CombatEnemyID);
			m_pObjects.push_back(temp2);
			m_pEnemies.push_back(temp2);
			break;
		default:
			temp = AddMinion(rand() % 4, 1);
			m_pObjects.push_back(temp);
			m_pEnemies.push_back(temp);
			temp2 = AddMinion(rand() % 4, player->CombatEnemyID);
			m_pObjects.push_back(temp2);
			m_pEnemies.push_back(temp2);
			break;
		}
		//temp->AddRef();
		//temp2->AddRef();
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
		//temp->AddRef();
		m_pObjects.push_back(temp);
		m_pEnemies.push_back(temp);
	}
	else if (player->CombatEnemyID == 4)
	{
		Object* temp;
		temp = AddMinion(4, player->CombatEnemyID);
		//temp->AddRef();
		m_pObjects.push_back(temp);
		m_pEnemies.push_back(temp);
	}
#pragma endregion
#pragma region AddingCombatCompanions

	/*for (unsigned int i = 0; i < 2; i++)
	{*/
	/*if (InventoryState::GetInstance()->m_vCompanion.size() != 0)
	{
	if (InventoryState::GetInstance()->m_vCompanion.size() == 2)
	{
	if (InventoryState::GetInstance()->m_vCompanion[i].GetCoType() != Companion::Companion_Type::NonClass)
	{
	Object* temp = AddCompanion(InventoryState::GetInstance()->m_vCompanion[i].GetCoType());
	((Companion*)temp)->SetPosIndex(i);

	if (m_pHeroes.size() == 1)
	temp->SetPosition({ Companion1rect.right, Companion1rect.bottom });
	else if (m_pHeroes.size() == 2)
	temp->SetPosition({ Companion2rect.right, Companion2rect.bottom });
	m_pObjects.push_back(temp);
	m_pHeroes.push_back(temp);
	}
	else if (InventoryState::GetInstance()->m_vCompanion[0].GetCoType() != Companion::Companion_Type::Cleric ||
	InventoryState::GetInstance()->m_vCompanion[0].GetCoType() != Companion::Companion_Type::Mage ||
	InventoryState::GetInstance()->m_vCompanion[0].GetCoType() != Companion::Companion_Type::Tank ||
	InventoryState::GetInstance()->m_vCompanion[0].GetCoType() != Companion::Companion_Type::Melee)
	{
	Object* temp = AddCompanion(0);
	((Companion*)temp)->SetPosIndex(i);

	if (m_pHeroes.size() == 1)
	temp->SetPosition({ Companion1rect.right, Companion1rect.bottom });
	else if (m_pHeroes.size() == 2)
	temp->SetPosition({ Companion2rect.right, Companion2rect.bottom });
	m_pObjects.push_back(temp);
	m_pHeroes.push_back(temp);
	}
	else if (InventoryState::GetInstance()->m_vCompanion[1].GetCoType() != Companion::Companion_Type::Cleric ||
	InventoryState::GetInstance()->m_vCompanion[1].GetCoType() != Companion::Companion_Type::Mage ||
	InventoryState::GetInstance()->m_vCompanion[1].GetCoType() != Companion::Companion_Type::Tank ||
	InventoryState::GetInstance()->m_vCompanion[1].GetCoType() != Companion::Companion_Type::Melee)
	{

	Object* temp = AddCompanion(1);
	((Companion*)temp)->SetPosIndex(i);

	if (m_pHeroes.size() == 1)
	temp->SetPosition({ Companion1rect.right, Companion1rect.bottom });
	else if (m_pHeroes.size() == 2)
	temp->SetPosition({ Companion2rect.right, Companion2rect.bottom });
	m_pObjects.push_back(temp);
	m_pHeroes.push_back(temp);
	}
	}
	else
	{
	Object* temp = AddCompanion(InventoryState::GetInstance()->m_vCompanion[i].GetCoType());
	((Companion*)temp)->SetPosIndex(i);

	if (m_pHeroes.size() == 1)
	temp->SetPosition({ Companion1rect.right, Companion1rect.bottom });
	else if (m_pHeroes.size() == 2)
	temp->SetPosition({ Companion2rect.right, Companion2rect.bottom });
	m_pObjects.push_back(temp);
	m_pHeroes.push_back(temp);
	}
	}
	else
	{*/

	for (unsigned int i = 0; i < 2; i++)
	{
		Object* temp = AddCompanion((rand() % 2) + (i * 2));
		((Companion*)temp)->SetPosIndex(i);

		if (m_pHeroes.size() == 1)
			temp->SetPosition({ Companion1rect.right, Companion1rect.bottom });
		else if (m_pHeroes.size() == 2)
			temp->SetPosition({ Companion2rect.right, Companion2rect.bottom });
		m_pObjects.push_back(temp);
		m_pHeroes.push_back(temp);
		//}
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
	selected = false;
	ActionSelected = false;

	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	((Player*)m_pHeroes[0])->SetPosition(SavePlayerPos);
	((Player*)m_pHeroes[0])->StopCombat();


	for (size_t i = 0; i < m_pHeroes.size(); i++)
		m_pHeroes[i]->Release();

	for (size_t i = 0; i < m_pEnemies.size(); i++)
		m_pEnemies[i]->Release();

	m_pObjects.clear();
	m_pEnemies.clear();
	m_pHeroes.clear();

	pGraphics->UnloadTexture(m_hplayer);
	pGraphics->UnloadTexture(m_hButton);
	pGraphics->UnloadTexture(m_hTurnIndicator);
	pGraphics->UnloadTexture(m_hTargetSelector);
	pAudio->UnloadAudio(cHealingAbility);
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

	if (pInput->IsKeyPressed(SGD::Key::B) || pInput->IsButtonPressed(0, 5))
	{
		selected = false;
		spellSelect = -1;
	}
	//if( pInput->IsKeyPressed(SGD::Key::Escape) )
	//{
	//	Game::GetInstance()->RemoveState();
	//}
	return true;
}

void CombatState::Update(float elapsedTime)
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	// Draw the bckgrnd here if you don't have screen shake reasons
	// DrawBackground();
	m_fArcadeTimer += elapsedTime;

	ActionTimer -= elapsedTime;
	if (ActionTimer <= 0.0f)
		ActionTimer = 0.0f;

	m_fFlash += elapsedTime;


	if (((Player*)m_pHeroes[0])->GetHealth() > 0)
	{

		PlayerHB.right = PlayerHB.left + (((Player*)m_pHeroes[0])->GetHealth() / ((Player*)m_pHeroes[0])->GetMaxHealth()) * 100;
		((Player*)m_pHeroes[0])->Update(elapsedTime);

		for (unsigned int i = 1; i < m_pHeroes.size(); i++)
		{
			if (((Companion*)m_pHeroes[i])->GetHealth())
				((Companion*)m_pHeroes[i])->Update(elapsedTime);
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
		if (((Player*)m_pHeroes[0])->GetDeathAnimationTimer() <= 0.0f)
		{
			((Player*)m_pHeroes[0])->SetCombat(false);
			Game::GetInstance()->RemoveState();
			return;
		}
		else
		{
			((Player*)m_pHeroes[0])->Update(elapsedTime);
			((Player*)m_pHeroes[0])->Render();
		}
	}

	if (ActionTimer <= 0.0f && ((Player*)m_pHeroes[0])->GetHealth() > 0)
	{
		ResetRects();
		//place here if you have weird screen shake reasons
		DrawBackground();

		m_bShake = false;

		for (size_t i = 0; i < m_pHeroes.size(); i++)
		{
			m_pHeroes[i]->SetDeltaHP(0);
			m_pHeroes[i]->SetDeltaHPPosY(0);
		}
		for (size_t i = 0; i < m_pEnemies.size(); i++)
		{
			m_pEnemies[i]->SetDeltaHP(0);
			m_pEnemies[i]->SetDeltaHPPosY(0);
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

				if (((Player*)m_pHeroes[0])->CombatEnemyID == 1)
				{
					Runes tempRune;
					tempRune.SetElement((Elements)(rand() % 4));
					tempRune.SetTier(rand() % 2 + 1);
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld(tempRune);
				}
				else if (((Player*)m_pHeroes[0])->CombatEnemyID == 2)
				{
					Runes tempRune;
					tempRune.SetElement((Elements)GameplayState::GetInstance()->GetCurrentLevel());
					tempRune.SetTier(3);
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld(tempRune);
				}
				else if (((Player*)m_pHeroes[0])->CombatEnemyID == 3)
				{
					Runes tempRune;
					tempRune.SetElement((Elements)GameplayState::GetInstance()->GetCurrentLevel());
					tempRune.SetTier(3);
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld(tempRune);
					Runes tempRune2;
					tempRune2.SetElement((Elements)GameplayState::GetInstance()->GetCurrentLevel());
					tempRune2.SetTier(3);
					InventoryState::GetInstance()->AddRunesToInventoryfromWorld(tempRune2);
				}
				pAudio->PlayAudio(GameplayState::GetInstance()->bmusic, true);

				Game::GetInstance()->RemoveState();

				return;
			}
		}


		if (CurrentTurn == m_pObjects.size() && ActionTimer <= 0) //m_pObjects.size can be smaller or larger than the actual number of entities
		{
			SortTurnOrder();
			CurrentTurn = 0;
		}
		switch (m_pObjects[CurrentTurn]->GetType())
		{
		case Object::ObjectType::OBJ_PLAYER:
		{
											   if (((Player*)m_pObjects[CurrentTurn])->GetHealth() > 0)
											   {
												   if (ActionTimer <= 0)
												   if (TakeTurn(((Player*)m_pObjects[CurrentTurn])))
													   CurrentTurn++;
											   }
											   else
												   CurrentTurn++;
		}
			break;
		case Object::ObjectType::OBJ_COMPANION:
		{
												  if (((Companion*)m_pObjects[CurrentTurn])->GetHealth() > 0)
												  {
													  if (((Companion*)m_pObjects[CurrentTurn])->GetHealth() > 0)
													  {
														  if (ActionTimer <= 0)
														  if (TakeTurn(((Companion*)m_pObjects[CurrentTurn])))
															  CurrentTurn++;
													  }
													  else
													  {
														  CurrentTurn++;

													  }
												  }
												  else
												  {
													  CurrentTurn++;
												  }
		}
			break;
		case Object::ObjectType::OBJ_MINION:
		{
											   if (((Minion*)m_pObjects[CurrentTurn])->GetHealth() > 0)
											   {
												   if (ActionTimer <= 0)
												   if (TakeTurn(((Minion*)m_pObjects[CurrentTurn])))
													   CurrentTurn++;
											   }
											   else
											   {
												   CurrentTurn++;
											   }
		}
			break;
		}

	}
	else
	{
		for (size_t i = 0; i < m_pHeroes.size(); i++)
			m_pHeroes[i]->SetDeltaHPPosY(m_pHeroes[i]->GetDeltaHPPosY() + 100 * elapsedTime);
		for (size_t i = 0; i < m_pEnemies.size(); i++)
			m_pEnemies[i]->SetDeltaHPPosY(m_pEnemies[i]->GetDeltaHPPosY() + 100 * elapsedTime);

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
		for (size_t i = 1; i < m_pHeroes.size(); i++)
		{
			if (((Companion*)m_pHeroes[i])->GetDeathAnimationTimer() > 0.0f)
			{
				((Companion*)m_pHeroes[i])->Update(elapsedTime);
				((Companion*)m_pHeroes[i])->CombatRender(i);
			}
		}
		//weird screen shake reasons
		ShakeScreen(elapsedTime);
	}

}
void CombatState::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = BitmapFontManager::GetInstance();
	InventoryState* pInventory = InventoryState::GetInstance();

	float width = Game::GetInstance()->GetScreenWidth();
	int len = ActionMessage.length();

	pGraphics->DrawRectangle(AbilityRect, SGD::Color{ 200, 0, 0, 0 });
	pGraphics->DrawRectangle(ActionRect, SGD::Color{ 200, 0, 0, 0 });
	pFont->Render("Other", ActionMessage.c_str(), SGD::Point{ (width - (len * 14)) / 2, ActionRect.top + 5 }, 1, SGD::Color(255, 255, 255, 255));

	SGD::Color pHcolor;
	if ((((Player*)m_pHeroes[0])->GetHealth() / ((Player*)m_pHeroes[0])->GetMaxHealth()) * 100 > 50)
		pHcolor = { 255, 0, 255, 0 };
	else if ((((Player*)m_pHeroes[0])->GetHealth() / ((Player*)m_pHeroes[0])->GetMaxHealth()) * 100 > 20)
		pHcolor = { 255, 255, 255, 0 };
	else
		pHcolor = { 255, 255, 0, 0 };

	pGraphics->DrawRectangle({ 75, 200, 175, 230 }, { 255, 255, 255, 255 });
	if (PlayerHB.right > PlayerHB.left && ((Player*)m_pHeroes[0])->GetHealth() > 0)
		pGraphics->DrawRectangle(PlayerHB, pHcolor);

	string playerHealth = to_string((int)((Player*)m_pHeroes[0])->GetHealth());
	playerHealth += "/";
	playerHealth += to_string((int)((Player*)m_pHeroes[0])->GetMaxHealth());
	pFont->Render("Dialog", playerHealth.c_str(), { PlayerHB.left + 5, PlayerHB.top }, 1.0f, SGD::Color{ 255, 0, 0, 0 });

	((Player*)m_pHeroes[0])->Render();

	if (m_bHealthWarning)
		pGraphics->DrawRectangle(SGD::Rectangle(0, 0, Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight()), { 100, 255, 0, 0 });

	for (size_t j = 0; j < m_pEnemies.size(); j++)
	{
		if (((Minion*)m_pEnemies[j])->GetHealth() > 0)
			((Minion*)m_pEnemies[j])->Render(j);
		else if (((Minion*)m_pEnemies[j])->GetDeathAnimationTimer() > 0.0f)
			((Minion*)m_pEnemies[j])->Render(j);
	}

	for (size_t j = 1; j < m_pHeroes.size(); j++)
	{
		if (((Companion*)m_pHeroes[j])->GetHealth() > 0)
			((Companion*)m_pHeroes[j])->CombatRender(j);
	}
	//Enemy Icons
	for (unsigned int i = 0; i < m_pEnemies.size(); i++)
	{
		if (((Minion*)m_pEnemies[i])->GetHealth() > 0)
		{
			if (((Minion*)(m_pEnemies[i]))->GetAffinity() == Water)
				pGraphics->DrawTexture(Game::GetInstance()->m_hWaterIcon, SGD::Point(m_pEnemies[i]->GetPosition().x + 50, m_pEnemies[i]->GetPosition().y - 110), {}, {}, {}, { .1f, .1f });
			if (((Minion*)(m_pEnemies[i]))->GetAffinity() == Fire)
				pGraphics->DrawTexture(Game::GetInstance()->m_hFireIcon, SGD::Point(m_pEnemies[i]->GetPosition().x + 50, m_pEnemies[i]->GetPosition().y - 110), {}, {}, {}, { .1f, .1f });
			if (((Minion*)(m_pEnemies[i]))->GetAffinity() == Air)
				pGraphics->DrawTexture(Game::GetInstance()->m_hAirIcon, SGD::Point(m_pEnemies[i]->GetPosition().x + 50, m_pEnemies[i]->GetPosition().y - 110), {}, {}, {}, { .1f, .1f });
			if (((Minion*)(m_pEnemies[i]))->GetAffinity() == Earth)
				pGraphics->DrawTexture(Game::GetInstance()->m_hEarthIcon, SGD::Point(m_pEnemies[i]->GetPosition().x + 50, m_pEnemies[i]->GetPosition().y - 110), {}, {}, {}, { .1f, .1f });
		}
	}

	if (GameplayState::GetInstance()->GetCurrentLevel() == 0)
		HandleTutorial();

	string message = to_string(m_pHeroes[0]->GetDeltaHP()).c_str();
	if (m_pHeroes[0]->GetDeltaHP() < 0)
		pFont->Render("Other", message.c_str(), { m_pHeroes[0]->GetPosition().x, m_pHeroes[0]->GetPosition().y - m_pHeroes[0]->GetDeltaHPPosY() }, 2.0, SGD::Color{ 255, 255, 0, 0 });
	else if (m_pHeroes[0]->GetDeltaHP() > 0)
		pFont->Render("Other", message.c_str(), { m_pHeroes[0]->GetPosition().x, m_pHeroes[0]->GetPosition().y - m_pHeroes[0]->GetDeltaHPPosY() }, 2.0, SGD::Color{ 255, 0, 255, 0 });

	else if (m_pHeroes[0]->GetTurnID() == 1)
		pFont->Render("Dialog", "+", { m_pHeroes[0]->GetPosition().x, m_pHeroes[0]->GetPosition().y }, 3.0, SGD::Color{ 255, 160, 32, 240 });
	else if (m_pHeroes[0]->GetTurnID() == 2)
		pFont->Render("Dialog", "-", { m_pHeroes[0]->GetPosition().x, m_pHeroes[0]->GetPosition().y }, 3.0, SGD::Color{ 255, 255, 165, 0 });

	for (size_t i = 1; i < m_pHeroes.size(); i++)
	{
		string message = to_string(m_pHeroes[i]->GetDeltaHP()).c_str();
		if (m_pHeroes[i]->GetDeltaHP() < 0)
			pFont->Render("Other", message.c_str(), { m_pHeroes[i]->GetPosition().x, m_pHeroes[i]->GetPosition().y - m_pHeroes[i]->GetDeltaHPPosY() }, 2.0, SGD::Color{ 255, 255, 0, 0 });
		else if (m_pHeroes[i]->GetDeltaHP() > 0)
			pFont->Render("Other", message.c_str(), { m_pHeroes[i]->GetPosition().x, m_pHeroes[i]->GetPosition().y - m_pHeroes[i]->GetDeltaHPPosY() }, 2.0, SGD::Color{ 255, 0, 255, 0 });

		else if (m_pHeroes[i]->GetTurnID() == 1)
			pFont->Render("Dialog", "+", { m_pHeroes[i]->GetPosition().x, m_pHeroes[i]->GetPosition().y }, 3.0, SGD::Color{ 255, 160, 32, 240 });
		else if (m_pHeroes[i]->GetTurnID() == 2)
			pFont->Render("Dialog", "-", { m_pHeroes[i]->GetPosition().x, m_pHeroes[i]->GetPosition().y }, 3.0, SGD::Color{ 255, 255, 165, 0 });
	}

	for (size_t i = 0; i < m_pEnemies.size(); i++)
	{
		string message = to_string(m_pEnemies[i]->GetDeltaHP()).c_str();
		if (m_pEnemies[i]->GetDeltaHP() < 0)
			pFont->Render("Other", message.c_str(), { m_pEnemies[i]->GetPosition().x, m_pEnemies[i]->GetPosition().y - m_pEnemies[i]->GetDeltaHPPosY() }, 2.0, SGD::Color{ 255, 255, 0, 0 });
		else if (m_pEnemies[i]->GetDeltaHP() > 0)
			pFont->Render("Other", message.c_str(), { m_pEnemies[i]->GetPosition().x, m_pEnemies[i]->GetPosition().y - m_pEnemies[i]->GetDeltaHPPosY() }, 2.0, SGD::Color{ 255, 0, 255, 0 });

		else if (m_pEnemies[i]->GetTurnID() == 1)
			pFont->Render("Dialog", "+", { m_pEnemies[i]->GetPosition().x, m_pEnemies[i]->GetPosition().y }, 2.0, SGD::Color{ 255, 160, 32, 240 });
		else if (m_pEnemies[i]->GetTurnID() == 2)
			pFont->Render("Dialog", "-", { m_pEnemies[i]->GetPosition().x, m_pEnemies[i]->GetPosition().y }, 2.0, SGD::Color{ 255, 255, 165, 0 });
	}
	if (CurrentTurn < (int)m_pObjects.size()) //Combat takeTurn rendering in unison with turn order loop
	{
		switch (m_pObjects[CurrentTurn]->GetType())
		{
		case Object::ObjectType::OBJ_PLAYER:
		{
											   if (((Player*)m_pObjects[CurrentTurn])->GetHealth() > 0)
											   {
												   SGD::Point turnIndicator = m_pObjects[CurrentTurn]->GetPosition();
												   pGraphics->DrawTexture(m_hTurnIndicator, SGD::Point(turnIndicator.x, turnIndicator.y + 20), 0.0f, {}, {}, { 2.0, 2.0 });
											   }

											   if (ActionTimer <= 0)
											   if (!selected)
											   {
												   pFont->Render("Other", "Melee", SGD::Point{ 250, 420 }, 1, SGD::Color(255, 255, 0, 0));

												   if (spellActive)
													   pFont->Render("Other", "Magic", SGD::Point{ 250, 470 }, 1, SGD::Color(255, 0, 255, 0));
												   else
													   pFont->Render("Other", "Magic", SGD::Point{ 250, 470 }, 1, SGD::Color(150, 0, 255, 0));


												   if (PlayerSelection.left < PlayerSelection.right)
													   pGraphics->DrawTexture(m_hTargetSelector, { PlayerSelection.left, PlayerSelection.top });
											   }
											   else
											   {

												   if (ActionSelected == 0) //Melee
												   {//pCombat->SetAction("Choose Target");
												   }
												   else if (ActionSelected == 1)
												   {
													   if (spellSelect == -1)
													   {
														   //pCombat->SetAction("Choose Spell");
														   Rune1.SetElement(pInventory->m_vRing[0].GetElement());
														   Rune1.SetTier(pInventory->m_vRing[0].GetTier());
														   Rune2.SetElement(pInventory->m_vRing[1].GetElement());
														   Rune2.SetTier(pInventory->m_vRing[1].GetTier());
														   Rune3.SetElement(pInventory->m_vRing[2].GetElement());
														   Rune3.SetTier(pInventory->m_vRing[2].GetTier());
#pragma region spells
														   string spell1;
														   switch (Rune1.GetElement())
														   {
														   case Fire:
														   {
																		if (Rune1.GetTier() == 1)
																		{
																			spell1 = "Fire Ball(1)";
																		}
																		if (Rune1.GetTier() == 2)
																		{
																			spell1 = "Fire Ball(2)";
																		}
																		if (Rune1.GetTier() == 3)
																		{
																			spell1 = "Fire Ball(3)";
																		}
														   }
															   break;
														   case Water:
														   {
																		 if (Rune1.GetTier() == 1)
																		 {
																			 spell1 = "Water Blast(1)";
																		 }
																		 if (Rune1.GetTier() == 2)
																		 {
																			 spell1 = "Water Blast(2)";
																		 }
																		 if (Rune1.GetTier() == 3)
																		 {
																			 spell1 = "Water Blast(3)";
																		 }
														   }
															   break;
														   case Air:
														   {
																	   if (Rune1.GetTier() == 1)
																	   {
																		   spell1 = "Wind Gust(1)";
																	   }
																	   if (Rune1.GetTier() == 2)
																	   {
																		   spell1 = "Wind Gust(2)";
																	   }
																	   if (Rune1.GetTier() == 3)
																	   {
																		   spell1 = "Wind Gust(3)";
																	   }
														   }
															   break;
														   case Earth:
														   {
																		 if (Rune1.GetTier() == 1)
																		 {
																			 spell1 = "Rock Throw(1)";
																		 }
																		 if (Rune1.GetTier() == 2)
																		 {
																			 spell1 = "Rock Throw(2)";
																		 }
																		 if (Rune1.GetTier() == 3)
																		 {
																			 spell1 = "Rock Throw(3)";
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
														   ComboElements firstCombo = rmanager.ElementCombination(Rune1.GetElement(), Rune2.GetElement());

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

														   ComboElements SecondCombo = rmanager.ElementCombination(Rune2.GetElement(), Rune3.GetElement());

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
																   if (((Player*)m_pObjects[CurrentTurn])->GetSpell1Cool())
																	   pFont->Render("Dialog", spell1.c_str(), { Spell1Rect.left, Spell1Rect.top }, .7f, { 100, 255, 255, 0 });
																   else
																	   pFont->Render("Dialog", spell1.c_str(), { Spell1Rect.left, Spell1Rect.top }, .7f, { 255, 255, 255, 255 });
																   break;
															   case 1:
																   if (((Player*)m_pObjects[CurrentTurn])->GetSpell2Cool())
																	   pFont->Render("Dialog", spell2.c_str(), { Spell2Rect.left, Spell2Rect.top }, .7f, { 100, 255, 255, 0 });
																   else
																	   pFont->Render("Dialog", spell2.c_str(), { Spell2Rect.left, Spell2Rect.top }, .7f, { 255, 255, 255, 255 });
																   break;
															   case 2:
																   if (((Player*)m_pObjects[CurrentTurn])->GetSpell3Cool())
																	   pFont->Render("Dialog", spell3.c_str(), { Spell3Rect.left, Spell3Rect.top }, .7f, { 100, 255, 255, 0 });
																   else
																	   pFont->Render("Dialog", spell3.c_str(), { Spell3Rect.left, Spell3Rect.top }, .7f, { 255, 255, 255, 255 });
																   break;
															   default:
																   break;
															   }
														   }
#pragma endregion spells
													   }
												   }
												   if (PlayerSelection.left < PlayerSelection.right)
													   pGraphics->DrawTexture(m_hTargetSelector, { PlayerSelection.left, PlayerSelection.top });
											   }
		}
			break;
		case Object::ObjectType::OBJ_COMPANION:
		{
												  if (((Companion*)m_pObjects[CurrentTurn])->GetHealth() > 0)
												  {
													  SGD::Point turnIndicator = m_pObjects[CurrentTurn]->GetPosition();
													  pGraphics->DrawTexture(m_hTurnIndicator, SGD::Point(turnIndicator.x - 50, turnIndicator.y - 40), 0.0f, {}, {}, { 2.0, 2.0 });
												  }

												  if (ActionTimer <= 0)
												  {
													  switch (((Companion*)m_pObjects[CurrentTurn])->GetCoType())
													  {
													  case Companion::Cleric:
													  {
																				if (!selected) //Pick an action (melee magic or armor)
																				{
																					pFont->Render("Other", "Melee", SGD::Point{ 250, 420 }, 1, SGD::Color(255, 255, 0, 0));
																					pFont->Render("Other", "Heal", SGD::Point{ 250, 470 }, 1, SGD::Color(255, 0, 0, 255));
																				}
																				if (ActionSelected == ActionType::Heal)
																					pGraphics->DrawTexture(m_hTargetSelector, { CompanionSelection.left, CompanionSelection.top }, 0.0f, {}, {}, { -1, 1 });
																				else
																					pGraphics->DrawTexture(m_hTargetSelector, { CompanionSelection.left, CompanionSelection.top });
													  }
														  break;
													  case Companion::Melee:
													  {
																			   if (selected == false) //Pick an action (melee magic or armor)
																			   {
																				   pFont->Render("Other", "Melee", SGD::Point{ 250, 420 }, 1, SGD::Color(255, 255, 0, 0));
																				   pFont->Render("Other", "Fury", SGD::Point{ 250, 470 }, 1, SGD::Color(255, 0, 0, 255));
																			   }
																			   if (CompanionSelection.left < CompanionSelection.right)
																				   pGraphics->DrawTexture(m_hTargetSelector, { CompanionSelection.left, CompanionSelection.top });
													  }
														  break;
													  case Companion::Mage:
													  {
																			  if (!selected) //Pick an action (melee magic or armor)
																			  {
																				  pFont->Render("Other", "Melee", SGD::Point{ 250, 420 }, 1, SGD::Color(255, 255, 0, 0));
																				  pFont->Render("Other", "Magic", SGD::Point{ 250, 470 }, 1, SGD::Color(255, 0, 0, 255));
																			  }
																			  else
																			  {
																				  if (ActionSelected == ActionType::Magic)
																				  {
																					  if (spellSelect == -1) //Display spells
																					  {
																						  string spell1;
																						  string spell2;

																						  switch (GameplayState::GetInstance()->GetCurrentLevel())
																						  {
																						  case GameplayState::EARTH_LEVEL:
																							  spell1 = "Wind Gust";
																							  spell2 = "Fire Ball";
																							  break;
																						  case GameplayState::WATER_LEVEL:
																							  spell1 = "Rock Throw";
																							  spell2 = "Wind Gust";
																							  break;
																						  case GameplayState::AIR_LEVEL:
																							  spell1 = "Fire Ball";
																							  spell2 = "Ice Blase";
																							  break;
																						  case GameplayState::FIRE_LEVEL:
																							  spell1 = "Ice Blase";
																							  spell2 = "Rock Throw";
																							  break;
																						  case GameplayState::BOSS_LEVEL: //Bobby wants random, I agree but it'll make things harder
																							  spell1 = "Ice Blase";
																							  spell2 = "Fire Ball";
																							  break;
																						  default:
																							  spell1 = "Ice Blase";
																							  spell2 = "Fire Ball";
																							  break;
																						  }

																						  if (((Companion*)m_pObjects[CurrentTurn])->GetSpell1Cool() > 0)
																							  pFont->Render("Dialog", spell1.c_str(), { Spell1Rect.left, Spell1Rect.top }, .7f, SGD::Color(255, 255, 255, 0));
																						  else
																							  pFont->Render("Dialog", spell1.c_str(), { Spell1Rect.left, Spell1Rect.top }, .7f, SGD::Color(255, 255, 255, 255));

																						  if (((Companion*)m_pObjects[CurrentTurn])->GetSpell2Cool() > 0)
																							  pFont->Render("Dialog", spell2.c_str(), { Spell2Rect.left, Spell2Rect.top }, .7f, SGD::Color(255, 255, 255, 0));
																						  else
																							  pFont->Render("Dialog", spell2.c_str(), { Spell2Rect.left, Spell2Rect.top }, .7f, SGD::Color(255, 255, 255, 255));
																					  }
																				  }
																			  }
																			  if (CompanionSelection.left < CompanionSelection.right)
																				  pGraphics->DrawTexture(m_hTargetSelector, { CompanionSelection.left, CompanionSelection.top });
													  }
														  break;
													  case Companion::Tank:
													  {
																			  if (selected == false) //Pick an action (melee magic or armor)
																			  {

																				  pFont->Render("Other", "Melee", SGD::Point{ 250, 420 }, 1, SGD::Color(255, 255, 0, 0));
																				  pFont->Render("Other", "Block", SGD::Point{ 250, 470 }, 1, SGD::Color(255, 0, 0, 255));
																			  }
																			  if (CompanionSelection.left < CompanionSelection.right)
																				  pGraphics->DrawTexture(m_hTargetSelector, { CompanionSelection.left, CompanionSelection.top });
													  }
														  break;
													  default:
														  break;
													  }
												  }
		}
			break;
		case Object::ObjectType::OBJ_MINION:
		{
											   if (((Minion*)m_pObjects[CurrentTurn])->GetHealth() > 0)
											   {
												   SGD::Point turnIndicator = m_pObjects[CurrentTurn]->GetPosition();
												   pGraphics->DrawTexture(m_hTurnIndicator, SGD::Point(turnIndicator.x - 80, turnIndicator.y - 40), 0.0f, {}, {}, { 2.0, 2.0 });
											   }
											   if (ActionTimer <= 0)
											   {
											   }

		}
			break;
		}
	}

}

Object* CombatState::AddMinion(int _region, int EnemyID) //This is gonna get big, don't care
{
	Minion* temp = new Minion;
	temp->SetSize({ 64, 64 });

	switch (EnemyID)
	{
	case 1:
	{
			  temp->SetInit(rand() % 20);
			  temp->SetAffinity((Elements)_region);
			  temp->SetAttckSpd(rand() % 3 + 4);

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
			  int randAI = rand() % 4 + 1;
			  int randHealth = 0;

			  switch (randAI)
			  {
			  case 0: // Minion has been disabled, useless
				  randHealth = rand() % 50 + 50;
				  temp->SetMods(3, _region, 0, 0);

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
				  randHealth = rand() % 35 + 55;

				  if (randHealth > 50)
					  temp->SetMods(5, _region, 2, 1);
				  else
					  temp->SetMods(5, _region, 3, 1);

				  temp->SetAttckSpd(rand() % 3 + 6);

				  switch (_region)
				  {

				  case 0:
					  temp->SetString(_region, randAI);
					  temp->SetAffinity((Elements)(rand() % 4));
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
				  randHealth = rand() % 30 + 90;

				  if (randHealth > 90)
					  temp->SetMods(2, _region, 1, 3);
				  else
					  temp->SetMods(2, _region, 2, 3);

				  temp->SetAttckSpd(rand() % 3 + 2);

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
					  temp->SetAffinity(Elements::Earth);
					  temp->SetAIType(Minion::AI_Type::Def_AI);
					  temp->SetMinionAnimation(Elements::Earth, randAI);
					  break;
				  }
				  break;
			  case 3: // Healing
				  randHealth = rand() % 25 + 65;

				  if (randHealth > 60)
					  temp->SetMods(1, _region, 1, 2);
				  else
					  temp->SetMods(1, _region, 1, 3);

				  temp->SetAttckSpd(rand() % 3 + 4);

				  switch (_region)
				  {
				  case 0:
					  temp->SetString(_region, randAI);
					  temp->SetAffinity((Elements)(rand() % 2));
					  temp->SetAIType(Minion::AI_Type::Heal_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 1:
					  temp->SetString(_region, randAI);
					  temp->SetAffinity((Elements)(rand() % 2));
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
				  randHealth = rand() % 40 + 60;

				  if (randHealth > 75)
					  temp->SetMods(4, _region, 2, 1);
				  else
					  temp->SetMods(4, _region, 3, 2);

				  temp->SetAttckSpd(rand() % 3 + 5);

				  switch (_region)
				  {
				  case 0:
					  temp->SetString(_region, randAI);
					  temp->SetAffinity((Elements)(rand() % 4));
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
					  temp->SetAffinity((Elements)(rand() % 4));
					  temp->SetAIType(Minion::AI_Type::AOE_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  case 3:
					  temp->SetString(_region, randAI);
					  temp->SetAffinity((Elements)(rand() % 4));
					  temp->SetAIType(Minion::AI_Type::AOE_AI);
					  temp->SetMinionAnimation(_region, randAI);
					  break;
				  }
				  break;
			  default:
				  break;
			  }

			  temp->SetHealth((float)randHealth);
			  temp->SetMaxHealth((float)randHealth);
	}
		break;
	case 2: //Mini Bosses
	{
				temp->SetInit(rand() % 10 + 10);
				temp->SetAffinity((Elements)_region);

				if (m_pEnemies.size() == 0)
					temp->SetPosition({ Enemy2rect.right, Enemy2rect.bottom });
				else if (m_pEnemies.size() == 1)
					temp->SetPosition({ Enemy1rect.right, Enemy1rect.bottom });
				else if (m_pEnemies.size() == 2)
					temp->SetPosition({ Enemy3rect.right, Enemy3rect.bottom });

				temp->SetAttckSpd(rand() % 4 + 5);

				switch (_region)
				{
				case 0:
				{
						  temp->SetMods(5, _region, 3, 3);
						  temp->SetString(_region, 5);
						  temp->SetAIType(Minion::AI_Type::Mini_Boss);
						  temp->SetMinionAnimation(_region, 5);
				}
					break;
				case 1:
				{
						  temp->SetMods(5, _region, 3, 3);
						  temp->SetString(_region, 5);
						  temp->SetAIType(Minion::AI_Type::Mini_Boss);
						  temp->SetMinionAnimation(_region, 5);
				}
					break;
				case 2:
				{
						  temp->SetMods(5, _region, 3, 3);
						  temp->SetString(_region, 5);
						  temp->SetAIType(Minion::AI_Type::Mini_Boss);
						  temp->SetMinionAnimation(_region, 5);
				}
					break;
				case 3:
				{
						  temp->SetMods(5, _region, 3, 3);
						  temp->SetString(_region, 5);
						  temp->SetAIType(Minion::AI_Type::Mini_Boss);
						  temp->SetMinionAnimation(_region, 5);
				}
					break;
				default:
					break;
				}

				temp->SetHealth(200);
				temp->SetMaxHealth(200);
	}
		break;
	case 3: //Level Bosses
	{
				if (m_pEnemies.size() == 0)
					temp->SetPosition({ Enemy2rect.right, Enemy2rect.bottom });
				else if (m_pEnemies.size() == 1)
					temp->SetPosition({ Enemy1rect.right, Enemy1rect.bottom });
				else if (m_pEnemies.size() == 2)
					temp->SetPosition({ Enemy3rect.right, Enemy3rect.bottom });

				temp->SetInit(rand() % 10 + 15);
				temp->SetAffinity((Elements)_region);

				temp->SetAttckSpd(rand() % 4 + 6);

				switch (_region)
				{
				case 0:
				{
						  temp->SetMods(5, _region, 3, 3);
						  temp->SetString(4, _region);
						  temp->SetAIType(Minion::AI_Type::Level_Boss);
						  temp->SetMinionAnimation(_region, 6);
				}
					break;
				case 1:
				{
						  temp->SetMods(5, _region, 3, 3);
						  temp->SetString(4, _region);
						  temp->SetAIType(Minion::AI_Type::Level_Boss);
						  temp->SetMinionAnimation(_region, 6);
				}
					break;
				case 2:
				{
						  temp->SetMods(5, _region, 3, 3);
						  temp->SetString(4, _region);
						  temp->SetAIType(Minion::AI_Type::Level_Boss);
						  temp->SetMinionAnimation(_region, 6);
				}
					break;
				case 3:
				{
						  temp->SetMods(5, _region, 3, 3);
						  temp->SetString(4, _region);
						  temp->SetAIType(Minion::AI_Type::Level_Boss);
						  temp->SetMinionAnimation(_region, 6);
				}
					break;
				default:
					break;
				}

				temp->SetHealth(300);
				temp->SetMaxHealth(300);
	}
		break;
	case 4: //Final Boss
	{
				temp->SetPosition({ Enemy2rect.right, Enemy2rect.bottom });
				temp->SetMods(5, _region, 3, 3);
				temp->SetString(4, _region);
				temp->SetAIType(Minion::AI_Type::Final_Boss);
				temp->SetMinionAnimation(_region, 0);
				temp->SetAffinity(Earth);
				temp->SetAttckSpd(12);
				temp->SetHealth(500);
				temp->SetMaxHealth(500);
	}
		break;
	default:
		break;
	}
	return temp;
}
Object* CombatState::AddCompanion(int _type)
{
	Companion* temp = new Companion;
	temp->SetInit(rand() % 20);

	if (m_pHeroes.size() == 1)
		temp->SetPosition({ Companion1rect.right, Companion1rect.bottom });
	else if (m_pHeroes.size() == 2)
		temp->SetPosition({ Companion2rect.right, Companion2rect.bottom });

	Companion::Companion_Type coT = (Companion::Companion_Type)(_type);
	switch (coT)
	{
	case 0:
		temp->SetC0Type(Companion::Companion_Type::Cleric);
		temp->SetCompanionAnimation(0);
		break;
	case 1:
		temp->SetC0Type(Companion::Companion_Type::Melee);
		temp->SetCompanionAnimation(1);
		break;
	case 2:
		temp->SetC0Type(Companion::Companion_Type::Mage);
		temp->SetCompanionAnimation(2);
		((Companion*)temp)->SetSpell1Cool(0);
		((Companion*)temp)->SetSpell2Cool(0);
		break;
	case 3:
		((Companion*)temp)->SetC0Type(Companion::Companion_Type::Tank);
		((Companion*)temp)->SetCompanionAnimation(3);
		break;
	default:
		break;
	}
	temp->SetHealth(100);
	temp->SetMaxHealth(100);
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

								if (((Player*)_this)->GetSpell1Cool() > 0)
									((Player*)_this)->SetSpell1Cool(((Player*)_this)->GetSpell1Cool() - 1);
								if (((Player*)_this)->GetSpell2Cool() > 0)
									((Player*)_this)->SetSpell2Cool(((Player*)_this)->GetSpell2Cool() - 1);
								if (((Player*)_this)->GetSpell3Cool() > 0)
									((Player*)_this)->SetSpell3Cool(((Player*)_this)->GetSpell3Cool() - 1);

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
																	   pAudio->PlayAudio(Game::GetInstance()->m_mMagicButton);
																	   DealMagicDamage(_this, m_pEnemies[_target], _spell);
								}
									break;
								default:
									break;
								}
	}
		break;
	case iObject::OBJ_COMPANION:
	{
								   if (((Companion*)_this)->GetSpell1Cool() > 0)
									   ((Companion*)_this)->SetSpell1Cool(((Companion*)_this)->GetSpell1Cool() - 1);
								   if (((Companion*)_this)->GetSpell2Cool() > 0)
									   ((Companion*)_this)->SetSpell2Cool(((Companion*)_this)->GetSpell2Cool() - 1);

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
																		  DealMagicDamage(_this, m_pEnemies[_target], _spell);
																		  pAudio->PlayAudio(Game::GetInstance()->m_mMagicButton);
								   }
									   break;
								   case CombatState::ActionType::Block:
								   {
																		  ((Companion*)_this)->SetBlock(true);
																		  string message = "Your Ally ";
																		  SetAction(message += " Prepares to Block");
								   }
									   break;
								   case CombatState::ActionType::Heal:
								   {
																		 HealAlly(_this, m_pHeroes[_target]);
								   }
									   break;
								   case CombatState::ActionType::AOE:
								   {
																		DealAOEDamage(_this, m_pEnemies[_target]);
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
											switch (_ActionType)
											{
											case ActionType::Melee:
												DealMeleeDamage(_this, m_pHeroes[_target]);
												break;
											case ActionType::AOE:
												DealAOEDamage(_this, m_pHeroes[_target]);
												break;
											case ActionType::Magic:
												DealMagicDamage(_this, m_pHeroes[_target], 0);
												break;
											default:
												break;
											}
								}
									break;
								case 6: //Level Boss
								{
											string message = "The ";
											message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
											SetAction(message += " Attacks!");
											switch (_ActionType)
											{
											case ActionType::Melee:
												DealMeleeDamage(_this, m_pHeroes[_target]);
												break;
											case ActionType::AOE:
												DealAOEDamage(_this, m_pHeroes[_target]);
												break;
											case ActionType::Magic:
												DealMagicDamage(_this, m_pHeroes[_target], 0);
												break;
											default:
												break;
											}
								}
									break;
								case 7: //Final Boss
								{
											string message = "The ";
											message += (pGame->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
											SetAction(message += " Attacks!");
											switch (_ActionType)
											{
											case ActionType::Melee:
												DealMeleeDamage(_this, m_pHeroes[_target]);
												break;
											case ActionType::AOE:
												DealAOEDamage(_this, m_pHeroes[_target]);
												break;
											case ActionType::Magic:
												break;
											default:
												break;
											}
								}
									break;
								}
	}
	default:
		break;
		return false;
	}
	return false;
}

int CombatState::DealMeleeDamage(Object* _From, Object* _To)
{
	// Would like to get damage modifiers for minion attacks against armor runes

	int Total = 0;
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
			else if (((Minion*)_To)->GetAIType() == Minion::AI_Type::Mini_Boss || ((Minion*)_To)->GetAIType() == Minion::AI_Type::Level_Boss)
			{
				if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::AIR_LEVEL)
				{
					if (rand() % 20 < 10)
					{
						localBlock = true;
						string message = "The ";
						message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
						SetAction(message += " Dodges the Attack!");
						_To->SetInit(25);
					}
				}
				else if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::WATER_LEVEL)
				{
					if (rand() % 20 < 10)
					{
						localBlock = true;
						string message = "The ";
						message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
						SetAction(message += " Repels your Attack!");
						_From->SetInit(-5);
					}
				}
				else if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::EARTH_LEVEL)
				{
					if (rand() % 20 < 10)
					{
						localBlock = true;
						string message = "The ";
						message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
						SetAction(message += " Blocks your Attack!");
					}
				}
			}
		}

		if (localBlock == false)
		{
			ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());

			Total = (int)((((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) + ((m_nNumQtCorrect *  (((Minion*)_To)->GetMods().DamageLevel - 1)) / m_nQTLength)) * 10) + 15));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			_To->SetDeltaHP(-Total);
			m_nNumQtCorrect = 0;

			if (((Minion*)_To)->GetAIType() == Minion::Off_AI)
			{
				if (rand() % 20 > 1)
				{
					DealCounterDamage(_To, _From);
					return 0;
				}
			}

			string message = "You Attack the ";
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
				if (((Companion*)m_pHeroes[i])->GetBlock() && ((Companion*)m_pHeroes[i])->GetHealth() > 0)
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
			Total = rand() % (10 * ((Minion*)_From)->GetMods().DamageLevel) + 3 * (((Minion*)_From)->GetMods().DamageLevel + 5);

			if (_To->GetType() == iObject::OBJ_PLAYER)
			{
				RuneManager rmtemp;

				switch (((Minion*)_From)->GetAIType())
				{
				case Minion::AI_Type::Off_AI:
					Total *= (int)(rmtemp.DamageReduction((((Minion*)_From)->GetAffinity()), InventoryState::GetInstance()->GetArmorSlot2()));
					break;
				case Minion::AI_Type::Def_AI:
					Total *= (int)(rmtemp.DamageReduction((((Minion*)_From)->GetAffinity()), InventoryState::GetInstance()->GetArmorSlot3()));
					break;
				case Minion::AI_Type::Heal_AI:
					Total *= (int)(rmtemp.DamageReduction((((Minion*)_From)->GetAffinity()), InventoryState::GetInstance()->GetArmorSlot1()));
					break;
				case Minion::AI_Type::AOE_AI:
					Total *= (int)(rmtemp.DamageReduction((((Minion*)_From)->GetAffinity()), InventoryState::GetInstance()->GetArmorSlot1()));
					break;
				default:
					int boss = rand() % 3;
					if (boss == 0)
						Total *= (int)(rmtemp.DamageReduction((((Minion*)_From)->GetAffinity()), InventoryState::GetInstance()->GetArmorSlot1()));
					else if (boss == 1)
						Total *= (int)(rmtemp.DamageReduction((((Minion*)_From)->GetAffinity()), InventoryState::GetInstance()->GetArmorSlot2()));
					else if (boss == 2)
						Total *= (int)(rmtemp.DamageReduction((((Minion*)_From)->GetAffinity()), InventoryState::GetInstance()->GetArmorSlot3()));
					break;
				}


				((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
				if (rand() % 20 > 15)
				{
					_To->SetDeltaHP(-Total);
					DealCounterDamage(_To, _From);
					return 0;
				}

			}
			if (_To->GetType() == iObject::OBJ_COMPANION)
			{
				((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
				if (((Companion*)_To)->GetCoType() == Companion::Melee)
				{
					if (rand() % 20 > 15)
					{
						_To->SetDeltaHP(-Total);
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
			else if (((Minion*)_To)->GetAIType() == Minion::AI_Type::Mini_Boss || ((Minion*)_To)->GetAIType() == Minion::AI_Type::Level_Boss)
			{
				if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::AIR_LEVEL) //Dodge
				{
					if (rand() % 20 < 10)
					{
						localBlock = true;
						string message = "The ";
						message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
						SetAction(message += " Dodges the Attack!");
						_To->SetInit(25);

					}
				}
				else if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::WATER_LEVEL) //Repel
				{
					if (rand() % 20 < 10)
					{
						localBlock = true;
						string message = "The ";
						message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
						SetAction(message += " Repels your Ally's Attack!");
						_From->SetInit(-5);
					}
				}
				else if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::EARTH_LEVEL) // ???
				{
					if (rand() % 20 < 10)
					{
						localBlock = true;
						string message = "The ";
						message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
						SetAction(message += " Blocks your Ally's Attack!");
					}
				}
				else if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::FIRE_LEVEL) // Burn?
				{

				}
			}
		}

		if (!localBlock)
		{
			Total = rand() % 25 + 30;
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			string message = "Your Ally attacks the ";
			message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
			SetAction(message += "!");
		}
	}
	m_bShake = true;
	_To->SetDeltaHP(-Total);
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
						 spell1 = "Fire Ball(1)";
					 }
					 if (temp1.GetTier() == 2)
					 {
						 spell1 = "Fire Ball(2)";
					 }
					 if (temp1.GetTier() == 3)
					 {
						 spell1 = "Fire Ball(3)";
					 }
		}
			break;
		case Water:
		{
					  if (temp1.GetTier() == 1)
					  {
						  spell1 = "Water Blase(1)";
					  }
					  if (temp1.GetTier() == 2)
					  {
						  spell1 = "Water Blase(2)";
					  }
					  if (temp1.GetTier() == 3)
					  {
						  spell1 = "Water Blase(3)";
					  }
		}
			break;
		case Air:
		{
					if (temp1.GetTier() == 1)
					{
						spell1 = "Wind Gust(1)";
					}
					if (temp1.GetTier() == 2)
					{
						spell1 = "Wind Gust(2)";
					}
					if (temp1.GetTier() == 3)
					{
						spell1 = "Wind Gust(3)";
					}
		}
			break;
		case Earth:
		{
					  if (temp1.GetTier() == 1)
					  {
						  spell1 = "Rock Throw(1)";
					  }
					  if (temp1.GetTier() == 2)
					  {
						  spell1 = "Rock Throw(2)";
					  }
					  if (temp1.GetTier() == 3)
					  {
						  spell1 = "Rock Throw(3)";
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
			Total = (int)((((mag.DamagetoBaseElement(e1, ((Minion*)_To)->GetAffinity()) * 2 + m_nNumQtCorrect) * (pInventory->m_vRing[0].GetTier() * 5)) / (((Minion*)_To)->GetMods().ElemResistance.ElementTier) + (rand() % 10 - 5)));
			((Player*)_From)->SetSpell1Cool(pInventory->m_vRing[0].GetTier());
			break;
		case 1:
			ComboElements d1;
			stuff += spell2.c_str();
			d1 = mag.ElementCombination(InventoryState::GetInstance()->GetRingSlot1(), InventoryState::GetInstance()->GetRingSlot2());
			Total = (int)((((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) * 2 + m_nNumQtCorrect) * (pInventory->m_vRing[1].GetTier() * 5)) / (((Minion*)_To)->GetMods().ElemResistance.ElementTier) + (rand() % 10 - 5)));
			((Player*)_From)->SetSpell2Cool(pInventory->m_vRing[1].GetTier());
			break;
		case 2:
			ComboElements d2;
			stuff += spell3.c_str();
			d2 = mag.ElementCombination(InventoryState::GetInstance()->GetRingSlot2(), InventoryState::GetInstance()->GetRingSlot3());
			Total = (int)((((mag.DamageComboElement(d2, ((Minion*)_To)->GetAffinity()) * 2 + m_nNumQtCorrect) * (pInventory->m_vRing[2].GetTier() * 5)) / (((Minion*)_To)->GetMods().ElemResistance.ElementTier) + (rand() % 10 - 5)));
			((Player*)_From)->SetSpell3Cool(pInventory->m_vRing[2].GetTier());
			break;
		default:
			break;
		}
		stuff += " on the ";
		SetAction(stuff += Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
		_To->SetDeltaHP(-Total);
		m_nNumQtCorrect = 0;
	}
	else if (_From->GetType() == iObject::OBJ_COMPANION)
	{
		string message = "Your Ally Casts ";

		switch ((_spell - 2) + (GameplayState::GetInstance()->GetCurrentLevel() * 2))
		{
		case 0: //Earth
			message += "Wind Gust";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Air, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		case 1:
			message += "Fire Ball";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Fire, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		case 2: //Water																  
			message += "Rock Throw";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Earth, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		case 3:
			message += "Wind Gust";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Air, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		case 4: //Air																  
			message += "Fire Ball";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Fire, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		case 5:
			message += "Ice Blase";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Water, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		case 6: //Fire																  
			message += "Ice Blase";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Water, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		case 7:
			message += "Rock Throw";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Earth, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		case 8:
			message += "Ice Blase";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Water, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		case 9:
			message += "Fire Ball";
			Total = ((rand() % 5 + 7) * 5 - (rand() % (((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
			Total *= (int)(mag.DamagetoBaseElement(Elements::Fire, ((Minion*)_To)->GetAffinity()));
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			break;
		default:
			if (_spell == 0)
			{
				message += "Ice Blase";
				Total = (((rand() % 5 + 7) * 5 - (rand() % ((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
				Total *= (int)(mag.DamagetoBaseElement(Elements::Water, ((Minion*)_To)->GetAffinity()));
				((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			}
			else
			{
				message += "Fire Ball";
				Total = (((rand() % 5 + 7) * 5 - (rand() % ((Minion*)_To)->GetMods().ElemResistance.ElementTier) * 3 + (rand() % 10 - 5)));
				Total *= (int)(mag.DamagetoBaseElement(Elements::Fire, ((Minion*)_To)->GetAffinity()));
				((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
			}
			break;
		}

		if (_spell == 0)
			((Companion*)_From)->SetSpell1Cool(2);
		else
			((Companion*)_From)->SetSpell2Cool(2);

		message += " on the ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += "!");
	}
	else if (_From->GetType() == iObject::OBJ_MINION)
	{
		string message = "The ";
		message += (Game::GetInstance()->GetString(((Minion*)_From)->GetName(0), ((Minion*)_From)->GetName(1)).c_str());
		message += " Casts ";
		if (_To->GetType() == iObject::OBJ_PLAYER)
		{
			switch (((Minion*)_From)->GetAIType())
			{
			case Minion::AI_Type::Mini_Boss: // Low level spell of that region
				Total = rand() % 20 + 35;
				switch (GameplayState::GetInstance()->GetCurrentLevel())
				{
				case GameplayState::EARTH_LEVEL:
					message += "Rock Throw";
					//Total *= (int)((mag.DamagetoBaseElement(Elements::Earth, InventoryState::m_vArmor[0].GetElement());

					((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
					break;
				case GameplayState::WATER_LEVEL:
					message += "Water Blast";
					//Total *= (int)((mag.DamagetoBaseElement(Elements::Earth, InventoryState::m_vArmor[0].GetElement());

					((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
					break;
				case GameplayState::AIR_LEVEL:
					message += "Wind Gust";
					//Total *= (int)((mag.DamagetoBaseElement(Elements::Earth, InventoryState::m_vArmor[0].GetElement());

					((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
					break;
				case GameplayState::FIRE_LEVEL:
					message += "Fire Ball";
					//Total *= (int)((mag.DamagetoBaseElement(Elements::Earth, InventoryState::m_vArmor[0].GetElement());

					((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
					break;
				default:
					break;
				}
				break;
			case Minion::AI_Type::Level_Boss: // High level spell of that region
				Total = rand() % 20 + 35;

				switch (GameplayState::GetInstance()->GetCurrentLevel())
				{
				case GameplayState::EARTH_LEVEL:
					message += "Rock Throw";
					//Total *= (int)((mag.DamagetoBaseElement(Elements::Earth, InventoryState::m_vArmor[0].GetElement());

					((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);

					break;
				case GameplayState::WATER_LEVEL:
					message += "Water Blast";
					//Total *= (int)((mag.DamagetoBaseElement(Elements::Earth, InventoryState::m_vArmor[0].GetElement());

					((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);

					break;
				case GameplayState::AIR_LEVEL:
					message += "Wind Gust";
					//Total *= (int)((mag.DamagetoBaseElement(Elements::Earth, InventoryState::m_vArmor[0].GetElement());

					((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);

					break;
				case GameplayState::FIRE_LEVEL:
					if (_spell == 0)
					{
						message += "Fire Ball";
						//Total *= (int)((mag.DamagetoBaseElement(Elements::Earth, InventoryState::m_vArmor[0].GetElement());

						((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
					}
					else if (_spell == 1) //Inferno AOE
					{
						message += "Inferno";
						//Total *= (int)((mag.DamagetoBaseElement(Elements::Earth, InventoryState::m_vArmor[0].GetElement());

						((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() - Total);
						for (size_t i = 1; i < (int)m_pHeroes.size(); i++)
						{
							((Companion*)m_pHeroes[i])->SetHealth(((Companion*)_To)->GetHealth() - Total);
						}
					}

					break;
				default:
					break;
				}
				break;
			case Minion::AI_Type::Final_Boss: // idfk
				break;
			default:
				break;
			}
			SetAction(message += " on You!");
		}
		else if (_To->GetType() == iObject::OBJ_COMPANION)
		{
			switch (((Minion*)_From)->GetAIType())
			{
			case Minion::AI_Type::Mini_Boss: // Low level spell of that region
				Total = rand() % 20 + 35;
				switch (GameplayState::GetInstance()->GetCurrentLevel())
				{
				case GameplayState::EARTH_LEVEL:
					message += "Rock Throw";
					((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
					break;
				case GameplayState::WATER_LEVEL:
					message += "Water Blast";
					((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
					break;
				case GameplayState::AIR_LEVEL:
					message += "Wind Gust";
					((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
					break;
				case GameplayState::FIRE_LEVEL:
					message += "Fire Ball";
					((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
					break;
				default:
					break;
				}
				break;
			case Minion::AI_Type::Level_Boss: // High level spell of that region
				Total = rand() % 25 + 40;
				switch (GameplayState::GetInstance()->GetCurrentLevel())
				{
				case GameplayState::EARTH_LEVEL:
					message += "Rock Throw";
					((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
					break;
				case GameplayState::WATER_LEVEL:
					message += "Water Blast";
					((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
					break;
				case GameplayState::AIR_LEVEL:
					message += "Wind Gust";
					((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
					break;
				case GameplayState::FIRE_LEVEL:
					message += "Fire Ball";
					((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
					break;
				default:
					break;
				}
				break;
			case Minion::AI_Type::Final_Boss: // idfk
				break;
			default:
				break;
			}

			SetAction(message += " on your Ally!");
		}
	}
	m_bShake = true;
	_To->SetDeltaHP(-Total);
	return Total;
}
int CombatState::DealCounterDamage(Object* _From, Object* _To)
{
	int Total = 0;
	RuneManager mag;

	if (_From->GetType() == iObject::OBJ_PLAYER)
	{
		ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());

		Total = (int)(((mag.DamageComboElement(d1, ((Minion*)_To)->GetAffinity()) * 15)));
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
		string message = "You Counter the ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += "'s Attack!");
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
	}
	else if (_From->GetType() == iObject::OBJ_COMPANION)
	{
		Total = rand() % 15 + 30;
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
		string message = "Your Ally counters the ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += "'s attack!");
	}

	_To->SetDeltaHP(-Total);
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

		m_nNumQtCorrect = 0;

		Total = rand() % 15 + 10;
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
	}
	else if (_From->GetType() == iObject::OBJ_MINION)
	{
		Total = rand() % 15 + 10;
		((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() - Total);
		string message = "Your Ally Intercepts the ";
		message += (Game::GetInstance()->GetString(((Minion*)_From)->GetName(0), ((Minion*)_From)->GetName(1)).c_str());
		SetAction(message += "'s  Attack!");
	}
	else if (_From->GetType() == iObject::OBJ_COMPANION)
	{
		string message = "The ";
		message += (Game::GetInstance()->GetString(((Minion*)_To)->GetName(0), ((Minion*)_To)->GetName(1)).c_str());
		SetAction(message += " Intercepts your Ally's Attack!");

		Total = rand() % 15 + 10;
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() - Total);
	}
	m_bShake = true;
	_To->SetDeltaHP(-Total);
	return Total;
}
int CombatState::HealAlly(Object* _From, Object* _To)
{
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	int Total;

	Total = rand() % 30 + 20;
	if (_From->GetType() == iObject::OBJ_PLAYER) //player never heals, but w/e
	{
		pAudio->PlayAudio(cHealingAbility, false);
		((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() + Total);

		_To->SetDeltaHP(Total);
	}
	else if (_From->GetType() == iObject::OBJ_MINION)
	{
		pAudio->PlayAudio(cHealingAbility, false);
		((Minion*)_To)->SetHealth(((Minion*)_To)->GetHealth() + Total);

		if (((Minion*)_To)->GetHealth() > ((Minion*)_To)->GetMaxHealth())
			((Minion*)_To)->SetHealth(((Minion*)_To)->GetMaxHealth());

		_To->SetDeltaHP(Total);
	}
	else if (_From->GetType() == iObject::OBJ_COMPANION)
	{
		if (_To->GetType() == iObject::OBJ_PLAYER)
		{
			pAudio->PlayAudio(cHealingAbility, false);
			((Player*)_To)->SetHealth(((Player*)_To)->GetHealth() + Total);

			if (((Player*)_To)->GetHealth() > ((Player*)_To)->GetMaxHealth())
				((Player*)_To)->SetHealth(((Player*)_To)->GetMaxHealth());

			_To->SetDeltaHP(Total);
		}
		else if (_To->GetType() == iObject::OBJ_COMPANION)
		{
			pAudio->PlayAudio(cHealingAbility, false);
			((Companion*)_To)->SetHealth(((Companion*)_To)->GetHealth() + Total);

			if (((Companion*)_To)->GetHealth() > ((Companion*)_To)->GetMaxHealth())
				((Companion*)_To)->SetHealth(((Companion*)_To)->GetMaxHealth());

			_To->SetDeltaHP(Total);
		}
	}

	return Total;
}
int CombatState::DealAOEDamage(Object* _From, Object* _To)
{
	int Total = 0;
	//RuneManager mag;
	bool localBlock = false;

	if (_From->GetType() == iObject::OBJ_MINION)
	{
		for (size_t i = 1; i < m_pHeroes.size(); i++)
		{
			if (((Companion*)m_pHeroes[i])->GetCoType() == Companion::Companion_Type::Tank)
			{
				if (((Companion*)m_pHeroes[i])->GetBlock())
				{
					BlockAttack(_From, m_pHeroes[i]);
					localBlock = true;
					((Companion*)m_pHeroes[i])->SetBlock(false);
					return 0;
				}
			}
		}

		if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::EARTH_LEVEL)
		{
			string message = "The ";
			message += (Game::GetInstance()->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
			SetAction(message += " Uses Ground Slam!");
		}
		else if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::WATER_LEVEL)
		{
			string message = "The ";
			message += (Game::GetInstance()->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
			SetAction(message += " Uses Whirlpool!");
		}
		else if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::AIR_LEVEL)
		{
			string message = "The ";
			message += (Game::GetInstance()->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
			SetAction(message += " Uses Sonic Boom!");
		}
		else if (GameplayState::GetInstance()->GetCurrentLevel() == GameplayState::FIRE_LEVEL)
		{
			string message = "The ";
			message += (Game::GetInstance()->GetString(((Minion*)m_pObjects[CurrentTurn])->GetName(0), ((Minion*)m_pObjects[CurrentTurn])->GetName(1)).c_str());
			SetAction(message += " Uses Ground Slam!");
		}

		if (((Player*)m_pHeroes[0])->GetHealth() > 0)
		{
			Total = rand() % 20 + 15;
			m_pHeroes[0]->SetDeltaHP(-Total);
			((Player*)m_pHeroes[0])->SetHealth(((Player*)m_pHeroes[0])->GetHealth() - Total);
		}
		for (size_t i = 1; i < m_pHeroes.size(); i++)
		{
			if (((Companion*)m_pHeroes[i])->GetHealth() > 0)
			{
				Total = rand() % 20 + 15;
				m_pHeroes[i]->SetDeltaHP(-Total);
				((Companion*)m_pHeroes[i])->SetHealth(((Companion*)m_pHeroes[i])->GetHealth() - Total);
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
					((Minion*)m_pEnemies[i])->m_Block = false;
					return 0;
				}
			}
		}
		string message = "You Ally uses ";
		SetAction(message += "Fury!");
		for (size_t i = 0; i < m_pEnemies.size(); i++)
		{
			if (((Minion*)m_pEnemies[i])->GetHealth() > 0)
			{
				Total = rand() % 20 + 15;
				m_pEnemies[i]->SetDeltaHP(-Total);
				((Minion*)m_pEnemies[i])->SetHealth(((Minion*)m_pEnemies[i])->GetHealth() - Total);
			}
		}
	}
	m_bShake = true;
	return Total;
}
bool CombatState::TakeTurn(Object* _this)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = BitmapFontManager::GetInstance();
	CombatState* pCombat = CombatState::GetInstance();
	InventoryState* pInventory = InventoryState::GetInstance();

	switch (_this->GetType())
	{
#pragma region PlayerTakeTurn
	case iObject::OBJ_PLAYER:
	{
								if (((Player*)_this)->GetHealth() < 0) //necessary?
									return false;

								if (!selected)
								{
									spellActive = false;
									if (((Player*)_this)->GetSpell1Cool() != -1)
										spellActive = true;
									if (((Player*)_this)->GetSpell2Cool() != -1)
										spellActive = true;
									if (((Player*)_this)->GetSpell3Cool() != -1)
										spellActive = true;

									float posX = 200.0f;
									PlayerSelection = { posX, (float)(420 + 50 * m_nCursor), posX + 40, (float)(430 + 50 * m_nCursor) };

									if (spellActive)
									{
										pCombat->SetAction("Choose Action");

										if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || ((pInput->GetLeftJoystick(0).y == -1 || pInput->IsKeyDown(SGD::Key::Down)) && m_fArcadeTimer >= 0.5f))
										{
											m_nCursor--;
											m_fArcadeTimer = 0.0f;
										}
										if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || ((pInput->GetLeftJoystick(0).y == 1 || pInput->IsKeyDown(SGD::Key::Down)) && m_fArcadeTimer >= 0.5f))
										{
											m_nCursor++;
											m_fArcadeTimer = 0.0f;
										}

										if (m_nCursor < 0)
											m_nCursor = 0;
										if (m_nCursor > 1)
											m_nCursor = 1;
									}
									else if (!spellActive)
										SetAction("No Spells Available!");

									//First Selection >> Action
									if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
									{
										if (m_nCursor == 0)
										{
											ActionSelected = m_nCursor;
											selected = true;
											m_nCursor = 0;
										}
										if (spellActive && m_nCursor == 1)
										{
											ActionSelected = m_nCursor;
											selected = true;
											m_nCursor = 0;
										}
										m_fArcadeTimer = 0.0f;
									}
								}
								else //Action selected, now pick target
								{
									if (ActionSelected == 0) //Melee
									{
										PlayerSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 120, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y - 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 80, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y };
										pCombat->SetAction("Choose Target");

										if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || ((pInput->GetLeftJoystick(0).y == -1 || pInput->IsKeyDown(SGD::Key::Down)) && m_fArcadeTimer >= 0.5f))
										{
											m_nCursor--;
											m_fArcadeTimer = 0.0f;
										}
										if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || ((pInput->GetLeftJoystick(0).y == 1 || pInput->IsKeyDown(SGD::Key::Down)) && m_fArcadeTimer >= 0.5f))
										{
											m_nCursor++;
											m_fArcadeTimer = 0.0f;
										}

										if (m_nCursor < 0)
											m_nCursor = m_pEnemies.size() - 1;
										if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
											m_nCursor = 0;

										if (((Minion*)pCombat->GetEnemies()[m_nCursor])->GetHealth() <= 0)
											m_nCursor++;

										if (m_nCursor < 0)
											m_nCursor = m_pEnemies.size() - 1;
										if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
											m_nCursor = 0;

										//Second Selection >> Target
										if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
										{
											((Player*)_this)->SetAttacking(true);
											entered = true;

											int xx = 0;
											for (int i = 0; i < (int)InventoryState::GetInstance()->m_vSword.size(); i++)
											{
												if (InventoryState::GetInstance()->m_vSword[i].GetElement() != None)
													xx++;
											}
											if (xx == 0)
												xx = 1;

											m_nQTLength = xx * 3;

											Game::GetInstance()->AddState(QuickTimeState::GetInstance());

											m_fArcadeTimer = 0.0f;
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
												((Player*)_this)->ResetAnimation();
												return true;
											}
										}
									}
									else if (ActionSelected == 1) //Magic
									{
										if (spellSelect == -1)
										{
											//#pragma region spells
											pCombat->SetAction("Choose Spell");

											if (m_nCursor == 0)
											{
												PlayerSelection = { Spell1Rect.left - 50, Spell1Rect.top, Spell1Rect.right - 50, Spell1Rect.bottom };
												CombatToolTip = 0;
											}
											else if (m_nCursor == 1)
											{
												PlayerSelection = { Spell2Rect.left - 50, Spell2Rect.top, Spell2Rect.right - 50, Spell3Rect.bottom };
												CombatToolTip = 1;

											}
											else if (m_nCursor == 2)
											{
												PlayerSelection = { Spell3Rect.left - 50, Spell3Rect.top, Spell3Rect.right - 50, Spell3Rect.bottom };
												CombatToolTip = 2;
											}
											if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::A) || ((pInput->GetLeftJoystick(0).x == -1 || pInput->IsKeyDown(SGD::Key::Down)) && m_fArcadeTimer >= 0.5f))
											{
												m_nCursor--;
												m_fArcadeTimer = 0.0f;
											}
											if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::D) || ((pInput->GetLeftJoystick(0).x == 1 || pInput->IsKeyDown(SGD::Key::Down)) && m_fArcadeTimer >= 0.5f))
											{
												m_nCursor++;
												m_fArcadeTimer = 0.0f;
											}


											if (m_nCursor < 0)
												m_nCursor = 0;
											if (m_nCursor >(int)pInventory->m_vRing.size() - 1)
												m_nCursor = (int)pInventory->m_vRing.size() - 1;

											if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
											{
												if (m_nCursor == 0)
												{
													if (((Player*)_this)->GetSpell1Cool() == 0)
													{
														spellSelect = m_nCursor;
														m_nCursor = 0;
													}
												}
												else if (m_nCursor == 1)
												{
													if (((Player*)_this)->GetSpell2Cool() == 0)
													{
														spellSelect = m_nCursor;
														m_nCursor = 0;
													}
												}
												else if (m_nCursor == 2)
												{
													if (((Player*)_this)->GetSpell3Cool() == 0)
													{
														spellSelect = m_nCursor;
														m_nCursor = 0;
													}
												}
												m_fArcadeTimer = 0.0f;
											}
										}
										//#pragma endregion
										else // spellSelect is set, choose target
										{
											pCombat->SetAction("Choose Target");
											int prevCursor = m_nCursor;
											PlayerSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 120, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y - 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 80, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y };
											if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || ((pInput->GetLeftJoystick(0).y == -1 || pInput->IsKeyDown(SGD::Key::Down)) && m_fArcadeTimer >= 0.5f))
											{
												m_nCursor--;
												m_fArcadeTimer = 0.0f;
											}
											if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || ((pInput->GetLeftJoystick(0).y == 1 || pInput->IsKeyDown(SGD::Key::Down)) && m_fArcadeTimer >= 0.5f))
											{
												m_nCursor++;
												m_fArcadeTimer = 0.0f;
											}

											if (m_nCursor < 0)
												m_nCursor = m_pEnemies.size() - 1;
											if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
												m_nCursor = 0;

											if (((Minion*)pCombat->GetEnemies()[m_nCursor])->GetHealth() <= 0)
												m_nCursor++;

											if (m_nCursor < 0)
												m_nCursor = m_pEnemies.size() - 1;
											if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
												m_nCursor = 0;

											//Second Selection >> Target
											if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
											{
												entered = true;

												int xx = 0;
												for (int i = 0; i < (int)InventoryState::GetInstance()->m_vRing.size(); i++)
												{
													if (InventoryState::GetInstance()->m_vRing[i].GetElement() != None)
														xx++;
												}
												if (xx == 0)
													xx = 1;

												m_nQTLength = xx * 3;
												Game::GetInstance()->AddState(QuickTimeState::GetInstance());
												m_fArcadeTimer = 0.0f;
											}
											if (entered)
											{
												if (QuickTimeState::GetInstance()->GetCurrentQT()->GetIsOver())
												{
													entered = false;
													selected = false;
													QuickTimeState::GetInstance()->StopQuickTime();
													((Player*)_this)->SetAttacking(true);
													TakeAction(ActionSelected, _this, m_nCursor, spellSelect);
													spellSelect = -1;
													m_nCursor = 0;
													return true;
												}
											}
										}
									}
								}
								return false;
								break;
	}
#pragma endregion
#pragma region CompTakeTurn
	case iObject::OBJ_COMPANION:
	{
								   float posX = 200.0f;
								   CompanionSelection = { posX, (float)(420 + 50 * m_nCursor), posX + 40, (float)(430 + 50 * m_nCursor) };

								   if (((Companion*)_this)->GetHealth() < 0)
									   return false;

								   switch (((Companion*)_this)->GetCoType())
								   {
#pragma region cleric
								   case Companion::Companion_Type::Cleric:
								   {
																			 if (!selected) //Pick an action (melee magic or armor)
																			 {
																				 pCombat->SetAction("Choose Action");

																				 if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || (pInput->GetLeftJoystick(0).y == -1 && m_fArcadeTimer >= 1.0f))
																				 {
																					 m_nCursor--;
																					 m_fArcadeTimer = 0.0f;
																				 }

																				 if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || (pInput->GetLeftJoystick(0).y == 1 && m_fArcadeTimer >= 1.0f))
																				 {
																					 m_nCursor++;
																					 m_fArcadeTimer = 0.0f;
																				 }
																				 if (m_nCursor < 0)
																					 m_nCursor = 1;
																				 if (m_nCursor > 1)
																					 m_nCursor = 0;

																				 //First Selection >> Action
																				 if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
																				 {
																					 if (m_nCursor == 0)
																					 {
																						 ActionSelected = m_nCursor;
																						 selected = true;
																						 m_nCursor = 0;
																					 }
																					 else if (m_nCursor == 1)
																					 {
																						 ActionSelected = CombatState::ActionType::Heal;
																						 selected = true;
																						 m_nCursor = 0;
																					 }
																					 m_fArcadeTimer = 0.0f;
																				 }
																			 }
																			 else//Action selected, now pick target
																			 {
																				 pCombat->SetAction("Choose Target");
																				 CompanionSelection = { ((Player*)m_pHeroes[m_nCursor])->GetPosition().x - 140, ((Player*)m_pHeroes[m_nCursor])->GetPosition().y - 40, ((Player*)m_pHeroes[m_nCursor])->GetPosition().x - 100, ((Player*)m_pHeroes[m_nCursor])->GetPosition().y };

																				 int prevCursor = m_nCursor;

																				 if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || (pInput->GetLeftJoystick(0).y == -1 && m_fArcadeTimer >= 1.0f))
																				 {
																					 m_nCursor++;
																					 m_fArcadeTimer = 0.0f;
																				 }

																				 if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || (pInput->GetLeftJoystick(0).y == 1 && m_fArcadeTimer >= 1.0f))
																				 {
																					 m_nCursor--;
																					 m_fArcadeTimer = 0.0f;
																				 }



																				 if (ActionSelected == CombatState::ActionType::Heal)
																				 {
																					 if (m_nCursor < 0)
																						 m_nCursor = m_pHeroes.size() - 1;
																					 if (m_nCursor >(int)m_pHeroes.size() - 1)
																						 m_nCursor = 0;

																					 if (((Player*)pCombat->GetHeroes()[m_nCursor])->GetHealth() <= 0)
																					 {
																						 if (m_nCursor > prevCursor)
																							 m_nCursor--;
																						 else
																							 m_nCursor++;
																					 }
																					 CompanionSelection = { ((Player*)m_pHeroes[m_nCursor])->GetPosition().x + 100, ((Player*)m_pHeroes[m_nCursor])->GetPosition().y, ((Player*)m_pHeroes[m_nCursor])->GetPosition().x + 140, ((Player*)m_pHeroes[m_nCursor])->GetPosition().y + 20 };

																					 if (m_nCursor < 0)
																						 m_nCursor = 0;
																					 if (m_nCursor >(int)m_pHeroes.size() - 1)
																						 m_nCursor = m_pHeroes.size() - 1;
																				 }
																				 else
																				 {
																					 if (m_nCursor < 0)
																						 m_nCursor = m_pEnemies.size() - 1;
																					 if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																						 m_nCursor = 0;

																					 if (((Minion*)pCombat->GetEnemies()[m_nCursor])->GetHealth() <= 0)
																						 m_nCursor++;

																					 if (m_nCursor < 0)
																						 m_nCursor = m_pEnemies.size() - 1;
																					 if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																						 m_nCursor = 0;

																					 CompanionSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 120, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y - 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 80, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y };
																				 }

																				 //Second Selection >> Target
																				 if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
																				 {
																					 selected = false;
																					 ((Companion*)_this)->SetAttacking(true);

																					 TakeAction(ActionSelected, _this, m_nCursor);
																					 m_nCursor = 0;
																					 m_fArcadeTimer = 0.0f;

																					 return true;
																				 }
																				 ((Companion*)_this)->SetAnimation(true);
																				 ((Companion*)_this)->ResetAnimation();
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
																				pCombat->SetAction("Choose Action");

																				if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || (pInput->GetLeftJoystick(0).y == -1 && m_fArcadeTimer >= 1.0f))
																				{
																					m_nCursor--;
																					m_fArcadeTimer = 0.0f;
																				}
																				if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || (pInput->GetLeftJoystick(0).y == 1 && m_fArcadeTimer >= 1.0f))
																				{
																					m_nCursor++;
																					m_fArcadeTimer = 0.0f;
																				}


																				if (m_nCursor < 0)
																					m_nCursor = 0;
																				if (m_nCursor > 1)
																					m_nCursor = 1;

																				//First Selection >> Action
																				if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
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
																						ActionSelected = CombatState::ActionType::AOE;
																						selected = true;
																						m_nCursor = 0;
																					}

																					m_fArcadeTimer = 0.0f;

																				}
																			}
																			else //Action selected, now pick target
																			{
																				pCombat->SetAction("Choose Target");

																				int prevCursor = m_nCursor;

																				if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || (pInput->GetLeftJoystick(0).y == -1 && m_fArcadeTimer >= 1.0f))
																				{
																					m_nCursor--;
																					m_fArcadeTimer = 0.0f;
																				}
																				if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || (pInput->GetLeftJoystick(0).y == 1 && m_fArcadeTimer >= 1.0f))
																				{
																					m_nCursor++;
																					m_fArcadeTimer = 0.0f;
																				}

																				if (m_nCursor < 0)
																					m_nCursor = m_pEnemies.size() - 1;
																				if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																					m_nCursor = 0;

																				if (((Minion*)pCombat->GetEnemies()[m_nCursor])->GetHealth() <= 0)
																					m_nCursor++;

																				if (m_nCursor < 0)
																					m_nCursor = m_pEnemies.size() - 1;
																				if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																					m_nCursor = 0;

																				CompanionSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 120, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y - 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 80, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y };
																				//Second Selection >> Target
																				if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
																				{
																					selected = false;
																					((Companion*)_this)->SetAttacking(true);
																					TakeAction(ActionSelected, _this, m_nCursor);
																					m_nCursor = 0;
																					m_fArcadeTimer = 0.0f;
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
																		   if (selected == false) //Pick an action (melee magic or armor)
																		   {
																			   spellActive = false;
																			   if (((Companion*)_this)->GetSpell1Cool() != -1)
																				   spellActive = true;
																			   if (((Companion*)_this)->GetSpell2Cool() != -1)
																				   spellActive = true;

																			   if (spellActive)
																			   {
																				   pCombat->SetAction("Choose Action");

																				   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || (pInput->GetLeftJoystick(0).y == -1 && m_fArcadeTimer >= 1.0f))
																				   {
																					   m_nCursor--;
																					   m_fArcadeTimer = 0.0f;
																				   }

																				   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || (pInput->GetLeftJoystick(0).y == 1 && m_fArcadeTimer >= 1.0f))
																				   {
																					   m_nCursor++;
																					   m_fArcadeTimer = 0.0f;
																				   }

																				   if (m_nCursor < 0)
																					   m_nCursor = 0;
																				   if (m_nCursor > 1)
																					   m_nCursor = 1;
																			   }
																			   else
																			   {
																				   SetAction("No Spells Active!");
																			   }

																			   //First Selection >> Action
																			   if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
																			   {
																				   if (m_nCursor == 0)
																				   {
																					   ActionSelected = ActionType::Melee;
																					   selected = true;
																					   m_nCursor = 0;
																				   }
																				   if (m_nCursor == 1)
																				   {
																					   ActionSelected = ActionType::Magic;
																					   selected = true;
																					   m_nCursor = 0;
																				   }
																				   m_fArcadeTimer = 0.0f;
																			   }
																		   }
																		   else //Action selected, now pick target
																		   {
																			   if (ActionSelected == ActionType::Magic)
																			   {
																				   pCombat->SetAction("Choose Spell"); //Giving spells and cooldowns to companions / Minions don't need cooldowns

																				   //Spell set up and selection
																				   if (spellSelect == -1)
																				   {
																					   if (m_nCursor < 0)
																						   m_nCursor = 0;
																					   if (m_nCursor > 1)
																						   m_nCursor = 1;

																					   if (m_nCursor == 0)
																						   CompanionSelection = { Spell1Rect.left - 50, Spell1Rect.top, Spell1Rect.right - 50, Spell1Rect.bottom };
																					   else if (m_nCursor == 1)
																						   CompanionSelection = { Spell2Rect.left - 50, Spell2Rect.top, Spell2Rect.right - 50, Spell2Rect.bottom };

																					   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::A) || (pInput->GetLeftJoystick(0).x == -1 && m_fArcadeTimer >= 1.0f))
																					   {
																						   m_nCursor--;
																						   m_fArcadeTimer = 0.0f;
																					   }
																					   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::D) || (pInput->GetLeftJoystick(0).x == 1 && m_fArcadeTimer >= 1.0f))
																					   {
																						   m_nCursor++;
																						   m_fArcadeTimer = 0.0f;
																					   }


																					   if (m_nCursor < 0)
																						   m_nCursor = 0;
																					   if (m_nCursor > 1)
																						   m_nCursor = 1;

																					   if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
																					   {
																						   if (m_nCursor == 0)
																						   {
																							   if (((Companion*)_this)->GetSpell1Cool() == 0)
																							   {
																								   spellSelect = m_nCursor;
																								   m_nCursor = 0;
																							   }
																						   }
																						   else if (m_nCursor == 1)
																						   {
																							   if (((Companion*)_this)->GetSpell2Cool() == 0)
																							   {
																								   spellSelect = m_nCursor;
																								   m_nCursor = 0;
																							   }
																						   }

																						   m_fArcadeTimer = 0.0f;
																					   }
																				   }
																				   else
																				   {
																					   pCombat->SetAction("Choose Target"); //Giving spells and cooldowns to companions / Minions don't need cooldowns
																					   int prevCursor = m_nCursor;

																					   CompanionSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 120, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y - 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 80, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y };
																					   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || (pInput->GetLeftJoystick(0).y == -1 && m_fArcadeTimer >= 1.0f))
																					   {
																						   m_nCursor--;
																						   m_fArcadeTimer = 0.0f;
																					   }
																					   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || (pInput->GetLeftJoystick(0).y == 1 && m_fArcadeTimer >= 1.0f))
																					   {
																						   m_nCursor++;
																						   m_fArcadeTimer = 0.0f;
																					   }

																					   if (m_nCursor < 0)
																						   m_nCursor = m_pEnemies.size() - 1;
																					   if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																						   m_nCursor = 0;

																					   if (((Minion*)m_pEnemies[m_nCursor])->GetHealth() <= 0)
																						   m_nCursor++;

																					   if (m_nCursor < 0)
																						   m_nCursor = m_pEnemies.size() - 1;
																					   if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																						   m_nCursor = 0;

																					   //Third Selection >> Target
																					   if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
																					   {
																						   if (spellSelect == 0)
																						   {
																							   if (((Companion*)_this)->GetSpell1Cool() == 0)
																							   {
																								   selected = false;
																								   ((Companion*)_this)->SetAttacking(true);
																								   TakeAction(ActionSelected, _this, m_nCursor, spellSelect);
																								   spellSelect = -1;
																								   m_nCursor = 0;
																								   return true;
																							   }
																						   }
																						   else if (spellSelect == 1)
																						   {
																							   if (((Companion*)_this)->GetSpell2Cool() == 0)
																							   {
																								   selected = false;
																								   ((Companion*)_this)->SetAttacking(true);
																								   TakeAction(ActionSelected, _this, m_nCursor, spellSelect);
																								   spellSelect = -1;
																								   m_nCursor = 0;
																								   return true;
																							   }
																						   }

																						   m_fArcadeTimer = 0.0;
																					   }
																				   }
																			   }
																			   else  // Melee
																			   {
																				   pCombat->SetAction("Choose Target");
																				   int prevCursor = m_nCursor;

																				   CompanionSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 120, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y - 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 80, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y };
																				   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || (pInput->GetLeftJoystick(0).y == -1 && m_fArcadeTimer >= 1.0))
																				   {
																					   m_nCursor--;
																					   m_fArcadeTimer = 0.0f;
																				   }
																				   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || (pInput->GetLeftJoystick(0).y == 1 && m_fArcadeTimer >= 1.0))
																				   {
																					   m_nCursor++;
																					   m_fArcadeTimer = 0.0f;
																				   }

																				   if (m_nCursor < 0)
																					   m_nCursor = m_pEnemies.size() - 1;
																				   if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																					   m_nCursor = 0;

																				   if (((Minion*)m_pEnemies[m_nCursor])->GetHealth() <= 0)
																					   m_nCursor++;

																				   if (m_nCursor < 0)
																					   m_nCursor = m_pEnemies.size() - 1;
																				   if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																					   m_nCursor = 0;

																				   //Second Selection >> Target
																				   if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
																				   {
																					   selected = false;
																					   ((Companion*)_this)->SetAttacking(true);

																					   TakeAction(ActionSelected, _this, m_nCursor);
																					   m_nCursor = 0;
																					   return true;
																				   }
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
																		   if (selected == false) //Pick an action (melee magic or armor)
																		   {
																			   pCombat->SetAction("Choose Action");

																			   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || (pInput->GetLeftJoystick(0).y == -1 && m_fArcadeTimer >= 1.0f))
																			   {
																				   m_nCursor--;
																				   m_fArcadeTimer = 0.0f;
																			   }

																			   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || (pInput->GetLeftJoystick(0).y == 1 && m_fArcadeTimer >= 1.0f))
																			   {
																				   m_nCursor++;
																				   m_fArcadeTimer = 0.0f;
																			   }


																			   if (m_nCursor < 0)
																				   m_nCursor = 0;
																			   if (m_nCursor > 1)
																				   m_nCursor = 1;

																			   //First Selection >> Action
																			   if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
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
																					   ActionSelected = 2;
																					   selected = true;
																					   m_nCursor = 0;
																				   }
																				   m_fArcadeTimer = 0.0f;
																			   }

																		   }
																		   else //Action selected, now pick target
																		   {
																			   if (ActionSelected == ActionType::Block)
																			   {
																				   selected = false;
																				   TakeAction(ActionSelected, _this, m_nCursor);
																				   m_nCursor = 0;
																				   return true;
																			   }

																			   pCombat->SetAction("Choose Target");
																			   int prevCursor = m_nCursor;

																			   CompanionSelection = { ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 120, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y - 40, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().x - 80, ((Minion*)pCombat->GetEnemies()[m_nCursor])->GetPosition().y };

																			   if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || (pInput->GetLeftJoystick(0).y == -1 && m_fArcadeTimer >= 1.0f))
																			   {
																				   m_nCursor--;
																				   m_fArcadeTimer = 0.0f;
																			   }
																			   if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || (pInput->GetLeftJoystick(0).y == 1 && m_fArcadeTimer >= 1.0f))
																			   {
																				   m_nCursor++;
																				   m_fArcadeTimer = 0.0f;
																			   }


																			   if (m_nCursor < 0)
																				   m_nCursor = m_pEnemies.size() - 1;
																			   if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																				   m_nCursor = 0;

																			   if (((Minion*)m_pEnemies[m_nCursor])->GetHealth() <= 0)
																				   m_nCursor++;

																			   if (m_nCursor < 0)
																				   m_nCursor = m_pEnemies.size() - 1;
																			   if (m_nCursor >(int)pCombat->GetEnemies().size() - 1)
																				   m_nCursor = 0;

																			   //Second Selection >> Target
																			   if (pInput->IsKeyPressed(SGD::Key::Enter) || pInput->IsButtonPressed(0, 0))
																			   {
																				   selected = false;
																				   ((Companion*)_this)->SetAttacking(true);

																				   TakeAction(ActionSelected, _this, m_nCursor);
																				   m_nCursor = 0;
																				   m_fArcadeTimer = 0.0f;
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
									}
									break;
								case Minion::AI_Type::Off_AI:
									if (((Minion*)_this)->GetHealth() > 0)
									{
										for (size_t i = 1; i < m_pHeroes.size(); i++)
										{
											if (((Companion*)m_pHeroes[i])->GetHealth() >((Player*)m_pHeroes[0])->GetHealth())
												target = i;
											else
												target = 0;
										}
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::Melee, _this, target);
									}
									break;
								case Minion::AI_Type::Def_AI:
									if (((Minion*)_this)->GetHealth() > 0)
									{
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::Melee, _this, target);
									}
									break;
								case Minion::AI_Type::Heal_AI:
									if (((Minion*)_this)->GetHealth() > 0)
									{
										pCombat->SetActionTimer(1);
										TakeAction(CombatState::ActionType::Melee, _this, target);
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
									}
									((Minion*)_this)->SetAnimation(true);
									((Minion*)_this)->ResetAnimation();
									break;
								case Minion::AI_Type::Mini_Boss:
									switch (((Minion*)_this)->GetAffinity())
									{
									case Elements::Earth:
										if (((Minion*)_this)->GetHealth() > 0) // AOE ground slam, inherit to Boss
										{
											pCombat->SetActionTimer(1);
											target = rand() % pCombat->GetHeroes().size(); //Can target dead people, need to fix
											if (target > 0)
											{
												if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
													target = 0;
											}
											int AI = rand() % 20;
											if (AI <= 15 && AI > 9) //AOE attack
												TakeAction(CombatState::ActionType::AOE, _this, target);
											else if (AI > 0 && AI <= 9)
												TakeAction(CombatState::ActionType::Magic, _this, target);
											else
												TakeAction(CombatState::ActionType::Melee, _this, target);

											((Minion*)_this)->SetAnimation(true);
											((Minion*)_this)->ResetAnimation();
										}
										break;
									case Elements::Water:
										if (((Minion*)_this)->GetHealth() > 0) //Repel (Sets target's initiative to 0)
										{
											target = rand() % pCombat->GetHeroes().size();
											if (target > 0)
											{
												if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
													target = 0;
											}
											pCombat->SetActionTimer(1);
											int AI = rand() % 20;
											if (AI > 0 && AI <= 10)
												TakeAction(CombatState::ActionType::Magic, _this, target);
											else
												TakeAction(CombatState::ActionType::Melee, _this, target);
											((Minion*)_this)->SetAnimation(true);
											((Minion*)_this)->ResetAnimation();
										}
										break;
									case Elements::Air:
										if (((Minion*)_this)->GetHealth() > 0) //Dodge, inherit to boss
										{
											target = rand() % pCombat->GetHeroes().size();
											if (target > 0)
											{
												if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
													target = 0;
											}
											pCombat->SetActionTimer(1);

											int AI = rand() % 20;
											if (AI > 0 && AI <= 10)
												TakeAction(CombatState::ActionType::Magic, _this, target);
											else
												TakeAction(CombatState::ActionType::Melee, _this, target);
											((Minion*)_this)->SetAnimation(true);
											((Minion*)_this)->ResetAnimation();
										}
										break;
									case Elements::Fire: //FireBall, inherits to boss
										if (((Minion*)_this)->GetHealth() > 0)
										{
											target = rand() % pCombat->GetHeroes().size();
											if (target > 0)
											{
												if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
													target = 0;
											}
											pCombat->SetActionTimer(1);
											int AI = rand() % 20;
											if (AI > 0 && AI <= 10)
												TakeAction(CombatState::ActionType::Magic, _this, target, 0); //FireBall
											else
												TakeAction(CombatState::ActionType::Melee, _this, target);
											((Minion*)_this)->SetAnimation(true);
											((Minion*)_this)->ResetAnimation();
										}
										break;
									default:
										if (((Minion*)_this)->GetHealth() > 0) //There really shouldn't be a default
										{
											target = rand() % pCombat->GetHeroes().size();
											if (target > 0)
											{
												if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
													target = 0;
											}
											pCombat->SetActionTimer(1);
											TakeAction(CombatState::ActionType::Melee, _this, target); //No spells for dirty defaults
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
										if (((Minion*)_this)->GetHealth() > 0) //Rock Throw
										{
											target = rand() % (pCombat->GetHeroes().size());
											if (target > 0)
											{
												if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
													target = 0;
											}
											int AI = rand() % 20;
											if (AI <= 15 && AI > 9) //AOE attack
												TakeAction(CombatState::ActionType::AOE, _this, target);
											else if (AI > 0 && AI <= 9)
												TakeAction(CombatState::ActionType::Magic, _this, target);
											else
												TakeAction(CombatState::ActionType::Melee, _this, target);
										}
										break;
									case Elements::Water:
										if (((Minion*)_this)->GetHealth() > 0) //Water Blast
										{
											target = rand() % pCombat->GetHeroes().size();
											if (target > 0)
											{
												if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
													target = 0;
											}
											pCombat->SetActionTimer(1);
											int AI = rand() % 20;
											if (AI > 0 && AI <= 9)
												TakeAction(CombatState::ActionType::Magic, _this, target);
											else
												TakeAction(CombatState::ActionType::Melee, _this, target);
										}
										break;
									case Elements::Air:
										if (((Minion*)_this)->GetHealth() > 0)
										{
											target = rand() % pCombat->GetHeroes().size();
											if (target > 0)
											{
												if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
													target = 0;
											}
											pCombat->SetActionTimer(1);
											int AI = rand() % 20;
											if (AI > 0 && AI <= 9)
												TakeAction(CombatState::ActionType::Magic, _this, target);
											else
												TakeAction(CombatState::ActionType::Melee, _this, target);
										}
										break;
									case Elements::Fire:
										if (((Minion*)_this)->GetHealth() > 0) //Fire Ball
										{
											target = rand() % pCombat->GetHeroes().size();
											if (target > 0)
											{
												if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
													target = 0;
											}
											pCombat->SetActionTimer(1);
											int AI = rand() % 20;
											if (AI > 0 && AI <= 7)
												TakeAction(CombatState::ActionType::Magic, _this, target, 0);
											else if (AI > 7 && AI < 15) //Inferno (AOE Magic)
												TakeAction(CombatState::ActionType::Magic, _this, target, 1);

											else
												TakeAction(CombatState::ActionType::Melee, _this, target);
										}
										break;
									default:
										if (((Minion*)_this)->GetHealth() > 0)
										{
											target = rand() % pCombat->GetHeroes().size();
											pCombat->SetActionTimer(1);
											TakeAction(CombatState::ActionType::Melee, _this, target);
										}
										break;

										((Minion*)_this)->SetAnimation(true);
										((Minion*)_this)->ResetAnimation();
									}
									break;

								case Minion::AI_Type::Final_Boss:

									if (((Minion*)_this)->GetHealth() > 0)
									{
										if (((Minion*)_this)->GetHealth() >= 400 && ((Minion*)_this)->GetHealth() < 500)
											((Minion*)_this)->SetAffinity(Water);
										if (((Minion*)_this)->GetHealth() >= 300 && ((Minion*)_this)->GetHealth() < 400)
											((Minion*)_this)->SetAffinity(Air);
										if (((Minion*)_this)->GetHealth() >= 100 && ((Minion*)_this)->GetHealth() < 200)
											((Minion*)_this)->SetAffinity(Fire);
										if (((Minion*)_this)->GetHealth() >= 0 && ((Minion*)_this)->GetHealth() < 100)
											((Minion*)_this)->SetAffinity(((Elements)(rand() % 4)));

										target = rand() % pCombat->GetHeroes().size();
										if (target > 0)
										{
											if (((Companion*)m_pHeroes[target])->GetHealth() <= 0)
												target = 0;
										}
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
	return false;
}

void CombatState::ShakeScreen(float elapsedTime)
{
	int randY = 0;
	int randX = 0;

	randX = rand() % 50 - 25;
	randY = rand() % 50 - 25;

	SGD::Rectangle tempShakeRect = { 0, 0, 0, 0 };

	if (m_bShake)
	{
		for (size_t i = 0; i < m_pObjects.size(); i++)
		{
			tempShakeRect = { ((float)randX / 10.0f), ((float)randY / 10.0f), ((float)randX / 10.0f), ((float)randY / 10.0f) };
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

	DrawBackground(SGD::Rectangle{ (float)(rand() % 10 - 5), (float)(rand() % 10 - 5), (float)(rand() % 10 - 5), (float)(rand() % 10 - 5) });
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
void CombatState::DrawBackground(SGD::Rectangle _shakeRect)
{
	switch (GameplayState::GetInstance()->GetCurrentLevel())
	{
	case 1:
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(Game::GetInstance()->m_hEarth1, { _shakeRect.left, _shakeRect.top }, { 0.0f, 300.0f, 800.0f, 1100.0f }, 0.0f,
		{}, { 255, 255, 255, 255 }, { 1.0f, 1.0f });
		break;
	case 2:
		SGD::GraphicsManager::GetInstance()->DrawTexture(Game::GetInstance()->m_hIce2, { _shakeRect.left, _shakeRect.top }, {}, {}, { 255, 255, 255, 255 }, { 1.0f, 1.2f });
		break;
	case 3:
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(Game::GetInstance()->m_hAir2, { _shakeRect.left, _shakeRect.top }, { 700.0f, 200.0f, 1500.0f, 800.0f }, 0.0f, {}, { 255, 255, 255, 255 }, { 1.0f, 1.0f });
		break;
	case 4:
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(Game::GetInstance()->m_hFire1, { _shakeRect.left, _shakeRect.top }, { 100.0f, 100.0f, 900.0f, 700.0f }, 0.0f, {}, { 255, 255, 255, 255 }, { 1.0f, 1.0f });
		break;
	case 5:
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(Game::GetInstance()->m_hFinal1, { _shakeRect.left, _shakeRect.top }, { 300.0f, 100.0f, 1100.0f, 700.0f }, 0.0f, {}, { 255, 255, 255, 255 }, { 1.0f, 1.0f });
		break;
	default:
		SGD::GraphicsManager::GetInstance()->DrawTextureSection(Game::GetInstance()->m_hEarth2, { _shakeRect.left, _shakeRect.top }, { 0.0f, 300.0f, 800.0f, 900.0f }, 0.0f, {}, { 255, 255, 255, 255 }, { 1.0f, 1.0f });
		break;
	}
}

void CombatState::SortTurnOrder()
{
	m_pObjects.clear();

	for (size_t i = 0; i < m_pHeroes.size(); i++)
	{
		if (((Player*)m_pHeroes[i])->GetHealth() > 0)
		{
			m_pHeroes[i]->SetTurnID(0);
			m_pHeroes[i]->SetInit(m_pHeroes[i]->GetInit() + ((rand() % (m_pHeroes[i]->GetAttckSpd()) - 3) * 2));
			m_pObjects.push_back(m_pHeroes[i]);
			//m_pHeroes[i]->AddRef();
		}
	}
	for (size_t i = 0; i < m_pEnemies.size(); i++)
	{
		if (((Minion*)m_pEnemies[i])->GetHealth() > 0)
		{
			m_pEnemies[i]->SetTurnID(0);
			m_pEnemies[i]->SetInit(m_pEnemies[i]->GetInit() + ((rand() % (m_pEnemies[i]->GetAttckSpd()) - 3) * 2));
			m_pObjects.push_back(m_pEnemies[i]);
			//m_pEnemies[i]->AddRef();
		}
	}
	for (size_t i = 1; i < m_pObjects.size(); i++)
	{
		for (size_t j = 0; j < m_pObjects.size(); j++)
		{
			if (m_pObjects[i] != nullptr && m_pObjects[j] != nullptr)
			{
				if (m_pObjects[i]->GetInit() > m_pObjects[j]->GetInit())
					swap(m_pObjects[i], m_pObjects[j]);
			}
		}
	}

	for (size_t i = 0; i < m_pObjects.size(); i++)
	{
		if (m_pObjects[i]->GetInit() < 0)
		{
			m_pObjects[i]->SetInit(10);
			m_pObjects[i]->SetTurnID(2);
			m_pObjects.pop_back();
		}
	}
	for (size_t j = 0; j < m_pObjects.size(); j++)
	{
		if (m_pObjects[j]->GetInit() > 20)
		{
			m_pObjects[j]->SetInit(10);
			m_pObjects[j]->SetTurnID(1);
			m_pObjects.push_back(m_pObjects[j]);
			break;
		}
	}
}

void CombatState::MuteCombatMusic()
{
	m_nCombatMusicVolume = SGD::AudioManager::GetInstance()->GetAudioVolume(cMusic);
	SGD::AudioManager::GetInstance()->SetAudioVolume(cMusic, 0);

}

void CombatState::UnMuteCombatMusic()
{
	SGD::AudioManager::GetInstance()->SetAudioVolume(cMusic, m_nCombatMusicVolume);

}
