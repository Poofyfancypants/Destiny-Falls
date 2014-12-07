#pragma once

#include "IGameState.h"
#include "InventoryState.h"
#include "../Managers/ObjectManager.h"
#include "../Game Objects/Object.h"
#include "../../SGD Wrappers/SGD_Handle.h"		
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../Managers/TileManager.h"
#include "../Managers/AnimationManager.h"
#include "../Managers/ParticleManager.h"
#include "../Managers/DialogManager.h"

class GameplayState :
	public IGameState
{
public:

	// - Holds all the levels of the game.
	enum LevelList { TUTORIAL_LEVEL, EARTH_LEVEL, WATER_LEVEL, AIR_LEVEL, FIRE_LEVEL, BOSS_LEVEL };
	enum SideLevels { TUTORIAL_SIDE, EARTH_SIDE, WATER_SIDE, AIR_SIDE, FIRE_SIDE, BOSS_SIDE };
	enum BucketList {
		BOULDER_BUCKET, PLAYER_BUCKET, ENEMY_BUCKET,
		CHEST_BUCKET, TRAP_BUCKET, TUTORIAL_HERO_BUCKET,
		TUTORIAL_BOSS_BUCKET, COMPANION_BUCKET
	};
	static GameplayState* GetInstance( void );

	virtual void Enter( void )				override;
	virtual void Exit( void )					override;
	virtual bool Input( void )				override;
	virtual void Update( float elapsedTime )	override;
	virtual void Render( void )				override;
	ObjectManager* GetObjManager() const { return m_pObjects; }
	// World Size Accessors
	float	GetWorldWidth( void ) const	{ return m_fWorldWidth; }
	float	GetWorldHeight( void ) const	{ return m_fWorldHeight; }

	SGD::Point GetWorldCam( void ) const	{ return m_ptWorldCam; }

	// - Debug A/M
	bool GetDebugState() const { return m_bDebug; }
	void SetDebugState( bool _state ) { m_bDebug = _state; }

	Object* GetPlayer() { return m_pPlayer; }
	TileManager* GetMap() const { return m_pMap; }

	Object* CreatePlayer( SGD::Point _pos );
	Object* CreateEnemy( SGD::Point _pos );
	Object* CreateChest( SGD::Point _pos );

	//Audio
	SGD::HAudio bmusic = SGD::INVALID_HANDLE;
	SGD::HAudio m_mMusic = SGD::INVALID_HANDLE;
	SGD::HAudio m_mButton = SGD::INVALID_HANDLE;

	Object* CreateChest( SGD::Point _pos, int _id );
	Object* CreateForge( SGD::Point _pos );

	Object* CreateTrap( SGD::Point _pos, int _id );
	Object* CreateBoulder( SGD::Point _pos );
	Object* CreateCompanion( SGD::Point _pos, int _ID );
	SGD::HTexture m_hInvButton = SGD::INVALID_HANDLE;
	SGD::Rectangle InventoryButton = { 0, 0, 100, 100 };
	SGD::Rectangle ForgeButton = { 0, 0, 100, 100 };
	SGD::Rectangle HealthPotionPosition = { 0, 0, 100, 100 };

	// - Hepler function to create the next level.
	void LoadNewLevel();
	void LoadNewSideLevel();
	void SetLevel( int _level ) { m_nCurrentLevel = _level; }
	void SetSideLevel( int _level ) { m_nCurrentSideLevel = _level; }
	void NextLevel() { m_nCurrentLevel++; }
	void PrevLevel() { m_nCurrentLevel--; }
	void NextSideLevel() { m_nCurrentSideLevel++; }
	void PrevSideLevel() { m_nCurrentSideLevel--; }
	void ChangeLevel( bool _change ) { m_bChangeLevels = _change; }
	void ChangeSideLevel(bool _change) {  m_bChangeSideLevels = _change; }
	bool GetChangeLevel() const { return m_bChangeLevels; }
	bool GetChangeSideLevel() const { return m_bChangeSideLevels; }
	void SetLoadLevelPosition(bool _change) {m_bSetLevelPosition = _change;}
	void SetLoadSidePosition(bool _change) {m_bSetSidePosition = _change;}
	int GetCurrentLevel() const { return m_nCurrentLevel; }
	int GetCurrentSideLevel() const { return m_nCurrentSideLevel; }

	void UnloadAndCreate();

	// - Helper functions for the Tutorial
	void HandleTutorial();
	void RenderDialog();
	SGD::HTexture GetPortrait() const { return m_hDialogImg; }

private:
	GameplayState() = default;
	virtual ~GameplayState() = default;

	GameplayState( const GameplayState& ) = delete;
	GameplayState& operator=( const GameplayState& ) = delete;

	int m_nCursor = 0;
	bool m_bSelect = false;

	// World Size
	float m_fWorldWidth = 1;
	float m_fWorldHeight = 1;

	SGD::Point m_ptWorldCam = SGD::Point{ 0, 0 };

	SGD::HTexture m_hplayer = SGD::INVALID_HANDLE;
	SGD::HTexture m_henemy = SGD::INVALID_HANDLE;
	SGD::HTexture m_hChest = SGD::INVALID_HANDLE;
	SGD::HTexture m_hBoulder = SGD::INVALID_HANDLE;
	SGD::HTexture m_hHealthPot = SGD::INVALID_HANDLE;
	SGD::HTexture m_hForge = SGD::INVALID_HANDLE;

	Object* m_pPlayer = nullptr;
	ObjectManager* m_pObjects;
	TileManager* m_pMap;
	AnimationManager* m_pAnimator;

	ParticleManager m_particle;

	bool m_bPaused = false;

	// - Debug Mode
	bool m_bDebug = false;
	float m_fFPSTime = 0;
	int m_nFrames = 0;
	int m_nFPS = 0;

	// - Level progression
	int m_nCurrentLevel = 0;
	bool m_bChangeLevels = false;
	int m_nCurrentSideLevel = -1;
	bool m_bChangeSideLevels = false;
	bool m_bSetSidePosition = false;
	bool m_bSetLevelPosition = false;
	// - Tutorial Level
	SGD::HTexture m_hHero = SGD::INVALID_HANDLE;
	SGD::HTexture m_hRanger = SGD::INVALID_HANDLE;
	SGD::HTexture m_hCleric = SGD::INVALID_HANDLE;
	SGD::HTexture m_hBoss = SGD::INVALID_HANDLE;
	SGD::HTexture m_hDialogImg = SGD::INVALID_HANDLE;
	bool m_bFirstDialog = false;
	bool m_bPuzzleDialog = false;
	bool m_bBoulderDialog = false;
	bool m_bTrapDialog = false;
	bool m_bMainDialog = false;
	bool m_bChestDialog = false;
	bool m_bSigmundDialog = false;
	bool m_bIcelandic = false;
};