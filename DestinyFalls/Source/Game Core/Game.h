
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <Windows.h>
#include "../../SGD Wrappers/SGD_Handle.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../Managers/BitmapFontManager.h"
#include "../Managers/AnimationManager.h"
#include "../Managers/DialogManager.h"

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

	void AddState( IGameState* pNewState );	//Add to stack
	void RemoveState();						//Remove from stack
	void ClearStates();
	IGameState* GetCurrentState() const { return m_pStateStack[m_nCurrState]; }

	float GetScreenWidth( void ) const { return m_fScreenWidth; }
	float GetScreenHeight( void ) const { return m_fScreenHeight; }
	 SGD::HTexture GetLoadingScreenBkGround() const {return m_hLoadingBackground;}
	 SGD::HTexture GetGameIcon() const {return m_hLogo;}
	void LoadingScreen( string _loading );
	//const BitmapFont*	GetFont(void) const	{ return m_pFont; }
	std::string GetString( int _type, int _string ) { return m_StringTable[_type][_string]; }

	SGD::HAudio m_mButton = SGD::INVALID_HANDLE;
	SGD::HAudio m_mMagicButton = SGD::INVALID_HANDLE;
	SGD::HAudio m_mMeleeButton = SGD::INVALID_HANDLE;
	SGD::HAudio potionSound = SGD::INVALID_HANDLE;
	SGD::HAudio deathSound = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime1 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime2 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime3 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime4 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime5 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime6 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime7 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime8 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime9 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime10 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime11 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mChime12 = SGD::INVALID_HANDLE;
	SGD::HAudio m_mBoo = SGD::INVALID_HANDLE;
	SGD::HAudio m_mCheer = SGD::INVALID_HANDLE;
	SGD::HAudio m_mWinMusic = SGD::INVALID_HANDLE;



	// Combat backgrounds
	SGD::HTexture m_hEarth1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hEarth2 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hEarth3 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hEarth4 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hIce1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hIce2 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hIce3 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hIce4 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hIce5 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hIce6 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hAir1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hAir2 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hAir3 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hAir4 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hFire1 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hFire2 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hFire3 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hFire4 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hFinal1 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hFinal2 = SGD::INVALID_HANDLE;
	//SGD::HTexture m_hFinal3 = SGD::INVALID_HANDLE;

	SGD::HTexture m_hFireIcon = SGD::INVALID_HANDLE;
	SGD::HTexture m_hWaterIcon = SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirIcon = SGD::INVALID_HANDLE;
	SGD::HTexture m_hEarthIcon = SGD::INVALID_HANDLE;


	int GetFrames() { return m_nFPS; }
	// Menu backgrounds
	SGD::HTexture m_hSaveLoad = SGD::INVALID_HANDLE;
	SGD::HTexture m_hHTP = SGD::INVALID_HANDLE;

	// - Accessor
	bool GetWindowed() const { return m_bWindowed; }
	void SetWindowd( bool _window ) { m_bWindowed = _window; }
	SGD::HAudio GetAudio() { return m_hMusic; }
	// - Icelandic
	bool GetIcelandic() const { return m_bIcelandic; }
	void SetIcelandic( bool _that ) { m_bIcelandic = _that; }
	void LoadStrings();

private:
	/**********************************************************/
	// Singleton Object:
	static Game*	s_pInstance;

	Game( void ) = default;		// default constructor
	~Game( void ) = default;		// destructor

	Game( const Game& ) = delete;	// copy constructor
	Game& operator= ( const Game& ) = delete;	// assignment operator

	float m_fScreenWidth = 1;
	float m_fScreenHeight = 1;
	bool m_bWindowed = false;
	unsigned long m_ulGameTime = 0;

	bool fullscreen = false;

	int m_nCurrState = 0;
	std::string m_StringTable[15][10];

	std::vector<IGameState*> m_pStateStack;
	AnimationManager* m_pAnimator;



	/**********************************************************/
	// Message Callback Function:
	static void MessageProc( const SGD::Message* pMsg );

	/**********************************************************/
	// Game Font
	//BitmapFont*				m_pFont = nullptr;
	BitmapFontManager * m_pFonts = nullptr;
	DialogManager* m_pDialogs;

	// - FPS
	bool m_bDebug = false;
	float m_fFPSTime = 0;
	int m_nFrames = 0;
	int m_nFPS = 60;

	// - Icelandic
	bool m_bIcelandic = false;

	// - Loading Screen
	SGD::HTexture m_hLogo;
	SGD::HTexture m_hLoadingBackground;
	SGD::HAudio m_hMusic;


};


#endif //GAME_H
