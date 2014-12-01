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
#include "../Quick Time/QuickTime.h"

CombatState* CombatState::GetInstance()
{
	static CombatState s_Instance;
	return &s_Instance;
}

void CombatState::Enter( void )
{
	CurrentTurn = 0;
	TurnIndex = 0;

	Player* player = ( Player* ) GameplayState::GetInstance()->GetPlayer();
	player->SetCombat( true );
	player->CurrentTurn( &CurrentTurn );
	player->SetTurnPos( TurnIndex );
	player->AddRef();
	m_pObjects.push_back( player );
	m_pHeroes.push_back(player);
	TurnIndex++;

	m_hplayer = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/ShadowKnight.png");
	m_henemy = SGD::GraphicsManager::GetInstance()->LoadTexture("resource/graphics/Rock.png");
	cMusic = SGD::AudioManager::GetInstance()->LoadAudio("resource/audio/combatMusic.wav");

	//play combat music
	SGD::AudioManager::GetInstance()->PlayAudio(cMusic, true);

	for (unsigned int i = 0; i < rand() % 3 + 1; i++)
	{
		Object* temp = AddMinion();
		m_pObjects.push_back(temp);
		m_pEnemies.push_back(temp);
		TurnIndex++;
	}

	PlayerHB.right = PlayerHB.left + ( ( Player* ) m_pObjects[ 0 ] )->GetHealth();

}

void CombatState::Exit( void )
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	for (size_t i = 0; i < m_pObjects.size(); i++)
		m_pObjects[i]->Release();

	m_pObjects.clear();
	m_pEnemies.clear();
	m_pHeroes.clear();

	pGraphics->UnloadTexture(m_hplayer);
	pGraphics->UnloadTexture(m_henemy);
	
	pAudio->UnloadAudio(cMusic);

}

bool CombatState::Input( void )
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();


	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		((Player*)GameplayState::GetInstance()->GetPlayer())->SetCombat(false);
		pAudio->PlayAudio(GameplayState::GetInstance()->bmusic, true);
	}

	if( pInput->IsKeyPressed( SGD::Key::Escape ) )
	{
		( ( Player* ) GameplayState::GetInstance()->GetPlayer() )->SetCombat( false );
		Game::GetInstance()->RemoveState();
	}

	return true;
}

void CombatState::Update( float elapsedTime )
{

	int numEnemies = 0;
	m_fFlash += elapsedTime;

	for (size_t i = 0; i < m_pEnemies.size(); i++)
	{
		if (((Minion*)m_pEnemies[i])->GetHealth() > 0)
		{
			numEnemies++;
			((Minion*)m_pEnemies[i])->Update(elapsedTime);
		}
		else if (((Minion*)m_pEnemies[i])->GetHealth() <= 0)
		{
			//numEnemies--;
		}
	}
	if (numEnemies <= 0) //Win
	{
		((Player*)m_pObjects[0])->SetCombat(false);
		Game::GetInstance()->RemoveState();
		return;
	}

	if (((Player*)m_pObjects[0])->GetHealth() > 0)
	{
		PlayerHB.right = PlayerHB.left + ((Player*)m_pObjects[0])->GetHealth();

		if (((Player*)m_pObjects[0])->GetHealth() < 25 && m_fFlash > 2)
		{
			m_bHealthWarning = true;
			m_fFlash = 0;
		}
		else
			m_bHealthWarning = false;
		
	}
	else
	{
		((Player*)m_pObjects[0])->SetCombat(false);
		Game::GetInstance()->RemoveState();
		return;
	}

	for (size_t i = 0; i < m_pObjects.size(); i++)
	{

		switch( m_pObjects[ i ]->GetType() )
		{
			case Object::ObjectType::OBJ_PLAYER:
			{
				if( ( ( Player* ) m_pObjects[ i ] )->GetTurnPos() == CurrentTurn )
				{
					if( ( ( Player* ) m_pObjects[ i ] )->TakeTurn( elapsedTime ) )
					{
						CurrentTurn++; //Put this back in the check once player combat input is complete
					}
				}
			}
				break;
			case Object::ObjectType::OBJ_MINION:
			{
				if( ( ( Minion* ) m_pObjects[ i ] )->GetTurnPos() == CurrentTurn )
				{
					( ( Minion* ) m_pObjects[ i ] )->TakeTurn();
					CurrentTurn++;
				}
			}
				break;
		}
	}


	CurrentTurn = 0;
}

