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
	int GetPosIndex( void ){ return m_nPosIndex; }
	void SetPosIndex( int posIndex ){ m_nPosIndex = posIndex; }
private:
	int * m_CurrentTurn;
	int m_nHealth = 20;

	int m_nPosIndex = 0;
	Companion_Type m_CoType;
	int TypeString = 0;

	SGD::HTexture m_hCompanion = SGD::INVALID_HANDLE;

	SGD::Rectangle Companion1rect = { 200 , 110 , 264 , 174 };
	SGD::Rectangle Companion2rect = { 200 , 290 , 264 , 354 };
	SGD::Rectangle Companion1HB = { 50 , 110 , 175 , 140 };
	SGD::Rectangle Companion2HB = { 50 , 290 , 175 , 320 };

	AnimationManager* m_pAnimator;
	bool m_bUpdateAnimation = false;


	int ActionSelected = 0;
	bool selected = false;
	int m_nCursor = 0;
};

