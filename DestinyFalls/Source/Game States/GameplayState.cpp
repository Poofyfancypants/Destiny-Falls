#include "stdafx.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Boulder.h"
#include "../Game Objects/Enemy.h"
#include "../Game Objects/Chest.h"
#include "../Game Objects/SpikeTrap.h"
#include "../Game Objects/FireTrap.h"

#include "GameplayState.h"
#include "MainMenuState.h"
#include "InventoryState.h"
#include "MainMenuState.h"
#include "PauseMenuState.h"
#include "CombatState.h"
#include "../Messages/MessageID.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_String.h"
#include "../../SGD Wrappers/SGD_MessageManager.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_EventManager.h"


GameplayState* GameplayState::GetInstance()
{
	static GameplayState s_Instance;
	return &s_Instance;
}

void GameplayState::Enter()
{
	SGD::AudioManager*	  pAudio = SGD::AudioManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	m_pObjects = new ObjectManager;
	m_pMap = new TileManager;

	//Set up Animation Manager
	m_pAnimator = m_pAnimator->GetInstance();

	//Load Animations
	m_pAnimator->Load( "resource/XML/HeroWalkingXML.xml" );
	m_pAnimator->Load( "resource/XML/ChestXML.xml" );
	m_pAnimator->Load( "resource/XML/HeroSwordSwingXML.xml" );
	m_pAnimator->Load( "resource/XML/RockElementalAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/AirBossAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/AirElementalAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/AirMiniBossAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/BaronAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/EarthEnemyAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/EarthMiniBossAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/EarthBossAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/GreenGoblinAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/IceBossAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/IceElementalAttackXML.xml" );
	m_pAnimator->Load( "resource/XML/OrcAttackXML.xml" );
	

	m_hplayer = pGraphics->LoadTexture( L"resource/graphics/testhero.png" );
	m_henemy = pGraphics->LoadTexture( L"resource/graphics/enemy1.png" );
	m_hChest = pGraphics->LoadTexture( L"resource/graphics/chest.png" );
	m_hBoulder = pGraphics->LoadTexture( L"resource/graphics/boulder.png" );

	bmusic = pAudio->LoadAudio( L"resource/audio/backgroundMusic.wav" );

	pAudio->PlayAudio( bmusic, true );




	m_ptWorldCam = { 0, 0 };
	m_fWorldWidth = 800;
	m_fWorldHeight = 600;

	// - Manage The map
	SetNewLevel();
	//	m_particle.ReadXML( "resource/XML/Test2.xml" );

}

void GameplayState::Exit()
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager*	  pAudio = SGD::AudioManager::GetInstance();

	if( m_pPlayer != nullptr )
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}
	//audio unload

	pAudio->UnloadAudio( bmusic );

	//unload images
	pGraphics->UnloadTexture( m_hplayer );
	pGraphics->UnloadTexture( m_henemy );
	pGraphics->UnloadTexture( m_hChest );
	pGraphics->UnloadTexture( m_hBoulder );

	//m_particle.Exit();
	m_pObjects->RemoveAll();
	delete m_pObjects;
	m_pObjects = nullptr;

	delete m_pMap;
	m_pMap = nullptr;
	m_pAnimator->DeleteInstance();
}

bool GameplayState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if( pInput->IsKeyPressed( SGD::Key::F1 ) )
	{
		Game::GetInstance()->RemoveState(); //Make this Pause
		Game::GetInstance()->AddState( MainMenuState::GetInstance() );
	}

	if( pInput->IsKeyPressed( SGD::Key::Escape ) )
	{
		m_bPaused = !m_bPaused;
		Game::GetInstance()->AddState( PauseMenuState::GetInstance() );
	}

	if( pInput->IsKeyPressed( SGD::Key::E ) )
	{
		Game::GetInstance()->AddState( InventoryState::GetInstance() );
	}
	// - Toggle DebugMode with F2
	if( pInput->IsKeyPressed( SGD::Key::F2 ) )
		m_bDebug = !m_bDebug;
	if( pInput->IsKeyPressed( SGD::Key::F5 ) )
	{
		NextLevel();
		m_bChangeLevels = true;
	}
	return true;
}

void GameplayState::Update( float elapsedTime )
{
	if( m_bChangeLevels )
		SetNewLevel();
	m_fFPSTime += elapsedTime;
	m_nFrames++;
	if( m_fFPSTime >= 1.0f )
	{
		m_nFPS = m_nFrames;
		m_nFrames = 0;
		m_fFPSTime = 0.0f;
	}


	SGD::InputManager* pInput = SGD::InputManager::GetInstance();


	m_pObjects->UpdateAll( elapsedTime );
	m_pObjects->CheckCollisions( PLAYER_BUCKET, BOULDER_BUCKET );
	m_pObjects->CheckCollisions( PLAYER_BUCKET, ENEMY_BUCKET );
	m_pObjects->CheckCollisions( PLAYER_BUCKET, CHEST_BUCKET );
	m_pObjects->CheckCollisions( PLAYER_BUCKET, TRAP_BUCKET );

	m_pObjects->UpdateAll( elapsedTime );
	m_ptWorldCam = { m_pPlayer->GetPosition().x - Game::GetInstance()->GetScreenWidth() / 2.0f, m_pPlayer->GetPosition().y - Game::GetInstance()->GetScreenHeight() / 2.0f };

	m_pObjects->RenderAll();

}

