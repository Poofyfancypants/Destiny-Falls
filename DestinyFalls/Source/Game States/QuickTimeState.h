#pragma once
#include "../Quick Time/QuickTime.h"
#include "IGameState.h"

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

private:
	QuickTimeState() = default;
	virtual ~QuickTimeState() = default;



	QuickTime* currentQT = nullptr;
	bool m_bDoQt = false;

	QuickTimeState( const QuickTimeState& ) = delete;
	QuickTimeState& operator=( const QuickTimeState& ) = delete;
};

