#include "stdafx.h"
#include <Windows.h>
#include "QuickTimeState.h"
#include "../Game Core/Game.h"
#include "../Game States/CombatState.h"
#include "../Game States/GameplayState.h"
#include "MainMenuState.h"
#include "../../SGD Wrappers/SGD_InputManager.h"

QuickTimeState* QuickTimeState::GetInstance()
{
	static QuickTimeState s_Instance;
	return &s_Instance;
}

void QuickTimeState::Enter()
{

	RunQuickTime();
}

void QuickTimeState::Exit()
{

}

bool QuickTimeState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if( pInput->IsKeyPressed( SGD::Key::Escape ) )
	{
		Game::GetInstance()->RemoveState();
	}

	if( currentQT != nullptr )
	{
		currentQT->m_kLastKeyPressed = pInput->GetAnyKeyPressed();
	}


	return true;
}

void QuickTimeState::Update( float elapsedTime )
{

	if( m_bDoQt )
	{
		CombatState::GetInstance()->DrawBackground();
		currentQT->Update( elapsedTime );

		if( currentQT->GetIsOver() == true )
		{
			CombatState::GetInstance()->SetNumQTCorrect( currentQT->GetNumCorrect() );
			StopQuickTime();
			Game::GetInstance()->RemoveState();
		}
	}
}

void QuickTimeState::Render()
{
	CombatState::GetInstance()->Render();
	if( GameplayState::GetInstance()->GetCurrentLevel() == 0 )
		HandleTutorial();
	if( m_bDoQt )
	{
		currentQT->Render();
	}
}

void QuickTimeState::RunQuickTime()
{


	m_bDoQt = true;
	if( currentQT == nullptr )
	{
		currentQT = new QuickTime;
		currentQT->SetLength( 12 );
	}
}
void QuickTimeState::StopQuickTime()
{
	m_bDoQt = false;
	delete currentQT;
	currentQT = nullptr;
}

void QuickTimeState::HandleTutorial()
{
	if( GameplayState::GetInstance()->GetCurrentLevel() == 0 )
	{
		SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
		BitmapFontManager *pFont = BitmapFontManager::GetInstance();

		SGD::Point ptWorldCam = GameplayState::GetInstance()->GetWorldCam();

		SGD::Point heroPosition;
		SGD::Point portraitPosition;
		// - Location of the Dialog Box at the bottom of the screen.

		SGD::Rectangle DialogBoxOne;
		DialogBoxOne.left = 25;
		DialogBoxOne.top = Game::GetInstance()->GetScreenHeight() - 105;
		DialogBoxOne.right = Game::GetInstance()->GetScreenWidth() - 25;
		DialogBoxOne.bottom = Game::GetInstance()->GetScreenHeight() - 5;

		// - Location to print the strings within the dialog Box
		SGD::Point TextPositionOne;
		SGD::Point TextPositionTwo;

		TextPositionOne.x = DialogBoxOne.left + 40;
		TextPositionOne.y = DialogBoxOne.top + 20;
		TextPositionTwo.x = DialogBoxOne.left + 20;
		TextPositionTwo.y = DialogBoxOne.top + 50;

		portraitPosition.x = DialogBoxOne.left - 10;
		portraitPosition.y = DialogBoxOne.top - 30;

		if( Game::GetInstance()->GetIcelandic() )
		{
			TextPositionOne.x = DialogBoxOne.left + 50;
			TextPositionTwo.x = DialogBoxOne.left + 50;
		}
		else
		{
			TextPositionOne.x = DialogBoxOne.left + 100;
			TextPositionTwo.x = DialogBoxOne.left + 100;
		}

		heroPosition = { (float)( ( 3 * 32 ) - ptWorldCam.x ), (float)( ( 8 * 32 ) - ptWorldCam.y ) };

		pGraphics->DrawRectangle( DialogBoxOne, SGD::Color( 220, 215, 143 ), SGD::Color( 0, 0, 0 ) );
		pGraphics->DrawTexture( GameplayState::GetInstance()->GetPortrait(), portraitPosition );
		pFont->Render( "Dialog", Game::GetInstance()->GetString( 9, 7 ).c_str(), TextPositionOne, .7f, SGD::Color( 0, 0, 0 ) );
		pFont->Render( "Dialog", Game::GetInstance()->GetString( 9, 8 ).c_str(), TextPositionTwo, .7f, SGD::Color( 0, 0, 0 ) );

		//Sleep( 3000 );
	}
}