void GameplayState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::Rectangle rect = { 100, 100, 150, 150 };

	m_pMap->DrawLevel( m_ptWorldCam, m_pPlayer->GetPosition() );

	m_pObjects->RenderAll();
	//m_particle.Render();

	if( m_bDebug )
	{
		SGD::OStringStream numEnt;
		numEnt << "Objects: " << GameplayState::GetInstance()->GetObjManager()->GetNumObjects();
		SGD::GraphicsManager::GetInstance()->DrawString( numEnt.str().c_str(), SGD::Point( 10, 30 ), { 0, 255, 0 } );

		SGD::OStringStream fps;
		fps << "FPS: " << m_nFPS;
		pGraphics->DrawString( fps.str().c_str(), SGD::Point( 10, 10 ), SGD::Color( 0, 255, 0 ) );
	}
}

Object* GameplayState::CreatePlayer( SGD::Point _pos )
{
	Player* temp = new Player;
	temp->SetImage( m_hplayer );
	temp->SetSize( { 16, 16 } );
	temp->SetPosition( _pos );
	temp->SetRotation( 0 );
	return temp;
}

Object* GameplayState::CreateEnemy( SGD::Point _pos )
{
	Enemy* temp = new Enemy;
	temp->SetImage( m_henemy );
	temp->SetPosition( _pos );
	temp->SetSize( SGD::Size( 32, 32 ) );
	m_pMap->NextWaypoint( temp );
	temp->SetWaypointID( 1 );
	return temp;
}

// - ID == Chest Tier
Object* GameplayState::CreateChest( SGD::Point _pos, int _id )
{
	// - Chest tier 1
	Chest* temp = new Chest;
	temp->SetImage( m_hChest );
	temp->SetSize( { 32, 32 } );

	if( _id == 1 ) // - Set the loot of Tier 1 chests
	{
		int numPots = rand() % 2;
		int numRunes = rand() % 2;
	}
	else if( _id == 2 ) // - Set the loot of Tier 2 chests
	{
		int numPots = rand() % 2;
		int numRunes = rand() % 2;
	}
	else if( _id == 3 ) // - Set the loot of Tier 3 chests
	{
		int numPots = rand() % 2;
		int numRunes = rand() % 2;
	}
	temp->SetPosition( _pos );
	return temp;
}

Object* GameplayState::CreateTrap( SGD::Point _pos, int _id )
{
	// 1 == fire trap || 2 == spike trap
	if( _id == 1 )
	{
		FireTrap* temp = new FireTrap;
		temp->SetPosition( _pos );
		temp->SetSize( SGD::Size( 32, 32 ) );
		return temp;
	}
	else if( _id == 2 )
	{
		SpikeTrap* temp = new SpikeTrap;
		temp->SetPosition( _pos );
		temp->SetSize( SGD::Size( 32, 32 ) );
		return temp;
	}
	return 0;
}

Object* GameplayState::CreateBoulder( SGD::Point _pos )
{
	Boulder* temp = new Boulder;
	temp->SetImage( m_hBoulder );
	temp->SetPosition( _pos );
	temp->SetSize( SGD::Size( 32, 32 ) );
	return temp;


}

// - Helper
void GameplayState::UnloadAndCreate()
{

	m_pObjects->RemoveAll();
	delete m_pObjects;
	m_pObjects = new ObjectManager;

	if( m_pPlayer != nullptr )
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	m_pPlayer = CreatePlayer( SGD::Point( 150, 150 ) );
	m_pObjects->AddObject( m_pPlayer, PLAYER_BUCKET );


	delete m_pMap;
	m_pMap = new TileManager;

}
void GameplayState::SetNewLevel()
{
	switch( m_nCurrentLevel )
	{
	case GameplayState::TUTORIAL_LEVEL:
		UnloadAndCreate();
		m_pMap->LoadLevel( "resource/XML/TutorialStage.xml" );
		break;
	case GameplayState::EARTH_LEVEL:
		UnloadAndCreate();
		m_pMap->LoadLevel( "resource/XML/earthLevel.xml" );
		break;
	case GameplayState::WATER_LEVEL:
		UnloadAndCreate();
		m_pMap->LoadLevel( "resource/XML/testMap1.xml" );
		break;
		//case GameplayState::AIR_LEVEL:
		//	break;
		//case GameplayState::FIRE_LEVEL:
		//	break;
		//case GameplayState::BOSS_LEVEL:
		//	break;
		//default:
		//	break;
	}


	m_bChangeLevels = false;
}
