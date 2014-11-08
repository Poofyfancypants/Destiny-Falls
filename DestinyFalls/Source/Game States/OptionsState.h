#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"

class OptionsState :
	public IGameState
{
public:
	static OptionsState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

private:
	OptionsState() = default;
	virtual ~OptionsState() = default;

	OptionsState(const OptionsState&) = delete;
	OptionsState& operator=(const OptionsState&) = delete;

	int m_nMusic;
	int m_nEffects;
	int m_nScreen;

	int m_nCursor;
	bool m_bSelect;
	bool m_bWindowed;

	SGD::HAudio m_hBackMusic;
	SGD::HAudio m_hEffectSound;
};

