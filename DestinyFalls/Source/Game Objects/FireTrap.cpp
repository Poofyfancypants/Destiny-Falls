#include "stdafx.h"
#include "FireTrap.h"
#include "../Messages/DestroyObjectMessage.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_Event.h"

FireTrap::FireTrap()
{
}


FireTrap::~FireTrap()
{
}

void FireTrap::Update( float elapsedTime )
{
	if( m_bStartTimer )
		m_fTimer += elapsedTime;

	if( m_fTimer >= .2 )
	{
		DestroyObjectMessage* pMsg = new DestroyObjectMessage( this );
		pMsg->QueueMessage();
		pMsg = nullptr;

	}
}
void FireTrap::Render( void )
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
	//SGD::Rectangle rec = GetRect();
//	rec.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
	// - Collision Rectangle

	pGraphics->DrawTexture(m_hImage, point);
	//pGraphics->DrawRectangle( rec, SGD::Color( 255, 0, 0 ) );
}
SGD::Rectangle FireTrap::GetRect( void ) const
{
	return Object::GetRect();
}
void FireTrap::HandleCollision( const iObject* pOther )
{
	if( pOther->GetType() == iObject::OBJ_PLAYER )
	{
		if( !m_bStartTimer )
			m_bStartTimer = true;
	}
}