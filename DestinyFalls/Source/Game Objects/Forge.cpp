#include "stdafx.h"
#include "Forge.h"
#include "../Game Core/Game.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

Forge::Forge()
{
}


Forge::~Forge()
{
	//SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hForge);
	//SGD::AudioManager::GetInstance()->UnloadAudio(m_hHammer);
}

void Forge::Update(float elapsedTime)
{

}

void Forge::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Vector vec = { (m_ptPosition.x), (m_ptPosition.y) };
	SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x, vec.y - GameplayState::GetInstance()->GetWorldCam().y };

	if (GameplayState::GetInstance()->GetDebugState())
	{
		SGD::Rectangle rec = GetRect();
		rec.Offset(-GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y);
		pGraphics->DrawRectangle(rec, SGD::Color(0, 0, 255));
	}

	pGraphics->DrawTexture(m_hForge, point);
}

SGD::Rectangle Forge::GetRect(void) const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, (m_ptPosition.x + m_szSize.width), (m_ptPosition.y + m_szSize.height) };
	return sourceRect;
}

void Forge::HandleCollision(const iObject* pOther)
{

}