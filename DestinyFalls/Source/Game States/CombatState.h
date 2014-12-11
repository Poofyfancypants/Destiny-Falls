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
	enum ActionType{Melee, Magic, Armor, AOE, Heal};

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

	bool TakeAction(int _DamType, Object* _this, int _target, int _spell = 0);

	//Helpers which take entities with runes and elemental resistances/affinities for health transactions
	//Functions will figure out who is who
	int DealMeleeDamage(Object* _From, Object* _To);
	int DealMagicDamage(Object* _From, Object* _To, int _spell);
	int DealCounterDamage(Object* _From, Object* _To);
	int BlockAttack(Object* _From, Object* _To);
	int HealAlly(Object* _From, Object* _To);
	int DealAOEDamage(Object* _From, Object* _To);

	std::vector<Object*> GetHeroes() const { return m_pHeroes; }
	std::vector<Object*> GetEnemies() const { return m_pEnemies; }
	const std::vector<Object*>* GetObjManager() const { return &m_pObjects; }
	Object* AddMinion(int _region = 0, int EnemyType = 0); //0->Earth, 1->Water, 2->Air, 3->Fire
	Object* AddCompanion(int _type); 

	bool GetCooldown() { return m_bCoolDown; }
	void SetCooldown(bool x) { m_bCoolDown = x; }
	void SetActionTimer(float _time) { ActionTimer = _time; }
	float GetActionTimer() const { return ActionTimer; }

	void SetAction(string _Action) { ActionMessage = _Action; } //Display information to the user
	string GetAction() const { return ActionMessage; }

	void SetNumQTCorrect( int numCorrect ){ m_nNumQtCorrect = numCorrect; }
	void ShakeScreen(float elapsedTime);
	void ResetRects();

	bool TakeTurn(Object*);

	void HandleTutorial();
	void DrawBackground();

private:

	CombatState() = default;
	virtual ~CombatState() = default;

	CombatState(const CombatState&) = delete;
	CombatState& operator=(const CombatState&) = delete;

	SGD::Rectangle AbilityRect = { 200, 400, 600, 575 };
	SGD::Rectangle ActionRect = { 200, 10, 600, 50 };


	SGD::Rectangle Playerrect	= { 225, 200, 289, 264 };
	SGD::Rectangle PlayerHB		= { 75, 200, 175, 230 };

	SGD::Rectangle Companion1rect = { 100, 100, 164, 164 };
	SGD::Rectangle Companion1HB = { 50, 80, 150, 110 };

	SGD::Rectangle Companion2rect = { 100, 300, 164, 364 };
	SGD::Rectangle Companion2HB = { 50, 280, 150, 310 };

	SGD::Rectangle Enemy1rect = { 531, 110, 605, 174 };
	SGD::Rectangle Enemy1HB = { 670, 80, 795, 110 };

	SGD::Rectangle Enemy2rect = { 436, 200, 500, 264 };
	SGD::Rectangle Enemy2HB = { 605, 200, 730, 230 };

	SGD::Rectangle Enemy3rect = { 531, 310, 605, 374 };
	SGD::Rectangle Enemy3HB = { 670, 310, 795, 340 };


	SGD::Point SavePlayerPos = { 0, 0 };

	int m_nCursor = 0;
	int ActionSelected = 0;
	bool selected = false;
	int spellSelect = -1;

	int CurrentTurn;
	bool m_bCoolDown = false;
	bool m_bShake = false;

	bool entered = false;

	string ActionMessage;
	float ActionTimer = 0.0f; //Reset the action string to null after time, update turn order

	float PlayerTimer = 0.0f;

	bool PlayerTurn = false;
	bool EnemyTurn = false;

	SGD::Vector m_vOffset = { 0, 0 };
	SGD::Point m_CombatPos1 = { 0, 0 };
	SGD::Point m_CombatPos2 = { 0, 0 };

	int Attacker1 = -1;
	int Attacker2 = -1;

	bool m_bHealthWarning = false;
	float m_fFlash = 0.0f;

	//Soon to be vectors of CombatEntities
	std::vector<Object*> m_pObjects; //Holds all combat entities
	//Sorts based off initiative
	int TurnIndex;					 //Any entity can be sub zero

	std::vector<Object*> m_pEnemies; //Holds all enemies
	//When an enemy dies, this list sorts to move the dead enemy into the last position, then pops
	int EnemyIndex;					 //Use the size of this list to check win condition
	//int NumEnemies;					 //Might add this back in

	std::vector<Object*> m_pHeroes;	 //Holds player and companions
	int HeroIndex;					 //Player is always sub zero in this list

	SGD::HTexture m_hplayer = SGD::INVALID_HANDLE;
	SGD::HAudio cMusic = SGD::INVALID_HANDLE;
	SGD::HAudio cHealingAbility = SGD::INVALID_HANDLE;


	int numPots;
	int numRunes;
	
	vector<SGD::HTexture> m_vBackgroundsEarth;
	vector<SGD::HTexture> m_vBackgroundsIce;
	vector<SGD::HTexture> m_vBackgroundsAir;
	vector<SGD::HTexture> m_vBackgroundsFire;
	vector<SGD::HTexture> m_vBackgroundsFinal;

	int m_nNumQtCorrect = 0;

};

