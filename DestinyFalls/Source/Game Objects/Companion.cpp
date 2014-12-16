#include "stdafx.h"
#include "Companion.h"
#include "../Game States/CombatState.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"

Companion::Companion()
{
}

Companion::~Companion()
{

}

void Companion::Update(float elapsedTime)
{

	if (m_nHealth <= 0)
		m_nHealth = 0;

	if( m_nHealth <= 0 )
	{
		if( this->GetTimeStamp()->GetCurrentAnimation() != "DeathAnimation" )
		{
			this->GetTimeStamp()->SetCurrentAnimation( "DeathAnimation" );
			this->GetTimeStamp()->SetCurrentFrame( 0 );
			this->GetTimeStamp()->SetTimeOnFrame( 0.0f );
		}
		else
		{
			m_fDeathAnimationTimer -= elapsedTime;

			if( m_fDeathAnimationTimer < 0.0f )
			{
				m_fDeathAnimationTimer = 0.0f;
			}

			m_pAnimator->GetInstance()->GetInstance()->Update( *this->GetTimeStamp() , elapsedTime );
		}
	}

	if (m_nHealth > 0)
		Companion1HB.right = Companion1HB.left + m_nHealth;

	if (m_nHealth > 0)
		Companion2HB.right = Companion2HB.left + m_nHealth;

	if (m_nHealth >= 60)
		m_HealthColor = { 255, 0, 255, 0 };
	else if (m_nHealth < 60 && m_nHealth >= 30)
		m_HealthColor = { 255, 255, 255, 0 };
	else if (m_nHealth < 30 && m_nHealth >= 0)
		m_HealthColor = { 255, 255, 0, 0 };

	if (m_bUpdateAnimation)
	{
		m_pAnimator->GetInstance()->GetInstance()->Update(*this->GetTimeStamp(), elapsedTime);
	}
}

void Companion::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Vector vec = { (m_ptPosition.x), (m_ptPosition.y) };
	SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x, vec.y - GameplayState::GetInstance()->GetWorldCam().y };
	pGraphics->DrawTexture(m_hImage, point);

}

void Companion::CombatRender(int _posIndex)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	switch (_posIndex)
	{
	case 1:
		pGraphics->DrawRectangle(Companion1HB, m_HealthColor);
		if (m_pAnimator->GetInstance()->CheckSize())
		{
			m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), (int)Companion1rect.right, (int)Companion1rect.bottom);
		}
		else if( GetDeathAnimationTimer() > 0.0f )
		{
			if( m_pAnimator->GetInstance()->CheckSize() )
			{
				m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), (int)Companion1rect.right, (int)Companion1rect.bottom);
			}
		}
		break;
	case 2:
		pGraphics->DrawRectangle(Companion2HB, m_HealthColor);
		if (m_pAnimator->GetInstance()->CheckSize())
		{
			m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), (int)Companion2rect.right, (int)Companion2rect.bottom);
		}
		else if( GetDeathAnimationTimer() > 0.0f )
		{
			if( m_pAnimator->GetInstance()->CheckSize() )
			{
				m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), (int)Companion2rect.right, (int)Companion2rect.bottom);
			}
		}
		break;

	default:
		break;
	}
}

void Companion::SetCompanionAnimation(int companionType)
{
	m_pAnimator = m_pAnimator->GetInstance();

	switch (companionType)
	{
	case 0:
		this->GetTimeStamp()->SetCurrentAnimation("ClericAttack");
		break;
	case 1:
		this->GetTimeStamp()->SetCurrentAnimation("Companion1Attack");
		break;
	case 2:
		this->GetTimeStamp()->SetCurrentAnimation("RangerAttack");
		break;
	case 3:
		this->GetTimeStamp()->SetCurrentAnimation("GladiatorAttack");
		break;
	default:
		break;
	}

	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);

}

void Companion::ResetAnimation()
{
	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);
}