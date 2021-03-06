#include "stdafx.h"
#include "OptionsState.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_String.h"
#include "../Managers/BitmapFontManager.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"
#include "../Game Core/Game.h"
#include "DeathState.h"
#include "PauseMenuState.h"
#include "GameplayState.h"
#include "MainMenuState.h"
#include <fstream>
#include <ostream>

OptionsState* OptionsState::GetInstance()
{
	static OptionsState s_Instance;
	return &s_Instance;
}

void OptionsState::Enter()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	m_hBackground = pGraphics->LoadTexture( L"resource/graphics/MenuBackgrounds/Options.png" );
	m_hButton = pGraphics->LoadTexture( "resource/graphics/optionsButton.png" );
	m_hButtonHighlighted = pGraphics->LoadTexture( "resource/graphics/optionHighlighted.png" );
	m_hBackMusic = pAudio->LoadAudio( "resource/audio/MainMenuSong.xwm" );
	m_hEffectSound = pAudio->LoadAudio( "resource/audio/HealAbility.wav" );
	m_hArrow = pGraphics->LoadTexture( "resource/graphics/MenuBackgrounds/optionArrow.png", {} );

	m_hWindow = Game::GetInstance()->GetWindowed();


	// - Rectangles
	m_mMouseoverRects["Music"] = SGD::Rectangle( 130, 110, 700, 170 );
	m_mMouseoverRects["SFX"] = SGD::Rectangle( 130, 220, 700, 280 );
	m_mMouseoverRects["Window"] = SGD::Rectangle( 130, 330, 700, 390 );
	m_mMouseoverRects["Language"] = SGD::Rectangle( 130, 440, 700, 500 );
	m_mMouseoverRects["Back"] = SGD::Rectangle( 595, 540.0f, 750, 582 );

}

void OptionsState::Exit()
{
	SGD::AudioManager *pAudio = SGD::AudioManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	std::ofstream save;
	save.open( "resource/XML/Options.txt" );
	if( save.is_open() )
		save << pAudio->GetMasterVolume( SGD::AudioGroup::Music ) << " " << pAudio->GetMasterVolume( SGD::AudioGroup::SoundEffects )
		<< " " << Game::GetInstance()->GetWindowed() << " " << Game::GetInstance()->GetIcelandic();

	m_hWindow = Game::GetInstance()->GetWindowed();
	pGraphics->UnloadTexture( m_hButton );
	pGraphics->UnloadTexture( m_hButtonHighlighted );
	pGraphics->UnloadTexture( m_hArrow );
	pGraphics->UnloadTexture( m_hBackground );

	pAudio->UnloadAudio( m_hBackMusic );
	pAudio->UnloadAudio( m_hEffectSound );
}

