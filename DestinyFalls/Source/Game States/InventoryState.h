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

	void AddRunesToInventory(Runes* _addrune);
	void AddRunesToSword(Runes* _addrune);
	void AddRunesToRing(Runes* _addrune);
	void AddRunesToArmor(Runes* _addrune);

private:
	InventoryState() = default;
	virtual ~InventoryState() = default;

	InventoryState(const InventoryState&) = delete;
	InventoryState& operator=(const InventoryState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;


protected:

	std::vector<Runes*> m_vSword;
	std::vector<Runes*> m_vRing;
	std::vector<Runes*> m_vArmor;
	std::vector<Runes*> m_vRunes;

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





