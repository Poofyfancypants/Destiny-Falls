#include "stdafx.h"
#include "Enemy.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Event.h"


Enemy::Enemy() : Listener(this)
{
}


Enemy::~Enemy()
{
}

void Enemy::Update(float elapsedTime)
{

}

void Enemy::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Rectangle Rect = { m_ptPosition.x, m_ptPosition.y, m_ptPosition.x + 64, m_ptPosition.y + 64 };
	pGraphics->DrawRectangle(Rect, SGD::Color(255, 0, 0));
}

SGD::Rectangle Enemy::GetRect() const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, (m_ptPosition.x + m_szSize.width), (m_ptPosition.y + m_szSize.height) };
	return sourceRect;
}

void Enemy::HandleCollision(const iObject* pOther)
{
	
}

void Enemy::HandleEvent(const SGD::Event* pEvent)
{

}