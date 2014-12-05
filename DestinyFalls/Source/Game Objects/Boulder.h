#pragma once
#include "StaticObject.h"

class Boulder :
	public StaticObject
{


	int m_nDirection = 0;
	float m_fCounter = 0;
	bool m_bButtonIndicator = false;
public:
	Boulder();
	~Boulder();


	virtual void Update( float elapsedTime ) override;
	virtual void Render( void ) override;
	virtual int GetType( void ) const { return OBJ_BOULDER; }
	virtual SGD::Rectangle GetRect( void ) const override;
	virtual void HandleCollision( const iObject* pOther ) override;

};

