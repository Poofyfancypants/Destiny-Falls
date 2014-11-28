#pragma once
#include "IGameState.h"
#include "../Managers/AnimationManager.h"
#include "../Engines/AnimationTimeStamp.h"
#include "../Quick Time/QuickTime.h"

class AnimationTestState :
	public IGameState
{
public:
	static AnimationTestState* GetInstance( void );

	void Enter();
	void Exit();

	bool Input();
	void Update( float elapsedTime );
	void Render();

	void RunQuickTime();
	void StopQuickTime();

private:
	AnimationTestState() = default;
	virtual ~AnimationTestState() = default;

	AnimationManager animator;
	AnimationTimeStamp ts;

	QuickTime* currentQT = nullptr;
	bool m_bDoQt = false;

	AnimationTestState( const AnimationTestState& ) = delete;
	AnimationTestState& operator=( const AnimationTestState& ) = delete;
};

