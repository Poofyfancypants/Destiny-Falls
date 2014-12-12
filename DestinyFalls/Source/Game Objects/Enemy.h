#pragma once
#include "AnimatedObject.h"
#include "MovingObject.h"
#include "../../SGD Wrappers/SGD_Listener.h"
#include "../Managers/AnimationManager.h"

class Enemy :
	public AnimatedObject,
	public SGD::Listener
{
public:
	Enemy();
	virtual ~Enemy();

	virtual void Update( float elapsedTime ) override;
	virtual void Render( void ) override;
	virtual int GetType( void ) const { return OBJ_ENEMY; }
	virtual SGD::Rectangle GetRect( void ) const override;
	virtual void HandleCollision( const iObject* pOther ) override;
	virtual void HandleEvent( const SGD::Event* pEvent ) override;

	// - WP accessors
	int GetWaypointID() const { return m_nWaypointID; }
	SGD::Point GetNextWaypoint() const { return m_ptNextWaypoint; }
	SGD::Point GetCurrentWaypoint() const { return m_ptCurrentWaypoint; }
	SGD::Vector GetPath() const {return m_vPath;}

	void SetWaypointID( int _id ) { m_nWaypointID = _id; }
	void SetNextWaypoint( SGD::Point _pt ) { m_ptNextWaypoint = _pt; }
	void SetCurrentWaypoint( SGD::Point _pt ) { m_ptCurrentWaypoint = _pt; }
	void SetPath(SGD::Vector _pth) {m_vPath = _pth;}

	int GetEnemyType() const { return m_nEnemyType; }
	void SetEnemyType(int _id) { m_nEnemyType = _id; }

	void SetAnimation(int _id);

private:
	// - Waypoint being chased
	int m_nWaypointID = 1;
	SGD::Point m_ptNextWaypoint;
	SGD::Point m_ptCurrentWaypoint;
	SGD::Vector m_vPath;

	int m_nEnemyType = -1;

	AnimationManager* m_pAnimator = nullptr;
	bool m_bAnimationSet = false;
};

