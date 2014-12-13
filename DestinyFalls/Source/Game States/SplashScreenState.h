#pragma once
#include "IGameState.h"
#include "..\..\SGD Wrappers\SGD_Handle.h"
#include <string>
using namespace std;

class SplashScreenState : public IGameState
{
public:
	static SplashScreenState* GetInstance( void );

	void Enter();
	void Exit();

	bool Input();
	void Update( float elapsedTime );
	void Render();

private:

	string file = "resource/graphics/1411_Turn5_logo.png";
	SGD::HTexture m_hImage = SGD::INVALID_HANDLE;

	SplashScreenState() = default;
	virtual ~SplashScreenState() = default;



	SplashScreenState( const SplashScreenState& ) = delete;
	SplashScreenState& operator=( const SplashScreenState& ) = delete;
};

