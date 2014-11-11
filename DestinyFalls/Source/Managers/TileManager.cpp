#include "stdafx.h"
#include "TileManager.h"
#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"

#include "../Game States/GameplayState.h"

#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
TileManager::TileManager()
{

}


TileManager::~TileManager()
{

}

bool TileManager::LoadLevel( const char* _file )
{
	TiXmlDocument doc;

	// - Load the XML file
	if( doc.LoadFile( _file ) == false )
		return false;

	// - Load the root element
	TiXmlElement* pRoot = doc.RootElement();
	if( pRoot == nullptr )
		return false;

	Tile readTile;
	int xIndex, yIndex, nMapSizeX, nMapSizeY;

	pRoot->Attribute( "MapSizeX", &nMapSizeX );
	pRoot->Attribute( "MapSizeY", &nMapSizeY );
	pRoot->Attribute( "tileWidth", &readTile.nWidth );
	pRoot->Attribute( "tileHeight", &readTile.nHeight );

	// - Access roots first ChildElement.
	TiXmlElement* pTile = pRoot->FirstChildElement();
	

	while( pTile != nullptr )
	{
		pTile->Attribute( "sourceX", &readTile.nX );
		pTile->Attribute( "sourceY", &readTile.nY );
		pTile->Attribute( "xIndex", &xIndex );
		pTile->Attribute( "yIndex", &yIndex );

		m_TileMap.resize( nMapSizeX );
		for( size_t i = 0; i < m_TileMap.size(); i++ )
			m_TileMap[i].resize( nMapSizeY );


		m_TileMap[xIndex][yIndex] = readTile;
		pTile = pTile->NextSiblingElement();
	}
	return true;

}

bool TileManager::DrawLevel()
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
				SGD::Point((float)((i*m_TileMap[i][j].nWidth) - GameplayState::GetInstance()->GetWorldCam().x), (float)((j*m_TileMap[i][j].nHeight) - GameplayState::GetInstance()->GetWorldCam().y)),
				SGD::Rectangle( (float)left, (float)top, (float)width, (float)height )
				);
		}
	}

	pGraphics->UnloadTexture( tileSet );
	return true;

}
