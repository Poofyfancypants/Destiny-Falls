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

void CombatState::Enter( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	CurrentTurn = 0;
	TurnIndex = 0;

	numPots = rand() % 3;
	numRunes = rand() % 2;

	Player* player = ( Player* ) GameplayState::GetInstance()->GetPlayer();
	player->CurrentTurn( &CurrentTurn );
	player->SetInit( rand() % 10 + 10 );

	player->AddRef();
	m_pObjects.push_back( player );
	m_pHeroes.push_back( player );

	m_hplayer = pGraphics->LoadTexture( "resource/graphics/ShadowKnight.png" );
	cMusic = SGD::AudioManager::GetInstance()->LoadAudio( "resource/audio/combatMusic.wav" );

	//play combat music
	SGD::AudioManager::GetInstance()->PlayAudio( cMusic , true );

	for( unsigned int i = 0; i < rand() % 3 + 1; i++ )
	{
		Object* temp;
		switch( GameplayState::GetInstance()->GetCurrentLevel() )
		{
			case 1:
				temp = AddMinion( 0 );
				break;
			case 2:
				temp = AddMinion( 1 );
				break;
			case 3:
				temp = AddMinion( 2 );
				break;
			case 4:
				temp = AddMinion( 3 );
				break;
			default:
				temp = AddMinion( rand() % 4 );

				break;
		}
		m_pObjects.push_back( temp );
		m_pEnemies.push_back( temp );
	}

	//Add 2 companions
	for( unsigned int i = 0; i < 2; i++ )
	{
		Object* temp = AddCompanion();
		( ( Companion* ) temp )->SetPosIndex( i );
		m_pObjects.push_back( temp );
		m_pHeroes.push_back( temp );
	}

	for( size_t i = 1; i < m_pObjects.size(); i++ )
	{
		for( size_t j = 0; j < m_pObjects.size(); j++ )
		{
			if( m_pObjects[ i ] != nullptr && m_pObjects[ j ] != nullptr )
			{
				if( m_pObjects[ i ]->GetInit() > m_pObjects[ j ]->GetInit() )
				{
					swap( m_pObjects[ i ] , m_pObjects[ j ] );
				}
			}
		}
	}

	for( size_t i = 0; i < m_pObjects.size(); i++ )
	{
		m_pObjects[ i ]->SetTurnPos( i );
	}

	PlayerHB.right = PlayerHB.left + ( ( Player* ) m_pObjects[ 0 ] )->GetHealth();
	SetActionTimer( 2 );
	SetAction( "Combat Ensues!" );

	m_CombatPos1.x = ( Game::GetInstance()->GetScreenWidth() / 2 - 35 );
	m_CombatPos1.y = ( Game::GetInstance()->GetScreenHeight() / 2 );

	m_CombatPos2.x = ( Game::GetInstance()->GetScreenWidth() / 2 + 35 );
	m_CombatPos2.y = ( Game::GetInstance()->GetScreenHeight() / 2 ); 

	( ( Player* ) m_pHeroes[ 0 ] )->StartCombat();
}

void CombatState::Exit( void )
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	( ( Player* ) m_pHeroes[ 0 ] )->StopCombat();
	for( size_t i = 0; i < m_pObjects.size(); i++ )
		m_pObjects[ i ]->Release();

	m_pObjects.clear();
	m_pEnemies.clear();
	m_pHeroes.clear();

	pGraphics->UnloadTexture( m_hplayer );

	pAudio->UnloadAudio( cMusic );

}

bool CombatState::Input( void )
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();


	if( pInput->IsKeyPressed( SGD::Key::Escape ) )
	{
		( ( Player* ) GameplayState::GetInstance()->GetPlayer() )->SetCombat( false );
		pAudio->PlayAudio( GameplayState::GetInstance()->bmusic , true );
		Game::GetInstance()->RemoveState();
	}

	return true;
}

