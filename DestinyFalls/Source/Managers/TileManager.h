#pragma once
#include <map>
#include <string>
#include <vector>
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

class Object;

using namespace std;
struct Tile
{
	int nX, nY;
	int m_nTileID;
	int m_nEnemyID;
	bool collisionTile;
	bool PlayerSpawn;
	bool StartSlide;
	bool EndSlide;
	bool CheckPoint;
	SGD::Rectangle CollisionRect;


};

class TileManager
{
public:
	TileManager();
	~TileManager();

	bool LoadLevel(const char* _tilePath);
	bool DrawLevel(SGD::Point _offset, SGD::Point _playerPos);
	bool TileCollision(Object* _player, SGD::Point _futurePos);
	void SpawnEnemies();
private:
	string m_strTileSetPath;
	vector<vector<Tile>> m_TileMap;
	SGD::Size m_szMapSize;
	SGD::Size m_szGridSize;

};

