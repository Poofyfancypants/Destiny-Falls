#pragma once

#include "IGameState.h"

class PauseMenuState : public IGameState
{
public:

	enum PauseSelections{resume, save, options, exit};
	static PauseMenuState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

private:
	PauseMenuState() = default;
	virtual ~PauseMenuState() = default;

	PauseMenuState(const PauseMenuState&) = delete;
	PauseMenuState& operator=(const PauseMenuState&) = delete;

	void SaveGame();

	int m_nCursor = 0;

};

