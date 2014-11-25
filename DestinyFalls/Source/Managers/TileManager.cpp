#include "stdafx.h"
#include "TileManager.h"
#include "../Game Core/Game.h"
#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"

#include "../Game States/GameplayState.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Boulder.h"
#include "../Game Objects/iObject.h"

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
	int xIndex, yIndex, nMapSizeX, nMapSizeY, nGridWidth, nGridHeight, col, pSpawn;
	int startSlide, endSlide, checkPoint, boulderSpawn, QTevent;
	tilePath = "resource/graphics/";

	pRoot->Attribute( "MapSizeX", &nMapSizeX );
	pRoot->Attribute( "MapSizeY", &nMapSizeY );
	pRoot->Attribute( "tileWidth", &nGridWidth );
	pRoot->Attribute( "tileHeight", &nGridHeight );
	tilePath += pRoot->Attribute( "tileSetPath" );

	m_szGridSize = SGD::Size( (float)nGridWidth, (float)nGridHeight );
	m_szMapSize = SGD::Size( (float)nMapSizeX, (float)nMapSizeY );

	// - Access roots first ChildElement.
	TiXmlElement* pTile = pRoot->FirstChildElement();


	while( pTile != nullptr )
	{
		pTile->Attribute( "sourceX", &readTile.nX );
		pTile->Attribute( "sourceY", &readTile.nY );
		pTile->Attribute( "enemyID", &readTile.m_nEnemyID );
		pTile->Attribute( "playerSpawn", &pSpawn );
		pTile->Attribute( "xIndex", &xIndex );
		pTile->Attribute( "yIndex", &yIndex );
		pTile->Attribute( "Collision", &col );
		pTile->Attribute( "startSlidingTile", &startSlide );
		pTile->Attribute( "endSlidingTile", &endSlide );
		pTile->Attribute( "checkPoint", &checkPoint );
		pTile->Attribute( "Boulder", &boulderSpawn );
		pTile->Attribute( "trapID", &readTile.m_nTrapID );
		pTile->Attribute( "waypointID", &readTile.m_nWaypointID );
		pTile->Attribute( "QTEvent", &QTevent );
		pTile->Attribute( "chestID", &readTile.m_nChestID );

		m_TileMap.resize( nMapSizeX );
		for( size_t i = 0; i < m_TileMap.size(); i++ )
			m_TileMap[i].resize( nMapSizeY );

		readTile.collisionTile = (bool)col;
		readTile.PlayerSpawn = (bool)pSpawn;
		readTile.StartSlide = (bool)startSlide;
		readTile.EndSlide = (bool)endSlide;
		readTile.CheckPoint = (bool)checkPoint;
		readTile.BoulderSpawn = (bool)boulderSpawn;
		readTile.QTEvent = (bool)QTevent;

		readTile.CollisionRect = SGD::Rectangle( (float)( xIndex*m_szGridSize.width ),
			(float)( yIndex*m_szGridSize.height ),
			(float)xIndex*m_szGridSize.width + m_szGridSize.width,
			(float)yIndex*m_szGridSize.height + m_szGridSize.height );

		m_TileMap[xIndex][yIndex] = readTile;
		pTile = pTile->NextSiblingElement();
	}

	SpawnEnemies();
	return true;

}

