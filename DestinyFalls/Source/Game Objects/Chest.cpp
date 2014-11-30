#include "stdafx.h"
#include "Chest.h"
#include "../Game Core/Game.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"

Chest::Chest()
{
	if (rand() % 10 > 6)
		trappedChest = true;
	else
		trappedChest = false;

	numPots = rand() % 3;
	numRunes = rand() % 2;
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
	SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x , vec.y - GameplayState::GetInstance()->GetWorldCam().y  };

	if( GameplayState::GetInstance()->GetDebugState() )
	{
		SGD::Rectangle rec = GetRect();
		rec.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
		pGraphics->DrawRectangle( rec, SGD::Color( 0, 0, 255 ) );
	}

	pGraphics->DrawTexture(m_hImage, point);

	if (Colliding)
	{
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
		if (Colliding == false && (numPots > 0 || numRunes > 0))
		{
			Colliding = true;
			textTimer = 3.0f;
		}
	}
}