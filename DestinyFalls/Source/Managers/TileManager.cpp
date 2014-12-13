#include "stdafx.h"
#include "TileManager.h"
#include "../Game Core/Game.h"
#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"

#include "../Game States/GameplayState.h"
#include "../Game Objects/Player.h"
#include "../Game Objects/Enemy.h"
#include "../Game Objects/Boulder.h"
#include "../Game Objects/iObject.h"

#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_Declarations.h"
TileManager::TileManager()
{

}


TileManager::~TileManager()
{
	SGD::GraphicsManager::GetInstance()->UnloadTexture( tileSet );

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
	int startSlide, endSlide, checkPoint, boulderSpawn, QTevent, nextLevel, prevLevel;
	int mainLevel, sideLevel;
	tilePath = "resource/graphics/TileSets/";

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
		pTile->Attribute( "MainLevel", &mainLevel );
		pTile->Attribute( "SideLevel", &sideLevel );
		pTile->Attribute( "PrevLevel", &prevLevel );
		pTile->Attribute( "NextLevel", &nextLevel );
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
		pTile->Attribute( "CompanionID", &readTile.m_nCompanionID );
		pTile->Attribute( "QTEvent", &QTevent );
		pTile->Attribute( "chestID", &readTile.m_nChestID );


		m_TileMap.resize( nMapSizeX );
		for( size_t i = 0; i < m_TileMap.size(); i++ )
			m_TileMap[i].resize( nMapSizeY );

		readTile.collisionTile = (col ? true : false);
		readTile.PlayerSpawn = (pSpawn ? true : false);
		readTile.StartSlide = (startSlide ? true : false);
		readTile.EndSlide = (endSlide ? true : false);
		readTile.CheckPoint = (checkPoint ? true : false);
		readTile.BoulderSpawn = (boulderSpawn ? true : false);
		readTile.QTEvent = (QTevent ? true : false);
		readTile.NextLevel = (nextLevel ? true : false);
		readTile.PrevLevel = (prevLevel ? true : false);
		readTile.SideLevel = (sideLevel ? true : false);
		readTile.MainLevel = (mainLevel ? true : false);

		readTile.CollisionRect = SGD::Rectangle( (float)( xIndex*m_szGridSize.width ),
			(float)( yIndex*m_szGridSize.height ),
			(float)xIndex*m_szGridSize.width + m_szGridSize.width,
			(float)yIndex*m_szGridSize.height + m_szGridSize.height );

		m_TileMap[xIndex][yIndex] = readTile;
		pTile = pTile->NextSiblingElement();
	}

	SpawnObjects();
	return true;

}

bool TileManager::DrawLevel( SGD::Point _offset, SGD::Point _playerPos )
{
	// - Load the tile set image
	SGD::GraphicsManager *pGraphics = SGD::GraphicsManager::GetInstance();

	if( tileSet == SGD::INVALID_HANDLE )
		tileSet = pGraphics->LoadTexture( tilePath.c_str() );


	int top = (int)( ( _offset.y / 2 - _playerPos.y ) / m_szGridSize.height );
	int height = (int)( ( ( Game::GetInstance()->GetScreenHeight() / 2 + _playerPos.y ) / m_szGridSize.height ) + 1 );
	int left = (int)( ( _offset.x / 2 - _playerPos.x ) / m_szGridSize.width );
	int width = (int)( ( ( Game::GetInstance()->GetScreenWidth() / 2 + _playerPos.x ) / m_szGridSize.width ) + 1 );

	if( top < 0 )
		top = 0;
	if( left < 0 )
		left = 0;
	if( width >( int )( m_szMapSize.width ) )
		width = (int)( m_szMapSize.width );
	if( height >( int )( m_szMapSize.height ) )
		height = (int)( m_szMapSize.height );

	for( int i = left; i < width; i++ )
	{
		for( int j = top; j < height; j++ )
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

			if( GameplayState::GetInstance()->GetDebugState() )
			{
				if( m_TileMap[i][j].collisionTile )
				{
					SGD::Rectangle rect = m_TileMap[i][j].CollisionRect;
					rect.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
					pGraphics->DrawRectangle( rect, SGD::Color( 255, 0, 0 ) );
				}
				else if( m_TileMap[i][j].EndSlide || m_TileMap[i][j].StartSlide )
				{
					SGD::Rectangle rect = m_TileMap[i][j].CollisionRect;
					rect.Offset( -GameplayState::GetInstance()->GetWorldCam().x, -GameplayState::GetInstance()->GetWorldCam().y );
					pGraphics->DrawRectangle( rect, SGD::Color( 0, 255, 0 ) );

				}
			}
		}
	}

	return true;

}

