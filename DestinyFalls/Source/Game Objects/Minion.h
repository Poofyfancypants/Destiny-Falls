#pragma once
#include "Enemy.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../Managers/AnimationManager.h"
#include "../Runes/Runes.h"
#include "../Runes/RuneManager.h"

class Minion :
	public Enemy
{
public:

	enum AI_Type {Minion_AI, Off_AI, Def_AI, Heal_AI, AOE_AI, Mini_Boss, Level_Boss, Final_Boss,};

	struct Element
	{
		int ElementType = 0;
		int ElementTier = 0;
	};

	struct EnemyMods
	{
		int AttackSpeed = 6; //Max Turn rotation is Default
							 //Implementing this on the side or in sprint three could be great

		int DamageLevel = 10;// 0-20 scale
		Element ElemResistance;
		Element ElemAffinity;
	};

	/*
	Minion 
	Medium health 0-40 +40
	Med Atk speed
	Medium damage
	No resistances
	No elemental damage

	Offensive - Behemoth
	Low health 0-20 + 40
	High Atk speed
	High damage
	Tier 1 resistances
	Tier 2-3 elemental damage
	Counter - Low (15-25%) chance on all melee attacks

	Defensive - Rock elemental
	High health 0-20 +80
	Low Atk speed
	Low damage
	Tier 3 resistances
	Tier 1-2 elemental damage
	Block - used on a low (20-30%) random chance
		  - intercepts any attacks at a reduced resistance level

	Healer - Plant
	Medium health 0-35 +55
	Med Atk speed
	Low damage
	Tier 2-3 resistances
	Tier 1 elemental damage
	Heal spell - allies/self
			   - Checks entire enemy list
			   - Offensive/Minion/Defensive/AOE Dam/Self
			   - 20-30     20-40  10-30     30-40   10-20

	AOE - Heavy Golem
	High health 0-35 +65
	High Atk speed
	Medium damage
	Tier 1-2 resistances
	Tier 2-3 elemental damage
	AOE attack 30% chance of use at all times
			   - Picks a target
			   - Hits that target for 10-20
			   - Hits adjacents heroes for 10-15
			   - If there is only one enemy, hits self for 10-15
	*/

	virtual bool TakeTurn();
	virtual void Update(float elapsedTime);
	virtual void Render(int _posIndex);
	virtual int GetType(void) const { return OBJ_MINION; }
	int GetAIType(void) const { return m_AIType; }

	void SetAIType(AI_Type _AIType) { m_AIType = _AIType; }

	void CurrentTurn(int * _CurrentTurn) { m_CurrentTurn = _CurrentTurn; }
	
	int GetHealth() const { return m_nHealth; }
	void SetHealth(int _health) { m_nHealth = _health; }
	Elements GetAffinity() { return m_rAffinity; }
	void SetAffinity(Elements x) { m_rAffinity = x; }

	EnemyMods GetMods() { return Modifiers; }
	void SetMods(int _atkSpeed, int _damageLevel, int _type, int _tier1, int _tier2);

	void SetString(int _region, int _AI);
	int GetName(int _index = 1);

	Minion();
	~Minion();

	Elements m_rAffinity;

	void SetMinionAnimation( int region , int minionType );

private:
	int * m_CurrentTurn;
	int m_nHealth = 0;
	
	AI_Type m_AIType;
	int AIString = 0;
	int RegionString = 0;

	EnemyMods Modifiers;

	SGD::Color m_HealthColor = {0,0,0,0};
	SGD::Rectangle Enemy1HB = { 650, 110, 775, 140 };
	SGD::Rectangle Enemy2HB = { 625, 200, 750, 230 };
	SGD::Rectangle Enemy3HB = { 650, 290, 775, 320 };

	SGD::Rectangle Enemy1rect = { 561, 110, 625, 174 };
	SGD::Rectangle Enemy2rect = { 536, 200, 600, 264 };
	SGD::Rectangle Enemy3rect = { 561, 290, 625, 354 };
	AnimationManager* m_pAnimator = nullptr;

	bool m_bUpdateAnimation = false;

};

