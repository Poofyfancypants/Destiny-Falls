#include "stdafx.h"
#include "Boulder.h"
#include "Player.h"
#include "Object.h"
#include "../Game States/GameplayState.h"
#include "../Managers/BitmapFontManager.h"
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
	if( m_bButtonIndicator )
		m_fCounter += elapsedTime;

	if( m_fCounter >= 3 )
	{
		m_bButtonIndicator = false;
		m_fCounter = 0;
	}

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
	pGraphics->DrawTexture( m_hImage, point );

	if( m_bButtonIndicator )
	{
		SGD::Point pos = dynamic_cast<const Player*>( GameplayState::GetInstance()->GetPlayer() )->GetPosition();
		pos.x -= GameplayState::GetInstance()->GetWorldCam().x;
		pos.y -= GameplayState::GetInstance()->GetWorldCam().y;

		BitmapFontManager::GetInstance()->Render( "Dialog", "R", point, 1, SGD::Color( 255, 0, 0 ) );
	}

	if( GameplayState::GetInstance()->GetDebugState() )
	{

		SGD::Rectangle rec = GetRect();
		rec.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
		pGraphics->DrawRectangle( rec, SGD::Color( 0, 0, 0 ) );
	}


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
		m_bButtonIndicator = true;

		SGD::Point pos = dynamic_cast<const Player*>( pOther )->GetPosition();
		pos.x -= GameplayState::GetInstance()->GetWorldCam().x;
		pos.y -= GameplayState::GetInstance()->GetWorldCam().y;

		if( m_nDirection == 0 )
			m_nDirection = dynamic_cast<const Player*>( pOther )->GetDirection();

		if( pInput->IsKeyPressed( SGD::Key::R ) || pInput->IsButtonPressed(0,3) )
		{
			switch( m_nDirection )
			{
			case 1: // - Up
				m_nDirection = 2;
				m_ptPosition.y += 40;
				break;
			case 2: // - Down
				m_nDirection = 1;
				m_ptPosition.y -= 40;
				break;
			case 3: // - Left
				m_nDirection = 4;
				m_ptPosition.x += 40;
				break;
			case 4: // - Right
				m_nDirection = 3;
				m_ptPosition.x -= 40;
				break;
			}

		}
		if( pOther->GetType() == OBJ_BOULDER )
		{

			switch( m_nDirection )
			{
			case 1: // - Up
				m_ptPosition.y = pOther->GetRect().bottom + 3;
				break;
			case 2: // - Down
				m_ptPosition.y = pOther->GetRect().top - m_szSize.height - 3;
				break;
			case 3: // - Left
				m_ptPosition.x = pOther->GetRect().right + 3;
				break;
			case 4: // - Right
				m_ptPosition.x = pOther->GetRect().left - m_szSize.width - 3;
				break;
			default:
				break;
			}
			m_nDirection = 0;
		}
	}
}
