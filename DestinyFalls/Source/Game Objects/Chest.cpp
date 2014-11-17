#include "stdafx.h"
#include "Chest.h"
#include "../Game Core/Game.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"

Chest::Chest()
{
}


Chest::~Chest()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture(m_hChestImage);
	SGD::AudioManager::GetInstance()->UnloadAudio(m_hChestOpen);
}

void Chest::Update(float elapsedTime)
{
	if (Colliding)
	{
		textTimer -= 1 * elapsedTime;
		if (textTimer <= 0.0f)
		{
			Colliding = false;
		}
	}
}

void Chest::Render(void)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Vector vec = { (m_ptPosition.x), (m_ptPosition.y) };
	SGD::Point point = { vec.x - (m_szSize.width / 2 + GameplayState::GetInstance()->GetWorldCam().x), vec.y - (m_szSize.height / 2 + GameplayState::GetInstance()->GetWorldCam().y) };

	SGD::Rectangle rec = GetRect();
	rec.Offset(-GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y);

	pGraphics->DrawRectangle(rec, SGD::Color(0, 0, 255));

	//pGraphics->DrawTextureSection(m_hChestImage, point, SGD::Rectangle{ 0, 0, 100, 100 });

	if (Colliding)
	{
		if (Opened)
		{
		}

		SGD::Point tempPos;
		tempPos.x = (m_ptPosition.x - GameplayState::GetInstance()->GetWorldCam().x);
		tempPos.y = (m_ptPosition.y - GameplayState::GetInstance()->GetWorldCam().y);
		SGD::GraphicsManager::GetInstance()->DrawString("Press Q to Open", tempPos, SGD::Color(255, 255, 0, 0));
	}
}

SGD::Rectangle Chest::GetRect(void) const
{
	SGD::Rectangle sourceRect = { m_ptPosition.x, m_ptPosition.y, (m_ptPosition.x + m_szSize.width), (m_ptPosition.y + m_szSize.height) };
	return sourceRect;
}

void Chest::HandleEvent(const SGD::Event* pEvent) /*override*/
{

}

void Chest::HandleCollision(const iObject* pOther)
{
	if (pOther->GetType() == OBJ_PLAYER)
	{
		if (Colliding == false)
		{
			Colliding = true;
			textTimer = 3.0f;
		}
	}
}