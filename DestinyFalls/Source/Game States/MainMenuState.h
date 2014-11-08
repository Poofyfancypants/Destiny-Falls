#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class MainMenuState :
	public IGameState
{
public:
	static MainMenuState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

private:
	MainMenuState() = default;
	virtual ~MainMenuState() = default;

	MainMenuState(const MainMenuState&) = delete;
	MainMenuState& operator=(const MainMenuState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;

	SGD::Rectangle PlayGame = { 0, 0, 0, 0 };
};

