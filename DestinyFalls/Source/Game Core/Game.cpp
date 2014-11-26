#include "stdafx.h"
#include "Game.h"

#include <ctime>
#include <cstdlib>
#include <cassert>

#include "../Messages/MessageID.h"
#include "../Game States/IGameState.h"
#include "../Game States/CombatState.h"
#include "../Game States/GameplayState.h"
#include "../Game States/MainMenuState.h"
#include "../Game States/SplashScreenState.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_MessageManager.h"
#include "../../SGD Wrappers/SGD_Message.h"
#include "../../SGD Wrappers/SGD_EventManager.h"

#include "../Messages/DestroyObjectMessage.h"

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
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();
	m_fScreenWidth = width;
	m_fScreenHeight = height;
	
	//set the font pointer to the BitmapFontManager Instance
	m_pFonts = m_pFonts->GetInstance();

	//Load the Bernardo font
	string fontName = "Bernardo";
	string imageName = "resource/graphics/Fonts/newfont_0.png";
	string xmlFile = "resource/XML/newfont.xml";
	m_pFonts->Load( fontName , imageName , xmlFile );
	//Load the Bernardo font
	string fontName1 = "Celtic";
	string imageName1 = "resource/graphics/Fonts/Celticfont_0.png";
	string xmlFile1 = "resource/XML/Celticfont.xml";
	m_pFonts->Load(fontName1, imageName1, xmlFile1);
	//Load the other font
	string fontName2 = "Other";
	string imageName2 = "resource/graphics/Fonts/otherfont1_0.png";
	string xmlFile2 = "resource/XML/otherfont1.xml";
	m_pFonts->Load(fontName2, imageName2, xmlFile2);
	

	m_mMusic = pAudio->LoadAudio(L"resource/audio/MenuMusic.wav");
	m_mButton = pAudio->LoadAudio(L"resource/audio/MenuButton.wav");
	m_mMeleeButton = pAudio->LoadAudio(L"resource/audio/Melee.wav");
	m_mMagicButton = pAudio->LoadAudio(L"resource/audio/Magic.wav");
	potionSound = pAudio->LoadAudio(L"resource/audio/healthPotion.wav");
	deathSound = pAudio->LoadAudio(L"resource/audio/deathSound.wav");

	pAudio->PlayAudio(m_mMusic, true);

	m_StringTable[0][1] = "Play";
	m_StringTable[0][2] = "Load Game";
	m_StringTable[0][3] = "Options";
	m_StringTable[0][4] = "How to Play";
	m_StringTable[0][5] = "Credits";
	m_StringTable[0][6] = "Exit";
	m_StringTable[0][7] = "Resume";
	m_StringTable[0][8] = "Save";
	m_StringTable[0][9] = "You Died";

	m_StringTable[1][1] = "Rock Elemental";
	m_StringTable[1][2] = "Plant Monster";

	m_hEarth1	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Forest1.png");
	m_hEarth2	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Forest2.png");
	m_hEarth3	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Forest3.png");
	m_hEarth4	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Forest4.png");
	m_hIce1		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Ice1.png");
	m_hIce2		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Ice2.png");
	m_hIce3		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Ice3.png");
	m_hIce4		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Ice4.png");
	m_hIce5		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Ice5.png");
	m_hIce6		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Ice6.png");
	m_hAir1		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Air1.png");
	m_hAir2		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Air2.png");
	m_hAir3		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Air3.png");
	m_hAir4		= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Air4.png");
	m_hFire1	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Fire1.png");
	m_hFire2	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Fire2.png");
	m_hFire3	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Fire3.png");
	m_hFire4	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Fire4.png");
	m_hFinal1	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Final1.png");
	m_hFinal2	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Final2.png");
	m_hFinal3	= SGD::GraphicsManager::GetInstance()->LoadTexture(L"resource/graphics/CombatBackgrounds/Final3.png");

	CombatState::GetInstance()->AddBackgroundsEarth(m_hEarth1);
	CombatState::GetInstance()->AddBackgroundsEarth(m_hEarth2);
	CombatState::GetInstance()->AddBackgroundsEarth(m_hEarth3);
	CombatState::GetInstance()->AddBackgroundsEarth(m_hEarth4);

	CombatState::GetInstance()->AddBackgroundsIce(m_hIce1);
	CombatState::GetInstance()->AddBackgroundsIce(m_hIce2);
	CombatState::GetInstance()->AddBackgroundsIce(m_hIce3);
	CombatState::GetInstance()->AddBackgroundsIce(m_hIce4);
	CombatState::GetInstance()->AddBackgroundsIce(m_hIce4);
	CombatState::GetInstance()->AddBackgroundsIce(m_hIce5);
	CombatState::GetInstance()->AddBackgroundsIce(m_hIce6);

	CombatState::GetInstance()->AddBackgroundsAir(m_hAir1);
	CombatState::GetInstance()->AddBackgroundsAir(m_hAir2);
	CombatState::GetInstance()->AddBackgroundsAir(m_hAir3);
	CombatState::GetInstance()->AddBackgroundsAir(m_hAir4);

	CombatState::GetInstance()->AddBackgroundsFire(m_hFire1);
	CombatState::GetInstance()->AddBackgroundsFire(m_hFire2);
	CombatState::GetInstance()->AddBackgroundsFire(m_hFire3);
	CombatState::GetInstance()->AddBackgroundsFire(m_hFire4);

	CombatState::GetInstance()->AddBackgroundsFinal(m_hFinal1);
	CombatState::GetInstance()->AddBackgroundsFinal(m_hFinal2);
	CombatState::GetInstance()->AddBackgroundsFinal(m_hFinal3);




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
	SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

	// Terminate the core SGD wrappers
	//MainMenuState::GetInstance()->Exit();

	CombatState::GetInstance()->ClearEarth();
	CombatState::GetInstance()->ClearIce();
	CombatState::GetInstance()->ClearAir();
	CombatState::GetInstance()->ClearFire();
	CombatState::GetInstance()->ClearFinal();

	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->UnloadTexture(m_hEarth1);
	pGraphics->UnloadTexture(m_hEarth2);
	pGraphics->UnloadTexture(m_hEarth3);
	pGraphics->UnloadTexture(m_hEarth4);
	pGraphics->UnloadTexture(m_hIce1);
	pGraphics->UnloadTexture(m_hIce2);
	pGraphics->UnloadTexture(m_hIce3);
	pGraphics->UnloadTexture(m_hIce4);
	pGraphics->UnloadTexture(m_hIce5);
	pGraphics->UnloadTexture(m_hIce6);
	pGraphics->UnloadTexture(m_hAir1);
	pGraphics->UnloadTexture(m_hAir2);
	pGraphics->UnloadTexture(m_hAir3);
	pGraphics->UnloadTexture(m_hAir4);
	pGraphics->UnloadTexture(m_hFire1);
	pGraphics->UnloadTexture(m_hFire2);
	pGraphics->UnloadTexture(m_hFire3);
	pGraphics->UnloadTexture(m_hFire4);
	pGraphics->UnloadTexture(m_hFinal1);
	pGraphics->UnloadTexture(m_hFinal2);
	pGraphics->UnloadTexture(m_hFinal3);


	pAudio->UnloadAudio(m_mMusic);
	pAudio->UnloadAudio(m_mButton);
	pAudio->UnloadAudio(m_mMagicButton);
	pAudio->UnloadAudio(m_mMeleeButton);
	pAudio->UnloadAudio(potionSound);
	pAudio->UnloadAudio(deathSound);

	SGD::AudioManager::GetInstance()->Terminate();
	SGD::AudioManager::DeleteInstance();

	m_pFonts->DeleteInstance();
	SGD::GraphicsManager::GetInstance()->Terminate();
	SGD::GraphicsManager::DeleteInstance();

	SGD::InputManager::GetInstance()->Terminate();
	SGD::InputManager::DeleteInstance();

	SGD::MessageManager::GetInstance()->Terminate();
	SGD::MessageManager::DeleteInstance();

	SGD::EventManager::GetInstance()->Terminate();
	SGD::EventManager::DeleteInstance();

	
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