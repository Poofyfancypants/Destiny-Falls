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
	virtual void	HandleEvent(const SGD::Event* pEvent) override;
	virtual void Update(float elapsedTime) override;
	virtual void Render(void) override;
	virtual int GetType(void) const { return OBJ_PLAYER; }
	virtual SGD::Rectangle GetRect(void) const override;
	virtual void HandleCollision(const iObject* pOther) override;

private:

};