#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

class WinState :
	public IGameState
{
public:
	static WinState* GetInstance();

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

private:
	WinState() = default;
	virtual ~WinState() = default;

	WinState(const WinState&) = delete;
	WinState& operator=(const WinState&) = delete;


	SGD::HAudio m_haBackground;
	SGD::HTexture m_htBackground;
};