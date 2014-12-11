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
	if (m_nHealth <= 0)
		m_nHealth = 0;

	if (m_nHealth > 0)
		Enemy1HB.right = Enemy1HB.left + m_nHealth;

	if (m_nHealth > 0)
		Enemy2HB.right = Enemy2HB.left + m_nHealth;

	if (m_nHealth > 0)
		Enemy3HB.right = Enemy3HB.left + m_nHealth;

	if (m_nHealth >= 60)
		m_HealthColor = { 255, 0, 255, 0 };
	else if (m_nHealth < 60 && m_nHealth >= 30)
		m_HealthColor = { 255, 255, 255, 0 };
	else if (m_nHealth < 30 && m_nHealth >= 0)
		m_HealthColor = { 255, 255, 0, 0 };

	if (m_bUpdateAnimation)
	{
		m_pAnimator->GetInstance()->GetInstance()->Update(*this->GetTimeStamp(), elapsedTime);
	}
}

void Minion::Render(int _posIndex)
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = pFont->GetInstance();

	switch (_posIndex)
	{
	case 0: //Middle
		if (m_nHealth > 0)
		{
			pGraphics->DrawRectangle(Enemy2HB, m_HealthColor);
			pFont->Render("Bernardo", Game::GetInstance()->GetString(RegionString, AIString).c_str(), SGD::Point(Enemy2rect.right, Enemy2rect.bottom), 1, { 255, 225, 255, 255 });
			if (m_pAnimator->GetInstance()->CheckSize())
			{
				m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), Enemy2rect.right, Enemy2rect.bottom);
			}
		}
		break;
	case 1:  //Top 
		if (m_nHealth > 0)
		{
			pGraphics->DrawRectangle(Enemy1HB, m_HealthColor);
			pFont->Render("Bernardo", Game::GetInstance()->GetString(RegionString, AIString).c_str(), SGD::Point(Enemy1rect.right, Enemy1rect.bottom), 1, { 255, 225, 255, 255 });
			if (m_pAnimator->GetInstance()->CheckSize())
			{
				m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), Enemy1rect.right, Enemy1rect.bottom);
			}
		}
		break;
	case 2: //Bottom
		if (m_nHealth > 0)
		{
			pGraphics->DrawRectangle(Enemy3HB, m_HealthColor);
			pFont->Render("Bernardo", Game::GetInstance()->GetString(RegionString, AIString).c_str(), SGD::Point(Enemy3rect.right, Enemy3rect.bottom), 1, { 255, 225, 255, 255 });
			if (m_pAnimator->GetInstance()->CheckSize())
			{
				m_pAnimator->GetInstance()->Render(*this->GetTimeStamp(), Enemy3rect.right, Enemy3rect.bottom);
			}
		}
		break;
	default:
		break;
	}

}

void Minion::SetString(int _region, int _AI)
{
	RegionString = _region + 1;
	AIString = _AI + 1;
}

int Minion::GetName(int _index)
{
	int name[2];
	name[0] = RegionString;
	name[1] = AIString;
	return name[_index];
}

bool Minion::TakeTurn() //This will be even bigger, still don't care
{
	CombatState* pCombat = CombatState::GetInstance();
	int target = 0;

	switch (this->GetAIType())
	{
	case Minion_AI:
		if (m_nHealth > 0)
		{
			target = rand() % pCombat->GetHeroes().size();
			pCombat->SetActionTimer(1);
			pCombat->TakeAction(CombatState::ActionType::Melee, this, target);
			m_bUpdateAnimation = true;
			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);
		}
		break;
	case Off_AI:
		if (m_nHealth > 0)
		{
			pCombat->SetActionTimer(1);
			pCombat->TakeAction(CombatState::ActionType::Melee, this, target);
			m_bUpdateAnimation = true;
			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);
		}
		break;
	case Def_AI:
		if (m_nHealth > 0)
		{
			pCombat->SetActionTimer(1);
			pCombat->TakeAction(CombatState::ActionType::Melee, this, target);
			m_bUpdateAnimation = true;
			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);
		}
		break;
	case Heal_AI:
		if (m_nHealth > 0)
		{
			pCombat->SetActionTimer(1);
			pCombat->TakeAction(CombatState::ActionType::Melee, this, target);
			m_bUpdateAnimation = true;
			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);
		}
		break;
	case AOE_AI:
		if (m_nHealth > 0)
		{
			int AI = rand() % 20;
			if (AI <= 15) //AOE attack
				pCombat->TakeAction(CombatState::ActionType::AOE, this, target);
			else
				pCombat->TakeAction(CombatState::ActionType::Melee, this, target);

			m_bUpdateAnimation = true;
			this->GetTimeStamp()->SetCurrentFrame(0);
			this->GetTimeStamp()->SetTimeOnFrame(0.0f);

		}
		break;
	default:
		break;
	}

	return true;
}

