#pragma once
#include "Enemy.h"
#include "../Runes/Runes.h"
#include "../Runes/RuneManager.h"

class Minion :
	public Enemy
{
public:

	//virtual int GetCMBType(void) const { return CMB_MINION_1; }
	virtual bool TakeTurn();

	virtual void Update(float elapsedTime);
	virtual void Render();

	virtual int GetType(void) const { return OBJ_MINION; }

	void CurrentTurn(int * _CurrentTurn) { m_CurrentTurn = _CurrentTurn; }
	void SetTurnPos(int _turn) { m_nTurnPos = _turn; }
	int GetTurnPos() const { return m_nTurnPos; }
	int GetHealth() const { return m_nHealth; }
	void SetHealth(int _health) { m_nHealth = _health; }

	Minion();
	~Minion();

	Runes m_rAffinity;

private:
	int * m_CurrentTurn;
	int m_nTurnPos;
	int m_nHealth = 100;
};

