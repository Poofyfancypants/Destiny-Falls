#pragma once
#include "AnimatedObject.h"
#include "Object.h"

#include "../../SGD Wrappers/SGD_Listener.h"

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
	virtual void HandleEvent(const SGD::Event* pEvent) override;
	void TakeInput(float elapsedTime);

	void SetCheckPoint(SGD::Point _point) {m_ptCheckpoint = _point;}
	void SetMoving(bool _move) {m_bMoving = _move;}
	void SetSliding(bool _slide) {m_bSliding = _slide;}
	void SetVelocity(SGD::Vector _vel) {velocity = _vel;}
	void SetDirection(int _direction) {m_nDirection = _direction;}
	int GetDirection() {return m_nDirection;}
	SGD::Point GetCheckpoint() {return m_ptCheckpoint;}
private:

	int m_nDirection;
	bool m_bSliding = false;
	bool m_bMoving = false;
	SGD::Vector velocity = SGD::Vector();
	SGD::Point m_ptCheckpoint;
};