bool OptionsState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();
	if (m_fArcadeTimer >= 0.5f)
	{
		if (pInput->IsKeyPressed(SGD::Key::Escape) || pInput->IsButtonPressed(0, 6))
		{
			if (PauseMenuState::GetInstance()->GetPauseState() || DeathState::GetInstance()->GetDeathState())
			{
				DeathState::GetInstance()->SetDeathState(false);
				PauseMenuState::GetInstance()->SetPauseState(false);
				Game::GetInstance()->RemoveState();
			}
			else
			{
				Game::GetInstance()->ClearStates();
				Game::GetInstance()->AddState(MainMenuState::GetInstance());
			}
			m_fArcadeTimer = 0.0f;
		}

		if (pInput->IsKeyPressed(SGD::Key::Down) || pInput->IsKeyPressed(SGD::Key::S) || pInput->GetLeftJoystick(0).y == 1)
		{
			++m_nCursor;
			if (m_nCursor > 5)
				m_nCursor = 1;
			m_fArcadeTimer = 0.0f;

		}
		else if (pInput->IsKeyPressed(SGD::Key::Up) || pInput->IsKeyPressed(SGD::Key::W) || pInput->GetLeftJoystick(0).y == -1)
		{
			--m_nCursor;
			if (m_nCursor < 1)
				m_nCursor = 5;
			m_fArcadeTimer = 0.0f;

		}

		if (pInput->IsKeyPressed(SGD::Key::Left) || pInput->IsKeyPressed(SGD::Key::A) || pInput->GetLeftJoystick(0).x == -1)
		{
			switch (m_nCursor)
			{
			case 1:
				pAudio->SetMasterVolume(SGD::AudioGroup::Music, pAudio->GetMasterVolume(SGD::AudioGroup::Music) - 10);
				break;
			case 2:
				pAudio->SetMasterVolume(SGD::AudioGroup::SoundEffects, pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects) - 10);
				if (!pAudio->IsAudioPlaying(m_hEffectSound))
					pAudio->PlayAudio(m_hEffectSound, false);
				break;
			case 3:
				Game::GetInstance()->SetWindowd(!Game::GetInstance()->GetWindowed());
				break;
			case 4:
				Game::GetInstance()->SetIcelandic(!Game::GetInstance()->GetIcelandic());
				Game::GetInstance()->LoadStrings();
				break;
			default:
				break;
			}
			m_fArcadeTimer = 0.0f;

		}
		if (pInput->IsKeyPressed(SGD::Key::Right) || pInput->IsKeyPressed(SGD::Key::D) || pInput->GetLeftJoystick(0).x == 1)
		{
			switch (m_nCursor)
			{
			case 1:
				pAudio->SetMasterVolume(SGD::AudioGroup::Music, pAudio->GetMasterVolume(SGD::AudioGroup::Music) + 10);
				break;
			case 2:
				pAudio->SetMasterVolume(SGD::AudioGroup::SoundEffects, pAudio->GetMasterVolume(SGD::AudioGroup::SoundEffects) + 10);
				if (!pAudio->IsAudioPlaying(m_hEffectSound))
					pAudio->PlayAudio(m_hEffectSound, false);
				break;
			case 3:
				Game::GetInstance()->SetWindowd(!Game::GetInstance()->GetWindowed());
				break;
			case 4:
				Game::GetInstance()->SetIcelandic(!Game::GetInstance()->GetIcelandic());
				Game::GetInstance()->LoadStrings();
				break;
			default:
				break;
			}
			m_fArcadeTimer = 0.0f;

		}
		if (pInput->IsKeyPressed(SGD::Key::Enter) && m_nCursor == 5 || pInput->IsButtonPressed(0, 0) && m_nCursor == 5)
		{
			Game::GetInstance()->RemoveState();
			m_fArcadeTimer = 0.0f;
		}
	}
	if( pInput->GetCursorMovement().x || pInput->GetCursorMovement().y )
	{
		if( pInput->GetCursorPosition().IsPointInRectangle( m_mMouseoverRects["Music"] ) )
			m_nCursor = 1;
		else if( pInput->GetCursorPosition().IsPointInRectangle( m_mMouseoverRects["SFX"] ) )
			m_nCursor = 2;
		else if( pInput->GetCursorPosition().IsPointInRectangle( m_mMouseoverRects["Window"] ) )
			m_nCursor = 3;
		else if( pInput->GetCursorPosition().IsPointInRectangle( m_mMouseoverRects["Language"] ) )
			m_nCursor = 4;
		else if( pInput->GetCursorPosition().IsPointInRectangle( m_mMouseoverRects["Back"] ) )
			m_nCursor = 5;
		//else
			//m_nCursor = -1;
	}

	if( pInput->IsKeyPressed( SGD::Key::MouseLeft ) )
	{
		SGD::Rectangle LeftArrow = SGD::Rectangle{ SGD::Point( 440, 110 * (float)m_nCursor ), SGD::Size( 60, 60 ) };
		SGD::Rectangle RightArrow = SGD::Rectangle(SGD::Point(650, 110 * (float)m_nCursor), SGD::Size(60, 60));
		if( pInput->GetCursorPosition().IsPointInRectangle( LeftArrow ) )
		{
			switch( m_nCursor )
			{
			case 1:
				pAudio->SetMasterVolume( SGD::AudioGroup::Music, pAudio->GetMasterVolume( SGD::AudioGroup::Music ) - 10 );
				break;
			case 2:
				pAudio->SetMasterVolume( SGD::AudioGroup::SoundEffects, pAudio->GetMasterVolume( SGD::AudioGroup::SoundEffects ) - 10 );
				if( !pAudio->IsAudioPlaying( m_hEffectSound ) )
					pAudio->PlayAudio( m_hEffectSound, false );

				break;
			case 3:
				Game::GetInstance()->SetWindowd( !Game::GetInstance()->GetWindowed() );
				break;
			case 4:
				Game::GetInstance()->SetIcelandic( !Game::GetInstance()->GetIcelandic() );
				Game::GetInstance()->LoadStrings();
				break;
			default:
				break;
			}
		}
		if( pInput->GetCursorPosition().IsPointInRectangle( RightArrow ) )
		{
			switch( m_nCursor )
			{
			case 1:
				pAudio->SetMasterVolume( SGD::AudioGroup::Music, pAudio->GetMasterVolume( SGD::AudioGroup::Music ) + 10 );
				break;
			case 2:
				pAudio->SetMasterVolume( SGD::AudioGroup::SoundEffects, pAudio->GetMasterVolume( SGD::AudioGroup::SoundEffects ) + 10 );
				if( !pAudio->IsAudioPlaying( m_hEffectSound ) )
					pAudio->PlayAudio( m_hEffectSound, false );
				break;
			case 3:
				Game::GetInstance()->SetWindowd( !Game::GetInstance()->GetWindowed() );
				break;
			case 4:
				Game::GetInstance()->SetIcelandic( !Game::GetInstance()->GetIcelandic() );
				Game::GetInstance()->LoadStrings();
				break;
			default:
				break;
			}
		}
		if( m_nCursor == 5 )
		{
			if( PauseMenuState::GetInstance()->GetPauseState() || DeathState::GetInstance()->GetDeathState() )
			{
				DeathState::GetInstance()->SetDeathState( false );
				PauseMenuState::GetInstance()->SetPauseState( false );
				Game::GetInstance()->RemoveState();
			}
			else
			{
				Game::GetInstance()->ClearStates();
				Game::GetInstance()->AddState( MainMenuState::GetInstance() );
			}
		}
	}
	return true;
}

