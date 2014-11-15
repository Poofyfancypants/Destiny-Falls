#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

class CombatState :
	public IGameState
{
public:
	static CombatState* GetInstance();

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;


private:
	CombatState() = default;
	virtual ~CombatState() = default;

	CombatState(const CombatState&) = delete;
	CombatState& operator=(const CombatState&) = delete;

	SGD::Rectangle AbilityRect = { 200, 375, 600, 550 };

	SGD::Rectangle Compation1HB	= { 50, 110, 175, 140 };
	SGD::Rectangle PlayerHB		= { 75, 200, 200, 230 };
	SGD::Rectangle Compation2HB	= { 50, 290, 175, 320 };
	SGD::Rectangle Enemy1HB		= { 650, 110, 775, 140};
	SGD::Rectangle Enemy2HB		= { 625, 200, 750, 230};
	SGD::Rectangle Enemy3HB		= { 650, 290, 775, 320};

	SGD::Rectangle Compation1rect	= { 200, 110, 264, 174 };
	SGD::Rectangle Playerrect		= { 225, 200, 289, 264 };
	SGD::Rectangle Compation2rect	= { 200, 290, 264, 354 };
	SGD::Rectangle Enemy1rect		= { 561, 110, 625, 174 };
	SGD::Rectangle Enemy2rect		= { 536, 200, 600, 264 };
	SGD::Rectangle Enemy3rect		= { 561, 290, 625, 354 };
};