void Minion::SetMinionAnimation(int region, int minionType)
{
	m_pAnimator = m_pAnimator->GetInstance();

	switch (region)
	{
	case 0://Earth minions
	{
			   switch (minionType)
			   {
			   case 0:
				   this->GetTimeStamp()->SetCurrentAnimation("OrcElementalAttack2");
				   break;
			   case 1:
				   this->GetTimeStamp()->SetCurrentAnimation("BehemothAttack2");
				   break;
			   case 2:
				   this->GetTimeStamp()->SetCurrentAnimation("RockElementalAttack");
				   break;
			   case 3:
				   this->GetTimeStamp()->SetCurrentAnimation("PlantAttack");
				   break;
			   case 4:
				   this->GetTimeStamp()->SetCurrentAnimation("GolemAttack");
				   break;
			   case 5:
				   this->GetTimeStamp()->SetCurrentAnimation("EarthMiniBossAttack");
				   break;
			   case 6:
				   this->GetTimeStamp()->SetCurrentAnimation("EarthBossAttack");
				   break;
			   default:
				   break;
			   }
	}
		break;
	case 1://water minions
	{
			   switch (minionType)
			   {
			   case 0:
				   this->GetTimeStamp()->SetCurrentAnimation("OrcElementalAttack2");
				   break;
			   case 1:
				   this->GetTimeStamp()->SetCurrentAnimation("BehemothAttack3");
				   break;
			   case 2:
				   this->GetTimeStamp()->SetCurrentAnimation("IceElementalAttack");
				   break;
			   case 3:
				   this->GetTimeStamp()->SetCurrentAnimation("WaterEnemyAttack");
				   break;
			   case 4:
				   this->GetTimeStamp()->SetCurrentAnimation("BombAttack2");
				   break;
			   case 5:
				   this->GetTimeStamp()->SetCurrentAnimation("BaronAttack");
				   break;
			   case 6:
				   this->GetTimeStamp()->SetCurrentAnimation("IceBossAttack");
				   break;
			   default:
				   break;
			   }
	}
		break;
	case 2://air minions
	{
			   switch (minionType)
			   {
			   case 0:
				   this->GetTimeStamp()->SetCurrentAnimation("OrcElementalAttack2");
				   break;
			   case 1:
				   this->GetTimeStamp()->SetCurrentAnimation("BehemothAttack2");
				   break;
			   case 2:
				   this->GetTimeStamp()->SetCurrentAnimation("GenieAttack");
				   break;
			   case 3:
				   this->GetTimeStamp()->SetCurrentAnimation("AirElementalAttack");
				   break;
			   case 4:
				   this->GetTimeStamp()->SetCurrentAnimation("BombAttack3");
				   break;
			   case 5:
				   this->GetTimeStamp()->SetCurrentAnimation("AirMiniBossAttack");
				   break;
			   case 6:
				   this->GetTimeStamp()->SetCurrentAnimation("AirBossAttack");
				   break;
			   default:
				   break;
			   }
	}
		break;
	case 3://fire minions
	{
			   switch (minionType)
			   {
			   case 0:
				   this->GetTimeStamp()->SetCurrentAnimation("OrcElementalAttack2");
				   break;
			   case 1:
				   this->GetTimeStamp()->SetCurrentAnimation("BehemothAttack1");
				   break;
			   case 2:
				   this->GetTimeStamp()->SetCurrentAnimation("EarthEnemyAttack");
				   break;
			   case 3:
				   this->GetTimeStamp()->SetCurrentAnimation("BombAttack1");
				   break;
			   case 4:
				   this->GetTimeStamp()->SetCurrentAnimation("BaronAttack");
				   break;
			   case 5:
				   this->GetTimeStamp()->SetCurrentAnimation("OrcSkeletonAttack");
				   break;
			   case 6:
				   this->GetTimeStamp()->SetCurrentAnimation("NagaAttack");
				   break;
			   default:
				   break;
			   }
	}
		break;
	case 4: // Higher cases will be used for bosses
		switch (minionType)
		{
		case 0:
			this->GetTimeStamp()->SetCurrentAnimation("TitanAttack");
			break;
		default:
			break;
		}
	default:
		break;
	}

	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);

}

void Minion::SetMods(int _damageLevel, int _type, int _tier1, int _tier2)
{
	
	Modifiers.DamageLevel = _damageLevel;
	Modifiers.ElemAffinity.ElementType = _type;
	Modifiers.ElemResistance.ElementType = _type;
	Modifiers.ElemAffinity.ElementTier = _tier1;
	Modifiers.ElemResistance.ElementTier = _tier2;
}

void Minion::ResetAnimation()
{
	this->GetTimeStamp()->SetCurrentFrame(0);
	this->GetTimeStamp()->SetTimeOnFrame(0.0f);
}