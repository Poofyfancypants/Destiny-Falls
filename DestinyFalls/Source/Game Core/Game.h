
#ifndef GAME_H
#define GAME_H

#include <vector>
#include "../../SGD Wrappers/SGD_Handle.h"
#include "../../SGD Wrappers/SGD_Declarations.h"

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
	static Game*	GetInstance(void);
	static void		DeleteInstance(void);


	/**********************************************************/
	// Setup, Play, Cleanup:
	bool Initialize(float width, float height);
	int	 Update(void);
	void Terminate(void);

	void AddState(IGameState* pNewState);	//Add to stack
	void RemoveState();						//Remove from stack
	void ClearStates();

	float GetScreenWidth(void) const { return m_fScreenWidth; }
	float GetScreenHeight(void) const { return m_fScreenHeight; }

	const BitmapFont*	GetFont(void) const	{ return m_pFont; }
	std::string GetString(int _string) { return m_StringTable[0][_string]; }

private:
	/**********************************************************/
	// Singleton Object:
	static Game*	s_pInstance;

	Game(void) = default;		// default constructor
	~Game(void) = default;		// destructor

	Game(const Game&) = delete;	// copy constructor
	Game& operator= (const Game&) = delete;	// assignment operator

	float m_fScreenWidth = 1;
	float m_fScreenHeight = 1;
	bool m_bWindowed = false;
	unsigned long m_ulGameTime = 0;

	int m_nCurrState = 0;
	std::string m_StringTable[1][10];

	std::vector<IGameState*> m_pStateStack;


	/**********************************************************/
	// Message Callback Function:
	static void MessageProc(const SGD::Message* pMsg);

	/**********************************************************/
	// Game Font
	BitmapFont*				m_pFont = nullptr;

};

#endif //GAME_H
