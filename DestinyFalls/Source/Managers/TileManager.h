#pragma once
#include <map>
#include <string>
#include <vector>
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

using namespace std;
struct Tile
{
	int nX, nY;
	int nWidth, nHeight;
	int m_nTileID;
	bool collisionTile;
	SGD::Rectangle CollisionRect;


};

class TileManager
{
public:
	TileManager();
	~TileManager();

	bool LoadLevel(const char* _tilePath);
	bool DrawLevel();

private:
	string m_strTileSetPath;
	vector<vector<Tile>> m_TileMap;
	SGD::Size m_szMapSize;

};

