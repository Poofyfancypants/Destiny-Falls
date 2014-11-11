#pragma once
#include "IGameState.h"
#include "../Managers/AnimationManager.h"
#include "../Engines/AnimationTimeStamp.h"

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

private:
	AnimationTestState() = default;
	virtual ~AnimationTestState() = default;

	AnimationManager animator;
	AnimationTimeStamp ts;

	AnimationTestState( const AnimationTestState& ) = delete;
	AnimationTestState& operator=( const AnimationTestState& ) = delete;
};

