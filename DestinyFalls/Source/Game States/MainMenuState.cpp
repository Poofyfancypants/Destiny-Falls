#include "stdafx.h"
#include "MainMenuState.h"
#include "GameplayState.h"
#include "OptionsState.h"
#include "CreditState.h"
#include "HowToPlayState.h"
#include "SaveState.h"
#include "../Managers/ParticleManager.h"
#include "../Managers/TileManager.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_String.h"
#include "../Game States/AnimationTestState.h"
//#include "../Bitmap Font/BitmapFont.h"
#include "../Managers/BitmapFontManager.h"

MainMenuState* MainMenuState::GetInstance()
{
	static MainMenuState s_Instance;
	return &s_Instance;
}

void MainMenuState::Enter()
{
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	m_bTutorial = false;

	m_hMusic = pAudio->LoadAudio( "resource/audio/MainMenuSong.xwm" );
	if( !pAudio->IsAudioPlaying( Game::GetInstance()->GetAudio() ) )
		pAudio->PlayAudio( m_hMusic, true );

	InventoryState::GetInstance()->m_vSword.resize( 3 );
	InventoryState::GetInstance()->SetSwordSlot1( None, 0 );
	InventoryState::GetInstance()->SetSwordSlot2( None, 0 );
	InventoryState::GetInstance()->SetSwordSlot3( None, 0 );
	InventoryState::GetInstance()->m_vArmor.resize( 3 );
	InventoryState::GetInstance()->SetArmorSlot1( None, 0 );
	InventoryState::GetInstance()->SetArmorSlot2( None, 0 );
	InventoryState::GetInstance()->SetArmorSlot3( None, 0 );
	InventoryState::GetInstance()->m_vRing.resize( 3 );
	InventoryState::GetInstance()->SetRingSlot1( None, 0 );
	InventoryState::GetInstance()->SetRingSlot2( None, 0 );
	InventoryState::GetInstance()->SetRingSlot3( None, 0 );
	InventoryState::GetInstance()->m_vCompanion.resize( 2 );
	InventoryState::GetInstance()->m_vCompanion[0].SetC0Type( Companion::Companion_Type::Mage );
	InventoryState::GetInstance()->m_vCompanion[1].SetC0Type( Companion::Companion_Type::Melee );


	// - Load Selection
	m_hBackground = pGraphics->LoadTexture( "resource/graphics/MenuBackgrounds/1411_Turn5_MenuBackground.png" );
	m_hPlay = pGraphics->LoadTexture( "resource/graphics/MenuBackgrounds/menuPlay.png" );
	m_hLogo = pGraphics->LoadTexture( "resource/graphics/1411_Turn5_logo.png" );
	m_hButton = pGraphics->LoadTexture( "resource/graphics/optionsButton.png" );
	FadeInMenu();
	m_hButtonHighlighted = pGraphics->LoadTexture( "resource/graphics/optionHighlighted.png" );
	m_hOptions = pGraphics->LoadTexture( "resource/graphics/MenuBackgrounds/menuOptions.png" );
	m_hCredit = pGraphics->LoadTexture( "resource/graphics/MenuBackgrounds/menuCredit.png" );
	m_hTutorial = pGraphics->LoadTexture( "resource/graphics/MenuBackgrounds/menuTutorial.png" );
}

void MainMenuState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hPlay );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hTutorial );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hCredit );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hOptions );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hBackground );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hLogo );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hButton );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hButtonHighlighted );
	SGD::AudioManager::GetInstance()->UnloadAudio( m_hMusic );
}

