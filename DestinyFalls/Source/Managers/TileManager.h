#pragma once
#include <map>
#include <string>
#include <vector>
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"

class Object;
class Enemy;

using namespace std;
struct Tile
{
	int nX, nY;
	int m_nEnemyID;
	int m_nTrapID, m_nChestID;
	int m_nWaypointID;
	int m_nCompanionID;
	bool QTEvent;
	bool collisionTile;
	bool PlayerSpawn;
	bool StartSlide;
	bool EndSlide;
	bool CheckPoint;
	bool BoulderSpawn;
	bool NextLevel;
	bool PrevLevel;
	bool MainLevel;
	bool SideLevel;
	
	SGD::Rectangle CollisionRect;

};

class TileManager
{
public:
	TileManager();
	~TileManager();

	bool LoadLevel(const char* _tilePath);
	bool DrawLevel(SGD::Point _offset, SGD::Point _playerPos);
	// - Returns false if no collision, true if collision
	bool TileCollision(Object* _player, SGD::Point _futurePos);
	void SpawnObjects();
	void NextWaypoint(Enemy* _enemy);
	SGD::Point GetPrevLevelPosition() const {return m_ptPrevLevelPos;}
	SGD::Point GetPrevPosition() const {return m_ptPrevBonusPos;}
	void SetPrevLevelPosition(SGD::Point _Pos) {m_ptPrevLevelPos = _Pos;}
	void SetPrevPosition(SGD::Point _Pos) {m_ptPrevBonusPos = _Pos;}
private:
	SGD::HTexture tileSet = SGD::INVALID_HANDLE;
	string m_strTileSetPath;
	string tilePath;
	vector<vector<Tile>> m_TileMap;
	SGD::Size m_szMapSize;
	SGD::Size m_szGridSize;
	SGD::Point m_ptPrevLevelPos;
	SGD::Point m_ptPrevBonusPos;
	
};

