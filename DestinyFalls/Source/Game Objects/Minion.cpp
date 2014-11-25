#include "stdafx.h"
#include "Minion.h"
#include "../Game Core/Game.h"
#include "../Game States/CombatState.h"
#include "../Bitmap Font/BitmapFont.h"

Minion::Minion()
{
}


Minion::~Minion()
{

}

void Minion::Update(float elapsedTime)
{
	if (m_nHealth > 0)
		Enemy1HB.right = Enemy1HB.left + m_nHealth;
	else
		Enemy1HB.right = Enemy1HB.left + 1; // Minion is Dead

	if (m_nHealth > 0)
		Enemy2HB.right = Enemy2HB.left + m_nHealth;
	else
		Enemy2HB.right = Enemy2HB.left + 1; // Minion is Dead

	if (m_nHealth > 0)
		Enemy3HB.right = Enemy3HB.left + m_nHealth;
	else
		Enemy3HB.right = Enemy3HB.left + 1; // Minion is Dead



}

void Minion::Render(int _posIndex)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	const BitmapFont* pFont = Game::GetInstance()->GetFont();

	switch (_posIndex)
	{
	case 0: //Top
		pGraphics->DrawRectangle(Enemy1rect, SGD::Color{ 100, 0, 150, 0 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hMinion, { Enemy1rect.left, Enemy1rect.top }, {}, {}, {}, { .5, .5 });
		pGraphics->DrawRectangle(Enemy1HB, SGD::Color{ 100, 0, 255, 0 });
		pFont->Draw(Game::GetInstance()->GetString(1, TypeString).c_str(), SGD::Point(450, (420 + (50 * _posIndex))), 1, { 255, 225, 255, 255 });

		break;
	case 1: //Middle
		pGraphics->DrawRectangle(Enemy2rect, SGD::Color{ 100, 0, 0, 150 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hMinion, { Enemy2rect.left, Enemy2rect.top }, {}, {}, {}, { .5, .5 });
		pGraphics->DrawRectangle(Enemy2HB, SGD::Color{ 100, 0, 255, 0 });
		pGraphics->DrawString(L"Minion", SGD::Point(450, (420 + (50 * _posIndex))));

		break;
	case 2: //Bottom
		pGraphics->DrawRectangle(Enemy3rect, SGD::Color{ 100, 150, 0, 0 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hMinion, { Enemy3rect.left, Enemy3rect.top }, {}, {}, {}, { .5, .5 });
		pGraphics->DrawRectangle(Enemy3HB, SGD::Color{ 100, 0, 255, 0 });
		pGraphics->DrawString(L"Minion", SGD::Point(450, (420 + (50 * _posIndex))));

		break;
	default:
		break;
	}

}

bool Minion::TakeTurn()
{
	CombatState* pCombat = CombatState::GetInstance();

	if (m_nHealth > 0)
	{
		pCombat->DealDamage(CombatState::DamType::Melee, this, 0);
	}

	return true;
}