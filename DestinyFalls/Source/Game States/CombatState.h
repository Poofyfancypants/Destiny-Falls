#pragma once
#include "IGameState.h"
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
};

