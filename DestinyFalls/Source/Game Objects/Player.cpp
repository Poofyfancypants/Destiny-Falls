#include "stdafx.h"
#include "Player.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_Event.h"

Player::Player() : Listener(this)
{

}

Player::~Player()
{
	SGD::GraphicsManager * pGraphics = SGD::GraphicsManager::GetInstance();
	pGraphics->UnloadTexture(m_hImage);
}

void Player::Update(float elapsedTime)
{

}

void Player::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Rectangle playerRect = { m_ptPosition.x, m_ptPosition.y, m_ptPosition.x + 64, m_ptPosition.y + 64 };
	pGraphics->DrawRectangle(playerRect, SGD::Color(255, 0, 0));
}

SGD::Rectangle Player::GetRect(void) const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, (m_ptPosition.x + m_szSize.width), (m_ptPosition.y + m_szSize.height) };
	return sourceRect;
}

void Player::HandleEvent(const SGD::Event* pEvent) /*override*/
{

}

void Player::HandleCollision(const iObject* pOther)
{

}