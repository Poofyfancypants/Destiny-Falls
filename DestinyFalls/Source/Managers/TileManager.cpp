#include "stdafx.h"
#include "TileManager.h"
#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"

#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
TileManager::TileManager()
{

}


TileManager::~TileManager()
{

}

bool TileManager::ReadXML( const char* _file )
{
	TiXmlDocument doc;

	// - Load the XML file
	if( doc.LoadFile( _file ) == false )
		return false;

	// - Load the root element
	TiXmlElement* pRoot = doc.RootElement();
	if( pRoot == nullptr )
		return false;

	//m_TileMap.clear();

	// - Access roots first ChildElement.
	TiXmlElement* pTile = pRoot->FirstChildElement();

	while( pTile != nullptr )
	{
		Tile readTile;
		int xIndex, yIndex, nMapSizeX, nMapSizeY;

		pTile->Attribute( "MapSizeX", &nMapSizeX );
		pTile->Attribute( "MapSizeY", &nMapSizeY );

		pTile->Attribute( "tileWidth", &readTile.nWidth );
		pTile->Attribute( "tileHeight", &readTile.nHeight );
		pTile->Attribute( "sourceX", &readTile.nX );
		pTile->Attribute( "sourceY", &readTile.nY );
		pTile->Attribute( "xIndex", &xIndex );
		pTile->Attribute( "yIndex", &yIndex );

		m_TileMap.resize(nMapSizeX);
		for( size_t i = 0; i < m_TileMap.size(); i++ )
			m_TileMap[i].resize(nMapSizeY);


		//for( size_t i = 0; i < m_TileMap.size(); i++ )
		//{
		//	for( size_t j = 0; j < m_TileMap[0].size(); j++ )
				m_TileMap[xIndex][yIndex] = readTile;
		//}
		pTile = pTile->NextSiblingElement();
	}
		return true;

}

bool TileManager::DrawMap()
{
	// - Load the tile set image
	SGD::GraphicsManager *pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::HTexture tileSet = pGraphics->LoadTexture( "default.bmp" );

	for( size_t i = 0; i < m_TileMap.size(); i++ )
	{
		for( size_t j = 0; j < m_TileMap[0].size(); j++ )
		{
			int left = m_TileMap[i][j].nX*m_TileMap[i][j].nWidth;
			int top = m_TileMap[i][j].nY*m_TileMap[i][j].nHeight;
			int width = m_TileMap[i][j].nX*m_TileMap[i][j].nWidth + m_TileMap[i][j].nWidth;
			int height = m_TileMap[i][j].nY*m_TileMap[i][j].nHeight + m_TileMap[i][j].nHeight;

			pGraphics->DrawTextureSection(
				tileSet,
				SGD::Point( i*m_TileMap[i][j].nWidth, j*m_TileMap[i][j].nWidth ),
				SGD::Rectangle( left, top, width, height )
				);
		}
	}

	pGraphics->UnloadTexture(tileSet);
	return true;

}
