#pragma once
#include "Trap.h"
class FireTrap :
	public Trap
{

	int m_nDamage = 20;

public:
	FireTrap();
	~FireTrap();

	int GetDamage() {return m_nDamage;}

	virtual void Update( float elapsedTime ) override;
	virtual void Render( void ) override;
	virtual int GetType( void ) const { return OBJ_TRAP; }
	virtual SGD::Rectangle GetRect( void ) const override;
	virtual void HandleCollision( const iObject* pOther ) override;

};

