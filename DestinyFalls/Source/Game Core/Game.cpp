/***************************************************************
|	File:		Game.cpp
|	Author:		Numi Stefansson
|	Course:		Structure of Game Desgin 1409.
|	Purpose:	Game class controls the SGD wrappers
|				& runs the game state machine
***************************************************************/

#include "stdafx.h"
#include "Game.h"

#include "../../SGD Wrappers/SGD_AudioManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_String.h"

#include "../Managers/TileManager.h"

#include <ctime>
#include <cstdlib>
#include <cassert>
#include <iostream>
#include <map>
#include <string>

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
		// Initialize the wrappers
	if( SGD::AudioManager::GetInstance()->Initialize() == false
		|| SGD::GraphicsManager::GetInstance()->Initialize( false ) == false
		|| SGD::InputManager::GetInstance()->Initialize() == false )
		return false;

	// Seed First!
	srand( (unsigned int)time( nullptr ) );
	rand();

	return true;	// success!
}


/**************************************************************/
// Update
//	- update the SGD wrappers
//	- run the current state
int Game::Update( void )
{

	SGD::GraphicsManager *pGraphics = SGD::GraphicsManager::GetInstance();
	pGraphics->DrawString("Test", SGD::Point(50,50),SGD::Color(255,150,150));

	/*TileManager tm;
	tm.Update();
*/
	return 0;		// keep playing!
}


/**************************************************************/
// Terminate
//	- exit the current state
//	- terminate the SGD wrappers
void Game::Terminate( void )
{


}

