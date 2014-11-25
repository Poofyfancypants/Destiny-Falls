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

	bool DealDamage(int _DamType, Object* _this, int _target);
	int GetNumEnemies() const { return m_nNumEnemies; }
	const std::vector<Object*>* GetObjManager() const { return &m_pObjects; }
	Object* AddMinion();
	Object* AddMinion1();

	bool GetCooldown() { return m_bCoolDown; }

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
	int TurnIndex;
	int m_nNumEnemies;

	bool m_bCoolDown = false;

	Object* Enemies[3];

	std::vector<Object*> m_pObjects;

	SGD::HTexture m_hplayer = SGD::INVALID_HANDLE;
	SGD::HTexture m_henemy = SGD::INVALID_HANDLE;
	SGD::HTexture m_henemy2 = SGD::INVALID_HANDLE;
	SGD::HAudio cMusic = SGD::INVALID_HANDLE;

};

