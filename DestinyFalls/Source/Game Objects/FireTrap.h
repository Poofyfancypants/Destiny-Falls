#pragma once
#include "Trap.h"
#include "../Managers/ParticleManager.h"

class FireTrap :
	public Trap
{

	int m_nDamage = 1;
	float m_fTimer = 0;
	bool m_bStartTimer = false;
	ParticleManager m_pParticle;
public:
	FireTrap();
	~FireTrap();

	virtual int GetDamage() const {return m_nDamage;}

	virtual void Update( float elapsedTime ) override;
	virtual void Render( void ) override;
	virtual int GetType( void ) const { return OBJ_TRAP; }
	virtual SGD::Rectangle GetRect( void ) const override;
	virtual void HandleCollision( const iObject* pOther ) override;

};

