#pragma once
#include "AnimatedObject.h"
#include "Object.h"

#include "../../SGD Wrappers/SGD_Listener.h"
#include "../Managers/AnimationManager.h"
#include "../Quick Time/QuickTime.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"


class Player :
	public AnimatedObject,
	public SGD::Listener
{
public:
	Player();
	virtual ~Player();

	//*******************************************************************
	// Listener Interface:
	virtual void Update( float elapsedTime ) override;
	virtual void Render( void ) override;
	virtual int GetType( void ) const { return OBJ_PLAYER; }
	virtual SGD::Rectangle GetRect( void ) const override;
	virtual void HandleCollision( const iObject* pOther ) override;
	virtual bool TakeTurn( float elapsedTime );

	void TakeInput();

	void SetCheckPoint( SGD::Point _point ) { m_ptCheckpoint = _point; }
	void SetMoving( bool _move ) { m_bMoving = _move; }
	void SetSliding( bool _slide ) { m_bSliding = _slide; }
	void SetVelocity( SGD::Vector _vel ) { velocity = _vel; }
	void SetDirection( int _direction ) { m_nDirection = _direction; }
	void SetCombat( bool _combat = false ) { m_bCombat = _combat; }
	void SetHealth( int _health ) { m_nHealth = _health; }
	void SetPotions( int _potion ) { m_nPotions = _potion; }
	virtual int GetHealth() const { return m_nHealth; }
	int GetMaxHealth() const { return m_nMaxHealth; }

	bool GetMoving() const { return m_bMoving; }
	SGD::Point GetCheckpoint() { return m_ptCheckpoint; }
	int GetDirection() const { return m_nDirection; }
	bool GetCombat() const { return m_bCombat; }
	void CurrentTurn( int * _CurrentTurn ) { m_CurrentTurn = _CurrentTurn; }
	int GetNumPotions() const { return m_nPotions; }
	int m_nPotions = 0;


	void RunQuickTime( int length );
	void StopQuickTime();
	QuickTime* GetQuickTime( void ){ return currentQT; }

	int GetPrevDirection() const { return m_nPrevDirection; }
	bool GetBoulderCollision() const { return m_bCollision; }

	void ResetAnimation();
	void StartCombat();
	void StopCombat();

	void RenderDialog();
	void UpdateDialog();
	void PreventDialogFromRestarting( float elapsedTime );
	QuickTime* GetQT() const { return currentQT; }
	bool m_bDoQt = false;

	bool GetSpell1Cool() const { return m_bSpell1; }
	bool GetSpell2Cool() const { return m_bSpell2; }
	bool GetSpell3Cool() const { return m_bSpell3; }

	void SetSpell1Cool( bool _Cool ) { m_bSpell1 = _Cool; }
	void SetSpell2Cool( bool _Cool ) { m_bSpell2 = _Cool; }
	void SetSpell3Cool( bool _Cool ) { m_bSpell3 = _Cool; }

	void SetRect( SGD::Rectangle pRect1 ) { playerRect = pRect1; }

	bool GetMapSwitch() const { return m_bMapSwitch; }
	void SetMapSwitch( bool MS ){ m_bMapSwitch = MS; }

	int CombatEnemyID = -1;

private:

	SGD::Rectangle playerRect = { 225, 200, 289, 264 };

	bool m_bMapSwitch = true;
	int m_nDirection;
	int m_nPrevDirection;
	bool m_bSliding = false;
	bool m_bMoving = false;
	bool m_bCollision = false;
	SGD::Vector velocity = SGD::Vector();
	SGD::Point m_ptCheckpoint;
	int m_nHealth = 100;
	int m_nMaxHealth = 100;

	bool m_bCombat = false;

	bool m_bSpell1 = false; //False == not on cooldown
	bool m_bSpell2 = false;
	bool m_bSpell3 = false;

	int ActionSelected = 0;

	bool selected = false;
	int m_nCursor = 0;
	int spellSelect = -1;
	int counter = 0;

	int * m_CurrentTurn;
	AnimationManager* m_pAnimator = nullptr;

	QuickTime* currentQT = nullptr;

	bool m_bLowHealthWarning = false;
	float m_fHealthFlash = 0.0f;
	bool m_bUpdateAnimation = true;

	SGD::HTexture m_hPortrait = SGD::INVALID_HANDLE;
	SGD::HTexture m_hDialogImg = SGD::INVALID_HANDLE;
	SGD::HTexture m_hDialogImg2 = SGD::INVALID_HANDLE;


	bool m_bPlayCombatAnimation = false;

	string m_szLastAnimation;

	bool m_bRunDialog = false;
	bool m_bPreventDialog = false;
	float m_fDialogTimer = 5.0f;
	int m_nLineCounter = 1;

	float p1, p2, v1;
	bool m_PrintDMG = false;

	float		m_fScroll = 0;
	float	m_fSecond = 0;

	int m_ptTrapDmg;
};