void CombatState::Render( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->DrawRectangle( AbilityRect , SGD::Color { 100 , 150 , 150 , 150 } );

	pGraphics->DrawRectangle(Playerrect, SGD::Color{ 100, 0, 0, 150 }, SGD::Color{ 255, 255, 255, 255 });
	pGraphics->DrawTexture(m_hplayer, { Playerrect.left - 20, Playerrect.top - 10 }, {}, {}, {}, { .5, .5 });
	pGraphics->DrawRectangle(PlayerHB, SGD::Color{ 255, 0, 255, 0 });
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

	for (size_t i = 1; i < m_pHeroes.size(); i++)
	{

	}
}

Object* CombatState::AddMinion()
{
	Minion* temp = new Minion;
	temp->SetCombatImage(m_henemy);
	temp->SetSize({ 64, 64 });
	temp->CurrentTurn(&CurrentTurn);
	temp->SetTurnPos(TurnIndex);
	temp->SetAffinity(Earth);
	temp->SetString(1);
	temp->SetAIType(Minion::AI_Type::Minion_AI);
	return temp;
}

bool CombatState::DealDamage(int _DamType, Object* _this, int _target)
{
	RuneManager mag;

	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	//Game::GetInstance()->AddState(InventoryState::GetInstance());


	switch (_DamType)
	{
	case CombatState::DamType::Melee:
	{
										if (m_pObjects[_target]->GetType() == iObject::OBJ_PLAYER)
										{
											((Player*)m_pObjects[_target])->SetHealth(((Player*)m_pObjects[_target])->GetHealth() - 5);
										}
										if (m_pObjects[_target]->GetType() == iObject::OBJ_MINION)
										{
											pAudio->PlayAudio(Game::GetInstance()->m_mMeleeButton);
											ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());

											((Minion*)m_pObjects[_target])->SetHealth(((Minion*)m_pObjects[_target])->GetHealth() -
												(mag.DamageComboElement(d1, ((Minion*)m_pObjects[_target])->GetAffinity()) * 10));
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
											pAudio->PlayAudio(Game::GetInstance()->m_mMagicButton);
											ComboElements d2 = mag.ElementCombination(InventoryState::GetInstance()->GetRingSlot1(), InventoryState::GetInstance()->GetRingSlot2());
											((Minion*)m_pObjects[_target])->SetHealth(((Minion*)m_pObjects[_target])->GetHealth() -
												(mag.DamageComboElement(d2, ((Minion*)m_pObjects[_target])->GetAffinity()) * 10));
										}
	}
		break;
	case CombatState::DamType::Armor:
		//Game::GetInstance()->AddState(InventoryState::GetInstance());


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

												ComboElements d1 = mag.ElementCombination(InventoryState::GetInstance()->GetSwordSlot1(), InventoryState::GetInstance()->GetSwordSlot2());

												((Minion*)m_pObjects[_target])->SetHealth(((Minion*)m_pObjects[_target])->GetHealth() -
													(mag.DamageComboElement(d1, ((Minion*)m_pObjects[_target])->GetAffinity()) * 10));
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
												ComboElements d2 = mag.ElementCombination(InventoryState::GetInstance()->GetRingSlot1(), InventoryState::GetInstance()->GetRingSlot2());

												((Minion*)m_pObjects[_target])->SetHealth(((Minion*)m_pObjects[_target])->GetHealth() -
													(mag.DamageComboElement(d2, ((Minion*)m_pObjects[_target])->GetAffinity()) * 10));
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

	}
		return false;
}