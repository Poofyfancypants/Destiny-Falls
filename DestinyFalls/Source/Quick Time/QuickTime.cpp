#include "stdafx.h"
#include "QuickTime.h"

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
	
	//push back buttons into the key vector
	m_vKeys.push_back( SGD::Key::Q );
	m_vKeys.push_back( SGD::Key::W );
	m_vKeys.push_back( SGD::Key::E );
	m_vKeys.push_back( SGD::Key::A );
	m_vKeys.push_back( SGD::Key::S );
	m_vKeys.push_back( SGD::Key::D );

	//clear out the input and output vectors
	m_vInput.clear();
	m_vOutput.clear();

	//set the qtover bool to false
	m_bqtOver = false;
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
	else if( m_fSeconds < 2.0f && m_uncounter < m_unlength && m_bShowAlert == false)
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
	SGD::Rectangle rect = { 250 , 300 , 300 , 350 };

	SGD::GraphicsManager::GetInstance()->DrawRectangle( rect , SGD::Color { 255 , 100 , 100 , 100 } );

	//const BitmapFont* pFont = Game::GetInstance()->GetFont();
	BitmapFontManager* pFonts = pFonts->GetInstance();
	if( m_bShowAlert )
	{
		pFonts->Render( "Other" , m_sAlert.c_str() , { 275 , 310 } , 1 , { 255 , 255 , 255 , 255 } );
	}
	else
	{
		pFonts->Render( "Other" , m_sRenderOutput.c_str() , { 275 , 310 } , 2 , { 255 , 255 , 255 , 0 } );
		pFonts->Render( "Other" , m_sRenderInput.c_str() , { 275 , 325 } , 2 , { 255 , 51 , 51 , 255 } );
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

	//create a pointer to the input manager
	/*SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	char l = *pInput->GetKeyName( m_vKeys[ temp ] );

	m_sOutput += l;*/

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
