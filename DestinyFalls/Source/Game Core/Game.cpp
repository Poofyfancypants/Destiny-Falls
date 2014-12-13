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
#include "../Game States/OptionsState.h"
#include "../Game States/SaveandLoadState.h"
#include "../Game States/HowToPlayState.h"
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
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	// - Loading Screen Loadins
	m_hLoadingBackground = pGraphics->LoadTexture( "resource/graphics/MenuBackgrounds/loadingScreenBackground.png" );
	m_hMusic = pAudio->LoadAudio( "resource/audio/MainMenuSong.xwm" );

	SGD::AudioManager::GetInstance()->PlayAudio(m_hMusic, true);

	m_pFonts = m_pFonts->GetInstance();
	string fontName2 = "Other";
	string imageName2 = "resource/graphics/Fonts/otherfont1_0.png";
	string xmlFile2 = "resource/XML/otherfont1.xml";
	m_pFonts->Load( fontName2, imageName2, xmlFile2 );


	// - Load options
	std::ifstream load;
	load.open( "resource/XML/Options.txt" );
	if( load.is_open() )
	{
		int m_nMusic, m_nEffects, m_nScreen, m_nIcelandic;
		load >> m_nMusic >> m_nEffects >> m_nScreen >> m_nIcelandic;
		pAudio->SetMasterVolume( SGD::AudioGroup::Music, m_nMusic );
		pAudio->SetMasterVolume( SGD::AudioGroup::SoundEffects, m_nEffects );

		m_bWindowed = ( m_nScreen ? true : false );
		Game::GetInstance()->SetIcelandic( ( m_nIcelandic ? true : false ) );

		load.close();
	}

	LoadingScreen( "Loading Settings." );

	m_fScreenWidth = width;
	m_fScreenHeight = height;

	SGD::GraphicsManager::GetInstance()->Resize( { m_fScreenWidth, m_fScreenHeight }, m_bWindowed );

	//set the font pointer to the BitmapFontManager Instance
	LoadingScreen( "Loading Fonts" );

	//Load the Bernardo font
	string fontName = "Bernardo";
	string imageName = "resource/graphics/Fonts/newfont_0.png";
	string xmlFile = "resource/XML/newfont.xml";
	m_pFonts->Load( fontName, imageName, xmlFile );
	//Load the Bernardo font
	//string fontName1 = "Celtic";
	//string imageName1 = "resource/graphics/Fonts/CelticMD_0.png";
	//string xmlFile1 = "resource/XML/Celticfont.xml";
	//m_pFonts->Load( fontName1, imageName1, xmlFile1 );
	//Load the other font

	//Load the dialog font
	string fontName3 = "Dialog";
	string imageName3 = "resource/graphics/Fonts/dialog.png";
	string xmlFile3 = "resource/XML/newDialog.xml";
	m_pFonts->Load( fontName3, imageName3, xmlFile3 );
	//Load the dialog font
	string fontName4 = "Goblin";
	string imageName4 = "resource/graphics/Fonts/Goblinfont_0.png";
	string xmlFile4 = "resource/XML/Goblinfont.xml";
	m_pFonts->Load( fontName4, imageName4, xmlFile4 );
	//Load the dialog font
	string fontName5 = "InventoryFont";
	string imageName5 = "resource/graphics/Fonts/InventoryFont_0.png";
	string xmlFile5 = "resource/XML/InventoryFont.xml";
	m_pFonts->Load(fontName5, imageName5, xmlFile5);

	LoadingScreen( "Loading Audio.." );

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
	m_mWinMusic = pAudio->LoadAudio( L"resource/audio/WinMusic.wav" );




	LoadStrings();

	LoadingScreen( "Loading Graphics..." );

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
	m_hAirIcon = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/AirIcon.png" );
	m_hFireIcon = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/FireIcon.png" );
	m_hWaterIcon = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/WaterIcon.png" );
	m_hEarthIcon = SGD::GraphicsManager::GetInstance()->LoadTexture( L"resource/graphics/EarthIcon.png" );
	m_hLogo = SGD::GraphicsManager::GetInstance()->LoadTexture( "resource/graphics/1411_Turn5_logo.png");



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
	//AddState( OptionsState::GetInstance() );
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
	ClearStates();

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

	pGraphics->UnloadTexture( m_hSaveLoad );

	pGraphics->UnloadTexture( m_hAirIcon );
	pGraphics->UnloadTexture( m_hFireIcon );
	pGraphics->UnloadTexture( m_hWaterIcon );
	pGraphics->UnloadTexture( m_hEarthIcon );

	pGraphics->UnloadTexture( m_hLoadingBackground );
	pGraphics->UnloadTexture( m_hLogo );

	pAudio->UnloadAudio( m_hMusic );
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
	pAudio->UnloadAudio( m_mWinMusic );


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
	m_pDialogs->DeleteInstance();


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

	unsigned int stackSize = m_pStateStack.size();
	for( size_t i = 0; i < stackSize; i++ )
	{
		m_pStateStack.back()->Exit();
		m_pStateStack.pop_back();
	}
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

