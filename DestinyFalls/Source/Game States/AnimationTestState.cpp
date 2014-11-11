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
	string file = "resource/XML/AnimationTestXML.xml";
	animator.GetInstance()->Load( file );
	ts.SetCurrentAnimation( "SwordSwing" );
	ts.SetCurrentFrame( 0 );
	ts.SetTimeOnFrame( 0.0f );
}

void AnimationTestState::Exit()
{

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
	animator.GetInstance()->Render( ts , 100 , 100 );
}