bool MainMenuState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	if( pInput->IsKeyPressed( SGD::Key::Escape ) )
	{
		pAudio->PlayAudio( Game::GetInstance()->m_mButton );
		m_nCursor = MenuSelections::exit;
	}
	if( pInput->IsKeyPressed( SGD::Key::Up ) || pInput->IsKeyPressed( SGD::Key::W ) )
	{
		pAudio->PlayAudio( Game::GetInstance()->m_mButton );

		//if( m_nCursor <= 0 )
		//	m_nCursor = MenuSelections::exit;
		//else
		//	m_nCursor--;
		if( m_nCursor == howToPlay )
			m_nCursor = exit;
		else
			m_nCursor = howToPlay;
	}
	else if( pInput->IsKeyPressed( SGD::Key::Down ) || pInput->IsKeyPressed( SGD::Key::S ) )
	{
		pAudio->PlayAudio( Game::GetInstance()->m_mButton );

		//if( m_nCursor >= MenuSelections::exit )
		//	m_nCursor = MenuSelections::play;
		//else
		//	m_nCursor++;
		if( m_nCursor == options )
			m_nCursor = exit;
		else
			m_nCursor = options;
	}
	else if( pInput->IsKeyPressed( SGD::Key::Left ) || pInput->IsKeyPressed( SGD::Key::A ) )
	{
		pAudio->PlayAudio( Game::GetInstance()->m_mButton );
		if( m_nCursor == play )
			m_nCursor = exit;
		else
			m_nCursor = play;
	}
	else if( pInput->IsKeyPressed( SGD::Key::Right ) || pInput->IsKeyPressed( SGD::Key::D ) )
	{
		pAudio->PlayAudio( Game::GetInstance()->m_mButton );
		if( m_nCursor == credits )
			m_nCursor = exit;
		else
			m_nCursor = credits;
	}

	if( pInput->IsKeyPressed( SGD::Key::Enter ) || pInput->IsKeyPressed( SGD::Key::MouseLeft ) )
	{
		pAudio->PlayAudio( Game::GetInstance()->m_mButton );

		switch( m_nCursor )
		{
		case MenuSelections::play:
			Game::GetInstance()->AddState( GameplayState::GetInstance() );
			pAudio->StopAudio( Game::GetInstance()->GetAudio() );
			break;
		case MenuSelections::options:
			Game::GetInstance()->AddState( OptionsState::GetInstance() );
			break;
		case MenuSelections::howToPlay:
			Game::GetInstance()->AddState( GameplayState::GetInstance() );
			m_bTutorial = true;
			break;
		case MenuSelections::credits:
			Game::GetInstance()->AddState( CreditState::GetInstance() );
			break;
		case MenuSelections::exit:
			return false;
			break;
		default:
			break;
		}
		//pAudio->StopAudio( m_hMusic );

	}

	if( pInput->GetCursorMovement().x || pInput->GetCursorMovement().y )
	{
		if( pInput->GetCursorPosition().IsPointInRectangle( playRect ) )
			m_nCursor = play;
		else if( pInput->GetCursorPosition().IsPointInRectangle( optionRect ) )
			m_nCursor = options;
		else if( pInput->GetCursorPosition().IsPointInRectangle( tutorialRect ) )
			m_nCursor = howToPlay;
		else if( pInput->GetCursorPosition().IsPointInRectangle( creditRect ) )
			m_nCursor = credits;
		else if( pInput->GetCursorPosition().IsPointInRectangle( exitRect ) )
			m_nCursor = exit;
		else
			m_nCursor = -1;
	}

	if( pInput->IsKeyPressed( SGD::Key::F2 ) )
		m_bDebug = !m_bDebug;
	return true;
}

void MainMenuState::Update( float elapsedTime )
{
	//Game::GetInstance()->AddState(SaveState::GetInstance());
	return;

}

void MainMenuState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = BitmapFontManager::GetInstance();
	if( m_bDebug )
	{
		//SGD::OStringStream numEnt;
		//numEnt << "Objects: " << GameplayState::GetInstance()->GetObjManager()->GetNumObjects();
		//SGD::GraphicsManager::GetInstance()->DrawString( numEnt.str().c_str(), SGD::Point( 10, 30 ), { 0, 255, 0 } );

		SGD::OStringStream fps;
		fps << "FPS: " << Game::GetInstance()->GetFrames();
		pGraphics->DrawString( fps.str().c_str(), SGD::Point( 10, 10 ), SGD::Color( 0, 255, 0 ) );
	}


	pGraphics->SetClearColor( { 64, 47, 25 } );
	pGraphics->DrawTexture( Game::GetInstance()->GetLoadingScreenBkGround(), { 0, 0 }, 0, {}, {}, { .78f, 1.2f } );

	pGraphics->DrawTexture( m_hBackground, { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );
	pGraphics->DrawTexture( m_hButton, SGD::Point( 630, 530 ), {}, {}, {}, { .5f, 1 } );
	pFont->Render( "Other", "Exit", SGD::Point( 655, 545 ), 1, SGD::Color( 0, 0, 0 ) );

	BitmapFontManager * pFonts = pFonts->GetInstance();

	switch( m_nCursor )
	{
	case MainMenuState::play:
		pGraphics->DrawTexture( m_hPlay, { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );
		break;
	case MainMenuState::options:
		pGraphics->DrawTexture( m_hOptions, { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );
		break;
	case MainMenuState::howToPlay:
		pGraphics->DrawTexture( m_hTutorial, { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );
		break;
	case MainMenuState::credits:
		pGraphics->DrawTexture( m_hCredit, { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );
		break;
	case MainMenuState::exit:
		pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 630, 530 ), {}, {}, {}, { .5f, 1 } );
		pFont->Render( "Other", "Exit", SGD::Point( 655, 545 ), 1, SGD::Color( 0, 0, 0 ) );
		break;
	default:
		break;
	}
	pGraphics->DrawTexture( m_hLogo, { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );


}
void MainMenuState::FadeInMenu()
{

	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	pGraphics->SetClearColor( { 64, 47, 25 } );
	for( size_t i = 0; i < 225; i++ )
	{
		pGraphics->DrawTexture( Game::GetInstance()->GetLoadingScreenBkGround(), { 0, 0 }, 0, {}, {}, { .78f, 1.2f } );
		pGraphics->DrawTexture( m_hBackground, { 100, 0 }, 0, {}, SGD::Color{ (unsigned char)( i ), 255, 255, 255 }, { 0.3f, 0.3f } );
		pGraphics->DrawTexture( m_hLogo, { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );
		pGraphics->Update();
		Sleep( 5 );

	}



}