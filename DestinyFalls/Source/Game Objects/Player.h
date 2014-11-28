#pragma once
#include "AnimatedObject.h"
#include "Object.h"

#include "../../SGD Wrappers/SGD_Listener.h"
#include "../Managers/AnimationManager.h"
#include "../Quick Time/QuickTime.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"

class Player :
	public AnimatedObject,
	public SGD::Listener
{
public:
	Player();
	virtual ~Player();

	//*******************************************************************
	// Listener Interface:
	virtual void Update(float elapsedTime) override;
	virtual void Render(void) override;
	virtual int GetType(void) const { return OBJ_PLAYER; }
	virtual SGD::Rectangle GetRect(void) const override;
	virtual void HandleCollision(const iObject* pOther) override;
	virtual bool TakeTurn(float elapsedTime);

	void TakeInput();

	void SetCheckPoint(SGD::Point _point) {m_ptCheckpoint = _point;}
	void SetMoving(bool _move) {m_bMoving = _move;}
	void SetSliding(bool _slide) {m_bSliding = _slide;}
	void SetVelocity(SGD::Vector _vel) {velocity = _vel;}
	void SetDirection(int _direction) {m_nDirection = _direction;}
	void SetCombat(bool _combat = false) { m_bCombat = _combat; }
	void SetHealth(int _health) { m_nHealth = _health; }

	int GetHealth() const { return m_nHealth; }
	int GetMaxHealth() const { return m_nMaxHealth; }

	SGD::Point GetCheckpoint() {return m_ptCheckpoint;}
	int GetDirection() const {return m_nDirection;}
	bool GetCombat() const { return m_bCombat; }
	void CurrentTurn(int * _CurrentTurn) { m_CurrentTurn = _CurrentTurn; }
	void SetTurnPos(int _turn) { m_nTurnPos = _turn; }
	int GetTurnPos() const { return m_nTurnPos; }

	//RunQuickTime
	//		Turns on QuickTime
	void RunQuickTime( );
	void StopQuickTime();

private:


	int m_nDirection;
	bool m_bSliding = false;
	bool m_bMoving = false;
	bool m_bCollision = false;
	SGD::Vector velocity = SGD::Vector();
	SGD::Point m_ptCheckpoint;
	int m_nHealth = 100;
	int m_nMaxHealth = 100;
	int m_nPotions = 0;

	bool m_bCombat = false;
	int m_nTurnPos;

	int ActionSelected = 0;
	bool selected = false;
	int m_nCursor = 0;

	int * m_CurrentTurn;
	AnimationManager* m_pAnimator = nullptr;

	QuickTime* currentQT = nullptr;
	bool m_bDoQt = false;

	

	

};