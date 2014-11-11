#pragma once

#include "IGameState.h"
#include "../Managers/ObjectManager.h"
#include "../Game Objects/Object.h"
#include "InventoryState.h"
#include "../../SGD Wrappers/SGD_Handle.h"		
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

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
	ObjectManager* GetObjManager() const { return m_pObjects; }
private:
	GameplayState() = default;
	virtual ~GameplayState() = default;

	GameplayState(const GameplayState&) = delete;
	GameplayState& operator=(const GameplayState&) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;

	Object* m_pPlayer = nullptr;
	ObjectManager* m_pObjects;
	
	SGD::HTexture m_hBackImage;

	Object* CreatePlayer();
	Object* CreateEnemy();
};