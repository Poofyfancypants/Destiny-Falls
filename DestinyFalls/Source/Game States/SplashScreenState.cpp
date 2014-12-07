#include "stdafx.h"
#include "SplashScreenState.h"

#include "../../SGD Wrappers/SGD_InputManager.h"
#include "MainMenuState.h"
#include "../Game Core/Game.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"


SplashScreenState* SplashScreenState::GetInstance()
{
	static SplashScreenState s_Instance;
	return &s_Instance;
}

void SplashScreenState::Enter()
{
	m_hImage = SGD::GraphicsManager::GetInstance()->LoadTexture( file.c_str() );

}

void SplashScreenState::Exit()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture( m_hImage );
}

bool SplashScreenState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();
	if( pInput->IsAnyKeyDown() )
	{
		//Main menu state here
		Game::GetInstance()->RemoveState();
		Game::GetInstance()->AddState( MainMenuState::GetInstance() );

	}

	return true;
}

void SplashScreenState::Update( float elapsedTime )
{

}

void SplashScreenState::Render()
{
	SGD::GraphicsManager::GetInstance()->DrawTextureSection( m_hImage , SGD::Point( 0.0f , 0.0f ), SGD::Rectangle(0.0f, 0.0f, 800.0f, 600.0f) );
}