void CombatState::Update( float elapsedTime )
{

	ActionTimer -= elapsedTime;
	if( ActionTimer <= 0.0f )
		ActionTimer = 0.0f;

	m_fFlash += elapsedTime;

	if( ( ( Player* ) m_pHeroes[ 0 ] )->GetHealth() > 0 )
	{
		PlayerHB.right = PlayerHB.left + ( ( Player* ) m_pHeroes[ 0 ] )->GetHealth();
		( ( Player* ) m_pHeroes[ 0 ] )->Update( elapsedTime );

		for( unsigned int i = 1; i < m_pHeroes.size(); i++ )
		{
			if( ( ( Companion* ) m_pHeroes[ i ] )->GetHealth() )
			{
				( ( Companion* ) m_pHeroes[ i ] )->Update( elapsedTime );

			}
		}
		if( ( ( Player* ) m_pHeroes[ 0 ] )->GetHealth() < 25 && m_fFlash > 2 )
		{
			m_bHealthWarning = true;
			m_fFlash = 0;
		}
		else
			m_bHealthWarning = false;

	}
	else
	{
		( ( Player* ) m_pHeroes[ 0 ] )->SetCombat( false );
		Game::GetInstance()->RemoveState();
		return;
	}

	if( ActionTimer <= 0.0f )
	{
		if( Attacker1 != -1 ) //System on hold
		{
			m_pHeroes[ Attacker1 ]->SetAttacking( false ); //After the time is up
		}
		if( Attacker2 != -1 )
		{

		}

		for( size_t i = 0; i < m_pEnemies.size(); i++ )
		{
			int numEnemies = 0;
			for( size_t i = 0; i < m_pEnemies.size(); i++ )
			{
				if( ( ( Minion* ) m_pEnemies[ i ] )->GetHealth() > 0 )
				{
					numEnemies++;
					( ( Minion* ) m_pEnemies[ i ] )->Update( elapsedTime );
				}
			}
			if( numEnemies <= 0 ) //Win
			{
				( ( Player* ) m_pHeroes[ 0 ] )->SetCombat( false );
				( ( Player* ) m_pHeroes[ 0 ] )->m_nPotions += numPots;

				Game::GetInstance()->RemoveState();
				return;
			}
		}


		for( size_t i = 0; i < m_pObjects.size(); i++ )
		{
			switch( m_pObjects[ i ]->GetType() )
			{
				case Object::ObjectType::OBJ_PLAYER:
					if( ( ( Player* ) m_pObjects[ i ] )->GetTurnPos() == CurrentTurn )
					{
						if( ActionTimer <= 0 )
						{
							//Attacker1 = 0; If we can make this work it might be cool
							//Not sure why I wanted it other than that
							if( ( ( Player* ) m_pObjects[ i ] )->TakeTurn( elapsedTime ) )
							{
								CurrentTurn++;
							}
						}
					}
					break;
				case Object::ObjectType::OBJ_COMPANION:
					if( ( ( Companion* ) m_pObjects[ i ] )->GetTurnPos() == CurrentTurn )
					{
						if( ActionTimer <= 0 )
							if( ( ( Companion* ) m_pObjects[ i ] )->TakeTurn(elapsedTime) )
								CurrentTurn++;
					}
					break;
				case Object::ObjectType::OBJ_MINION:
					if( ( ( Minion* ) m_pObjects[ i ] )->GetTurnPos() == CurrentTurn )
					{
						if( ActionTimer <= 0 )
							if( ( ( Minion* ) m_pObjects[ i ] )->TakeTurn() )
								CurrentTurn++;
					}
					break;
			}
		}

		if( CurrentTurn == m_pObjects.size() && ActionTimer <= 0 )
			CurrentTurn = 0;

	}
	else
	{
		if( Attacker1 != -1 )
		{
			if( m_pHeroes[ Attacker1 ]->GetAttacking() )
			{
				m_vOffset.x = ( ( m_pHeroes[ Attacker1 ]->GetPosition().x + m_CombatPos1.x ) );
				m_vOffset.y = ( ( m_pHeroes[ Attacker1 ]->GetPosition().y + m_CombatPos1.y ) );
				m_vOffset.Normalize();
				( Playerrect.Offset( m_vOffset / 3 ) );
			}
		}


		for( size_t i = 0; i < m_pEnemies.size(); i++ )
		{
			( ( Minion* ) m_pEnemies[ i ] )->Update( elapsedTime );
			( ( Minion* ) m_pEnemies[ i ] )->Render( i );

		}
	}
}

