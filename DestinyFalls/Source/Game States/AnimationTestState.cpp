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
	string file = "resource/XML/TestAnimation.xml";
	animator.GetInstance()->Load( file );
	ts.SetCurrentAnimation( "test" );
	ts.SetCurrentFrame( 0 );
	ts.SetTimeOnFrame( 0.0f );
}

void AnimationTestState::Exit()
{
	animator.DeleteInstance();
}

bool AnimationTestState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyPressed(SGD::Key::Escape))
	{
		Game::GetInstance()->RemoveState();
	}

	return true;
}
	
void AnimationTestState::Update( float elapsedTime )
{
	animator.GetInstance()->Update( ts , elapsedTime );
}

void AnimationTestState::Render()
{
	if( animator.GetInstance()->CheckSize() )
	{
		animator.GetInstance()->Render( ts , 100 , 100 );
	}
}