#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "../Game States/CombatState.h"
#include "../Messages/DestroyObjectMessage.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Event.h"
#include "../Game States/GameplayState.h"

Enemy::Enemy() : Listener(this)
{
	m_pAnimator = m_pAnimator->GetInstance();

}


Enemy::~Enemy()
{
}

void Enemy::Update(float elapsedTime)
{

	if (abs(m_ptPosition.x - m_ptNextWaypoint.x) <= 5 && abs(m_ptPosition.y - m_ptNextWaypoint.y) <= 5)
	{
		m_nWaypointID++;
		GameplayState::GetInstance()->GetMap()->NextWaypoint((Enemy*)(this));
		if (m_nWaypointID >= 3)
			m_nWaypointID = 0;
	}
	else
	{
		SGD::Vector velocity;
		velocity = (m_vPath / 10) * elapsedTime;
		m_ptPosition += velocity;
	}
	m_pAnimator->GetInstance()->GetInstance()->Update( *this->GetTimeStamp() , elapsedTime );


}

void Enemy::Render()
{

	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Vector vec = { (m_ptPosition.x), (m_ptPosition.y) };
	//SGD::Point point = { vec.x - (m_szSize.width / 2 + GameplayState::GetInstance()->GetWorldCam().x), vec.y - (m_szSize.height / 2 + GameplayState::GetInstance()->GetWorldCam().y) };
	SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x, vec.y - GameplayState::GetInstance()->GetWorldCam().y };

	if (GameplayState::GetInstance()->GetDebugState())
	{
		SGD::Rectangle rec = GetRect();
		rec.Offset(-GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y);
		pGraphics->DrawRectangle(rec, SGD::Color(0, 0, 255));
	}
	m_pAnimator->GetInstance()->Render( *this->GetTimeStamp() , point.x,  point.y );

	//pGraphics->DrawTextureSection(m_hImage, point, SGD::Rectangle{ 0, 0, 100, 100 });
}

SGD::Rectangle Enemy::GetRect() const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, (m_ptPosition.x + m_szSize.width), (m_ptPosition.y + m_szSize.height) };
	return sourceRect;
}

void Enemy::HandleCollision(const iObject* pOther)
{
	if (!((Player*)pOther)->GetCombat())
	{
		DestroyObjectMessage* pMsg = new DestroyObjectMessage(this);
		pMsg->QueueMessage();
		pMsg = nullptr;

		((Player*)pOther)->SetCombat(true);
	}
}

void Enemy::HandleEvent(const SGD::Event* pEvent)
{

}

void Enemy::SetAnimation( int _id )
{
	switch( _id )
	{
		case 0:
			this->GetTimeStamp()->SetCurrentAnimation( "SpearMoblin" );
			break;
		case 1:
			this->GetTimeStamp()->SetCurrentAnimation( "SpearMoblin" );
			break;
		case 2:
			this->GetTimeStamp()->SetCurrentAnimation( "IronBall Soldier" );
			break;	
		case 3:
			this->GetTimeStamp()->SetCurrentAnimation( "Wizzrobe" );
			break;
		case 4:
			this->GetTimeStamp()->SetCurrentAnimation( "Eyegore" );
			break;
		default:
			break;
	}

	this->GetTimeStamp()->SetCurrentFrame( 0 );
	this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
}
