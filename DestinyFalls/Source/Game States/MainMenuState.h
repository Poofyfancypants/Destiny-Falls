#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class MainMenuState :
	public IGameState
{
public:
	static MainMenuState* GetInstance(void);
	enum MenuSelections{play, load, options, howToPlay, credits, exit,};

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

	SGD::Rectangle Options = { 0, 0, 0, 0 };
	SGD::Rectangle LoadGame = { 0, 0, 0, 0 };
	SGD::Rectangle HowToPlay = { 0, 0, 0, 0 };
	SGD::Rectangle Credit = { 0, 0, 0, 0 };
	SGD::Rectangle ExitGame = { 0, 0, 0, 0 };


};

