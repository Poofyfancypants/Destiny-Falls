#include "stdafx.h"
#include "FireTrap.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"


FireTrap::FireTrap()
{
}


FireTrap::~FireTrap()
{
}

void FireTrap::Update( float elapsedTime )
{

}
void FireTrap::Render( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Point point = { m_ptPosition.x - GameplayState::GetInstance()->GetWorldCam().x, m_ptPosition.y - GameplayState::GetInstance()->GetWorldCam().y };


	SGD::Rectangle rec = GetRect();
	rec.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
	// - Collision Rectangle
	pGraphics->DrawRectangle(rec, SGD::Color(255,0,0));
}
SGD::Rectangle FireTrap::GetRect( void ) const
{
	return Object::GetRect();
}
void FireTrap::HandleCollision( const iObject* pOther )
{

}