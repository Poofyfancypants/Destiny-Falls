#include "stdafx.h"
#include "CreditState.h"
#include "../Game Objects/Player.h"
#include "../Game Core/Game.h"
#include "../Game States/MainMenuState.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_String.h"
#include "../Managers/BitmapFontManager.h"
#include "GameplayState.h"
CreditState* CreditState::GetInstance()
{
	static CreditState s_Instance;
	return &s_Instance;
}

void CreditState::Enter()
{
	m_particle.ReadXML( "resource/XML/Test2.xml" );
	m_vCredits.push_back( "EP:" );
	m_vCredits.push_back( "John OLeske:" );
	m_vCredits.push_back( "AP:" );
	m_vCredits.push_back( "Sean Hathaway" );
	m_vCredits.push_back( "Artist:" );
	m_vCredits.push_back( "Caris Frazie" );
	m_vCredits.push_back( "Gregory Bey:" );
	m_vCredits.push_back( "Developers:" );
	m_vCredits.push_back( "Numi Stefansson" );
	m_vCredits.push_back( "Bobby Criswell" );
	m_vCredits.push_back( "Jeff Lamas" );
	m_vCredits.push_back( "Yvonne Neuland" );
	m_vCredits.push_back( "Evan Doyle" );
	m_vCredits.push_back( "Thanks To:" );
	m_vCredits.push_back( "Spencer Slaton" );
	m_vCredits.push_back( "Dave Olack" );
	m_vCredits.push_back( "Riley Wood" );
	m_vCredits.push_back( "Kidnapped Brick" );

	m_hBackground = SGD::GraphicsManager::GetInstance()->LoadTexture( "resource/graphics/MenuBackgrounds/creditBackground.png" );
	m_bExit = false;
}

void CreditState::Exit()
{
	m_particle.Exit();
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hBackground );
	m_vCredits.clear();
}


bool CreditState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	if( pInput->IsKeyPressed( SGD::Key::Escape ) || pInput->IsButtonDown( 0, 6 ) || m_bExit )
	{
		Game::GetInstance()->ClearStates();
		//pAudio->StopAudio(Game::GetInstance()->m_mWinMusic);
		Game::GetInstance()->AddState( MainMenuState::GetInstance() );

	}
	return true;
}

void CreditState::Update( float elapsedTime )
{
	Timer -= 1 * elapsedTime;


	m_fSecond += elapsedTime;
	if( m_fSecond >= .05f )
	{
		m_fScroll += 1.0f;
		m_fSecond = 0;
		for( size_t i = 0; i < m_vScrollCount.size(); i++ )
			m_vScrollCount[i] += 1.0f;
	}
	if( m_fScroll > 100.0f )
	{
		//	m_fScroll = 0.0f;
	}


	//pFonts->Render("Other", "EP:", { 100, (100 - 5 * m_fScroll) }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "John OLeske", { 125, 125 - 5 * m_fScroll) }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "AP:", { 100, 150 - 5 * m_fScroll) }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Sean Hathaway", { 125, 175 - 5 * m_fScroll) }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Artist", { 100, 200 - 5 * m_fScroll) }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Caris Frazier", { 125, 225- 5 * m_fScroll)  }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Gregory Bey", { 125, 250 - 5 * m_fScroll) }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Devs:", { 100, 275 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Bobby Criswell", { 125, 300 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Yvonne Neuland", { 125, 325 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Numi Stefansson", { 125, 350 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Jeff Lamas", { 125, 375 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Evan Doyle", { 125, 400 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Thanks To", { 100, 425 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Spencer Slaton", { 125, 450 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Dave Olack", { 125, 475 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Riley Wood", { 125, 500 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "Kidnapped Brick", { 125, 525 }, 1, { 255, 255, 255, 255 });
	//pFonts->Render("Other", "esc to Exit", { 680, 550 }, 1, { 255, 255, 255, 255 });

}

void CreditState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	pGraphics->SetClearColor();

	BitmapFontManager* pFonts = pFonts->GetInstance();
	SGD::Color fontColor = SGD::Color( 0,0,0 );
	//SGD::Color fontColor = SGD::Color( 12, 243, 215 );
	float x = Game::GetInstance()->GetScreenWidth() / 1024;
	float y = Game::GetInstance()->GetScreenHeight() / 512;
	pGraphics->DrawTexture( Game::GetInstance()->GetLoadingScreenBkGround(), { 0, 0 }, 0, {}, {}, { .78f, 1.2f } );
	pGraphics->DrawTexture( Game::GetInstance()->GetGameIcon(), { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );

	pFonts->Render( "Other", "Credits:", { 100, 25 }, 2, { 0,0,0 } );
	// 0 , 2, 4, 7, 13

	for( size_t i = 0; i < m_vCredits.size(); i++ )
	{
		float futureY = (float)( ( 650 + ( 30 * i ) ) - 5 * m_fScroll );

		if( i == m_vCredits.size() - 1 && futureY < 50.0f )
		{
			m_bExit = true;
			m_fScroll = 0;
			futureY = (float)( ( 650 + ( 30 * i ) ) - 5 * m_fScroll );
		}
		if( futureY > 80.0f )
		{
			if( i == 0 || i == 2 || i == 4 || i == 7 || i == 13 )
				pFonts->Render( "Other", m_vCredits[i].c_str(), SGD::Point( 100, futureY ), 1, fontColor );
			else
				pFonts->Render( "Other", m_vCredits[i].c_str(), SGD::Point( 130, futureY ), 1, fontColor );
		}

	}

	//m_particle.Render();
}