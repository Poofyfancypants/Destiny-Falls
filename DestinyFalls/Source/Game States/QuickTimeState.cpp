#include "stdafx.h"
#include "QuickTimeState.h"
#include "../Game Core/Game.h"
#include "../Game States/CombatState.h"
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
