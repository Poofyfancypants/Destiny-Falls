#include "stdafx.h"
#include "SaveState.h"
#include "MainMenuState.h"
#include "PauseMenuState.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Player.h"
#include "../Managers/BitmapFontManager.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include <fstream>
#include "GameplayState.h"


SaveState* SaveState::GetInstance()
{
	static SaveState s_Instance;
	return &s_Instance;
}

void SaveState::Enter()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	m_hBackground = pGraphics->LoadTexture( L"resource/graphics/MenuBackgrounds/Options.png" );
	m_hButton = pGraphics->LoadTexture( "resource/graphics/optionsButton.png" );
	m_hButtonHighlighted = pGraphics->LoadTexture( "resource/graphics/optionHighlighted.png" );
	m_hNameFrame = pGraphics->LoadTexture( "resource/graphics/MenuBackgrounds/saveScroll.png" );

}

void SaveState::Exit()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	pGraphics->UnloadTexture( m_hButton );
	pGraphics->UnloadTexture( m_hButtonHighlighted );
	pGraphics->UnloadTexture( m_hBackground );
	pGraphics->UnloadTexture( m_hNameFrame );
}

bool SaveState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if( pInput->IsKeyPressed( SGD::Key::Escape ) )
	{
		Game::GetInstance()->RemoveState();
	}

	if( m_bGetKey )
	{
		if( pInput->IsAnyKeyPressed() )
		{

			switch( m_nCursor )
			{
			case 0:
				if( pInput->IsKeyPressed( SGD::Key::Backspace ) && m_sSlot1Name.length() >= 1 )
					m_sSlot1Name.pop_back();
				else
					m_sSlot1Name.push_back( (char)pInput->GetAnyCharPressed() );
				break;
			case 1:
				if( pInput->IsKeyPressed( SGD::Key::Backspace ) && m_sSlot1Name.length() >= 1 )
					m_sSlot2Name.pop_back();
				else
					m_sSlot2Name.push_back( (char)pInput->GetAnyCharPressed() );
				break;
			case 2:
				if( pInput->IsKeyPressed( SGD::Key::Backspace ) && m_sSlot1Name.length() >= 1 )
					m_sSlot3Name.pop_back();
				else
					m_sSlot3Name.push_back( (char)pInput->GetAnyCharPressed() );
				break;
			case 3:
				break;
			}

			if( pInput->IsKeyPressed( SGD::Key::Enter ) || pInput->IsKeyPressed( SGD::Key::MouseLeft ) )
				m_bGetKey = false;
		}
	}
	else
	{
		if( pInput->IsKeyPressed( SGD::Key::Escape ) )
		{
			Game::GetInstance()->RemoveState();
		}


		if( pInput->GetCursorMovement().x || pInput->GetCursorMovement().y )
		{
			if( pInput->GetCursorPosition().IsPointInRectangle( saveslot1 ) )
				m_nCursor = 0;
			else if( pInput->GetCursorPosition().IsPointInRectangle( saveslot2 ) )
				m_nCursor = 1;
			else if( pInput->GetCursorPosition().IsPointInRectangle( saveslot3 ) )
				m_nCursor = 2;
			else if( pInput->GetCursorPosition().IsPointInRectangle( exit ) )
				m_nCursor = 3;
			else
				m_nCursor = -1;
		}
		if( pInput->IsKeyPressed( SGD::Key::Enter ) || pInput->IsKeyPressed( SGD::Key::MouseLeft ) )
			m_bGetKey = true;
	}

	return true;
}

void SaveState::Update( float elapsedTime )
{
	return;
}

