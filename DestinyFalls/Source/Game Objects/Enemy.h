#pragma once
#include "AnimatedObject.h"
#include "MovingObject.h"
#include "../../SGD Wrappers/SGD_Listener.h"

class Enemy :
	public AnimatedObject,
	public SGD::Listener
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update(float elapsedTime) override;
	virtual void Render(void) override;
	virtual int GetType(void) const { return OBJ_ENEMY; }
	virtual SGD::Rectangle GetRect(void) const override;
	virtual void HandleCollision(const iObject* pOther) override;
	virtual void HandleEvent(const SGD::Event* pEvent) override;

private:

};

