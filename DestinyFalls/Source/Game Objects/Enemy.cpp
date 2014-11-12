#include "stdafx.h"
#include "Enemy.h"
#include "../Messages/DestroyObjectMessage.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Event.h"
#include "../Game States/GameplayState.h"

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
	/*SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Rectangle Rect = { m_ptPosition.x, m_ptPosition.y, m_ptPosition.x + 64, m_ptPosition.y + 64 };
	pGraphics->DrawRectangle(Rect, SGD::Color(255, 0, 0));*/

	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Vector vec = { (m_ptPosition.x), (m_ptPosition.y) };
	SGD::Point point = { vec.x - (m_szSize.width / 2 + GameplayState::GetInstance()->GetWorldCam().x), vec.y - (m_szSize.height / 2 + GameplayState::GetInstance()->GetWorldCam().y) };

	SGD::Rectangle rec = GetRect();
	rec.Offset(-GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y);

	pGraphics->DrawRectangle(rec, SGD::Color(0, 0, 255));

	pGraphics->DrawTextureSection(m_hImage, point, SGD::Rectangle{ 0, 0, 100, 100 });
}

SGD::Rectangle Enemy::GetRect() const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, (m_ptPosition.x + m_szSize.width), (m_ptPosition.y + m_szSize.height) };
	return sourceRect;
}

void Enemy::HandleCollision(const iObject* pOther)
{
	DestroyObjectMessage* pMsg = new DestroyObjectMessage(this);
	pMsg->QueueMessage();
	pMsg = nullptr;
}

void Enemy::HandleEvent(const SGD::Event* pEvent)
{

}