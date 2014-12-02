#include "stdafx.h"
#include "Minion.h"
#include "../Game Core/Game.h"
#include "../Game States/CombatState.h"
#include "../Managers/BitmapFontManager.h"

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
	BitmapFontManager* pFont = pFont->GetInstance();

	switch (_posIndex)
	{
	case 0: //Top
		pGraphics->DrawRectangle(Enemy1rect, SGD::Color{ 100, 0, 150, 0 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hMinion, { Enemy1rect.left, Enemy1rect.top }, {}, {}, {}, { .5, .5 });
		pGraphics->DrawRectangle(Enemy1HB, SGD::Color{ 100, 0, 255, 0 });
		pFont->Render("Bernardo", Game::GetInstance()->GetString(1, TypeString).c_str(), SGD::Point(450, (420 + (50 * _posIndex))), 1, { 255, 225, 255, 255 });
		break;
	case 1: //Middle
		pGraphics->DrawRectangle(Enemy2rect, SGD::Color{ 100, 0, 0, 150 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hMinion, { Enemy2rect.left, Enemy2rect.top }, {}, {}, {}, { .5, .5 });
		pGraphics->DrawRectangle(Enemy2HB, SGD::Color{ 100, 0, 255, 0 });
		pFont->Render("Bernardo", Game::GetInstance()->GetString(1, TypeString).c_str(), SGD::Point(450, (420 + (50 * _posIndex))), 1, { 255, 225, 255, 255 });
		break;
	case 2: //Bottom
		pGraphics->DrawRectangle(Enemy3rect, SGD::Color{ 100, 150, 0, 0 }, SGD::Color{ 255, 255, 255, 255 });
		pGraphics->DrawTexture(m_hMinion, { Enemy3rect.left, Enemy3rect.top }, {}, {}, {}, { .5, .5 });
		pGraphics->DrawRectangle(Enemy3HB, SGD::Color{ 100, 0, 255, 0 });
		pFont->Render("Bernardo", Game::GetInstance()->GetString(1, TypeString).c_str(), SGD::Point(450, (420 + (50 * _posIndex))), 1, { 255, 225, 255, 255 });
		break;
	default:
		break;
	}

}

bool Minion::TakeTurn() //This will be even bigger, still don't care
{
	CombatState* pCombat = CombatState::GetInstance();

	switch (this->GetAIType())
	{
	case Minion_AI:
		if (m_nHealth > 0)
		{
			pCombat->DealDamage(CombatState::DamType::Melee, this, 0);
			pCombat->SetActionTimer(3);
		}
		break;
	case Off_AI:
		if (m_nHealth > 0)
		{
			pCombat->DealDamage(CombatState::DamType::Melee, this, 0);
			pCombat->SetActionTimer(3);

		}
		break;
	case Def_AI:
		if (m_nHealth > 0)
		{
			pCombat->DealDamage(CombatState::DamType::Melee, this, 0);
			pCombat->SetActionTimer(3);

		}
		break;
	case Heal_AI:
		break;
	case AOE_AI:
		break;
	default:
		break;
	}


	return true;
}