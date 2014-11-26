#pragma once
#include "Enemy.h"
#include "../Runes/Runes.h"
#include "../Runes/RuneManager.h"

class Minion :
	public Enemy
{
public:

	enum AI_Type {Minion_AI, Off_AI, Def_AI, Heal_AI, AOE_AI};
	//enum Monster_Type {}; Could use both enums to determine the string used

	//virtual int GetCMBType(void) const { return CMB_MINION_1; }
	virtual bool TakeTurn();
	virtual void Update(float elapsedTime);
	virtual void Render(int _posIndex);
	void SetCombatImage(SGD::HTexture _texture) { m_hMinion = _texture; }
	virtual int GetType(void) const { return OBJ_MINION; }
	int GetAIType(void) const { return Minion_AI; }

	void SetAIType(AI_Type _AIType) { m_AIType = _AIType; }

	void CurrentTurn(int * _CurrentTurn) { m_CurrentTurn = _CurrentTurn; }
	
	int GetHealth() const { return m_nHealth; }
	void SetHealth(int _health) { m_nHealth = _health; }
	Elements GetAffinity() { return m_rAffinity; }
	void SetAffinity(Elements x) { m_rAffinity = x; }

	void SetString(int _type) { TypeString = _type; }

	Minion();
	~Minion();

	Elements m_rAffinity;

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
};

