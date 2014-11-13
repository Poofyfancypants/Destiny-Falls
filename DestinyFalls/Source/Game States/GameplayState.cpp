#include "stdafx.h"
#include "../Game Core/Game.h"
#include "GameplayState.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"
#include "MainMenuState.h"
#include "InventoryState.h"
#include "../Messages/MessageID.h"
#include "../../SGD Wrappers/SGD_MessageManager.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_EventManager.h"
#include "MainMenuState.h"


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

	m_hplayer = pGraphics->LoadTexture( L"resource/graphics/testhero.png" );

	m_pPlayer = CreatePlayer();
	m_pObjects->AddObject( m_pPlayer, PLAYER_BUCKET );


	m_fWorldWidth = 800;
	m_fWorldHeight = 600;

	// - Manage The map
	m_pMap->LoadLevel( "resource/XML/Test.xml" );


	for( unsigned int i = 0; i < 3; i++ )
	{
		Object* tempEnemy = nullptr;
		tempEnemy = CreateEnemy();
		m_pObjects->AddObject( tempEnemy, ENEMY_BUCKET );
		tempEnemy->Release();
	}
}

void GameplayState::Exit()
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	if( m_pPlayer != nullptr )
	{
		m_pPlayer->Release();
		m_pPlayer = nullptr;
	}

	pGraphics->UnloadTexture( m_hBackImage );
	m_pObjects->RemoveAll();

	delete m_pObjects;
	m_pObjects = nullptr;

	delete m_pMap;
	m_pMap = nullptr;
}

bool GameplayState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if( pInput->IsKeyPressed( SGD::Key::Escape ) )
	{
		Game::GetInstance()->RemoveState(); //Make this Pause
		Game::GetInstance()->AddState( MainMenuState::GetInstance() );
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
	SGD::MessageManager::GetInstance()->Update();

	m_pObjects->CheckCollisions( PLAYER_BUCKET, ENEMY_BUCKET );



	m_pObjects->UpdateAll( elapsedTime );


	m_ptWorldCam = { m_pPlayer->GetPosition().x - Game::GetInstance()->GetScreenWidth() / 2.0f, m_pPlayer->GetPosition().y - Game::GetInstance()->GetScreenHeight() / 2.0f };

	m_pObjects->RenderAll();
}

void GameplayState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::Rectangle rect = { 100, 100, 150, 150 };

	m_pMap->DrawLevel( m_ptWorldCam, m_pPlayer->GetPosition() );

	pGraphics->DrawRectangle( rect, SGD::Color{ 255, 255, 255, 0 } );

	m_pObjects->RenderAll();
}

Object* GameplayState::CreatePlayer()
{
	Player* temp = new Player;
	temp->SetImage( m_hplayer );
	temp->SetSize( { 38, 67 } );
	temp->SetPosition( SGD::Point( 0, 0 ) );
	temp->SetRotation( 0 );
	return temp;
}

Object* GameplayState::CreateEnemy()
{
	Enemy* temp = new Enemy;
	temp->SetSize( { 64, 64 } );
	int posx = rand() % 300 + 200;
	int posy = rand() % 300 + 250;

	temp->SetPosition( SGD::Point( (float)posx, (float)posy ) );
	return temp;
}