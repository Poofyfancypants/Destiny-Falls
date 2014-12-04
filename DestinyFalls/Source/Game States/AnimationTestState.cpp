#include "stdafx.h"
#include "../Game Core/Game.h"
#include "AnimationTestState.h"
#include "MainMenuState.h"
#include "../../SGD Wrappers/SGD_InputManager.h"


AnimationTestState* AnimationTestState::GetInstance()
{
	static AnimationTestState s_Instance;
	return &s_Instance;
}

void AnimationTestState::Enter()
{
	/*string file = "resource/XML/TestAnimation.xml";
	animator.GetInstance()->Load( file );
	ts.SetCurrentAnimation( "test" );
	ts.SetCurrentFrame( 0 );
	ts.SetTimeOnFrame( 0.0f );*/
}

void AnimationTestState::Exit()
{
	//animator.DeleteInstance();
}

bool AnimationTestState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if( pInput->IsKeyPressed(SGD::Key::Enter ))
	{
		RunQuickTime();
	}

	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		Game::GetInstance()->RemoveState();
	}

	if( currentQT != nullptr )
	{
		currentQT->m_kLastKeyPressed = pInput->GetAnyKeyPressed();
	}
	

	return true;
}
	
void AnimationTestState::Update( float elapsedTime )
{
	//animator.GetInstance()->Update( ts , elapsedTime );
	if( m_bDoQt )
	{
		currentQT->Update( elapsedTime );

		if( currentQT->GetIsOver() == true )
		{
			StopQuickTime();
		}
	}
}

void AnimationTestState::Render()
{
	/*if( animator.GetInstance()->CheckSize() )
	{
		animator.GetInstance()->Render( ts , 100 , 100 );
	}*/

	if( m_bDoQt )
	{
		currentQT->Render(  );
	}
}

void AnimationTestState::RunQuickTime()
{
	m_bDoQt = true;
	if( currentQT == nullptr )
	{
		currentQT = new QuickTime;
		currentQT->SetLength( 12 );
	}
}
void AnimationTestState::StopQuickTime()
{
	m_bDoQt = false;
	delete currentQT;
	currentQT = nullptr;
}
