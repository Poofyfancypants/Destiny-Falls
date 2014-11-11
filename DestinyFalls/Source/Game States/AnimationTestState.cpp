#include "stdafx.h"
#include "AnimationTestState.h"
#include "MainMenuState.h"


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