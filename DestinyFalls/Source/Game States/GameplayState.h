#pragma once

#include "IGameState.h"
#include "../Managers/ObjectManager.h"
#include "../Game Objects/Object.h"
#include "InventoryState.h"
#include "../../SGD Wrappers/SGD_Handle.h"		
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../Managers/TileManager.h"

class GameplayState :
	public IGameState
{
public:

	enum BucketList {PLAYER_BUCKET, ENEMY_BUCKET,};
	static GameplayState* GetInstance(void);

	virtual void Enter(void)				override;
	virtual void Exit(void)					override;
	virtual bool Input(void)				override;
	virtual void Update(float elapsedTime)	override;
	virtual void Render(void)				override;

	// World Size Accessors
	float	GetWorldWidth(void) const	{ return m_fWorldWidth; }
	float	GetWorldHeight(void) const	{ return m_fWorldHeight; }

	SGD::Point GetWorldCam(void) const	{ return m_ptWorldCam; }

private:
	GameplayState() = default;
	virtual ~GameplayState() = default;

	GameplayState(const GameplayState&) = delete;
	GameplayState& operator=(const GameplayState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;

	// World Size
	float m_fWorldWidth = 1;
	float m_fWorldHeight = 1;

	SGD::Point m_ptWorldCam = SGD::Point{ 0, 0 };

	SGD::HTexture m_hplayer = SGD::INVALID_HANDLE;

	Object* m_pPlayer = nullptr;
	ObjectManager* m_pObjects;
	TileManager* m_pMap;
	SGD::HTexture m_hBackImage;

	Object* CreatePlayer();
	Object* CreateEnemy();


};