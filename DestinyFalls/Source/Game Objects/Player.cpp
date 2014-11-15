#include "stdafx.h"
#include "Player.h"
#include "../Game Core/Game.h"
#include "../Game States/CombatState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Event.h"

#include "../Game States/GameplayState.h"

Player::Player() : Listener( this )
{
}

Player::~Player()
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
}

void Player::Update( float elapsedTime )
{
	if( !m_bSliding )
		m_nDirection = 0;


	TakeInput( elapsedTime );
	float speed = 500 * elapsedTime;

	switch( m_nDirection )
	{
	case 1:
		velocity = SGD::Vector( 0, -speed );
		break;
	case 2:
		velocity = SGD::Vector( 0, speed );
		break;
	case 3:
		velocity = SGD::Vector( -speed, 0 );
		break;
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

		if( m_bSliding && m_nDirection != 0 )
			m_bMoving = true;
	}
	else if (m_bSliding)
	{
		m_bMoving = false;
	}

}

void Player::Render( void )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Vector vec = { ( m_ptPosition.x ), ( m_ptPosition.y ) };
	SGD::Point point = { vec.x - ( m_szSize.width / 2 + GameplayState::GetInstance()->GetWorldCam().x ), vec.y - ( m_szSize.height / 2 + GameplayState::GetInstance()->GetWorldCam().y ) };

	SGD::Rectangle rec = GetRect();
	rec.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );

	pGraphics->DrawRectangle( rec, SGD::Color( 0, 0, 255 ) );

	pGraphics->DrawTextureSection( m_hImage, point, SGD::Rectangle{ 0, 0, 100, 100 } );


}

void Player::TakeInput( float elapsedTime )
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if( m_bMoving )
	{
		return;
	}
		if( pInput->IsKeyDown( SGD::Key::Up ) || pInput->IsKeyDown( SGD::Key::W ) )
		{
			m_nDirection = 1;
		}
		if( pInput->IsKeyDown( SGD::Key::Down ) || pInput->IsKeyDown( SGD::Key::S ) )
		{
			m_nDirection = 2;
		}

		if( pInput->IsKeyDown( SGD::Key::Left ) || pInput->IsKeyDown( SGD::Key::A ) )
		{
			m_nDirection = 3;
		}
		if( pInput->IsKeyDown( SGD::Key::Right ) || pInput->IsKeyDown( SGD::Key::D ) )
		{
			m_nDirection = 4;
		}
		//if( pInput->IsKeyDown(SGD::Key::M) )
		//{
		//	m_ptPosition = GetCheckpoint();
		//}
}

SGD::Rectangle Player::GetRect( void ) const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, ( m_ptPosition.x + m_szSize.width ), ( m_ptPosition.y + m_szSize.height ) };
	return sourceRect;
}

void Player::HandleEvent( const SGD::Event* pEvent ) /*override*/
{

}

void Player::HandleCollision( const iObject* pOther )
{
	if( pOther->GetType() == OBJ_ENEMY )
	{
		Game::GetInstance()->AddState( CombatState::GetInstance() );
	}
}