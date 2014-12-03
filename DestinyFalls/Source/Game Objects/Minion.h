#pragma once
#include "Enemy.h"
#include "../Managers/AnimationManager.h"
#include "../Runes/Runes.h"
#include "../Runes/RuneManager.h"

class Minion :
	public Enemy
{
public:

	enum AI_Type {Minion_AI, Off_AI, Def_AI, Heal_AI, AOE_AI, Mini_Boss, Level_Boss, Final_Boss,};
	//enum Monster_Type {}; Could use both enums to determine the string used

	//virtual int GetCMBType(void) const { return CMB_MINION_1; }
	virtual bool TakeTurn();
	virtual void Update(float elapsedTime);
	virtual void Render(int _posIndex);
	void SetCombatImage(SGD::HTexture _texture) { m_hMinion = _texture; }
	virtual int GetType(void) const { return OBJ_MINION; }
	int GetAIType(void) const { return m_AIType; }

	void SetAIType(AI_Type _AIType) { m_AIType = _AIType; }

	void CurrentTurn(int * _CurrentTurn) { m_CurrentTurn = _CurrentTurn; }
	
	int GetHealth() const { return m_nHealth; }
	void SetHealth(int _health) { m_nHealth = _health; }
	Elements GetAffinity() { return m_rAffinity; }
	void SetAffinity(Elements x) { m_rAffinity = x; }

	void SetString(int _type) { TypeString = _type; }
	int GetName() const { return TypeString; }

	Minion();
	~Minion();

	Elements m_rAffinity;

	void SetMinionAnimation( int region , int minionType );

private:
	int * m_CurrentTurn;
	int m_nHealth = 20;
	
	AI_Type m_AIType;
	int TypeString = 0;

	SGD::HTexture m_hMinion = SGD::INVALID_HANDLE;

	SGD::Rectangle Enemy1HB = { 650, 110, 775, 140 };
	SGD::Rectangle Enemy2HB = { 625, 200, 750, 230 };
	SGD::Rectangle Enemy3HB = { 650, 290, 775, 320 };

	SGD::Rectangle Enemy1rect = { 561, 110, 625, 174 };
	SGD::Rectangle Enemy2rect = { 536, 200, 600, 264 };
	SGD::Rectangle Enemy3rect = { 561, 290, 625, 354 };
	AnimationManager* m_pAnimator = nullptr;


};

