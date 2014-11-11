#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_Handle.h"		
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

#include "../Runes/Runes.h"
#include <vector>

class InventoryState :
	public IGameState
{
public:

	static InventoryState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

	void AddRunesToInventoryfromWorld(Runes* _addrune);
	void AddRunesToSwordfromInventory(Runes* _addrune);
	void AddRunesToRingfromInventory(Runes* _addrune);
	void AddRunesToArmorfromInventory(Runes* _addrune);

private:
	InventoryState() = default;
	virtual ~InventoryState() = default;

	InventoryState(const InventoryState&) = delete;
	InventoryState& operator=(const InventoryState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;

	SGD::Rectangle rect = { 50, 50, 650, 550 };
	SGD::Rectangle rect1 = { 50, 50, 250, 200 };
	SGD::Rectangle rect2 = { 250, 50, 450, 200 };
	SGD::Rectangle rect3 = { 450, 50, 650, 200 };

	SGD::Rectangle IventoryRect1	= { 50, 200, 200, 317 };
	SGD::Rectangle IventoryRect2	= { 50, 317, 200, 434 };
	SGD::Rectangle IventoryRect3	= { 50, 434, 200, 550 };
	SGD::Rectangle IventoryRect4	= { 200, 200, 350, 317 };
	SGD::Rectangle IventoryRect5	= { 200, 317, 350, 434 };
	SGD::Rectangle IventoryRect6	= { 200, 434, 350, 550 };
	SGD::Rectangle IventoryRect7	= { 350, 200, 500, 317 };
	SGD::Rectangle IventoryRect8	= { 350, 317, 500, 434 };
	SGD::Rectangle IventoryRect9	= { 350, 434, 500, 550 };
	SGD::Rectangle IventoryRect10	= { 500, 200, 650, 317 };
	SGD::Rectangle IventoryRect11	= { 500, 317, 650, 434 };
	SGD::Rectangle IventoryRect12	= { 500, 434, 650, 550 };


protected:

	std::vector<Runes*> m_vSword;
	std::vector<Runes*> m_vRing;
	std::vector<Runes*> m_vArmor;
	std::vector<Runes*> m_vRunes;

	SGD::HTexture m_hSword		= SGD::INVALID_HANDLE;
	SGD::HTexture m_hRing		= SGD::INVALID_HANDLE;
	SGD::HTexture m_hArmor		= SGD::INVALID_HANDLE;
	SGD::HTexture m_hFiret1		= SGD::INVALID_HANDLE;
	SGD::HTexture m_hFiret2		= SGD::INVALID_HANDLE;
	SGD::HTexture m_hFiret3		= SGD::INVALID_HANDLE;
	SGD::HTexture m_hWatert1	= SGD::INVALID_HANDLE;
	SGD::HTexture m_hWatert2	= SGD::INVALID_HANDLE;
	SGD::HTexture m_hWatert3	= SGD::INVALID_HANDLE;
	SGD::HTexture m_hEartht1	= SGD::INVALID_HANDLE;
	SGD::HTexture m_hEartht2	= SGD::INVALID_HANDLE;
	SGD::HTexture m_hEartht3	= SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirt1		= SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirt2		= SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirt3		= SGD::INVALID_HANDLE;

};