void SaveState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = pFont->GetInstance();
	SGD::Color textColor = { 239, 208, 162 };

	pGraphics->DrawTexture( Game::GetInstance()->GetLoadingScreenBkGround(), { 0, 0 }, 0, {}, {}, { .78f, 1.2f } );
	pGraphics->DrawTexture( Game::GetInstance()->GetGameIcon(), { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );


	pGraphics->DrawTexture( m_hButton, SGD::Point( 20, 300 ) );
	pFont->Render( "Other", m_sSlot1Name.c_str(), SGD::Point( 50, 315 ), 1, textColor );
	pGraphics->DrawTexture( m_hButton, SGD::Point( 525, 300 ) );
	pFont->Render( "Other", m_sSlot2Name.c_str(), SGD::Point( 555, 315 ), 1, textColor );
	pGraphics->DrawTexture( m_hButton, SGD::Point( 285, 470 ) );
	pFont->Render( "Other", m_sSlot3Name.c_str(), SGD::Point( 315, 485 ), 1, textColor );



	switch( m_nCursor )
	{
	case 0:
		pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 20, 300 ) );
		pFont->Render( "Other", m_sSlot1Name.c_str(), SGD::Point( 50, 315 ), 1, textColor );
		break;
	case 1:
		pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 525, 300 ) );
		pFont->Render( "Other", m_sSlot2Name.c_str(), SGD::Point( 555, 315 ), 1, textColor );
		break;
	case 3:
		pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 285, 470 ) );
		pFont->Render( "Other", m_sSlot3Name.c_str(), SGD::Point( 315, 485 ), 1, textColor );
		break;

	}

	if( m_bGetKey )
	{
		switch( m_nCursor )
		{
		case 0:
			pGraphics->DrawTexture( m_hNameFrame, SGD::Point( 200, 190 ) );
			pFont->Render( "Other", "Name;", SGD::Point( 290, 240 ), 1, SGD::Color( 0, 0, 0 ) );
			pFont->Render( "Other", m_sSlot1Name.c_str(), SGD::Point( 325, 310 ), 1, SGD::Color( 0, 0, 0 ) );
			break;
		case 1:
			pGraphics->DrawTexture( m_hNameFrame, SGD::Point( 200, 190 ) );
			pFont->Render( "Other", "Name;", SGD::Point( 290, 240 ), 1, SGD::Color( 0, 0, 0 ) );
			pFont->Render( "Other", m_sSlot2Name.c_str(), SGD::Point( 325, 310 ), 1, SGD::Color( 0, 0, 0 ) );
			break;
		case 3:
			pGraphics->DrawTexture( m_hNameFrame, SGD::Point( 200, 190 ) );
			pFont->Render( "Other", "Name;", SGD::Point( 290, 240 ), 1, SGD::Color( 0, 0, 0 ) );
			pFont->Render( "Other", m_sSlot3Name.c_str(), SGD::Point( 325, 310 ), 1, SGD::Color( 0, 0, 0 ) );
			break;
		}
	}
}

void SaveState::Save()
{
	fstream fout;
	fout.open( "resource/Save/Save.txt", ios_base::out | ios_base::binary );

	if( fout.is_open() )
	{
		int health = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetHealth();
		float posx = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().x;
		float posy = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().y;
		int currLevel = GameplayState::GetInstance()->GetCurrentLevel();

		fout.write( (char*)&health, sizeof( int ) );
		fout.write( (char*)&posx, sizeof( float ) );
		fout.write( (char*)&posy, sizeof( float ) );
		fout.write( (char*)&currLevel, sizeof( int ) );

		//unsigned int fileLength = m_sSlot1Name.length() + 1;
		//fout.write( (char*)( &fileLength ), sizeof( ( fileLength ) ) );
		//fout.write( m_sSlot3Name.c_str(), fileLength );

		fout.close();
	}

}
void SaveState::Save2()
{
	fstream fout;
	fout.open( "resource/Save/Save2.txt", ios_base::out | ios_base::binary );
	if( fout.is_open() )
	{
		int health = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetHealth();
		float posx = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().x;
		float posy = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().y;
		int currlevel = GameplayState::GetInstance()->GetChangeLevel();

		fout.write( (char*)&health, sizeof( int ) );
		fout.write( (char*)&posx, sizeof( float ) );
		fout.write( (char*)&posy, sizeof( float ) );
		fout.write( (char*)&currlevel, sizeof( int ) );

		//unsigned int fileLength = m_sSlot2Name.length() + 1;
		//fout.write( (char*)( &fileLength ), sizeof( ( fileLength ) ) );
		//fout.write( m_sSlot2Name.c_str(), fileLength );

		fout.close();
	}

}
void SaveState::Save3()
{
	fstream fout;
	fout.open( "resource/Save/Save3.txt", ios_base::out | ios_base::binary );
	if( fout.is_open() )
	{
		int health = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetHealth();
		float posx = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().x;
		float posy = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().y;
		int currlevel = GameplayState::GetInstance()->GetChangeLevel();

		fout.write( (char*)&health, sizeof( int ) );
		fout.write( (char*)&posx, sizeof( float ) );
		fout.write( (char*)&posy, sizeof( float ) );
		fout.write( (char*)&currlevel, sizeof( int ) );

		//unsigned int fileLength = m_sSlot3Name.length() + 1;
		//fout.write( (char*)( &fileLength ), sizeof( ( fileLength ) ) );
		//fout.write( m_sSlot3Name.c_str(), fileLength );

		fout.close();
	}

}