void CombatState::Render( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->DrawRectangle( AbilityRect , SGD::Color { 100 , 150 , 150 , 150 } );
	pGraphics->DrawRectangle( ActionRect , SGD::Color { 100 , 150 , 150 , 150 } );
	pGraphics->DrawString( ActionMessage.c_str() , SGD::Point { ActionRect.left + 60 , ActionRect.top + 5 } , SGD::Color( 255 , 255 , 255 , 255 ) );

	SGD::Color pHcolor;
	if( ( ( Player* ) m_pHeroes[ 0 ] )->GetHealth() > 50 )
		pHcolor = { 255 , 0 , 255 , 0 };
	else if( ( ( Player* ) m_pHeroes[ 0 ] )->GetHealth() > 20 )
		pHcolor = { 255 , 255 , 255 , 0 };
	else
		pHcolor = { 255 , 255 , 0 , 0 };

	pGraphics->DrawRectangle( Playerrect , SGD::Color { 100 , 0 , 0 , 150 } , SGD::Color { 255 , 255 , 255 , 255 } );
	/*pGraphics->DrawTexture( m_hplayer , { Playerrect.left - 20 , Playerrect.top - 10 } , { } , { } , { } , { .5 , .5 } );*/
	( ( Player* ) m_pHeroes[ 0 ] )->Render();


	if( PlayerHB.right > PlayerHB.left )
		pGraphics->DrawRectangle( PlayerHB , pHcolor );

	if( m_bHealthWarning )
	{
		pGraphics->DrawRectangle( SGD::Rectangle( 0 , 0 , Game::GetInstance()->GetScreenWidth() , Game::GetInstance()->GetScreenHeight() ) , { 100 , 255 , 0 , 0 } );
	}

	for( size_t j = 0; j < m_pEnemies.size(); j++ )
	{
		if( ( ( Minion* ) m_pEnemies[ j ] )->GetHealth() > 0 )
		{
			( ( Minion* ) m_pEnemies[ j ] )->Render( j );
		}
	}

	for( size_t j = 1; j < m_pHeroes.size(); j++ )
	{
		if( ( ( Companion* ) m_pHeroes[ j ] )->GetHealth() > 0 )
		{
			( ( Companion* ) m_pHeroes[ j ] )->CombatRender( j-1 );
		}
	}

	pGraphics->DrawRectangle( Companion1rect , SGD::Color() , SGD::Color() );
	pGraphics->DrawRectangle( Companion2rect , SGD::Color() , SGD::Color() );

}

Object* CombatState::AddMinion( int _region ) //This is gonna get big, don't care
{
	//_region = rand() % 4;
	Minion* temp = new Minion;
	temp->SetSize( { 64 , 64 } );
	temp->CurrentTurn( &CurrentTurn );
	temp->SetInit( rand() % 20 );
	temp->SetAffinity( ( Elements ) _region );

	int randAI = rand() % 5;
	int randHealth = 0;

	switch( randAI )
	{
		case 0: // Minion
			randHealth = rand() % 40 + 40;
			temp->SetMods( 6 , 3 , _region , 0 , 0 );

			switch( _region )
			{
				case 0:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Minion_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
				case 1:
					temp->SetMinionAnimation( _region , randAI );
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Minion_AI );
					break;
				case 2:
					temp->SetMinionAnimation( _region , randAI );
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Minion_AI );
					break;
				case 3:
					temp->SetMinionAnimation( _region , randAI );
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Minion_AI );
					break;
			}
			break;
		case 1: // Offensive
			randHealth = rand() % 25 + 40;

			if( randHealth > 50 )
				temp->SetMods( 6 , 5 , _region , 2 , 1 );
			else
				temp->SetMods( 6 , 5 , _region , 3 , 1 );

			switch( _region )
			{

				case 0:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Off_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
				case 1:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Off_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
				case 2:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Off_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
				case 3:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Off_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
			}
			break;
		case 2: // Defensive
			randHealth = rand() % 20 + 80;

			if( randHealth > 90 )
				temp->SetMods( 6 , 2 , _region , 1 , 3 );
			else
				temp->SetMods( 6 , 2 , _region , 2 , 3 );

			switch( _region )
			{

				case 0:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Def_AI );
					temp->SetMinionAnimation( _region , randAI );

					break;
				case 1:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Def_AI );
					temp->SetMinionAnimation( _region , randAI );


					break;
				case 2:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Def_AI );
					temp->SetMinionAnimation( _region , randAI );

					break;
				case 3:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Def_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
			}
			break;
		case 3: // Healing
			randHealth = rand() % 35 + 45;

			if( randHealth > 60 )
				temp->SetMods( 6 , 1 , _region , 1 , 2 );
			else
				temp->SetMods( 6 , 1 , _region , 1 , 3 );

			switch( _region )
			{

				case 0:

					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Heal_AI );
					temp->SetMinionAnimation( _region , randAI );

					break;
				case 1:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Heal_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
				case 2:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Heal_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
				case 3:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::Heal_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
			}
			break;
		case 4: // AOE
			randHealth = rand() % 40 + 55;

			if( randHealth > 75 )
				temp->SetMods( 6 , 4 , _region , 2 , 1 );
			else
				temp->SetMods( 6 , 4 , _region , 3 , 2 );

			switch( _region )
			{
				case 0:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::AOE_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
				case 1:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::AOE_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
				case 2:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::AOE_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
				case 3:
					temp->SetString( _region , randAI );
					temp->SetAIType( Minion::AI_Type::AOE_AI );
					temp->SetMinionAnimation( _region , randAI );
					break;
			}
			break;
		default:
			break;
	}


	temp->SetHealth( randHealth );
	return temp;
}

