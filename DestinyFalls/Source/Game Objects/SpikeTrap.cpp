#include "stdafx.h"
#include "SpikeTrap.h"

#include "Player.h"

#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../Game States/GameplayState.h"

SpikeTrap::SpikeTrap()
{
}


SpikeTrap::~SpikeTrap()
{
}


void SpikeTrap::Update( float elapsedTime )
{

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
	pGraphics->DrawRectangle( rec, SGD::Color() );
}
SGD::Rectangle SpikeTrap::GetRect( void ) const
{
	return Object::GetRect();
}
void SpikeTrap::HandleCollision( const iObject* pOther )
{

}