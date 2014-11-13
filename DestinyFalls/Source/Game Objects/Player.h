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

	void SetVelocity(SGD::Vector _vel) {velocity = _vel;}
	void SetDirection(int _direction) {m_nDirection = _direction;}
	int GetDirection() {return m_nDirection;}
private:
	int m_nDirection;
	SGD::Vector velocity = SGD::Vector();
};