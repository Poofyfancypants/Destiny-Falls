#pragma once
#include "../Game Core/Game.h"
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../Managers/ParticleManager.h"

class CreditState :
	public IGameState
{
public:
	static CreditState* GetInstance();

	virtual void Enter( void )				override;
	virtual void Exit( void )					override;
	virtual bool Input( void )				override;
	virtual void Update( float elapsedTime )	override;
	virtual void Render( void )				override;

private:
	CreditState() = default;
	virtual ~CreditState() = default;

	CreditState( const CreditState& ) = delete;
	CreditState& operator=( const CreditState& ) = delete;


	SGD::HTexture m_hBackground;
	vector<string> m_vCredits;
	vector<float> m_vScrollCount;
	float Timer = 20.0f;
	ParticleManager m_particle;

	float		m_fScroll = 0;
	float	m_fSecond = 0;

	bool m_bExit =false;
};

