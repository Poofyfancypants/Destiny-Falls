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
	m_pAnimator = m_pAnimator->GetInstance();
	m_pAnimator->Load( "resource/XML/HeroWalkingXML.xml" );
	m_pAnimator->Load( "resource/XML/ChestXML.xml" );


	m_hplayer = pGraphics->LoadTexture( L"resource/graphics/testhero.png" );
	m_henemy = pGraphics->LoadTexture( L"resource/graphics/enemy1.png" );
	m_hChest = pGraphics->LoadTexture( L"resource/graphics/chest.jpg" );
	m_hBoulder = pGraphics->LoadTexture( L"resource/graphics/boulder.png" );

	bmusic = pAudio->LoadAudio(L"resource/audio/backgroundMusic.wav");
	
	pAudio->PlayAudio(bmusic, true);
	

	
	m_pPlayer = CreatePlayer( SGD::Point( 150, 150 ) );
	m_pObjects->AddObject( m_pPlayer, PLAYER_BUCKET );

	m_ptWorldCam = { 0, 0 };
	m_fWorldWidth = 800;
	m_fWorldHeight = 600;

	// - Manage The map
	m_pMap->LoadLevel( "resource/XML/testMap1.xml" );
	m_particle.ReadXML( "resource/XML/Test2.xml" );

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
	
	pAudio->UnloadAudio(bmusic);

	//unload images
	pGraphics->UnloadTexture(m_hplayer);
	pGraphics->UnloadTexture(m_henemy);
	pGraphics->UnloadTexture(m_hChest);
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hplayer);
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_henemy);
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hChest);

	pGraphics->UnloadTexture( m_hplayer );
	pGraphics->UnloadTexture( m_henemy );
	pGraphics->UnloadTexture( m_hChest );
	pGraphics->UnloadTexture(m_hBoulder);

	m_particle.Exit();
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


	return true;
}

void GameplayState::Update( float elapsedTime )
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();


	m_pObjects->UpdateAll( elapsedTime );
	m_pObjects->CheckCollisions( PLAYER_BUCKET, BOULDER_BUCKET );
	m_pObjects->CheckCollisions( PLAYER_BUCKET, ENEMY_BUCKET );
	m_pObjects->CheckCollisions( PLAYER_BUCKET, CHEST_BUCKET );
	m_pObjects->CheckCollisions( PLAYER_BUCKET, TRAP_BUCKET );


	m_pObjects->RenderAll();

}

void GameplayState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::Rectangle rect = { 100, 100, 150, 150 };

	m_pMap->DrawLevel( m_ptWorldCam, m_pPlayer->GetPosition() );

	m_pObjects->RenderAll();
	m_particle.Render();
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
	//int posx = rand() % 300 + 200;
	//int posy = rand() % 300 + 250;

	temp->SetPosition( _pos );
	temp->SetSize( SGD::Size( 32, 32 ) );
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
}

Object* GameplayState::CreateBoulder( SGD::Point _pos)
{
		Boulder* temp = new Boulder;
		temp->SetImage(m_hBoulder);
		temp->SetPosition( _pos );
		temp->SetSize( SGD::Size( 32, 32 ) );
		return temp;
	

}