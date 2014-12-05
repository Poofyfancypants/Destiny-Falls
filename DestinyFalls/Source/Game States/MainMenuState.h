#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include <fstream>
#include "../Runes/Runes.h"

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

	//Textures
	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;

private:
	MainMenuState() = default;
	virtual ~MainMenuState() = default;

	MainMenuState(const MainMenuState&) = delete;
	MainMenuState& operator=(const MainMenuState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;

	//GameState Selection Rectangles
	SGD::Rectangle PlayGame = { 0, 0, 0, 0 };
	SGD::Rectangle TestAnimationSystem = { 0 , 0 , 0 , 0 };

	SGD::Rectangle Options = { 0, 0, 0, 0 };
	SGD::Rectangle LoadGame = { 0, 0, 0, 0 };
	SGD::Rectangle HowToPlay = { 0, 0, 0, 0 };
	SGD::Rectangle Credit = { 0, 0, 0, 0 };
	SGD::Rectangle ExitGame = { 0, 0, 0, 0 };

	Runes* temp;
	Runes* temp1;
	Runes* temp2;
	Runes* temp3;
	Runes* temp4;
	Runes* temp5;
	Runes* temp6;
	Runes* temp7;
	Runes* temp8;

	
	bool m_bDebug = false;

};

