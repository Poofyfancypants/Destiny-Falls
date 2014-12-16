#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"

#include <map>
#include <string.h>
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
	float m_fArcadeTimer = 0.0f;

	OptionsState() = default;
	virtual ~OptionsState() = default;

	OptionsState(const OptionsState&) = delete;
	OptionsState& operator=(const OptionsState&) = delete;

	int m_nCursor = 1;
	bool m_hWindow;
	// height 40

	std::map<std::string, SGD::Rectangle> m_mMouseoverRects;
	SGD::HAudio m_hBackMusic;
	SGD::HAudio m_hEffectSound;
	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;
	SGD::HTexture m_hButton = SGD::INVALID_HANDLE;
	SGD::HTexture m_hButtonHighlighted = SGD::INVALID_HANDLE;
	SGD::HTexture m_hArrow = SGD::INVALID_HANDLE;

};

