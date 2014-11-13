#pragma once
#include "..\..\SGD Wrappers\SGD_Geometry.h"
#include <vector>
#include <string>
using namespace std;

class Frame
{
	SGD::Rectangle m_rDrawRect;
	vector<SGD::Rectangle> m_vCollisionRects;
	string m_szEvent;
	SGD::Point m_ptAnchorPoint;

	float m_fDuration;

	int m_nDamage = 0;

	bool m_bTriggerCombat = false;
	bool m_bTriggerQT = false;



public:
	Frame() = default;
	~Frame() = default;

	///////////////////////////////////////////////////////
	//ACCESSORS

	//Returns the m_rDrawRect
	SGD::Rectangle GetDrawRect() { return m_rDrawRect; }

	//returns entire vector of m_vCollisionRects
	vector<SGD::Rectangle> GetCollisionRects() { return m_vCollisionRects; }

	//returns a particular collision rect at the specified index
	SGD::Rectangle GetCollisionRect( int index ) { return m_vCollisionRects[ index ]; }

	//returns the string name of the event
	string GetEvent() { return m_szEvent; }

	//Returns m_ptAnchorPoint
	SGD::Point GetAnchorPoint(){ return m_ptAnchorPoint; }

	//returns m_fDuration
	float GetDuration(){ return m_fDuration; }

	//returns m_nDamage
	int GetDamage(){ return m_nDamage; }

	//returns m_bTriggerCombat
	bool GetCombatTrigger(){ return m_bTriggerCombat; }

	//returns m_bTriggerQT
	bool GetQTTrigger() { return m_bTriggerQT; }

	///////////////////////////////////////////////////////
	//MUTATORS

	//Set m_rDrawRect
	void SetDrawRect( SGD::Rectangle drawRect ){ m_rDrawRect = drawRect; }

	//Set entire vector of m_vCollisionRects
	void SetCollisionRectVector( vector<SGD::Rectangle> collisionRectVector ) { m_vCollisionRects = collisionRectVector; }

	//Set a particular collisionRect at the specified index of the m_vCollisionRectVector 
	//		(if there is not already a rect at the specified index, this will probably blow up the program.
	//			it is meant to allow you to change a rect already in the vector, not add one.)
	//				----to add a collision rect use the AddCollisionRect() function-------
	void SetCollisionRect( int index , SGD::Rectangle collisionRect ){ m_vCollisionRects[ index ] = collisionRect; }

	//Set the event name 
	void SetEventName( string eventName ) { m_szEvent = eventName; }

	//Set m_ptAnchorPoint
	void SetAnchorPoint( SGD::Point anchorPoint ) { m_ptAnchorPoint = anchorPoint; }

	//Set m_fDuration
	void SetDuration( float duration ) { m_fDuration = duration; }

	//Set m_nDamage 
	//	-	how much damage is triggered by this frame
	void SetDamage( int damage ) { m_nDamage = damage; }

	//Set m_bTriggerCombat
	//	-	Does this frame trigger combat?
	void SetCombatTrigger( bool combatTrigger ) { m_bTriggerCombat = combatTrigger; }

	//Set m_bTriggerQT
	//	-	 Does this frame trigger a QT event?

	void SetQTTrigger( bool qtTrigger ) { m_bTriggerQT = qtTrigger; }


	///////////////////////////////////////////////////////
	//FUNCTIONS

	//push a new collision rect back into the collisionRects vector
	void AddCollisionRect( SGD::Rectangle collisionRect );




};

