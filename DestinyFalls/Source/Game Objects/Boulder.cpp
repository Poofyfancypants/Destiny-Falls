#include "stdafx.h"
#include "Boulder.h"
#include "Player.h"
#include "Object.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"

Boulder::Boulder()
{
}


Boulder::~Boulder()
{

}

void Boulder::Update( float elapsedTime )
{
	float speed = 500 * elapsedTime;
	SGD::Vector velocity;
		switch( m_nDirection )
		{
			// - Slide Up
		case 1:
			velocity = SGD::Vector( 0, -speed );
			break;
			// - Side Down
		case 2:
			velocity = SGD::Vector( 0, speed );
			break;
			// - Slide Left
		case 3:
			velocity = SGD::Vector( -speed, 0 );
			break;
			// - Slide Right
		case 4:
			velocity = SGD::Vector( speed, 0 );
			break;
		default:
			velocity = SGD::Vector();
			break;
		}
		SGD::Point futurePos = m_ptPosition + velocity;
		if( !GameplayState::GetInstance()->GetMap()->TileCollision( this, futurePos ) )
		{
			m_ptPosition = futurePos;
		}
		else
			m_nDirection = 0;
}

void Boulder::Render( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::Vector vec = { ( m_ptPosition.x ), ( m_ptPosition.y ) };
	SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x, vec.y - GameplayState::GetInstance()->GetWorldCam().y };


	SGD::Rectangle rec = GetRect();
	rec.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
	// - Collision Rectangle
	//pGraphics->DrawRectangle( rec, SGD::Color( 0, 0, 0 ) );

	pGraphics->DrawTexture( m_hImage, point );

}
SGD::Rectangle Boulder::GetRect( void ) const
{
	return Object::GetRect();
}
void Boulder::HandleCollision( const iObject* pOther )
{
	SGD::InputManager *pInput = SGD::InputManager::GetInstance();
	SGD::GraphicsManager *pGraphics = SGD::GraphicsManager::GetInstance();


	if( pOther->GetType() == OBJ_PLAYER )
	{
		SGD::Point pos = dynamic_cast<const Player*>( pOther )->GetPosition();
		pos.x -= GameplayState::GetInstance()->GetWorldCam().x;
		pos.y -= GameplayState::GetInstance()->GetWorldCam().y;

		pGraphics->DrawString( "R", pos, SGD::Color( 255, 0, 0 ) );
		m_nDirection = dynamic_cast<const Player*>( pOther )->GetDirection();

		if( pInput->IsKeyPressed( SGD::Key::R ) )
		{
			switch( m_nDirection )
			{
			case 1:
				m_nDirection = 2;
				break;
			case 2:
				m_nDirection = 1;
				break;
			case 3:
				m_nDirection = 4;
				break;
			case 4:
				m_nDirection = 3;
				break;
			}

		}
	}
}
