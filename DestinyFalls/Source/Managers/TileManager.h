#pragma once
#include <map>
#include <string>
#include <vector>
#include "../../SGD Wrappers/SGD_Declarations.h"
#include "../../SGD Wrappers/SGD_Geometry.h"

using namespace std;
struct Tile
{
	SGD::Point m_ptSource;
	SGD::Size m_szSize;
	int m_nTileID;

};

class TileManager
{
public:
	TileManager();
	~TileManager();

	bool ReadXML(string _tilePath);
	bool DrawMap();

private:
	string m_strTileSetPath;
	vector<vector<Tile>> m_TileMap;
	SGD::Size m_szMapSize;

};

