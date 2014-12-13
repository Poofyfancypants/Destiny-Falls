#pragma once
#include "IGameState.h"
#include "../../SGD Wrappers/SGD_Handle.h"		
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../Game Objects/Companion.h"
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

	void AddRunesToInventoryfromWorld(Runes _addrune);
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

	std::vector<Companion> m_vCompanion;

	void ClearInventory();

	// - Tutorial 
	void HandleTutorial();

	SGD::HTexture GetRuneImage() const { return m_hFiret2; }

	SGD::HTexture GetTankIcon() const { return m_hFighterIcon; }
	SGD::HTexture GetMageIcon() const { return m_hMageIcon; }
	SGD::HTexture GetMeleeIcon() const { return m_hHunterIcon; }
	SGD::HTexture GetClericIcon() const { return m_hHealerIcon; }
private:
	InventoryState() = default;
	virtual ~InventoryState() = default;

	InventoryState(const InventoryState&) = delete;
	InventoryState& operator=(const InventoryState&) = delete;
	int m_ntabCursor = 0;
	int m_nCursor = 0;
	unsigned int CompanionSelect = 30;
	bool m_bSelect = false;
	bool m_bSwordSelect = false;
	bool m_bArmorSelect = false;
	bool m_bRingSelect = false;
	bool m_bfirstEnter = true;

	bool m_bArmorTab = false;
	bool m_bWeaponsTab = false;
	bool m_bCompanionsTab = false;
	bool m_bRunesTab = false;

	bool m_bShowToolTip1 = false;
	bool m_bShowToolTip2 = false;
	bool m_bShowToolTip3 = false;
	bool m_bShowToolTip4 = false;
	bool m_bShowToolTip5 = false;
	bool m_bShowToolTip6 = false;
	bool m_bShowToolTip7 = false;
	bool m_bShowToolTip8 = false;
	bool m_bShowToolTip9 = false;
	bool m_bShowToolTip10 = false;
	bool m_bShowToolTip11 = false;
	bool m_bShowToolTip12 = false;

	bool tabLock = false;
	bool OnlyEquipEnter = false;

	bool equipslot1selected = false;
	bool equipslot2selected = false;
	bool equipslot3selected = false;
	bool pauseSelection = false;
	bool inventoryslot1 = false;

	int equipPos = 0;
	Runes m_ptSelectedRune;

	//full inventory rectangle
	SGD::Rectangle Fullrect = { 50, 50, 500, 400 };

	SGD::Rectangle RuneToolRect = { 500, 50, 700, 170 };
	// left side of inventory displaying images
	SGD::Rectangle ImageRect = { 50, 50, 200, 400 };
	//
	SGD::Rectangle CompanionRectSide = { 200, 50, 500, 400 };
	//tabs
	SGD::Rectangle tabArmor = { 50, 0, 162, 50 };
	SGD::Rectangle TabWeapons = { 162, 0, 274, 50 };
	SGD::Rectangle TabRunes = { 274, 0, 386, 50 };
	SGD::Rectangle TabCompanions = { 386, 0, 500, 50 };
	//line dividers in inventory
	SGD::Rectangle RuneSet1 = { 200, 170, 300, 200 };
	SGD::Rectangle RuneSet2 = { 300, 170, 400, 200 };
	SGD::Rectangle RuneSet3 = { 400, 170, 500, 200 };
	//rune equip slots
	SGD::Rectangle rect1 = { 200, 50, 300, 170 };
	SGD::Rectangle rect2 = { 300, 50, 400, 170 };
	SGD::Rectangle rect3 = { 400, 50, 500, 170 };

	SGD::Rectangle rect4 = { 200, 200, 300, 400 };
	SGD::Rectangle rect5 = { 300, 200, 400, 400 };
	SGD::Rectangle rect6 = { 400, 200, 500, 400 };

	//Rune Images
	//t1
	SGD::Rectangle IventoryRect1 =  { 208, 240, 244, 276 };
	SGD::Rectangle IventoryRect4 =  { 258, 240, 294, 276 };
	SGD::Rectangle IventoryRect7 =  { 208, 320, 244, 356 };
	SGD::Rectangle IventoryRect10 = { 258, 320, 294, 356 };
	//t2
	SGD::Rectangle IventoryRect2 =  { 308, 240, 344, 276 };
	SGD::Rectangle IventoryRect5 =  { 358, 240, 394, 276 };
	SGD::Rectangle IventoryRect8 =  { 308, 320, 344, 356 };
	SGD::Rectangle IventoryRect11 = { 358, 320, 394, 356 };
	//t3
	SGD::Rectangle IventoryRect3 =  { 408, 240, 444, 276 };
	SGD::Rectangle IventoryRect6 =  { 458, 240, 494, 276 };
	SGD::Rectangle IventoryRect9 =  { 408, 320, 444, 356 };
	SGD::Rectangle IventoryRect12 = { 458, 320, 494, 356 };
	//companions select rects
	SGD::Rectangle CompanionTopLeft = { 200, 50, 350, 225 };
	SGD::Rectangle CompanionTopRight = { 350, 50, 500, 225 };
	SGD::Rectangle CompanionBottomLeft = { 200, 225, 350, 400 };
	SGD::Rectangle CompanionBottomRight = { 350, 225, 500, 400 };
	//companion Equip Rects
	SGD::Rectangle Comp1Rect = { 600, 50, 700, 150 };
	SGD::Rectangle Comp2Rect = { 700, 50, 800, 150 };

	//Rune Rect Sized images for sword
	SGD::Rectangle Equip1 = { 220, 70, 280, 150 };
	SGD::Rectangle Equip2 = { 320, 70, 380, 150 };
	SGD::Rectangle Equip3 = { 420, 70, 480, 150 };
	//Rune Rect Sized images for Armor
	SGD::Rectangle EquipA1 = { 220, 70, 280, 150 };
	SGD::Rectangle EquipA2 = { 320, 70, 380, 150 };
	SGD::Rectangle EquipA3 = { 420, 70, 480, 150 };
	//Rune Rect Sized images for Gauntlet
	SGD::Rectangle EquipG1 = { 220, 70, 280, 150 };
	SGD::Rectangle EquipG2 = { 320, 70, 380, 150 };
	SGD::Rectangle EquipG3 = { 420, 70, 480, 150 };

	// - Tutorial Info 
	float m_fDialogScroll = 7.0f;
	float m_fTimer = 0;
	bool m_nDialogSwap = false;
