#pragma once
#include "IGameState.h"
#include "../Managers/ObjectManager.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Minion.h"
#include <vector>
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"


class CombatState :
	public IGameState
{
public:
	enum DamType{Melee, Magic, Armor, AOE, };

	static CombatState* GetInstance();

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

	void AddBackgroundsEarth	(SGD::HTexture x)	{ m_vBackgroundsEarth.push_back(x); }
	void AddBackgroundsIce		(SGD::HTexture x)	{ m_vBackgroundsIce.push_back(x); }
	void AddBackgroundsAir		(SGD::HTexture x)	{ m_vBackgroundsAir.push_back(x); }
	void AddBackgroundsFire		(SGD::HTexture x)	{ m_vBackgroundsFire.push_back(x); }
	void AddBackgroundsFinal	(SGD::HTexture x)	{ m_vBackgroundsFinal.push_back(x); }

	void ClearEarth()	{ m_vBackgroundsEarth.clear(); }
	void ClearIce()		{ m_vBackgroundsIce.clear(); }
	void ClearAir()		{ m_vBackgroundsAir.clear(); }
	void ClearFire()	{ m_vBackgroundsFire.clear(); }
	void ClearFinal()	{ m_vBackgroundsFinal.clear(); }

	bool DealDamage(int _DamType, Object* _this, int _target);
	int GetNumEnemies() const { return m_pEnemies.size(); }
	const std::vector<Object*>* GetObjManager() const { return &m_pObjects; }
	Object* AddMinion();

	bool GetCooldown() { return m_bCoolDown; }
	void SetCooldown(bool x) { m_bCoolDown = x; }

private:
	CombatState() = default;
	virtual ~CombatState() = default;

	CombatState(const CombatState&) = delete;
	CombatState& operator=(const CombatState&) = delete;

	SGD::Rectangle AbilityRect = { 200, 400, 600, 575 };

	SGD::Rectangle Compation1HB	= { 50, 110, 175, 140 };
	SGD::Rectangle PlayerHB		= { 75, 200, 200, 230 };
	SGD::Rectangle Compation2HB	= { 50, 290, 175, 320 };
	SGD::Rectangle Enemy1HB		= { 650, 110, 775, 140};
	SGD::Rectangle Enemy2HB		= { 625, 200, 750, 230};
	SGD::Rectangle Enemy3HB		= { 650, 290, 775, 320};

	SGD::Rectangle Compation1rect	= { 200, 110, 264, 174 };
	SGD::Rectangle Playerrect		= { 225, 200, 289, 264 };
	SGD::Rectangle Compation2rect	= { 200, 290, 264, 354 };
	SGD::Rectangle Enemy1rect		= { 561, 110, 625, 174 };
	SGD::Rectangle Enemy2rect		= { 536, 200, 600, 264 };
	SGD::Rectangle Enemy3rect		= { 561, 290, 625, 354 };

	int CurrentTurn;

	bool m_bCoolDown = false;

	bool m_bHealthWarning = false;
	float m_fFlash = 0.0f;

	//Soon to be vectors of CombatEntities
	std::vector<Object*> m_pObjects; //Holds all combat entities
	//Sorts based off initiative
	int TurnIndex;					 //Any entity can be sub zero

	std::vector<Object*> m_pEnemies; //Holds all enemies
	//When an enemy dies, this list sorts to move the dead enemy into the last position, then pops
	int EnemyIndex;					 //Use the size of this list to check win condition

	std::vector<Object*> m_pHeroes;	 //Holds player and companions
	int HeroIndex;					 //Player is always sub zero in this list

	SGD::HTexture m_hplayer = SGD::INVALID_HANDLE;
	SGD::HTexture m_henemy = SGD::INVALID_HANDLE;
	SGD::HTexture m_henemy2 = SGD::INVALID_HANDLE;
	SGD::HAudio cMusic = SGD::INVALID_HANDLE;

	vector<SGD::HTexture> m_vBackgroundsEarth;
	vector<SGD::HTexture> m_vBackgroundsIce;
	vector<SGD::HTexture> m_vBackgroundsAir;
	vector<SGD::HTexture> m_vBackgroundsFire;
	vector<SGD::HTexture> m_vBackgroundsFinal;

};

