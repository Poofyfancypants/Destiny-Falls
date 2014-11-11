#include "stdafx.h"
#include "Player.h"
#include "../Game Core/Game.h"
#include "../Game States/CombatState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_Event.h"

#include "../Game States/GameplayState.h"

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

	SGD::Vector vec = { (m_ptPosition.x), (m_ptPosition.y) };
	SGD::Point point = { vec.x - (m_szSize.width / 2 + GameplayState::GetInstance()->GetWorldCam().x), vec.y - (m_szSize.height / 2 + GameplayState::GetInstance()->GetWorldCam().y) };

	SGD::Rectangle rec = GetRect();
	rec.Offset(-GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y);

	pGraphics->DrawRectangle(rec, SGD::Color(0, 0, 255));

	pGraphics->DrawTextureSection(m_hImage, point, SGD::Rectangle{ 0, 0, 100, 100 });


}

void Player::TakeInput(float elapsedTime)
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if (pInput->IsKeyDown(SGD::Key::Up) || pInput->IsKeyDown(SGD::Key::W))
	{
		m_ptPosition.y -= 500 * elapsedTime;
	}
	if (pInput->IsKeyDown(SGD::Key::Down) || pInput->IsKeyDown(SGD::Key::S))
	{
		m_ptPosition.y += 500 * elapsedTime;
	}

	if (pInput->IsKeyDown(SGD::Key::Left) || pInput->IsKeyDown(SGD::Key::A))
	{
		m_ptPosition.x -= 500 * elapsedTime;
	}
	if (pInput->IsKeyDown(SGD::Key::Right) || pInput->IsKeyDown(SGD::Key::D))
	{
		m_ptPosition.x += 500 * elapsedTime;
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