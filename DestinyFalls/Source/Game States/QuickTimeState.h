#pragma once
#include "../Quick Time/QuickTime.h"
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_Handle.h"

class QuickTimeState :
	public IGameState
{
public:
	static QuickTimeState* GetInstance( void );

	void Enter();
	void Exit();

	bool Input();
	void Update( float elapsedTime );
	void Render();

	void RunQuickTime();
	void StopQuickTime();

	void HandleTutorial();

	QuickTime* GetCurrentQT()const { return currentQT; }

private:
	QuickTimeState() = default;
	virtual ~QuickTimeState() = default;


	SGD::HAudio m_mQTMusic = SGD::INVALID_HANDLE;

	QuickTime* currentQT = nullptr;
	bool m_bDoQt = false;

	QuickTimeState( const QuickTimeState& ) = delete;
	QuickTimeState& operator=( const QuickTimeState& ) = delete;
};

