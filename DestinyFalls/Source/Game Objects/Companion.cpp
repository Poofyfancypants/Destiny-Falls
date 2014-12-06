#include "stdafx.h"
#include "Companion.h"
#include "../Game States/CombatState.h"
#include "../Game States/GameplayState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

Companion::Companion()
{
}


Companion::~Companion()
{
}

void Companion::Update(float elapsedTime)
{

}

void Companion::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::Vector vec = { ( m_ptPosition.x ), ( m_ptPosition.y ) };
	SGD::Point point = { vec.x - GameplayState::GetInstance()->GetWorldCam().x, vec.y - GameplayState::GetInstance()->GetWorldCam().y };
	pGraphics->DrawTexture( m_hImage, point );

}

void Companion::CombatRender(int _posIndex)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
}

bool Companion::TakeTurn()
{
	CombatState* pCombat = CombatState::GetInstance();


	return true;
}
