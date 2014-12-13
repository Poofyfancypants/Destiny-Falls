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
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	//pGraphics->SetClearColor( { 148, 99, 50 } );
	pGraphics->SetClearColor( { 64,47,25} );
	pGraphics->DrawTexture( Game::GetInstance()->GetLoadingScreenBkGround(), { 0, 0 }, 0, {}, {}, { .78f, 1.2f } );

	pGraphics->DrawTexture(m_hImage, { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f });
	BitmapFontManager::GetInstance()->Render("Other", "Press Any Key To Continue.", SGD::Point(275,500), 1, SGD::Color(0,0,0));

}