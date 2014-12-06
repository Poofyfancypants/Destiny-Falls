#pragma once
#include "AnimatedObject.h"
#include "Player.h"

class Companion :
	/*public AnimatedObject,*/ public Player
{
public:
	enum Companion_Type { Cleric = 1, Melee, Mage, Tank };

	Companion();
	~Companion();

	virtual bool TakeTurn( float elapsedTime ) override;
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

private:
	int * m_CurrentTurn;
	int m_nHealth = 20;

	Companion_Type m_CoType;
	int TypeString = 0;

	SGD::HTexture m_hCompanion = SGD::INVALID_HANDLE;

	SGD::Rectangle Comp1HB = { 650, 110, 775, 140 };
	SGD::Rectangle Comp2HB = { 625, 200, 750, 230 };
	SGD::Rectangle Comp1rect = { 561, 110, 625, 174 };
	SGD::Rectangle Comp2rect = { 536, 200, 600, 264 };
	AnimationManager* m_pAnimator;
	bool m_bUpdateAnimation = false;
};