Object* CombatState::AddCompanion()
{
	Companion* temp = new Companion;
	Companion::Companion_Type coT = (Companion::Companion_Type)( rand() % 4 + 1 );
	switch( coT )
	{
		case 1:
			temp->SetC0Type( Companion::Companion_Type::Cleric );
			temp->SetCompanionAnimation( 1 );
			break;
		case 2:
			temp->SetC0Type( Companion::Companion_Type::Mage );
			temp->SetCompanionAnimation( 2 );

			break;
		case 3:
			temp->SetC0Type( Companion::Companion_Type::Melee );
			temp->SetCompanionAnimation( 3 );
			break;
		case 4:
			temp->SetC0Type( Companion::Companion_Type::Tank );
			temp->SetCompanionAnimation( 4 );
			break;
		default:
			break;
	}
	temp->SetSize( { 64 , 64 } );
	temp->CurrentTurn( &CurrentTurn );
	return temp;
}

bool CombatState::TakeAction( int _ActionType , Object* _this , int _target ) //Can I Add An Object* for the target
//I'm thinking about the order of actions here
//Possibly get the target or attacker's type before damage type, we'll see what's most repetative
//Companions are going to possibly cause some problems
{
	RuneManager mag;
	Game* pGame = Game::GetInstance();
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	//Game::GetInstance()->AddState(InventoryState::GetInstance());

	SetActionTimer( GetActionTimer() + 1.5f );
	switch( _this->GetType() )
	{
		case iObject::OBJ_PLAYER:
		{
			switch( _ActionType )
			{
				case CombatState::ActionType::Melee:
				{
					pAudio->PlayAudio( Game::GetInstance()->m_mMeleeButton );
					ComboElements d1 = mag.ElementCombination( InventoryState::GetInstance()->GetSwordSlot1() , InventoryState::GetInstance()->GetSwordSlot2() );

					( ( Minion* ) m_pEnemies[ _target ] )->SetHealth( ( ( Minion* ) m_pEnemies[ _target ] )->GetHealth() -
						( mag.DamageComboElement( d1 , ( ( Minion* ) m_pEnemies[ _target ] )->GetAffinity() ) * 60 ) );
					( ( Player* ) m_pHeroes[ 0 ] )->ResetAnimation();
					string message = "You Slash the ";
					message += ( pGame->GetString( ( ( Minion* ) m_pEnemies[ _target ] )->GetName( 0 ) , ( ( Minion* ) m_pEnemies[ _target ] )->GetName( 1 ) ).c_str() );
					SetAction( message );
				}
					break;
				case CombatState::ActionType::Magic:
				{
					m_bCoolDown = true;

					pAudio->PlayAudio( Game::GetInstance()->m_mMagicButton );
					ComboElements d2 = mag.ElementCombination( InventoryState::GetInstance()->GetRingSlot1() , InventoryState::GetInstance()->GetRingSlot2() );
					( ( Minion* ) m_pObjects[ _target ] )->SetHealth( ( ( Minion* ) m_pObjects[ _target ] )->GetHealth() -
						( mag.DamageComboElement( d2 , ( ( Minion* ) m_pObjects[ _target ] )->GetAffinity() ) * 10 ) );
					SetActionTimer( GetActionTimer() + 3 );
					string stuff = "You Magify the ";
					SetAction( stuff += Game::GetInstance()->GetString( 1 , ( ( Minion* ) m_pEnemies[ _target ] )->GetName() ).c_str() );
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
			switch( _ActionType )
			{
				case 0:
					break;
				default:
					break;
			}
		}
			break;
		case iObject::OBJ_MINION:
		{
			switch( ( ( Minion* ) _this )->GetAIType() )
			{
				case 0: //Minion
				{
					DealMeleeDamage( _this , m_pHeroes[ _target ] );
					string message = "The ";
					message += ( pGame->GetString( ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 0 ) , ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 1 ) ).c_str() );
					SetAction( message += " Attacks!" );
				}
					break;
				case 1: //Offensive
				{
					DealMeleeDamage( _this , m_pHeroes[ _target ] );

					string message = "The ";
					message += ( pGame->GetString( ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 0 ) , ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 1 ) ).c_str() );
					SetAction( message += " Attacks!" );
				}
					break;
				case 2: //Defensive
				{
					DealMeleeDamage( _this , m_pHeroes[ _target ] );

					string message = "The ";
					message += ( pGame->GetString( ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 0 ) , ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 1 ) ).c_str() );
					SetAction( message += " Attacks!" );
				}
					break;
				case 3: //Healing
				{
					DealMeleeDamage( _this , m_pHeroes[ _target ] );

					string message = "The ";
					message += ( pGame->GetString( ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 0 ) , ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 1 ) ).c_str() );
					SetAction( message += " Attacks!" );
				}
					break;
				case 4: //AOE
				{
					string message = "The ";
					message += ( pGame->GetString( ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 0 ) , ( ( Minion* ) m_pObjects[ CurrentTurn ] )->GetName( 1 ) ).c_str() );
					SetAction( message += " Attacks!" );

					if( _ActionType == ActionType::AOE )
					{
						if( m_pHeroes.size() == 1 ) // attack player and damage self
						{
							for( size_t i = 0; i < m_pHeroes.size(); i++ )
							{
								DealMeleeDamage( _this , m_pHeroes[ i ] );
							}
							( ( Minion* ) _this )->SetHealth( ( ( Minion* ) _this )->GetHealth() - 10 );
						}
						else if( m_pHeroes.size() > 1 )
						{
							for( size_t i = 0; i < m_pHeroes.size(); i++ )
							{
								( ( Player* ) m_pHeroes[ i ] )->SetHealth( ( ( Player* ) m_pHeroes[ _target ] )->GetHealth() - 10 );
							}
						}
					}
					else if( _ActionType == ActionType::Melee )
					{
						DealMeleeDamage( _this , m_pHeroes[ _target ] );

					}

				}
					break;
				default:
					break;
			}

		}
			break;
			//Bosses
		default:
			break;
	}
	return false;
}

