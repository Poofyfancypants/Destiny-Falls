#pragma once

#include "IGameState.h"
#include "InventoryState.h"
#include "../../SGD Wrappers/SGD_Handle.h"		
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class GameplayState :
	public IGameState
{
public:
	static GameplayState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

private:
	GameplayState() = default;
	virtual ~GameplayState() = default;

	GameplayState(const GameplayState&) = delete;
	GameplayState& operator=(const GameplayState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;

	/**********************************************************/
	// Message Callback Function:
	static void MessageProc(const SGD::Message* pMsg);
};