// - Returns 0 if no collision, 1 for tile collision, 2 for boulder collision
bool TileManager::TileCollision( Object* _player, SGD::Point _futurePos )
{

	if( _player->GetType() == iObject::OBJ_PLAYER )
	{
		Player* player = dynamic_cast<Player*>( _player );
		SGD::Rectangle PlayerCollision = SGD::Rectangle( _futurePos, player->GetSize() );

		int top = (int)( ( GameplayState::GetInstance()->GetWorldCam().y / 2 - GameplayState::GetInstance()->GetPlayer()->GetPosition().y ) / m_szGridSize.height );
		int height = (int)( ( Game::GetInstance()->GetScreenHeight() / 2 + GameplayState::GetInstance()->GetPlayer()->GetPosition().y ) / m_szGridSize.height );
		int left = (int)( ( GameplayState::GetInstance()->GetWorldCam().x / 2 - GameplayState::GetInstance()->GetPlayer()->GetPosition().x ) / m_szGridSize.width );
		int width = (int)( ( Game::GetInstance()->GetScreenWidth() / 2 + GameplayState::GetInstance()->GetPlayer()->GetPosition().x ) / m_szGridSize.width );

		if( top < 0 )
			top = 0;
		if( left < 0 )
			left = 0;
		if( width >( int )( m_szMapSize.width ) )
			width = (int)( m_szMapSize.width );
		if( height >( int )( m_szMapSize.height ) )
			height = (int)( m_szMapSize.height );

		for( int i = left; i < width; i++ )
		{
			for( int j = top; j < height; j++ )
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

				}
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].NextLevel )
				{
					if( GameplayState::GetInstance()->GetCurrentSideLevel() == -1 )
						GameplayState::GetInstance()->SetSideLevel( 0 );

					if( GameplayState::GetInstance()->GetChangeLevel() == false )
					{
						GameplayState::GetInstance()->SetLoadLevelPosition( false );
						GameplayState::GetInstance()->SetLoadSidePosition( false );
						GameplayState::GetInstance()->NextLevel();
						GameplayState::GetInstance()->NextSideLevel();
						GameplayState::GetInstance()->ChangeLevel( true );
						
						m_ptPrevLevelPos = player->GetCheckpoint();

					}
				}
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].PrevLevel )
				{
					if( GameplayState::GetInstance()->GetChangeLevel() == false )
					{
						GameplayState::GetInstance()->SetLoadLevelPosition( true );
						GameplayState::GetInstance()->SetLoadSidePosition( false );

						GameplayState::GetInstance()->PrevLevel();
						GameplayState::GetInstance()->PrevSideLevel();
						GameplayState::GetInstance()->ChangeLevel( true );
					}
				}
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].SideLevel )
				{
					if( GameplayState::GetInstance()->GetChangeSideLevel() == false )
					{
						if( GameplayState::GetInstance()->GetCurrentSideLevel() == -1 )
							GameplayState::GetInstance()->SetSideLevel( 0 );


						GameplayState::GetInstance()->SetLoadSidePosition( false );
						GameplayState::GetInstance()->SetLoadLevelPosition( false );

						GameplayState::GetInstance()->ChangeSideLevel( true );
						switch( player->GetDirection() )
						{
						case 1:
							m_ptPrevBonusPos = { (float)( i*m_szGridSize.width ), (float)( ( 1 + j )*m_szGridSize.height ) };
							break;
						case 2:
							m_ptPrevBonusPos = { (float)( i*m_szGridSize.width ), (float)( ( j - 1 )*m_szGridSize.height ) };
							break;
						case 3:
							m_ptPrevBonusPos = { (float)( ( i + 1 )*m_szGridSize.width ), (float)( j*m_szGridSize.height ) };
							break;
						case 4:
							m_ptPrevBonusPos = { (float)( ( i - 1 )*m_szGridSize.width ), (float)( j*m_szGridSize.height ) };
							break;
						}
					}
				}
				if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].MainLevel )
				{
					if( GameplayState::GetInstance()->GetChangeSideLevel() == false )
					{
						GameplayState::GetInstance()->SetLoadSidePosition( true );
						GameplayState::GetInstance()->SetLoadLevelPosition( false );
						GameplayState::GetInstance()->ChangeLevel( true );
					}
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
				//else if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].StartSlide )
				//	return true;
				//else if( PlayerCollision.IsIntersecting( m_TileMap[i][j].CollisionRect ) && m_TileMap[i][j].EndSlide )
				//	return true;
			}
		}

	}
	return false;
}