bool TileManager::DrawLevel( SGD::Point _offset, SGD::Point _playerPos )
{
	// - Load the tile set image
	SGD::GraphicsManager *pGraphics = SGD::GraphicsManager::GetInstance();

	tileSet = pGraphics->LoadTexture( tilePath.c_str() );


	float height = Game::GetInstance()->GetScreenHeight() / 2;
	float width = Game::GetInstance()->GetScreenWidth() / 2;

	//SGD::Rectangle screen = SGD::Rectangle( _playerPos.x-width, _playerPos.y-height, _playerPos.x+width, _playerPos.y +height );

	for( size_t i = 0; i < m_TileMap.size(); i++ )
	{
		for( size_t j = 0; j < m_TileMap[0].size(); j++ )
		{
			SGD::Point dest = { (float)( ( i*m_szGridSize.width ) - _offset.x ), (float)( ( j*m_szGridSize.height ) - _offset.y ) };
			SGD::Rectangle source = { (float)( m_TileMap[i][j].nX*m_szGridSize.width ),
				(float)( m_TileMap[i][j].nY*m_szGridSize.height ),
				(float)( m_TileMap[i][j].nX*m_szGridSize.width + m_szGridSize.width ),
				(float)( m_TileMap[i][j].nY*m_szGridSize.height + m_szGridSize.height ) };

			// - Tile culling
			if( m_TileMap[i][j].CollisionRect.left > _playerPos.x + width )
				continue;
			else if( m_TileMap[i][j].CollisionRect.bottom < _playerPos.y - height )
				continue;
			else if( m_TileMap[i][j].CollisionRect.right < _playerPos.x - width )
				continue;
			else if( m_TileMap[i][j].CollisionRect.top > _playerPos.y + height )
				continue;

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

// - Returns 0 if no collision, 1 for tile collision, 2 for boulder collision
bool TileManager::TileCollision( Object* _player, SGD::Point _futurePos )
{

	if( _player->GetType() == iObject::OBJ_PLAYER )
	{
		Player* player = dynamic_cast<Player*>( _player );
		SGD::Rectangle PlayerCollision = SGD::Rectangle( _futurePos, player->GetSize() );

		for( size_t i = 0; i < m_TileMap.size(); i++ )
		{
			for( size_t j = 0; j < m_TileMap[0].size(); j++ )
			{
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].CheckPoint )
				{
					player->SetCheckPoint( SGD::Point( m_TileMap[i][j].CollisionRect.left, m_TileMap[i][j].CollisionRect.top ) );
				}
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].StartSlide )
					player->SetSliding( true );

				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].EndSlide )
				{
					player->SetSliding( false );
					player->SetMoving( false );
				}
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].m_nTrapID != 0 )
				{
					//react to trap;
				}
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].QTEvent )
				{
					// QT Event;
				}
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].collisionTile )
					return true;
			}
		}
	}
	else if( _player->GetType() == iObject::OBJ_BOULDER )
	{
		Boulder* boulder = dynamic_cast<Boulder*>( _player );
		SGD::Rectangle PlayerCollision = SGD::Rectangle( _futurePos, boulder->GetSize() );

		for( size_t i = 0; i < m_TileMap.size(); i++ )
		{
			for( size_t j = 0; j < m_TileMap[0].size(); j++ )
			{
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].collisionTile )
					return true;
			}
		}

	}
	return 0;
}
void TileManager::SpawnEnemies()
{
	for( size_t row = 0; row < m_TileMap.size(); row++ )
	{
		for( size_t col = 0; col < m_TileMap[0].size(); col++ )
		{
			SGD::Point dest = { (float)( ( row*m_szGridSize.width ) - GameplayState::GetInstance()->GetWorldCam().x ), (float)( ( col*m_szGridSize.height ) - GameplayState::GetInstance()->GetWorldCam().y ) };
			if( m_TileMap[row][col].m_nEnemyID != 0 )
			{
				// - MOER SPESIFIC WHEN WE HAVE MORE ENEMY TYPES

				Object* tempEnemy = nullptr;
				tempEnemy = GameplayState::GetInstance()->CreateEnemy( dest );
				GameplayState::GetInstance()->GetObjManager()->AddObject( tempEnemy, GameplayState::ENEMY_BUCKET );
				tempEnemy->Release();
			}
			if( m_TileMap[row][col].PlayerSpawn )
			{
				GameplayState::GetInstance()->GetPlayer()->SetPosition( dest );
			}
			if( m_TileMap[row][col].m_nChestID != 0 )
			{
				//spawn chest;
				Object* tempChest = nullptr;
				tempChest = GameplayState::GetInstance()->CreateChest( dest, m_TileMap[row][col].m_nChestID );
				GameplayState::GetInstance()->GetObjManager()->AddObject( tempChest, GameplayState::CHEST_BUCKET );
				tempChest->Release();
			}
			if( m_TileMap[row][col].m_nTrapID != 0 )
			{
				// - Spawn Traps
				Object* tempTrap = nullptr;
				tempTrap = GameplayState::GetInstance()->CreateTrap( dest, m_TileMap[row][col].m_nTrapID );
				GameplayState::GetInstance()->GetObjManager()->AddObject( tempTrap, GameplayState::TRAP_BUCKET );
				tempTrap->Release();
			}
			if( m_TileMap[row][col].BoulderSpawn )
			{
				Object* tempObj = nullptr;
				tempObj = GameplayState::GetInstance()->CreateBoulder( dest );
				GameplayState::GetInstance()->GetObjManager()->AddObject( tempObj, GameplayState::BOULDER_BUCKET );
				tempObj->Release();
			}
		}
	}
}
