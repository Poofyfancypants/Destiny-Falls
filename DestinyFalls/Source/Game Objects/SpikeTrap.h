#pragma once
#include "Trap.h"
class SpikeTrap :
	public Trap
{
	int m_nDamage = 3;
	float m_fTimer = 0;
	bool m_bStartTimer = false;

public:
	SpikeTrap();
	~SpikeTrap();

	virtual int GetDamage() const {return m_nDamage;}

	virtual void Update( float elapsedTime ) override;
	virtual void Render( void ) override;
	virtual int GetType( void ) const { return OBJ_TRAP; }
	virtual SGD::Rectangle GetRect( void ) const override;
	virtual void HandleCollision( const iObject* pOther ) override;
};

