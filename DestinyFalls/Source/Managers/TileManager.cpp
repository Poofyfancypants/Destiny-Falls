#include "stdafx.h"
#include "TileManager.h"
#include "../Game Core/Game.h"
#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"

#include "../Game States/GameplayState.h"
#include "../Game Objects/Player.h"

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
	int xIndex, yIndex, nMapSizeX, nMapSizeY, nGridWidth, nGridHeight, col;

	pRoot->Attribute( "MapSizeX", &nMapSizeX );
	pRoot->Attribute( "MapSizeY", &nMapSizeY );
	pRoot->Attribute( "tileWidth", &nGridWidth );
	pRoot->Attribute( "tileHeight", &nGridHeight);

	m_szGridSize = SGD::Size((float)nGridWidth, (float)nGridHeight);
	m_szMapSize = SGD::Size((float)nMapSizeX, (float)nMapSizeY);

	// - Access roots first ChildElement.
	TiXmlElement* pTile = pRoot->FirstChildElement();


	while( pTile != nullptr )
	{
		pTile->Attribute( "sourceX", &readTile.nX );
		pTile->Attribute( "sourceY", &readTile.nY );
		pTile->Attribute( "xIndex", &xIndex );
		pTile->Attribute( "yIndex", &yIndex );
		pTile->Attribute( "Collision", &col );

		m_TileMap.resize( nMapSizeX );
		for( size_t i = 0; i < m_TileMap.size(); i++ )
			m_TileMap[i].resize( nMapSizeY );

		readTile.collisionTile = (bool)col;

		readTile.CollisionRect = SGD::Rectangle( (float)( xIndex*m_szGridSize.width ),
			(float)( yIndex*m_szGridSize.height ),
			(float)xIndex*m_szGridSize.width + m_szGridSize.width,
			(float)yIndex*m_szGridSize.height + m_szGridSize.height );

		m_TileMap[xIndex][yIndex] = readTile;
		pTile = pTile->NextSiblingElement();
	}
	return true;

}

bool TileManager::DrawLevel( SGD::Point _offset, SGD::Point _playerPos )
{
	// - Load the tile set image
	SGD::GraphicsManager *pGraphics = SGD::GraphicsManager::GetInstance();

	SGD::HTexture tileSet = pGraphics->LoadTexture( "default.bmp" );

	float height = Game::GetInstance()->GetScreenHeight()/2;
	float width = Game::GetInstance()->GetScreenWidth()/2;

	for( size_t i = 0; i < m_TileMap.size(); i++ )
	{
		for( size_t j = 0; j < m_TileMap[0].size(); j++ )
		{
			SGD::Point dest = { (float)( ( i*m_szGridSize.width ) - _offset.x ), (float)( ( j*m_szGridSize.height ) - _offset.y ) };
			SGD::Rectangle source = { (float)( m_TileMap[i][j].nX*m_szGridSize.width ),
				(float)( m_TileMap[i][j].nY*m_szGridSize.height ),
				(float)( m_TileMap[i][j].nX*m_szGridSize.width + m_szGridSize.width ),
				(float)( m_TileMap[i][j].nY*m_szGridSize.height + m_szGridSize.height ) };


				pGraphics->DrawTextureSection(
					tileSet,
					dest,
					source
					);
		}
	//pGraphics->DrawRectangle(screen, SGD::Color(155,155,155));
	}

	pGraphics->UnloadTexture( tileSet );
	return true;

}

bool TileManager::TileCollision( Object* _player, SGD::Point _futurePos )
{

	Player* player = dynamic_cast<Player*>( _player );
	SGD::Rectangle PlayerCollision = SGD::Rectangle( _futurePos, player->GetSize() );

	for( size_t i = 0; i < m_TileMap.size(); i++ )
	{
		for( size_t j = 0; j < m_TileMap[0].size(); j++ )
		{
			if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].collisionTile )
				return true;
		}
	}
	return false;
}