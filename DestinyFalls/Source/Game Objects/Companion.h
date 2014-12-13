#pragma once
#include "AnimatedObject.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "Player.h"

class Companion :
	/*public AnimatedObject,*/ public Player
{
public:
	enum Companion_Type { Cleric = 1, Melee, Mage, Tank };

	Companion();
	~Companion();

	virtual void Update( float elapsedTime );
	virtual void Render();
	virtual void CombatRender( int _posIndex = 0 );
	void SetCombatImage( SGD::HTexture _texture ) { m_hCompanion = _texture; }
	virtual int GetType( void ) const { return OBJ_COMPANION; }
	int GetCoType( void ) const { return m_CoType; }

	void SetC0Type( Companion_Type _CoType ) { m_CoType = _CoType; }

	void CurrentTurn( int * _CurrentTurn ) { m_CurrentTurn = _CurrentTurn; }

	int GetHealth() const { return m_nHealth; }
	void SetHealth( int _health ) { m_nHealth = _health; }

	void SetString( int _type ) { TypeString = _type; }


	void SetCompanionAnimation( int companionType );
	int GetPosIndex( void ){ return m_nPosIndex; }
	void SetPosIndex( int posIndex ){ m_nPosIndex = posIndex; }


	void SetCompanionRect1(SGD::Rectangle cRect1) { Companion1rect = cRect1; }
	void SetCompanionRect2(SGD::Rectangle cRect2) { Companion2rect = cRect2; }

	bool GetBlock() const { return m_Block; }
	void SetBlock(bool _block) { m_Block = _block; }

	void ResetAnimation();
	void SetAnimation(bool _update) { m_bUpdateAnimation = _update; }
	float GetDeathAnimationTimer( void ){ return m_fDeathAnimationTimer; }
	void SetDeathAnimationTimer( float seconds = 3.0f ){ m_fDeathAnimationTimer = seconds; }

	int GetSpell1Cool() const { return m_bSpell1; }
	int GetSpell2Cool() const { return m_bSpell2; }
	void SetSpell1Cool(int _Cool) { m_bSpell1 = _Cool; }
	void SetSpell2Cool(int _Cool) { m_bSpell2 = _Cool; }

private:
	int * m_CurrentTurn;
	int m_nHealth = 0;

	bool m_Block = false;
	int m_nPosIndex = 0;
	Companion_Type m_CoType;
	int TypeString = 0;

	int m_bSpell1 = -1; //Cooldowns
	int m_bSpell2 = -1;

	SGD::HTexture m_hCompanion = SGD::INVALID_HANDLE;

	SGD::Color m_HealthColor = { 0, 0, 0, 0 };

	SGD::Rectangle Companion1rect = { 100 , 100 , 164 , 164 };
	SGD::Rectangle Companion1HB = { 50 , 60 , 150 , 90 };
	SGD::Rectangle Companion2rect = { 100 , 300 , 164 , 364 };
	SGD::Rectangle Companion2HB = { 50 , 260 , 150 , 290 };

	AnimationManager* m_pAnimator;
	bool m_bUpdateAnimation = false;


	float m_fDeathAnimationTimer = 3.0f;

	int ActionSelected = 0;
	bool selected = false;
	int m_nCursor = 0;
};