protected:


	SGD::HTexture m_hSword = SGD::INVALID_HANDLE;
	SGD::HTexture m_hGauntlet = SGD::INVALID_HANDLE;
	SGD::HTexture m_hArmor = SGD::INVALID_HANDLE;
	SGD::HTexture m_hFiret1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hFiret2 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hFiret3 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hWatert1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hWatert2 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hWatert3 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hEartht1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hEartht2 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hEartht3 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirt1 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirt2 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hAirt3 = SGD::INVALID_HANDLE;
	SGD::HTexture m_hHero = SGD::INVALID_HANDLE;
	SGD::HTexture m_hHeroBackground = SGD::INVALID_HANDLE;
	SGD::HTexture m_hInventoryBackground = SGD::INVALID_HANDLE;
	SGD::HTexture m_hArmorBackground = SGD::INVALID_HANDLE;
	SGD::HTexture m_hWeaponBackground = SGD::INVALID_HANDLE;



	// icons for companions
	SGD::HTexture m_hHunterIcon = SGD::INVALID_HANDLE;
	SGD::HTexture m_hFighterIcon = SGD::INVALID_HANDLE;
	SGD::HTexture m_hHealerIcon = SGD::INVALID_HANDLE;
	SGD::HTexture m_hMageIcon = SGD::INVALID_HANDLE;


};