void Game::LoadStrings()
{
	m_pDialogs = m_pDialogs->GetInstance();

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
	m_StringTable[1][4] = "Plant Healer";
	m_StringTable[1][5] = "Heavy Golem";
	m_StringTable[1][6] = "Earth Mini Boss";
	//Water
	m_StringTable[2][1] = "Minion";
	m_StringTable[2][2] = "doge";
	m_StringTable[2][3] = "Water Elemental";
	m_StringTable[2][4] = "Plant Healer";
	m_StringTable[2][5] = "Heavy Golem";
	m_StringTable[2][6] = "Water Mini Boss";
	//Air
	m_StringTable[3][1] = "Minion";
	m_StringTable[3][2] = "Behemoth";
	m_StringTable[3][3] = "Air Elemental";
	m_StringTable[3][4] = "White Sage";
	m_StringTable[3][5] = "Heavy Golem";
	m_StringTable[3][6] = "Air Mini Boss";
	//Fire
	m_StringTable[4][1] = "Minion";
	m_StringTable[4][2] = "Behemoth";
	m_StringTable[4][3] = "Fire Elemental";
	m_StringTable[4][4] = "Fire Sage";
	m_StringTable[4][5] = "Fire Baron";
	m_StringTable[4][6] = "Fire Mini Boss";
	//Level Bosses/Final Boss

	m_StringTable[5][1] = "Earth Boss";
	m_StringTable[5][2] = "Water Boss";
	m_StringTable[5][3] = "Air Boss";
	m_StringTable[5][4] = "Fire Boss";

	//inventory

	m_StringTable[6][5] = "Tier1:";
	m_StringTable[6][6] = "Tier2:";
	m_StringTable[6][7] = "Tier3:";
	m_StringTable[6][8] = "Tank:";
	m_StringTable[6][9] = "Healer:";
	m_StringTable[6][10] = "Fighter:";
	m_StringTable[6][11] = "Mage:";




	// - Tutorial Strings

	if( !m_bIcelandic )
	{
		m_StringTable[6][1] = "Armor";
		m_StringTable[6][2] = "Sword";
		m_StringTable[6][3] = "Gauntlet";
		m_StringTable[6][4] = "Companions";

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
		m_StringTable[8][6] = "*Run into the boulders and press R repeatedly until it moves*";

		m_StringTable[9][1] = "Music Vol";
		m_StringTable[9][2] = "SFX Vol";
		m_StringTable[9][3] = "Screen";
		m_StringTable[9][4] = "Language";
		m_StringTable[10][6] = "Options";


		// - Combat Tutorial
		m_StringTable[9][5] = "When it is your turn you get to select between your abilities.";
		m_StringTable[9][6] = "Once you've selected an action, you can choose your target.";
		m_StringTable[9][7] = "Your attacks power is based on the amount of right keystrokes";
		m_StringTable[9][8] = "during this quick time, be ready to press the displayed keys.";
		m_StringTable[9][9] = "You control your Companions turns as well and they have different";
		m_StringTable[10][1] = "set of abilities, but do not utilise the QuickTime.";
		m_StringTable[10][2] = "The enemy will retalliate and attack you during their turn,";
		m_StringTable[10][3] = "you have to be careful and watch your health.";
		m_StringTable[10][4] = "Runes that you equip will affect your abilities in combat,";
		m_StringTable[10][5] = "plus the Forge will let you combine any spare Runes you have.";


		if( m_pDialogs != nullptr )
		{
			m_pDialogs->DeleteInstance();
			m_pDialogs = m_pDialogs->GetInstance();
		}
		m_pDialogs->Load( "resource/XML/CompanionDialog.xml" );
		m_pDialogs->Load( "resource/XML/PlayerDialog.xml" );
	}
	else
	{
		m_StringTable[6][1] = "Brynja";
		m_StringTable[6][2] = "Sverd";
		m_StringTable[6][3] = "Hanski";
		m_StringTable[6][4] = "Forunautar";

		m_StringTable[7][1] = "Tharna ertu! Sigmundur sast fyrir Nord-Austan okkur!";
		m_StringTable[7][2] = "Thetta gaeti verid okkar eini sens til ad stodvann.";
		m_StringTable[7][3] = "Fardu Varlega, hann hefur buid til thrautir til ad haegja a okkur";
		m_StringTable[7][4] = "Thu getur leyst thaer med thvi ad renna ther a milli veggja";
		m_StringTable[7][5] = "Thessir steinar geta verid gagnlegir, Yttu a R til ad henda theim.";
		m_StringTable[7][6] = "Thetta eru haettulegar gildrur, reyndu ad fordast thaer!";
		m_StringTable[7][7] = "Og mundu ad gosbrunnurinn hjalpar ther ef thu tapar bardaga.";
		m_StringTable[7][8] = "Passadu thig! Onnur gildra, ekki styga a hana!";
		m_StringTable[7][9] = "Thessi thraut hefur tvaer utkomur, thu gaetir fundid kystu!";
		m_StringTable[8][1] = "Sko thu fannst kystu! Fekkstu Rune? Eda kanski Potion?";
		m_StringTable[8][2] = "Runeir getturu notad i gegnum bakpokann thinn med thvi ad yta E";
		m_StringTable[8][3] = "Tharna! Vertu fyrir aftan mig!";
		m_StringTable[8][4] = "Kysstur geta gefid ther Health Potion, ef thu hefur meidst geturu ";
		m_StringTable[8][5] = "drukkid Health Potion med tvhi ad yta a P";
		m_StringTable[8][6] = "*Hlauptu a tha og yttu a R oft thangad til hann hreyfist*";

		m_StringTable[9][1] = "Tonlist Vol";
		m_StringTable[9][2] = "SFX Vol";
		m_StringTable[9][3] = "Skjar";
		m_StringTable[9][4] = "Tungumal";
		m_StringTable[10][6] = "Stillingar";

		// - Combat Tutorial
		m_StringTable[9][5] = "Thegar umferdin kemur ad ther faerdu ad velja ability til ad nota.";
		m_StringTable[9][6] = "Eftir ad ability er valinn, veluru ovin til ad radast a.";
		m_StringTable[9][7] = "Kraftur arasarinnar fer eftir thvi hvad thu hittir a marga retta takka";
		m_StringTable[9][8] = "a medan thetta Quick Time er i gangi, vertu tilbuin ad yta a tha sem thu serd";
		m_StringTable[9][9] = "Thu faerd einnig ad stjorna vinum thinum, their hafa adra abilities en thu,";
		m_StringTable[10][1] = "en notast ekki vid QuickTime.";
		m_StringTable[10][2] = "Thegar thad er ekki think umferd mun ovinurinn radast a thig til baka";
		m_StringTable[10][3] = "thu verdur ad passa thad ad thu deyjir ekki.";
		m_StringTable[10][4] = "Runir sem ad thu setur a thig hafa ahrif a abilites i bardaga,";
		m_StringTable[10][5] = "og Forgeinn leyfir ther ad blanda saman Runeum sem ad thu tharf ekki ad nota.";

		if( m_pDialogs != nullptr )
		{
			m_pDialogs->DeleteInstance();
			m_pDialogs = m_pDialogs->GetInstance();
		}
		m_pDialogs->Load( "resource/XML/CompanionDialogIS.xml" );
		m_pDialogs->Load( "resource/XML/PlayerDialogIS.xml" );
	}

}

void Game::LoadingScreen( string _loading )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = BitmapFontManager::GetInstance();
	pGraphics->DrawTexture( m_hLoadingBackground, { 0, 0 }, 0, {}, {}, { .78f, 1.2f } );
	pFont->Render( "Other", _loading.c_str(), SGD::Point{ 255, 300 }, 1.5, SGD::Color{ 0, 0, 0} );
	pGraphics->Update();
	Sleep( 150 );
}