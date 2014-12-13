#include "stdafx.h"
#include "QuickTime.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../Bitmap Font/BitmapFont.h"
#include "../Game Core/Game.h"
#include "../Managers/BitmapFontManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"



QuickTime::QuickTime()
{
	//clear key vector
	m_vKeys.clear();

	if( SGD::InputManager::GetInstance()->IsControllerConnected( 0 ) || SGD::InputManager::GetInstance()->IsControllerConnected( 1 ) )
	{
		//push back buttons into the key vector
		m_vKeys.push_back( SGD::Key::Zero	);
		m_vKeys.push_back( SGD::Key::One	);
		m_vKeys.push_back( SGD::Key::Two	);
		m_vKeys.push_back( SGD::Key::Three	);
		m_vKeys.push_back( SGD::Key::Four	);
		m_vKeys.push_back( SGD::Key::Five	);
	}
	else
	{
		//push back buttons into the key vector
		m_vKeys.push_back( SGD::Key::Q );
		m_vKeys.push_back( SGD::Key::W );
		m_vKeys.push_back( SGD::Key::E );
		m_vKeys.push_back( SGD::Key::A );
		m_vKeys.push_back( SGD::Key::S );
		m_vKeys.push_back( SGD::Key::D );
	}
	
	if( GameplayState::GetInstance()->GetCurrentLevel() == 0 )
	{
		m_fAlertTimer = 4.0f;
	}

	//clear out the input and output vectors
	m_vInput.clear();
	m_vOutput.clear();

	//set the qtover bool to false
	m_bqtOver = false;

	m_hScroll = SGD::GraphicsManager::GetInstance()->LoadTexture( "resource/graphics/Scroll.png" );

}


QuickTime::~QuickTime()
{
}

void QuickTime::Update( float elapsedTime )
{
	//create a pointer to the input manager
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if( !m_bShowAlert )
	{
		//add the elapsed time to the number of seconds that have passed 
		m_fSeconds += elapsedTime;

	}
	
	if( m_sRenderInput.size() == 9 && m_uncounter < m_unlength && m_bShowAlert == false )
	{
		m_unCurrentSet++;
		ChangeRenderSet( m_unCurrentSet );

	}	

	if( m_bShowAlert )
	{
		if( m_fAlertTimer >= 0.0f )
		{
			m_fAlertTimer -= elapsedTime;
		}
		else
		{
			m_bShowAlert = false;
		}
	}
	//if the number of seconds passed is less than 2 and the number of guessed letters is less than the number of letters in the qt event
	else if( m_fSeconds < m_fLetterTimer && m_uncounter < m_unlength && m_bShowAlert == false )
	{//if the user presses a button that is the same as the letter to be guessed
		SGD::Key output = m_vOutput[ m_uncounter ];

		if( output == m_kLastKeyPressed )
		{
			//Add the guess to the input vector
			AddGuess( m_kLastKeyPressed );

			//increase the number of letters guessed
			m_uncounter++;
			//set the timer back to 0
			m_fSeconds = 0.0f;

			m_fLetterTimer -= 0.125f;
		}//if there is any other button pressed the guess was wrong
		else if( m_kLastKeyPressed != SGD::Key::None )
		{
			//Add the wrong guess to the string
			AddGuess(  m_kLastKeyPressed  );
			//Boo the player
			SGD::AudioManager::GetInstance()->PlayAudio( Game::GetInstance()->m_mBoo );
			//Set num correct to the counter
			m_unNumCorrect = m_uncounter;
			//set the event over bool to true
			m_bqtOver = true;
		}
	}
	else
	{	
		if( m_uncounter < m_unlength )
		{
			SGD::AudioManager::GetInstance()->PlayAudio( Game::GetInstance()->m_mBoo );
		}
		else
		{
			SGD::AudioManager::GetInstance()->PlayAudio( Game::GetInstance()->m_mCheer );
		}

		//Set num correct to the counter
		m_unNumCorrect = m_uncounter;
		//set the event over bool to true
		m_bqtOver = true;
	}

	if( m_unLastPlayed < m_uncounter )
	{
		SGD::AudioManager * pAudio = SGD::AudioManager::GetInstance();

		switch( m_uncounter )
		{
			case 1:				
				pAudio->PlayAudio( Game::GetInstance()->m_mChime1 );
				break;
			case 2:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime2 );
				break;
			case 3:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime3 );
				break;
			case 4:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime4 );
				break;
			case 5:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime5 );
				break;
			case 6:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime6 );
				break;
			case 7:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime7 );
				break;
			case 8:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime8 );
				break;
			case 9:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime9 );
				break;
			case 10:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime10 );
				break;
			case 11:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime11 );
				break;
			case 12:
				pAudio->PlayAudio( Game::GetInstance()->m_mChime12 );
				break;
			default:
				break;
		}
		m_unLastPlayed++;
	}

	
}

