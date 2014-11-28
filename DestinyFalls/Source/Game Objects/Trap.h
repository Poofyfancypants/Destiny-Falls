#pragma once
#include "StaticObject.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
class Trap :
	public StaticObject
{
public:
	Trap();
	~Trap();

	virtual int GetDamage() const = 0;

	virtual void Update( float elapsedTime ) override;
	virtual void Render( void ) override;
	virtual int GetType( void ) const { return OBJ_TRAP; }
	virtual SGD::Rectangle GetRect( void ) const override;
	virtual void HandleCollision( const iObject* pOther ) override;
};

