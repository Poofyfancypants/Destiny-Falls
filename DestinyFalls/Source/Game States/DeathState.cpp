#include "stdafx.h"
#include "DeathState.h"
#include "OptionsState.h"
#include "GameplayState.h"
#include "PauseMenuState.h"
#include "MainMenuState.h"
#include "SaveandLoadState.h"
#include "../Game Objects/Player.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../Managers/BitmapFontManager.h"


DeathState* DeathState::GetInstance( void )
{
	static DeathState s_Instance;
	return &s_Instance;
}

void DeathState::Enter( void )
{
	m_hBackground = SGD::GraphicsManager::GetInstance()->LoadTexture( "resource/graphics/MenuBackgrounds/deathBackground.png" );
	m_hButton = SGD::GraphicsManager::GetInstance()->LoadTexture( "resource/graphics/MenuBackgrounds/deathButton.png" );
	m_hSelected = SGD::GraphicsManager::GetInstance()->LoadTexture( "resource/graphics/MenuBackgrounds/deathSelected.png" );


	m_mMouseoverRects["Resume"] = SGD::Rectangle( 150, 305, 380, 360 );
	m_mMouseoverRects["Load"] = SGD::Rectangle( 150, 425, 375, 480 );
	m_mMouseoverRects["Options"] = SGD::Rectangle( 420, 305, 650, 360 );
	m_mMouseoverRects["Exit"] = SGD::Rectangle( 420, 425, 650, 480 );
}

void DeathState::Exit( void )
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hBackground );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hButton );
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hSelected );
}

bool DeathState::Input( void )
{
	SGD::InputManager * pInput = SGD::InputManager::GetInstance();

	if( pInput->IsKeyPressed( SGD::Key::Escape ) || pInput->IsButtonDown( 0, 6 ) )
	{
		m_nCursor = PauseSelections::exit;
	}
	if( pInput->IsKeyPressed( SGD::Key::Up ) || pInput->IsKeyPressed( SGD::Key::W ) )
	{
		if( m_nCursor <= 0 )
			m_nCursor = PauseSelections::exit;
		else
			m_nCursor--;
	}
	else if( pInput->IsKeyPressed( SGD::Key::Down ) || pInput->IsKeyPressed( SGD::Key::S ) )
	{
		if( m_nCursor >= PauseSelections::exit )
			m_nCursor = PauseSelections::resume;
		else
			m_nCursor++;
	}
	else if( pInput->IsKeyPressed( SGD::Key::Left ) || pInput->IsKeyPressed( SGD::Key::A ) )
	{
		m_nCursor -= 2;
		if( m_nCursor < 0 )
			m_nCursor += 4;
	}
	else if( pInput->IsKeyPressed( SGD::Key::Right ) || pInput->IsKeyPressed( SGD::Key::D ) )
	{
		m_nCursor += 2;
		if( m_nCursor > PauseSelections::exit )
			m_nCursor -= 4;
	}

	if( pInput->IsKeyPressed( SGD::Key::Enter ) || pInput->IsButtonDown( 0, 0 ) || pInput->IsKeyPressed( SGD::Key::MouseLeft ) )
	{
		Player* player = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) );
		switch( m_nCursor )
		{
		case PauseSelections::resume:
			player->SetPosition( player->GetCheckpoint() );
			player->SetHealth( 100 );
			Game::GetInstance()->RemoveState();
			break;
		case PauseSelections::save:
			Game::GetInstance()->AddState( SaveandLoadState::GetInstance() );
			break;
		case PauseSelections::options:
			Game::GetInstance()->AddState( OptionsState::GetInstance() );
			m_bdeathState = true;
			break;
		case PauseSelections::exit:
			Game::GetInstance()->ClearStates();
			Game::GetInstance()->AddState( MainMenuState::GetInstance() );
			break;
		default:
			break;
		}

	}

	if( pInput->GetCursorMovement().x || pInput->GetCursorMovement().y )
	{
		if( pInput->GetCursorPosition().IsPointInRectangle( m_mMouseoverRects["Resume"] ) )
			m_nCursor = 0;
		else if( pInput->GetCursorPosition().IsPointInRectangle( m_mMouseoverRects["Load"] ) )
			m_nCursor = 1;
		else if( pInput->GetCursorPosition().IsPointInRectangle( m_mMouseoverRects["Options"] ) )
			m_nCursor = 2;
		else if( pInput->GetCursorPosition().IsPointInRectangle( m_mMouseoverRects["Exit"] ) )
			m_nCursor = 3;
		else
			m_nCursor = -1;
	}
	return true;
}

void DeathState::Update( float elapsedTime )
{

}

void DeathState::Render( void )
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();

	//const BitmapFont* pFont = Game::GetInstance()->GetFont();
	BitmapFontManager* pFonts = pFonts->GetInstance();
	SGD::Color fontColor = SGD::Color{ 167, 166, 164 };
	pGraphics->DrawTexture( m_hBackground, SGD::Point( 0, 0 ), {}, {}, {}, { .8f, .7f } );

	if( dynamic_cast<Player*>( GameplayState::GetInstance()->GetPlayer() )->GetInTrap() )
		pFonts->Render( "Other", Game::GetInstance()->GetString( 11, 0 ).c_str(), { 225, 200 }, 1.5f, fontColor );
	else
		pFonts->Render( "Other", Game::GetInstance()->GetString( 11, 1 ).c_str(), { 150, 50 }, 1.5f, fontColor );

	int j = 0;
	for( size_t i = 0; i < 4; i++ )
	{
		if( i > 1 )
		{
			if( i == m_nCursor )
				pGraphics->DrawTexture( m_hSelected, SGD::Point( 400, (float)( 300 + 120 * j ) ) );
			else
				pGraphics->DrawTexture( m_hButton, SGD::Point( 400, (float)( 300 + 120 * j ) ) );
			pFonts->Render( "Other", Game::GetInstance()->GetString( 0, i + 4 ).c_str(), SGD::Point( 475, (float)( 315 + 120 * j ) ), 1, fontColor );
			j++;
		}
		else
		{
			if( i == m_nCursor )
				pGraphics->DrawTexture( m_hSelected, SGD::Point( 130, (float)( 300 + 120 * i ) ) );
			else
				pGraphics->DrawTexture( m_hButton, SGD::Point( 130, (float)( 300 + 120 * i ) ) );
			pFonts->Render( "Other", Game::GetInstance()->GetString( 0, i + 4 ).c_str(), SGD::Point( 200, (float)( 315 + 120 * i ) ), 1, fontColor );
		}
	}
}