int CombatState::DealMeleeDamage( Object* _From , Object* _To )
{
	int Total;
	if( _From->GetType() == iObject::OBJ_PLAYER )
	{
		( ( Player* ) _From )->ResetAnimation();
	}
	else
	{
		Total = rand() % ( 10 * ( ( Minion* ) _From )->GetMods().DamageLevel ) + ( ( Minion* ) _From )->GetMods().DamageLevel;

		( ( Player* ) _To )->SetHealth( ( ( Player* ) _To )->GetHealth() - Total );
	}
	return Total;
}
int CombatState::DealMagicDamage( Object* _From , Object* _To )
{
	int Total;

	if( _From->GetType() == iObject::OBJ_PLAYER )
	{

	}
	else
	{

	}
	return Total;
}
int CombatState::DealCounterDamage( Object* _From , Object* _To )
{
	int Total;
	if( _From->GetType() == iObject::OBJ_PLAYER )
	{

	}
	else
	{

	}
	return Total;
}
int CombatState::BlockAttack( Object* _From , Object* _To )
{
	int Total;
	if( _From->GetType() == iObject::OBJ_PLAYER )
	{

	}
	else
	{

	}
	return Total;
}
int CombatState::HealAlly( Object* _From , Object* _To )
{
	int Total;
	if( _From->GetType() == iObject::OBJ_PLAYER )
	{

	}
	else
	{

	}
	return Total;
}
int CombatState::DealAOEDamage( Object* _From , Object* _To )
{
	int Total;
	if( _From->GetType() == iObject::OBJ_PLAYER )
	{

	}
	else
	{

	}
	return Total;
}