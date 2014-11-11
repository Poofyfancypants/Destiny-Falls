#include "stdafx.h"
#include "Player.h"
#include "../Game Core/Game.h"
#include "../Game States/CombatState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
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
	TakeInput(elapsedTime);
}

void Player::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Rectangle playerRect = { m_ptPosition.x, m_ptPosition.y, m_ptPosition.x + 64, m_ptPosition.y + 64 };
	pGraphics->DrawRectangle(playerRect, SGD::Color(0, 0, 255));
}

void Player::TakeInput(float elapsedTime)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyDown(SGD::Key::Up) || pInput->IsKeyDown(SGD::Key::W))
	{
		m_ptPosition.y -= 100 * elapsedTime;
	}
	if (pInput->IsKeyDown(SGD::Key::Down) || pInput->IsKeyDown(SGD::Key::S))
	{
		m_ptPosition.y += 100 * elapsedTime;
	}

	if (pInput->IsKeyDown(SGD::Key::Left) || pInput->IsKeyDown(SGD::Key::A))
	{
		m_ptPosition.x -= 100 * elapsedTime;
	}
	if (pInput->IsKeyDown(SGD::Key::Right) || pInput->IsKeyDown(SGD::Key::D))
	{
		m_ptPosition.x += 100 * elapsedTime;
	}
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
	if (pOther->GetType() == OBJ_ENEMY)
	{
		Game::GetInstance()->AddState(CombatState::GetInstance());
	}
}