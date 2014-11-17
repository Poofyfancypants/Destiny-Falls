#pragma once
#include "StaticObject.h"
#include "AnimatedObject.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include <vector>

class Chest :
	public AnimatedObject
{
public:
	Chest();
	~Chest();

	virtual void Update(float elapsedTime) override;
	virtual void Render(void) override;
	virtual int GetType(void) const { return OBJ_CHEST; }
	virtual SGD::Rectangle GetRect(void) const override;
	virtual void HandleCollision(const iObject* pOther);
	virtual void HandleEvent(const SGD::Event* pEvent);
	void TakeTurn(){ return; }
	void SetNumPots(int NumPots) { numPots = NumPots; }
	void SetNumRunes(int NumRunes) { numRunes = NumRunes; }

	int GetNumPots() const { return numPots; }
	int GetNumRunes() const { return numRunes; }
	bool Opened = false;
	bool Colliding = false;

private:
	SGD::HTexture m_hChestImage = SGD::INVALID_HANDLE;
	SGD::HAudio m_hChestOpen = SGD::INVALID_HANDLE;

	int numPots;
	int numRunes;

	float textTimer = 3.0f;
};
