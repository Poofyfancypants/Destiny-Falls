#include "stdafx.h"
#include "Companion.h"
#include "../Game States/CombatState.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

Companion::Companion()
{
}


Companion::~Companion()
{
}

void Companion::Update( float elapsedTime )
{
	if( m_bUpdateAnimation )
	{
		m_pAnimator->GetInstance()->GetInstance()->Update( *this->GetTimeStamp() , elapsedTime );
	}
}

void Companion::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();


	SGD::Vector vec = { ( m_ptPosition.x ) , ( m_ptPosition.y ) };
	SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x , vec.y - GameplayState::GetInstance()->GetWorldCam().y };
	pGraphics->DrawTexture( m_hImage , point );

}


void Companion::CombatRender( int _posIndex )
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	switch( _posIndex )
	{
		case 0:
			if( m_pAnimator->GetInstance()->CheckSize() )
			{
				m_pAnimator->GetInstance()->Render( *this->GetTimeStamp() , Companion1rect.right , Companion1rect.bottom );
			}
			break;
		case 1:
			if( m_pAnimator->GetInstance()->CheckSize() )
			{
				m_pAnimator->GetInstance()->Render( *this->GetTimeStamp() , Companion2rect.right , Companion2rect.bottom );
			}
			break;

		default:
			break;
	}
}

bool Companion::TakeTurn( float elapsedTime )
{
	CombatState* pCombat = CombatState::GetInstance();

	switch( GetCoType() )
	{
		case Cleric:
		{

		}
			break;
		case Melee:
		{

		}
			break;
		case Mage:
		{

		}
			break;
		case Tank:
		{

		}
			break;
		default:
			break;
	}

	m_bUpdateAnimation = true;
	this->GetTimeStamp()->SetCurrentFrame( 0 );
	this->GetTimeStamp()->SetTimeOnFrame( 0.0f );

	return true;
}

void Companion::SetCompanionAnimation( int companionType )
{
	m_pAnimator = m_pAnimator->GetInstance();

	switch( companionType )
	{
		case 1:
			this->GetTimeStamp()->SetCurrentAnimation( "ClericAttack" );
			break;
		case 2:
			this->GetTimeStamp()->SetCurrentAnimation( "Companion1Attack" );
			break;
		case 3:
			this->GetTimeStamp()->SetCurrentAnimation( "RangerAttack" );
			break;
		case 4:
			this->GetTimeStamp()->SetCurrentAnimation( "RangerAttack" );
			break;
		default:
			break;
	}

	this->GetTimeStamp()->SetCurrentFrame( 0 );
	this->GetTimeStamp()->SetTimeOnFrame( 0.0f );

}