void QuickTime::Render()
{

	

	SGD::Rectangle timer = SGD::Rectangle( 350 , 410 , 450 , 425 );

	
	BitmapFontManager* pFonts = pFonts->GetInstance();

	if( m_bShowAlert )
	{
		SGD::Rectangle rect = SGD::Rectangle( 150 , 300 , 615 , 450 );

		//SGD::GraphicsManager::GetInstance()->DrawRectangle( rect , SGD::Color( 220 , 215 , 143 ) );
		SGD::GraphicsManager::GetInstance()->DrawTextureSection( m_hScroll , SGD::Point( 150.0f , 300.0f ) , SGD::Rectangle( 0.0f , 0.0f , 465.0f , 290.0f ) , 0.0f , { } , { } , SGD::Size( 1.0f , 0.5f ) );
		pFonts->Render( "Goblin" , m_sAlert.c_str() , { 175 , 360 } , 1 , { 255 , 0 , 0, 0} );
	}
	else
	{
		//SGD::Rectangle rect = SGD::Rectangle( 250 , 300 , 550 , 450 );
		//SGD::GraphicsManager::GetInstance()->DrawRectangle( rect , SGD::Color( 220 , 215 , 143 ) );

		//Draw Scroll
		SGD::GraphicsManager::GetInstance()->DrawTextureSection( m_hScroll , SGD::Point( 150.0f , 300.0f ) , SGD::Rectangle( 0.0f , 0.0f , 465.0f , 290.0f ) , 0.0f , { } , { } , SGD::Size( 1.0f , 0.5f ) );

		// draw timer rect
		timer.right = timer.right - ( ( m_fSeconds / m_fLetterTimer ) * 100 );
		SGD::GraphicsManager::GetInstance()->DrawRectangle( timer , SGD::Color( 255 , 0 , 0 , 0 ) );

		//Draw text
		pFonts->Render( "Goblin" , m_sRenderOutput.c_str() , { 275 , 325 } , 2 , { 255 , 0 , 0 , 0 } );
		pFonts->Render( "Goblin" , m_sRenderInput.c_str() , { 275 , 340 } , 2 , { 255 , 255 , 255 , 255 } );
	}
	
}

void QuickTime::SetLength( unsigned int x )
{
	m_unlength = x;	

	for( unsigned int i = 0; i < m_unlength; i++ )
	{
		GenerateRandomLetter();
	}
	
	string temp = "";

	for( size_t i = 0; i < 3; i++ )
	{
		temp = m_sOutput[ i ];
		m_sRenderOutput += " ";
		m_sRenderOutput += temp;
		m_sRenderOutput += " ";

	}

}

void QuickTime::GenerateRandomLetter()
{
	int temp = rand() % 6;

	m_vOutput.push_back( m_vKeys[ temp ] );


	switch( m_vKeys[ temp ] )
	{
		case SGD::Key::Q:
		{
			m_sOutput += "Q";
		}
			break;
		case SGD::Key::W:
		{
			m_sOutput += "W";
		}
			break;
		case SGD::Key::E:
		{
			m_sOutput += "E";
		}
			break;
		case SGD::Key::A:
		{
			m_sOutput += "A";
		}
			break;
		case SGD::Key::S:
		{
			m_sOutput += "S";
		}
			break;
		case SGD::Key::D:
		{
			m_sOutput += "D";
		}
			break;
		case SGD::Key::Zero:
		{
			m_sOutput += "0";
		}
			break;
		case SGD::Key::One:
		{
			m_sOutput += "1";
		}
			break;
		case SGD::Key::Two:
		{
			m_sOutput += "2";
		}
			break;
		case SGD::Key::Three:
		{
			m_sOutput += "3";
		}
			break;
		case SGD::Key::Four:
		{
			m_sOutput += "4";
		}
			break;
		case SGD::Key::Five:
		{
			m_sOutput += "5";
		}
			break;
		
		default:
			break;
	}
}

void QuickTime::AddGuess( SGD::Key x )
{
	m_vInput.push_back( x );

	switch( x )
	{
		case SGD::Key::Q:
		{
			m_sInput += "Q";
			m_sRenderInput += " Q ";

		}
			break;
		case SGD::Key::W:
		{
			m_sInput += "W";
			m_sRenderInput += " W ";
		}
			break;
		case SGD::Key::E:
		{
			m_sInput += "E";
			m_sRenderInput += " E ";
		}
			break;
		case SGD::Key::A:
		{
			m_sInput += "A";
			m_sRenderInput += " A ";
		}
			break;
		case SGD::Key::S:
		{
			m_sInput += "S";
			m_sRenderInput += " S ";
		}
			break;
		case SGD::Key::D:
		{
			m_sInput += "D";
			m_sRenderInput += " D ";
		}
			break;
		case SGD::Key::Zero:
		{
			m_sInput += "0";
			m_sRenderInput += " 0 ";

		}
			break;
		case SGD::Key::One:
		{
			m_sInput += "1";
			m_sRenderInput += " 1 ";
		}
			break;
		case SGD::Key::Two:
		{
			m_sInput += "2";
			m_sRenderInput += " 2 ";
		}
			break;
		case SGD::Key::Three:
		{
			m_sInput += "3";
			m_sRenderInput += " 3 ";
		}
			break;
		case SGD::Key::Four:
		{
			m_sInput += "4";
			m_sRenderInput += " 4 ";
		}
			break;
		case SGD::Key::Five:
		{
			m_sInput += "5";
			m_sRenderInput += " 5 ";
		}
		default:
			break;
	}
}

void QuickTime::ChangeRenderSet( int set )
{
	m_sRenderInput.clear();
	m_sRenderOutput.clear();

	
	for( unsigned int i = ( set * 3 ); i < (( set * 3 )+3); i++ )
	{
		m_sRenderOutput += " ";
		m_sRenderOutput += m_sOutput[ i ];
		m_sRenderOutput += " ";

	}
}
