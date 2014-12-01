#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../Managers/ParticleManager.h"

class CreditState :
	public IGameState
{
public:
	static CreditState* GetInstance();

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

private:
	CreditState() = default;
	virtual ~CreditState() = default;

	CreditState(const CreditState&) = delete;
	CreditState& operator=(const CreditState&) = delete;


	SGD::HAudio m_haBackground;
	SGD::HTexture m_htBackground;

	float Timer = 20.0f;
	ParticleManager m_particle;

};

