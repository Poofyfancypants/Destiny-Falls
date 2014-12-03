#pragma once
#include "AnimatedObject.h"
#include "../../SGD Wrappers/SGD_Declarations.h"

class Forge :
	public AnimatedObject
{
public:
	Forge();
	~Forge();

	virtual void Update(float elapsedTime) override;
	virtual void Render(void) override;
	virtual int GetType(void) const { return OBJ_FORGE; }
	virtual SGD::Rectangle GetRect(void) const override;
	virtual void HandleCollision(const iObject* pOther);

private:
	SGD::HTexture m_hForge = SGD::INVALID_HANDLE;
	SGD::HAudio m_hHammer = SGD::INVALID_HANDLE;
};

