#pragma once

#include "IGameState.h"

class DeathState : public IGameState
{
public:

	enum PauseSelections{ resume, save, exit };

	static DeathState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

private:

	DeathState() = default;
	virtual ~DeathState() = default;

	DeathState(const DeathState&) = delete;
	DeathState& operator=(const DeathState&) = delete;

	int m_nCursor = 0;
};
