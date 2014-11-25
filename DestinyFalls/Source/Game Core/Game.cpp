#include "stdafx.h"
#include "Game.h"

#include <ctime>
#include <cstdlib>
#include <cassert>

#include "../Game States/IGameState.h"
#include "../Game States/GameplayState.h"
#include "../Game States/MainMenuState.h"
#include "../Game States/SplashScreenState.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"

#include "../Messages/MessageID.h"
#include "../../SGD Wrappers/SGD_MessageManager.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../../SGD Wrappers/SGD_EventManager.h"

#include "../Messages/DestroyObjectMessage.h"
#include "../Bitmap Font/BitmapFont.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


/**************************************************************/
// Singleton
//	- instantiate the static member
/*static*/ Game* Game::s_pInstance = nullptr;

// GetInstance
//	- allocate the ONE instance & return it
/*static*/ Game* Game::GetInstance( void )
{
	if( s_pInstance == nullptr )
		s_pInstance = new Game;

	return s_pInstance;
}

// DeleteInstance
//	- deallocate the ONE instance
/*static*/ void Game::DeleteInstance( void )
{
	delete s_pInstance;
	s_pInstance = nullptr;
}

/**************************************************************/
// Initialize
//	- initialize the SGD wrappers
//	- enter the Main Menu state
bool Game::Initialize( float width , float height )
{
	// Seed First!
	srand( ( unsigned int ) time( nullptr ) );
	rand();

	if( SGD::AudioManager::GetInstance()->Initialize() == false
		|| SGD::GraphicsManager::GetInstance()->Initialize( false ) == false
		|| SGD::InputManager::GetInstance()->Initialize() == false )
		return false;

	SGD::MessageManager::GetInstance()->Initialize( &MessageProc );
	SGD::EventManager::GetInstance()->Initialize();

	m_fScreenWidth = width;
	m_fScreenHeight = height;

	m_pFont = new BitmapFont;
	m_pFont->Initialize( "resource/graphics/newfont_0.png" );
	m_pFont->LoadFontFile( "resource/XML/newfont.xml" );


	m_StringTable[0][1] = "Play";
	m_StringTable[0][2] = "Load Game";
	m_StringTable[0][3] = "Options";
	m_StringTable[0][4] = "How to Play";
	m_StringTable[0][5] = "Credits";
	m_StringTable[0][6] = "Exit";
	m_StringTable[0][7] = "Resume";
	m_StringTable[0][8] = "Save";
	m_StringTable[0][9] = "You Died";

	//Main menu state here
	AddState( SplashScreenState::GetInstance() );

	return true;	// success!
}

/**************************************************************/
// Update
//	- update the SGD wrappers
//	- run the current state
int Game::Update( void )
{
	unsigned long now = GetTickCount();					// current time in milliseconds
	float elapsedTime = ( now - m_ulGameTime ) / 1000.0f;	// convert to fraction of a second
	if( elapsedTime == 0.0f )
		return 0;

	m_ulGameTime = now;

	// Update the wrappers
	if( SGD::AudioManager::GetInstance()->Update() == false
		|| SGD::GraphicsManager::GetInstance()->Update() == false
		|| SGD::InputManager::GetInstance()->Update() == false )
		return -10;		// exit FAILURE!

	SGD::MessageManager::GetInstance()->Update();


	// Cap the elapsed time to 1/8th of a second
	if( elapsedTime >= 0.125f )
		elapsedTime = 0.125f;

	int pCurrent = m_nCurrState;
	// Let the current state handle input
	if( m_pStateStack[ m_nCurrState ]->Input() == false )
		return 1;	// exit success!

	// Update & render the current state if it was not changed
	if( m_nCurrState == pCurrent )
		m_pStateStack[ m_nCurrState ]->Update( elapsedTime );

	//for (int i = 0; i <= (int)m_pStateStack.size() - 1; i++)
	//	m_pStateStack[i]->Render();

	m_pStateStack[ m_nCurrState ]->Render();

	return 0;		// keep playing!
}

/**************************************************************/
// Terminate
//	- exit the current state
//	- terminate the SGD wrappers
void Game::Terminate( void )
{
	// Terminate the core SGD wrappers
	SGD::AudioManager::GetInstance()->Terminate();
	SGD::AudioManager::DeleteInstance();

	m_pFont->Terminate();
	SGD::GraphicsManager::GetInstance()->Terminate();
	SGD::GraphicsManager::DeleteInstance();

	SGD::InputManager::GetInstance()->Terminate();
	SGD::InputManager::DeleteInstance();

	SGD::MessageManager::GetInstance()->Terminate();
	SGD::MessageManager::DeleteInstance();

	SGD::EventManager::GetInstance()->Terminate();
	SGD::EventManager::DeleteInstance();

	delete m_pFont;
}

void Game::AddState( IGameState* pNewState )
{
	m_pStateStack.push_back( pNewState );
	m_nCurrState = m_pStateStack.size() - 1;
	m_pStateStack[ m_nCurrState ]->Enter();
}

void Game::RemoveState()
{
	m_pStateStack[ m_nCurrState ]->Exit();
	m_pStateStack.pop_back();
	m_nCurrState--;
}

void Game::ClearStates()
{
	for( size_t i = 0; m_pStateStack.size(); i++ )
	{
		m_pStateStack.pop_back();
		m_nCurrState--;
	}
}

/*static*/ void Game::MessageProc( const SGD::Message* pMsg )
{
	switch( pMsg->GetMessageID() )
	{
		case MessageID::MSG_DESTROY_OBJECT:
		{
			const DestroyObjectMessage* pDestroyMSG = dynamic_cast< const DestroyObjectMessage* >( pMsg );

			assert( pDestroyMSG != nullptr );
			iObject* ptr = pDestroyMSG->GetiObject();
			GameplayState::GetInstance()->GetObjManager()->RemoveObject( ptr );
		}
			break;
		default:
		{
			OutputDebugStringW( L"GameplayState::MessageProc - unknown message id\n" );
		}
			break;
	}

}