void OptionsState::Update( float elapsedTime )
{
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();
	if( !pAudio->IsAudioPlaying( Game::GetInstance()->GetAudio() ) || !pAudio->IsAudioPlaying( m_hBackMusic ) )
		pAudio->PlayAudio( m_hBackMusic, true );

	if( Game::GetInstance()->GetWindowed() != m_hWindow )
	{
		SGD::GraphicsManager::GetInstance()->Resize( { Game::GetInstance()->GetScreenWidth(), Game::GetInstance()->GetScreenHeight() }, Game::GetInstance()->GetWindowed() );
		m_nCursor = 3;
	}
	m_hWindow = Game::GetInstance()->GetWindowed();


	m_fArcadeTimer += elapsedTime;
}

void OptionsState::Render()
{
	SGD::AudioManager *pAudio = SGD::AudioManager::GetInstance();
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFonts = pFonts->GetInstance();

	SGD::Color textColor = { 239, 208, 162 };
	pGraphics->DrawTexture( Game::GetInstance()->GetLoadingScreenBkGround(), { 0, 0 }, 0, {}, {}, { .78f, 1.2f } );
	pGraphics->DrawTexture( Game::GetInstance()->GetGameIcon(), { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );

	pFonts->Render( "Other", Game::GetInstance()->GetString( 10, 6 ).c_str(), { 340, 10 }, 2.0f, { 255, 0, 0, 0 } );
	pFonts->Render( "Other", Game::GetInstance()->GetString( 10, 6 ).c_str(), { 340, 13 }, 2.0f, textColor );

	string MusicVolume;
	string SFXVolume;
	MusicVolume = to_string( pAudio->GetMasterVolume( SGD::AudioGroup::Music ) / 10 );
	SFXVolume = to_string( pAudio->GetMasterVolume( SGD::AudioGroup::SoundEffects ) / 10 );

	for( size_t i = 1; i <= 4; i++ )
	{
		if( i == m_nCursor )
			pGraphics->DrawTexture( m_hButtonHighlighted, { 130, (float)( 110 * i ) } );
		else
			pGraphics->DrawTexture( m_hButton, { 130, (float)( 110 * i ) } );
		pFonts->Render( "Other", Game::GetInstance()->GetString( 9, i ).c_str(), { 210, (float)( ( 110 * i ) + 15 ) }, 1, { 255, 0, 0, 0 } );
		pFonts->Render( "Other", Game::GetInstance()->GetString( 9, i ).c_str(), { 210, (float)( ( 110 * i ) + 17 ) }, 1, textColor );

		if( i == m_nCursor )
		{
			pGraphics->DrawTexture( m_hButtonHighlighted, { 500, (float)( 110 * i ) }, {}, {}, {}, { .6f, 1.0f } );
			pGraphics->DrawTexture( m_hArrow, { 447, (float)( 110 * i ) }, {}, {}, {}, { 1, 1 } );
		}
		else
			pGraphics->DrawTexture( m_hButton, { 500, (float)( 110 * i ) }, {}, {}, {}, { .6f, 1.0f } );

	}

	pFonts->Render( "Other", MusicVolume.c_str(), { 565, (float)( ( 110 ) + 5 ) }, 1.5f, { 255, 0, 0, 0 } );
	pFonts->Render( "Other", MusicVolume.c_str(), { 565, (float)( ( 110 ) + 7 ) }, 1.5f, textColor );

	pFonts->Render( "Other", SFXVolume.c_str(), { 565, (float)( ( 220 ) + 5 ) }, 1.5f, { 255, 0, 0, 0 } );
	pFonts->Render( "Other", SFXVolume.c_str(), { 565, (float)( ( 220 ) + 7 ) }, 1.5f, textColor );


	pFonts->Render( "Other", ( Game::GetInstance()->GetWindowed() ? "Windowed" : "Fullscreen" ), { 520, (float)( ( 340 ) + 5 ) }, 1, { 255, 0, 0, 0 } );
	pFonts->Render( "Other", ( Game::GetInstance()->GetWindowed() ? "Windowed" : "Fullscreen" ), { 520, (float)( ( 340 ) + 7 ) }, 1, textColor );

	pFonts->Render( "Other", ( Game::GetInstance()->GetIcelandic() ? "Icelandic" : "English" ), { 540, (float)( ( 450 ) + 5 ) }, 1, { 255, 0, 0, 0 } );
	pFonts->Render( "Other", ( Game::GetInstance()->GetIcelandic() ? "Icelandic" : "English" ), { 540, (float)( ( 450 ) + 7 ) }, 1, textColor );

	if( 5 == m_nCursor )
		pGraphics->DrawTexture( m_hButtonHighlighted, { 595, 540.0f }, {}, {}, {}, { .6f, .6f } );
	else
		pGraphics->DrawTexture( m_hButton, { 595, 540.0f }, {}, {}, {}, { .6f, .6f } );

	pFonts->Render( "Other", "Back", { 645.0f, 542.0f }, 1, { 255, 0, 0, 0 } );
	pFonts->Render( "Other", "Back", { 645.0f, 545.0f }, 1, textColor );


}