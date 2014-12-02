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
	void AddRunesToSword0fromInventory(Runes _addrune);
	void AddRunesToSword1fromInventory(Runes _addrune);
	void AddRunesToSword2fromInventory(Runes _addrune);
	void AddRunesToRing0fromInventory(Runes _addrune);
	void AddRunesToRing1fromInventory(Runes _addrune);
	void AddRunesToRing2fromInventory(Runes _addrune);
	void AddRunesToArmor0fromInventory(Runes _addrune);
	void AddRunesToArmor1fromInventory(Runes _addrune);
	void AddRunesToArmor2fromInventory(Runes _addrune);

	void AddRunesToInventoryfromSword0();
	void AddRunesToInventoryfromSword1();
	void AddRunesToInventoryfromSword2();
	void AddRunesToInventoryfromRing0();
	void AddRunesToInventoryfromRing1();
	void AddRunesToInventoryfromRing2();
	void AddRunesToInventoryfromArmor0();
	void AddRunesToInventoryfromArmor1();
	void AddRunesToInventoryfromArmor2();

	Elements GetSwordSlot1()  { return m_vSword[0].GetElement(); }
	Elements GetSwordSlot2()  { return m_vSword[1].GetElement(); }
	Elements GetSwordSlot3()  { return m_vSword[2].GetElement(); }

	void SetSwordSlot1(Elements x, int t)  { m_vSword[0].SetElement(x); m_vSword[0].SetTier(t); }
	void SetSwordSlot2(Elements x, int t)  { m_vSword[1].SetElement(x); m_vSword[1].SetTier(t); }
	void SetSwordSlot3(Elements x, int t)  { m_vSword[2].SetElement(x); m_vSword[2].SetTier(t); }

	Elements GetArmorSlot1()  { return m_vArmor[0].GetElement(); }
	Elements GetArmorSlot2()  { return m_vArmor[1].GetElement(); }
	Elements GetArmorSlot3()  { return m_vArmor[2].GetElement(); }

	void SetArmorSlot1(Elements x, int t)  { m_vArmor[0].SetElement(x); m_vArmor[0].SetTier(t); }
	void SetArmorSlot2(Elements x, int t)  { m_vArmor[1].SetElement(x); m_vArmor[1].SetTier(t); }
	void SetArmorSlot3(Elements x, int t)  { m_vArmor[2].SetElement(x); m_vArmor[2].SetTier(t); }
	
	Elements GetRingSlot1()  { return m_vRing[0].GetElement(); }
	Elements GetRingSlot2()  { return m_vRing[1].GetElement(); }
	Elements GetRingSlot3()  { return m_vRing[2].GetElement(); }

	void SetRingSlot1(Elements x, int t)  { m_vRing[0].SetElement(x);  m_vRing[0].SetTier(t); }
	void SetRingSlot2(Elements x, int t)  { m_vRing[1].SetElement(x);  m_vRing[1].SetTier(t); }
	void SetRingSlot3(Elements x, int t)  { m_vRing[2].SetElement(x);  m_vRing[2].SetTier(t); }

	std::vector<Runes> m_vSword;
	std::vector<Runes> m_vRing;
	std::vector<Runes> m_vArmor;
	std::vector<Runes> m_vRunes;
	


private:
	InventoryState() = default;
	virtual ~InventoryState() = default;

	InventoryState(const InventoryState&) = delete;
	InventoryState& operator=(const InventoryState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;
	bool m_bSwordSelect = false;
	bool m_bArmorSelect = false;
	bool m_bRingSelect = false;
	bool m_bfirstEnter = true;

	Runes* m_ptSelectedRune;

	SGD::Rectangle rect				= { 50, 50, 650, 550 };

	SGD::Rectangle rect1			= { 50, 50, 250, 200 };
	SGD::Rectangle swordslot1		= { 75,  125, 125, 175 };
	SGD::Rectangle swordslot2		= { 125, 125, 175, 175 };
	SGD::Rectangle swordslot3		= { 175, 125, 225, 175 };

	SGD::Rectangle rect2			= { 250, 50, 450, 200 };
	SGD::Rectangle armorslot1		= { 275, 125, 325, 175 };
	SGD::Rectangle armorslot2		= { 325, 125, 375, 175 };
	SGD::Rectangle armorslot3		= { 375, 125, 425, 175 };

	SGD::Rectangle rect3			= { 450, 50, 650, 200 };
	SGD::Rectangle ringslot1		= { 475, 125, 525, 175 };
	SGD::Rectangle ringslot2		= { 525, 125, 575, 175 };
	SGD::Rectangle ringslot3		= { 575, 125, 625, 175 };

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