void TileManager::SpawnObjects()
{
	for( size_t row = 0; row < m_TileMap.size(); row++ )
	{
		for( size_t col = 0; col < m_TileMap[0].size(); col++ )
		{
			SGD::Point dest = { (float)( row*m_szGridSize.width ), (float)( col*m_szGridSize.height ) };
			//SGD::Point dest = { (float)( ( row*m_szGridSize.width ) - GameplayState::GetInstance()->GetWorldCam().x ), (float)( ( col*m_szGridSize.height ) - GameplayState::GetInstance()->GetWorldCam().y ) };
			if( m_TileMap[row][col].m_nEnemyID != 0 )
			{
				// - MOER SPESIFIC WHEN WE HAVE MORE ENEMY TYPES

				Object* tempEnemy = nullptr;
				tempEnemy = GameplayState::GetInstance()->CreateEnemy( dest, m_TileMap[row][col].m_nEnemyID );
				GameplayState::GetInstance()->GetObjManager()->AddObject( tempEnemy, GameplayState::ENEMY_BUCKET );
				tempEnemy->Release();
			}
			if( m_TileMap[row][col].PlayerSpawn )
			{
				GameplayState::GetInstance()->GetPlayer()->SetPosition( dest );
				//( (Player*)GameplayState::GetInstance()->GetPlayer() )->SetCheckPoint( dest );
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
			if( m_TileMap[row][col].m_nCompanionID != 0 )
			{
				Object* tempComp = nullptr;
				tempComp = GameplayState::GetInstance()->CreateCompanion( dest, m_TileMap[row][col].m_nCompanionID );
				GameplayState::GetInstance()->GetObjManager()->AddObject( tempComp, GameplayState::COMPANION_BUCKET );
				tempComp->Release();
			}
			//if( m_TileMap[row][col].NextLevel )
			//{
			//	switch( dynamic_cast<Player*>( GameplayState::GetInstance()->GetPlayer() )->GetDirection() )
			//	{
			//	case 0:
			//		break;
			//	case 1:
			//		m_ptPrevLevelPos = { (float)( row*m_szGridSize.width ), (float)( ( 1 + col )*m_szGridSize.height ) };
			//		break;
			//	case 2:
			//		m_ptPrevLevelPos = { (float)( row*m_szGridSize.width ), (float)( ( col - 1 )*m_szGridSize.height ) };
			//		break;
			//	case 3:
			//		m_ptPrevLevelPos = { (float)( ( row + 1 )*m_szGridSize.width ), (float)( col*m_szGridSize.height ) };
			//		break;
			//	case 4:
			//		m_ptPrevLevelPos = { (float)( ( row - 1 )*m_szGridSize.width ), (float)( col*m_szGridSize.height ) };
			//		break;
			//	}
			//}
		}

	}
}

void TileManager::NextWaypoint( Enemy* _enemy )
{

	if( _enemy->GetType() == iObject::OBJ_ENEMY )
	{
		int id = _enemy->GetWaypointID();
		SGD::Point next = _enemy->GetNextWaypoint();
		SGD::Point currPos = _enemy->GetPosition();
		SGD::Point range = { 150, 150 };
		for( size_t row = 0; row < m_TileMap.size(); row++ )
		{
			for( size_t col = 0; col < m_TileMap[0].size(); col++ )
			{
				SGD::Point dest = { (float)( row*m_szGridSize.width ), (float)( col*m_szGridSize.height ) };
				int temp = m_TileMap[row][col].m_nWaypointID;
				// - Is it the next waypoint? ID == WP being chased
				if( id == m_TileMap[row][col].m_nWaypointID )
				{
					// - Is waypoint within the range?
					if( ( abs( dest.x - currPos.x ) <= range.x && abs( dest.y - currPos.y ) <= range.y ) )
					{
						_enemy->SetNextWaypoint( dest );
						_enemy->SetPath( dest - currPos );
						return;
					}
				}
			}
		}
	}

}