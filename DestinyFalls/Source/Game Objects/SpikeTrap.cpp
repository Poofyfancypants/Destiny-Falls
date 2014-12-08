#include "stdafx.h"
#include "SpikeTrap.h"
#include "Player.h"

#include "../Game States/GameplayState.h"
#include "../Game States/GameplayState.h"

#include "../../SGD Wrappers/SGD_Event.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

#include "../Messages/DestroyObjectMessage.h"

SpikeTrap::SpikeTrap()
{
}


SpikeTrap::~SpikeTrap()
{
}


void SpikeTrap::Update( float elapsedTime )
{
	if( m_bStartTimer )
		m_fTimer += elapsedTime;

	if( m_fTimer >= .2 )
	{
		// do what ever
	}
}
void SpikeTrap::Render( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Point point = { m_ptPosition.x - GameplayState::GetInstance()->GetWorldCam().x, m_ptPosition.y - GameplayState::GetInstance()->GetWorldCam().y };

	if( GameplayState::GetInstance()->GetDebugState() )
	{
		SGD::Rectangle rec = GetRect();
		rec.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
		pGraphics->DrawRectangle( rec, SGD::Color( 0, 0, 255 ) );
	}

	// - Temp Code till we have sprites.
	SGD::Rectangle rec = GetRect();
	rec.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
	// - Collision Rectangle
	//pGraphics->DrawRectangle( rec, SGD::Color() );

	pGraphics->DrawTexture(m_hImage, point);
}
SGD::Rectangle SpikeTrap::GetRect( void ) const
{
	return Object::GetRect();
}
void SpikeTrap::HandleCollision( const iObject* pOther )
{
	if( pOther->GetType() == iObject::OBJ_PLAYER )
	{
		if( !m_bStartTimer )
			m_bStartTimer = true;
	}
}