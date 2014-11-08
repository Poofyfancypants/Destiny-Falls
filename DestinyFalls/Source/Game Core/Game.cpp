#include "stdafx.h"
#include "Game.h"

#include <ctime>
#include <cstdlib>
#include <cassert>

#include "../Game States/IGameState.h"
#include "../Game States/MainMenuState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>


/**************************************************************/
// Singleton
//	- instantiate the static member
/*static*/ Game* Game::s_pInstance = nullptr;

// GetInstance
//	- allocate the ONE instance & return it
/*static*/ Game* Game::GetInstance( void )
{
	if( s_pInstance == nullptr )
		s_pInstance = new Game;

	return s_pInstance;
}

// DeleteInstance
//	- deallocate the ONE instance
/*static*/ void Game::DeleteInstance( void )
{
	delete s_pInstance;
	s_pInstance = nullptr;
}


/**************************************************************/
// Initialize
//	- initialize the SGD wrappers
//	- enter the Main Menu state
bool Game::Initialize( float width, float height )
{
	// Seed First!
	srand( (unsigned int)time( nullptr ) );
	rand();

	if (SGD::AudioManager::GetInstance()->Initialize() == false
		|| SGD::GraphicsManager::GetInstance()->Initialize(false) == false
		|| SGD::InputManager::GetInstance()->Initialize() == false)
		return false;

	m_fScreenWidth = width;
	m_fScreenHeight = height;

	//Main menu state here
	AddState(MainMenuState::GetInstance());

	return true;	// success!
}


/**************************************************************/
// Update
//	- update the SGD wrappers
//	- run the current state
int Game::Update( void )
{
	// Update the wrappers
	if (SGD::AudioManager::GetInstance()->Update() == false
		|| SGD::GraphicsManager::GetInstance()->Update() == false
		|| SGD::InputManager::GetInstance()->Update() == false)
		return -10;		// exit FAILURE!


	unsigned long now = GetTickCount();					// current time in milliseconds
	float elapsedTime = (now - m_ulGameTime) / 1000.0f;	// convert to fraction of a second

	m_ulGameTime = now;

	// Cap the elapsed time to 1/8th of a second
	if (elapsedTime >= 0.125f)
		elapsedTime = 0.125f;

	int pCurrent = m_nCurrState;
	// Let the current state handle input
	if (m_pStateStack[m_nCurrState]->Input() == false)
		return 1;	// exit success!

	// Update & render the current state if it was not changed
	if (m_nCurrState == pCurrent)
	{
		m_pStateStack[m_nCurrState]->Update(elapsedTime);
		m_pStateStack[m_nCurrState]->Render();
	}

	return 0;		// keep playing!
}


/**************************************************************/
// Terminate
//	- exit the current state
//	- terminate the SGD wrappers
void Game::Terminate( void )
{

	// Terminate the core SGD wrappers
	SGD::AudioManager::GetInstance()->Terminate();
	SGD::AudioManager::DeleteInstance();

	SGD::GraphicsManager::GetInstance()->Terminate();
	SGD::GraphicsManager::DeleteInstance();

	SGD::InputManager::GetInstance()->Terminate();
	SGD::InputManager::DeleteInstance();
}

void Game::AddState(IGameState* pNewState)
{
	m_pStateStack.push_back(pNewState);
	m_nCurrState = m_pStateStack.size() - 1;
	m_pStateStack[m_nCurrState]->Enter();
}

void Game::RemoveState()
{
	m_pStateStack[m_nCurrState]->Exit();
	m_pStateStack.pop_back();
	m_nCurrState--;
}