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
bool Game::Initialize( float width, float height )
{
	// Seed First!
	srand( (unsigned int)time( nullptr ) );
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
	m_pFonts->Load( fontName, imageName, xmlFile );
	//Load the Bernardo font
	string fontName1 = "Celtic";
	string imageName1 = "resource/graphics/Fonts/Celticfont_0.png";
	string xmlFile1 = "resource/XML/Celticfont.xml";
	m_pFonts->Load( fontName1, imageName1, xmlFile1 );
	//Load the other font
	string fontName2 = "Other";
	string imageName2 = "resource/graphics/Fonts/otherfont1_0.png";
	string xmlFile2 = "resource/XML/otherfont1.xml";
	m_pFonts->Load( fontName2, imageName2, xmlFile2 );


	m_mMusic = pAudio->LoadAudio( L"resource/audio/MenuMusic.wav" );
	m_mButton = pAudio->LoadAudio( L"resource/audio/MenuButton.wav" );
	m_mMeleeButton = pAudio->LoadAudio( L"resource/audio/Melee.wav" );
	m_mMagicButton = pAudio->LoadAudio( L"resource/audio/Magic.wav" );
	potionSound = pAudio->LoadAudio( L"resource/audio/healthPotion.wav" );
	deathSound = pAudio->LoadAudio( L"resource/audio/deathSound.wav" );
	m_mChime1 = pAudio->LoadAudio( L"resource/audio/chime-1.wav" );
	m_mChime2 = pAudio->LoadAudio( L"resource/audio/chime-2.wav" );
	m_mChime3 = pAudio->LoadAudio( L"resource/audio/chime-3.wav" );
	m_mChime4 = pAudio->LoadAudio( L"resource/audio/chime-4.wav" );
	m_mChime5 = pAudio->LoadAudio( L"resource/audio/chime-5.wav" );
	m_mChime6 = pAudio->LoadAudio( L"resource/audio/chime-6.wav" );
	m_mChime7 = pAudio->LoadAudio( L"resource/audio/chime-7.wav" );
	m_mChime8 = pAudio->LoadAudio( L"resource/audio/chime-8.wav" );
	m_mChime9 = pAudio->LoadAudio( L"resource/audio/chime-9.wav" );
	m_mChime10 = pAudio->LoadAudio( L"resource/audio/chime-10.wav" );
	m_mChime11 = pAudio->LoadAudio( L"resource/audio/chime-11.wav" );
	m_mChime12 = pAudio->LoadAudio( L"resource/audio/chime-12.wav" );
	m_mBoo = pAudio->LoadAudio( L"resource/audio/Boo.wav" );
	m_mCheer = pAudio->LoadAudio( L"resource/audio/Cheer.wav" );


	pAudio->PlayAudio( m_mMusic, true );

	m_StringTable[0][1] = "Play";
	m_StringTable[0][2] = "Load Game";
	m_StringTable[0][3] = "Options";
	m_StringTable[0][4] = "How to Play";
	m_StringTable[0][5] = "Credits";
	m_StringTable[0][6] = "Exit";
	m_StringTable[0][7] = "Resume";
	m_StringTable[0][8] = "Save";
	m_StringTable[0][9] = "You Died";

	//Earth
	m_StringTable[1][1] = "Minion";
	m_StringTable[1][2] = "Behemoth";
	m_StringTable[1][3] = "Rock Elemental";
	m_StringTable[1][4] = "Green Sage";
	m_StringTable[1][5] = "Heavy Golem";

	//Water
	m_StringTable[2][1] = "Minion";
	m_StringTable[2][2] = "Behemoth";
	m_StringTable[2][3] = "Water Elemental";
	m_StringTable[2][4] = "Blue Sage";
	m_StringTable[2][5] = "Heavy Golem";

	//Air
	m_StringTable[3][1] = "Minion";
	m_StringTable[3][2] = "Behemoth";
	m_StringTable[3][3] = "Air Elemental";
	m_StringTable[3][4] = "White Sage";
	m_StringTable[3][5] = "Heavy Golem";

	//Fire
	m_StringTable[4][1] = "Minion";
	m_StringTable[4][2] = "Behemoth";
	m_StringTable[4][3] = "Fire Elemental";
	m_StringTable[4][4] = "Fire Sage";
	m_StringTable[4][5] = "Fire Baron";

	// - Tutorial Strings
	m_StringTable[7][1] = "Finally, you are here! Sigmund has been sighted to the North-East of here.";
	m_StringTable[7][2] = "This might be our only chance to stop him!";
	m_StringTable[7][3] = "Careful though, he has laid puzzles to slow us down. ";
	m_StringTable[7][4] = "Solve them by sliding between walls! I'll see you on the other side.";
	m_StringTable[7][5] = "These Boulders can be useful to solve puzzles! Press R to throw them around!";
	m_StringTable[7][6] = "Thouse are dangerous traps that you should do your best to avoid!";
	m_StringTable[7][7] = "And remember the fountain will help you recover from defeat.";
	m_StringTable[7][8] = "Watch out! Another Trap. Try not to step on it. Also..";
	m_StringTable[7][9] = "This puzzle has two different exits, You could find a Chest!";

	m_StringTable[8][1] = "See you found a chest! Press Q to open it! Did you find a rune?";
	m_StringTable[8][2] = "Runes you can equip through your Inventory by pressing E";
	m_StringTable[8][3] = "Look, There he is! Get behind me!";
	m_StringTable[8][4] = "If you are low on health already, chests can drop health potions,";
	m_StringTable[8][5] = "that will restore your health once aquiered by pressing P";
	m_StringTable[8][6] = "Press E to Continue";



	m_hMainMenu = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/MenuBackgrounds/main.png" );
	MainMenuState::GetInstance()->m_hBackground = m_hMainMenu;

	m_hEarth1 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Forest1.png" );
	m_hEarth2 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Forest2.png" );
	m_hEarth3 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Forest3.png" );
	m_hEarth4 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Forest4.png" );
	m_hIce1 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Ice1.png" );
	m_hIce2 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Ice2.png" );
	m_hIce3 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Ice3.png" );
	m_hIce4 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Ice4.png" );
	m_hIce5 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Ice5.png" );
	m_hIce6 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Ice6.png" );
	m_hAir1 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Air1.png" );
	m_hAir2 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Air2.png" );
	m_hAir3 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Air3.png" );
	m_hAir4 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Air4.png" );
	m_hFire1 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Fire1.png" );
	m_hFire2 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Fire2.png" );
	m_hFire3 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Fire3.png" );
	m_hFire4 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Fire4.png" );
	m_hFinal1 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Final1.png" );
	m_hFinal2 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Final2.png" );
	m_hFinal3 = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/CombatBackgrounds/Final3.png" );

	CombatState::GetInstance()->AddBackgroundsEarth( m_hEarth1 );
	CombatState::GetInstance()->AddBackgroundsEarth( m_hEarth2 );
	CombatState::GetInstance()->AddBackgroundsEarth( m_hEarth3 );
	CombatState::GetInstance()->AddBackgroundsEarth( m_hEarth4 );

	CombatState::GetInstance()->AddBackgroundsIce( m_hIce1 );
	CombatState::GetInstance()->AddBackgroundsIce( m_hIce2 );
	CombatState::GetInstance()->AddBackgroundsIce( m_hIce3 );
	CombatState::GetInstance()->AddBackgroundsIce( m_hIce4 );
	CombatState::GetInstance()->AddBackgroundsIce( m_hIce4 );
	CombatState::GetInstance()->AddBackgroundsIce( m_hIce5 );
	CombatState::GetInstance()->AddBackgroundsIce( m_hIce6 );

	CombatState::GetInstance()->AddBackgroundsAir( m_hAir1 );
	CombatState::GetInstance()->AddBackgroundsAir( m_hAir2 );
	CombatState::GetInstance()->AddBackgroundsAir( m_hAir3 );
	CombatState::GetInstance()->AddBackgroundsAir( m_hAir4 );

	CombatState::GetInstance()->AddBackgroundsFire( m_hFire1 );
	CombatState::GetInstance()->AddBackgroundsFire( m_hFire2 );
	CombatState::GetInstance()->AddBackgroundsFire( m_hFire3 );
	CombatState::GetInstance()->AddBackgroundsFire( m_hFire4 );

	CombatState::GetInstance()->AddBackgroundsFinal( m_hFinal1 );
	CombatState::GetInstance()->AddBackgroundsFinal( m_hFinal2 );
	CombatState::GetInstance()->AddBackgroundsFinal( m_hFinal3 );




	//Main menu state here
	AddState( SplashScreenState::GetInstance() );

	//Set up Animation Manager
	m_pAnimator = m_pAnimator->GetInstance();


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
	//if( elapsedTime == 0.0f )
	//	return 0;

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

	m_fFPSTime += elapsedTime;
	m_nFrames++;
	if( m_fFPSTime >= 1.0f )
	{
		m_nFPS = m_nFrames;
		m_nFrames = 0;
		m_fFPSTime = 0.0f;
	}

	int pCurrent = m_nCurrState;
	// Let the current state handle input
	if( m_pStateStack[m_nCurrState]->Input() == false )
		return 1;	// exit success!

	// Update & render the current state if it was not changed
	if( m_nCurrState == pCurrent )
		m_pStateStack[m_nCurrState]->Update( elapsedTime );

	//for (int i = 0; i <= (int)m_pStateStack.size() - 1; i++)
	//	m_pStateStack[i]->Render();

	m_pStateStack[m_nCurrState]->Render();

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

	pGraphics->UnloadTexture( m_hEarth1 );
	pGraphics->UnloadTexture( m_hEarth2 );
	pGraphics->UnloadTexture( m_hEarth3 );
	pGraphics->UnloadTexture( m_hEarth4 );
	pGraphics->UnloadTexture( m_hIce1 );
	pGraphics->UnloadTexture( m_hIce2 );
	pGraphics->UnloadTexture( m_hIce3 );
	pGraphics->UnloadTexture( m_hIce4 );
	pGraphics->UnloadTexture( m_hIce5 );
	pGraphics->UnloadTexture( m_hIce6 );
	pGraphics->UnloadTexture( m_hAir1 );
	pGraphics->UnloadTexture( m_hAir2 );
	pGraphics->UnloadTexture( m_hAir3 );
	pGraphics->UnloadTexture( m_hAir4 );
	pGraphics->UnloadTexture( m_hFire1 );
	pGraphics->UnloadTexture( m_hFire2 );
	pGraphics->UnloadTexture( m_hFire3 );
	pGraphics->UnloadTexture( m_hFire4 );
	pGraphics->UnloadTexture( m_hFinal1 );
	pGraphics->UnloadTexture( m_hFinal2 );
	pGraphics->UnloadTexture( m_hFinal3 );

	pGraphics->UnloadTexture( m_hMainMenu );

	pAudio->UnloadAudio( m_mMusic );
	pAudio->UnloadAudio( m_mButton );
	pAudio->UnloadAudio( m_mMagicButton );
	pAudio->UnloadAudio( m_mMeleeButton );
	pAudio->UnloadAudio( potionSound );
	pAudio->UnloadAudio( deathSound );
	pAudio->UnloadAudio( m_mChime1 );
	pAudio->UnloadAudio( m_mChime2 );
	pAudio->UnloadAudio( m_mChime3 );
	pAudio->UnloadAudio( m_mChime4 );
	pAudio->UnloadAudio( m_mChime5 );
	pAudio->UnloadAudio( m_mChime6 );
	pAudio->UnloadAudio( m_mChime7 );
	pAudio->UnloadAudio( m_mChime8 );
	pAudio->UnloadAudio( m_mChime9 );
	pAudio->UnloadAudio( m_mChime10 );
	pAudio->UnloadAudio( m_mChime11 );
	pAudio->UnloadAudio( m_mChime12 );
	pAudio->UnloadAudio( m_mBoo );
	pAudio->UnloadAudio( m_mCheer );


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
	m_pAnimator->DeleteInstance();


}

void Game::AddState( IGameState* pNewState )
{
	m_pStateStack.push_back( pNewState );
	m_nCurrState = m_pStateStack.size() - 1;
	m_pStateStack[m_nCurrState]->Enter();
}

void Game::RemoveState()
{
	m_pStateStack[m_nCurrState]->Exit();
	m_pStateStack.pop_back();
	m_nCurrState--;
}

void Game::ClearStates()
{
	//unsigned int stackSize = m_pStateStack.size() - 1;
	//for( unsigned int i = 0; i < stackSize; i++ )
	//{
	//	RemoveState();
	//	m_nCurrState--;
	//}

	for( size_t i = 0; i < m_pStateStack.size(); i++ )
	{
		m_pStateStack.back()->Exit();
		m_pStateStack.pop_back();
	}

	AddState( MainMenuState::GetInstance() );
}

/*static*/ void Game::MessageProc( const SGD::Message* pMsg )
{
	switch( pMsg->GetMessageID() )
	{
	case MessageID::MSG_DESTROY_OBJECT:
	{
										  const DestroyObjectMessage* pDestroyMSG = dynamic_cast<const DestroyObjectMessage*>( pMsg );

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