#pragma once
#include "IGameState.h"
class HowToPlayState :
	public IGameState
{
public:
	static HowToPlayState* GetInstance();

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;
	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;


private:
	HowToPlayState() = default;
	virtual ~HowToPlayState() = default;

	HowToPlayState(const HowToPlayState&) = delete;
	HowToPlayState& operator=(const HowToPlayState&) = delete;
};

