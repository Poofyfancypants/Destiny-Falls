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
	enum MenuSelections{play, options, howToPlay, credits, exit,};

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;


	bool GetTutorial() const {return m_bTutorial;}

	void FadeInMenu();
private:
	//Textures
	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;
	SGD::HTexture m_hLogo = SGD::INVALID_HANDLE;
	MainMenuState() = default;
	virtual ~MainMenuState() = default;

	MainMenuState(const MainMenuState&) = delete;
	MainMenuState& operator=(const MainMenuState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;

	//GameState Selection Rectangles
	// - top left - 124, 162
	// - bot right - 232, 457
	SGD::Rectangle playRect = { 124, 162, 232, 457 };
	// - 277 , 472
	// - 525 , 141
	SGD::Rectangle optionRect = { 266 , 470 , 566 , 568 };
	// - 248, 34
	// - 526 , 138
	SGD::Rectangle tutorialRect = { 248 , 34 , 526 , 138 };
	// - 548, 154
	// - 689, 447
	SGD::Rectangle creditRect = { 548 , 154 , 689 , 447 };

	SGD::HTexture m_hPlay = SGD::INVALID_HANDLE;
	SGD::HTexture m_hOptions = SGD::INVALID_HANDLE;
	SGD::HTexture m_hCredit= SGD::INVALID_HANDLE;
	SGD::HTexture m_hTutorial = SGD::INVALID_HANDLE;
	SGD::HAudio m_hMusic = SGD::INVALID_HANDLE;
	
	bool m_bDebug = false;
	bool m_bTutorial = false;

};

