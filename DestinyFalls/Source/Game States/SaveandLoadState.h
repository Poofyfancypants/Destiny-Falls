#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include <fstream>

class SaveandLoadState :
	public IGameState
{
public:
	static SaveandLoadState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;
	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;

private:
	SaveandLoadState() = default;
	virtual ~SaveandLoadState() = default;

	SaveandLoadState(const SaveandLoadState&) = delete;
	SaveandLoadState& operator=(const SaveandLoadState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;

	void Save();
	void Save2();
	void Save3();

	void Load();
	void Load2();
	void Load3();

	SGD::Rectangle saveslot1 = {50,  50, 300, 150};
	SGD::Rectangle saveslot2 = {50, 200, 300, 300};
	SGD::Rectangle saveslot3 = {50, 350, 300, 450};

	SGD::Rectangle loadslot1 = { 600,  50, 800, 150 };
	SGD::Rectangle loadslot2 = { 600, 200, 800, 300 };
	SGD::Rectangle loadslot3 = { 600, 350, 800, 450 };

};

