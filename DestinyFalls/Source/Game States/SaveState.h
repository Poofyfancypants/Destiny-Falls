#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include <fstream>
#include <string>

class SaveState :
	public IGameState
{
public:
	static SaveState* GetInstance( void );

	virtual void Enter( void )				override;
	virtual void Exit( void )					override;
	virtual bool Input( void )				override;
	virtual void Update( float elapsedTime )	override;
	virtual void Render( void )				override;
private:
	SaveState() = default;
	virtual ~SaveState() = default;

	SaveState( const SaveState& ) = delete;
	SaveState& operator=( const SaveState& ) = delete;
	
	float m_fArcadeTimer = 0.0f;

	int m_nRenameCursor = 0;
	int m_nCursor = 0;
	bool m_bSelect = false;
	bool m_bGetKey = false;
	bool m_bRename = false;
	void Save();
	void Save2();
	void Save3();

	void SlotName();
	void LoadNames();


	std::string m_sSlot1Name = "slot1";
	std::string m_sSlot2Name = "slot2";
	std::string m_sSlot3Name = "slot3";

	SGD::Rectangle saveslot1 = { 20, 300, 270, 350 };
	SGD::Rectangle saveslot2 = { 525, 300, 775, 350 };
	SGD::Rectangle saveslot3 = { 285, 470, 535, 520 };
	SGD::Rectangle yesRect = { 250, 300, 370, 370 };
	SGD::Rectangle noRect = {450, 300, 570,360};
	SGD::Rectangle exit = { 640, 530, 763, 590 };

	SGD::Rectangle loadslot1 = { 600, 50, 800, 150 };
	SGD::Rectangle loadslot2 = { 600, 200, 800, 300 };
	SGD::Rectangle loadslot3 = { 600, 350, 800, 450 };

	SGD::HTexture m_hBackground = SGD::INVALID_HANDLE;
	SGD::HTexture m_hButton = SGD::INVALID_HANDLE;
	SGD::HTexture m_hButtonHighlighted = SGD::INVALID_HANDLE;

	SGD::HTexture m_hNameFrame = SGD::INVALID_HANDLE;

};

