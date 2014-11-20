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

	SGD::Rectangle saveslot1 = {100,  50, 300, 150};
	SGD::Rectangle saveslot2 = {100, 150, 300, 300};
	SGD::Rectangle saveslot3 = {100, 300, 300, 450};

	SGD::Rectangle loadslot1 = {400,  50, 575, 150};
	SGD::Rectangle loadslot2 = {400, 150, 575, 300};
	SGD::Rectangle loadslot3 = {400, 300, 575, 450};

	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;
};

