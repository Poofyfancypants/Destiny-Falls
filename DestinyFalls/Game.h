/***************************************************************
|	File:		Game.h
|	Author:		Numi Stefansson
|	Course:		Structure of Game Design  1409.
|	Purpose:	Game class controls the SGD wrappers
|				& runs the game state machine
***************************************************************/

#ifndef GAME_H
#define GAME_H

#include <vector>
#include "SGD Wrappers/SGD_Handle.h"
/**************************************************************/
// Forward class declaration
//	- tells the compiler that the type exists
//	- allows us to create pointers or references
class BitmapFont;
class IGameState;


/**************************************************************/
// Game class
//	- runs the game logic
//	- controls the SGD wrappers
//	- SINGLETON!
//		- there is only ONE instance
//		- global access method (GetInstance)
class Game
{
public:
	/**********************************************************/
	// Singleton Accessors:
	static Game*	GetInstance( void );
	static void		DeleteInstance( void );


	/**********************************************************/
	// Setup, Play, Cleanup:
	bool Initialize( float width, float height );
	int	 Update( void );
	void Terminate( void );


private:
	/**********************************************************/
	// Singleton Object:
	static Game*	s_pInstance;

	Game( void ) = default;		// default constructor
	~Game( void ) = default;		// destructor

	Game( const Game& ) = delete;	// copy constructor
	Game& operator= ( const Game& ) = delete;	// assignment operator


};

#endif //GAME_H