void SaveState::Load()
{
	fstream fin;
	fin.open( "resource/Save/Save.txt", ios_base::in | ios_base::binary );
	if( fin.is_open() )
	{
		int health, currLevel;
		float posx, posy;

		fin.read( (char*)&health, sizeof( int ) );
		fin.read( (char*)&posx, sizeof( float ) );
		fin.read( (char*)&posy, sizeof( float ) );
		fin.read( (char*)&currLevel, sizeof( int ) );

		Game::GetInstance()->RemoveState();
		Game::GetInstance()->AddState( GameplayState::GetInstance() );

		GameplayState::GetInstance()->SetLevel( currLevel );
		GameplayState::GetInstance()->LoadNewLevel();

		( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetHealth( health );
		( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetPosition( SGD::Point{ posx, posy } );

		fin.close();
	}
}

void SaveState::Load2()
{
	fstream fin;
	fin.open( "resource/Save/Save2.txt", ios_base::in | ios_base::binary );
	if( fin.is_open() )
	{
		int health, currLevel;
		float posx, posy;

		fin.read( (char*)&health, sizeof( int ) );
		fin.read( (char*)&posx, sizeof( float ) );
		fin.read( (char*)&posy, sizeof( float ) );
		fin.read( (char*)&currLevel, sizeof( int ) );

		Game::GetInstance()->RemoveState();
		Game::GetInstance()->AddState( GameplayState::GetInstance() );


		GameplayState::GetInstance()->SetLevel( currLevel );
		GameplayState::GetInstance()->LoadNewLevel();

		( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetHealth( health );
		( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetPosition( SGD::Point{ posx, posy } );

		fin.close();
	}
}

void SaveState::Load3()
{
	fstream fin;
	fin.open( "resource/Save/Save3.txt", ios_base::in | ios_base::binary );
	if( fin.is_open() )
	{
		int health, currLevel;
		float posx, posy;

		fin.read( (char*)&health, sizeof( int ) );
		fin.read( (char*)&posx, sizeof( float ) );
		fin.read( (char*)&posy, sizeof( float ) );
		fin.read( (char*)&currLevel, sizeof( int ) );

		Game::GetInstance()->RemoveState();
		Game::GetInstance()->AddState( GameplayState::GetInstance() );


		GameplayState::GetInstance()->SetLevel( currLevel );
		GameplayState::GetInstance()->LoadNewLevel();

		( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetHealth( health );
		( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetPosition( SGD::Point{ posx, posy } );

		fin.close();
	}
}

//wchar_t SaveState::GetName()
//{
//
//	//SGD::InputManager* pInput = SGD::InputManager::GetInstance();
//	//SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
//	//BitmapFontManager* pFont = BitmapFontManager::GetInstance();
//	//SGD::Color fontColor = SGD::Color( 0, 0, 0 );
//	//name += pInput->GetAnyCharPressed();
//	//if( pInput->IsKeyPressed( SGD::Key::Backspace ) )
//	//	name.pop_back();
//	//pGraphics->DrawTexture( m_hNameFrame, SGD::Point( 420, 300 ) );
//	//pFont->Render( "Other", "Name:", SGD::Point( 290, 240 ), 1, fontColor );
//	//pFont->Render( "Other", name.c_str(), SGD::Point( 325, 310 ), 1, fontColor );
//
//	//pGraphics->Update();
//
//	//if( pInput->IsKeyUp( SGD::Key::Enter ) )
//	//	return name;
//
//}


