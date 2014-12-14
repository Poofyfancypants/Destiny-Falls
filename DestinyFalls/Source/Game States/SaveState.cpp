#include "stdafx.h"
#include "SaveState.h"
#include "MainMenuState.h"
#include "PauseMenuState.h"
#include "../Game Core/Game.h"
#include "../Game Objects/Player.h"
#include "../Managers/BitmapFontManager.h"
#include "../../SGD Wrappers/SGD_Geometry.h"
#include "../../SGD Wrappers/SGD_InputManager.h"
#include "../../SGD Wrappers/SGD_GraphicsManager.h"
#include "../../SGD Wrappers/SGD_AudioManager.h"
#include <fstream>
#include "GameplayState.h"
#include "../TinyXML/tinystr.h"
#include "../TinyXML/tinyxml.h"


SaveState* SaveState::GetInstance()
{
	static SaveState s_Instance;
	return &s_Instance;
}

void SaveState::Enter()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	m_hBackground = pGraphics->LoadTexture( L"resource/graphics/MenuBackgrounds/Options.png" );
	m_hButton = pGraphics->LoadTexture( "resource/graphics/optionsButton.png" );
	m_hButtonHighlighted = pGraphics->LoadTexture( "resource/graphics/optionHighlighted.png" );
	m_hNameFrame = pGraphics->LoadTexture( "resource/graphics/MenuBackgrounds/saveScroll.png" );

	LoadNames();
}

void SaveState::Exit()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	SGD::AudioManager* pAudio = SGD::AudioManager::GetInstance();

	pGraphics->UnloadTexture( m_hButton );
	pGraphics->UnloadTexture( m_hButtonHighlighted );
	pGraphics->UnloadTexture( m_hBackground );
	pGraphics->UnloadTexture( m_hNameFrame );
	SlotName();
}

bool SaveState::Input()
{
	SGD::InputManager* pInput = SGD::InputManager::GetInstance();

	if( pInput->IsKeyPressed( SGD::Key::Escape ) )
	{
		Game::GetInstance()->RemoveState();
	}

	if( m_bRename )
	{
		if( pInput->GetCursorMovement().x || pInput->GetCursorMovement().y )
		{
			if( pInput->GetCursorPosition().IsPointInRectangle( yesRect ) )
				m_nRenameCursor = 0;
			else if( pInput->GetCursorPosition().IsPointInRectangle( noRect ) )
				m_nRenameCursor = 1;
		}

		if( pInput->IsKeyPressed( SGD::Key::Left ) || pInput->IsKeyPressed( SGD::Key::A ) )
			m_nRenameCursor--;
		if( pInput->IsKeyPressed( SGD::Key::Right ) || pInput->IsKeyPressed( SGD::Key::D ) )
			m_nRenameCursor++;

		if( m_nRenameCursor > 1 )
			m_nRenameCursor = 0;
		else if( m_nRenameCursor < 0 )
			m_nRenameCursor = 1;

		if( pInput->IsKeyPressed( SGD::Key::Enter ) || pInput->IsKeyPressed( SGD::Key::MouseLeft ) )
		{
			if( m_nRenameCursor == 0 )
				m_bGetKey = true;
			else if( m_nRenameCursor == 1 )
			{
				m_bGetKey = false;

				switch( m_nCursor )
				{
				case 0:
					Save();
					break;
				case 1:
					Save2();
					break;
				case 2:
					Save3();
					break;
				}
			}
			m_bRename = false;
		}
	}
	else if( m_bGetKey )
	{
		if( pInput->IsAnyKeyPressed() )
		{
			if( pInput->IsKeyPressed( SGD::Key::Shift ) )
				return true;

			switch( m_nCursor )
			{
			case 0:
				if( pInput->IsKeyPressed( SGD::Key::Backspace ) && m_sSlot1Name.length() >= 1 )
					m_sSlot1Name.pop_back();
				else if( m_sSlot1Name.length() <= 15 )
					m_sSlot1Name.push_back( (char)pInput->GetAnyCharPressed() );
				break;
			case 1:
				if( pInput->IsKeyPressed( SGD::Key::Backspace ) && m_sSlot1Name.length() >= 1 )
					m_sSlot2Name.pop_back();
				else if( m_sSlot2Name.length() <= 15 )
					m_sSlot2Name.push_back( (char)pInput->GetAnyCharPressed() );
				break;
			case 2:
				if( pInput->IsKeyPressed( SGD::Key::Backspace ) && m_sSlot1Name.length() >= 1 )
					m_sSlot3Name.pop_back();
				else if( m_sSlot3Name.length() <= 15 )
					m_sSlot3Name.push_back( (char)pInput->GetAnyCharPressed() );
				break;
			case 3:
				break;
			}

			if( pInput->IsKeyPressed( SGD::Key::Enter ) || pInput->IsKeyPressed( SGD::Key::MouseLeft ) )
			{
				m_bGetKey = false;
			}
		}
	}
	else
	{
		if( pInput->IsKeyPressed( SGD::Key::Escape ) )
		{
			Game::GetInstance()->RemoveState();
		}


		if( pInput->GetCursorMovement().x || pInput->GetCursorMovement().y )
		{
			if( pInput->GetCursorPosition().IsPointInRectangle( saveslot1 ) )
				m_nCursor = 0;
			else if( pInput->GetCursorPosition().IsPointInRectangle( saveslot2 ) )
				m_nCursor = 1;
			else if( pInput->GetCursorPosition().IsPointInRectangle( saveslot3 ) )
				m_nCursor = 2;
			else if( pInput->GetCursorPosition().IsPointInRectangle( exit ) )
				m_nCursor = 3;
			else
				m_nCursor = -1;
		}

		if( pInput->IsKeyPressed( SGD::Key::Left ) || pInput->IsKeyPressed( SGD::Key::A ) )
		{
			m_nCursor--;
			if( m_nCursor < 0 )
				m_nCursor = 3;
		}
		else if( pInput->IsKeyPressed( SGD::Key::Right ) || pInput->IsKeyPressed( SGD::Key::D ) )
		{
			m_nCursor++;
			if( m_nCursor > 3 )
				m_nCursor = 0;
		}
		else if( pInput->IsKeyPressed( SGD::Key::Up ) || pInput->IsKeyPressed( SGD::Key::W ) )
		{
			m_nCursor--;
			if( m_nCursor < 0 )
				m_nCursor = 3;
		}
		else if( pInput->IsKeyPressed( SGD::Key::Down ) || pInput->IsKeyPressed( SGD::Key::S ) )
		{
			m_nCursor++;
			if( m_nCursor > 3 )
				m_nCursor = 0;
		}

		if( pInput->IsKeyPressed( SGD::Key::Enter ) || pInput->IsKeyPressed( SGD::Key::MouseLeft ) )
		{
			if( m_nCursor == 3 )
			{
				Game::GetInstance()->RemoveState();
			}
			else if( m_nCursor != -1 )
				m_bRename = true;
		}
	}

	return true;
}

void SaveState::Update( float elapsedTime )
{
	return;
}

void SaveState::Render()
{
	SGD::GraphicsManager* pGraphics = SGD::GraphicsManager::GetInstance();
	BitmapFontManager* pFont = pFont->GetInstance();
	SGD::Color textColor = { 239, 208, 162 };

	pGraphics->DrawTexture( Game::GetInstance()->GetLoadingScreenBkGround(), { 0, 0 }, 0, {}, {}, { .78f, 1.2f } );
	pGraphics->DrawTexture( Game::GetInstance()->GetGameIcon(), { 100, 0 }, 0, {}, {}, { 0.3f, 0.3f } );
	pFont->Render( "Other", "Select a Slot to Save", SGD::Point( 225, 100 ), 1.5f, SGD::Color( 0, 0, 0 ) );


	pGraphics->DrawTexture( m_hButton, SGD::Point( 20, 300 ) );
	pFont->Render( "Other", m_sSlot1Name.c_str(), SGD::Point( 50, 315 ), 1, textColor );
	pGraphics->DrawTexture( m_hButton, SGD::Point( 525, 300 ) );
	pFont->Render( "Other", m_sSlot2Name.c_str(), SGD::Point( 555, 315 ), 1, textColor );
	pGraphics->DrawTexture( m_hButton, SGD::Point( 285, 470 ) );
	pFont->Render( "Other", m_sSlot3Name.c_str(), SGD::Point( 315, 485 ), 1, textColor );
	pGraphics->DrawTexture( m_hButton, SGD::Point( 630, 530 ), {}, {}, {}, { .5f, 1 } );
	pFont->Render( "Other", "Exit", SGD::Point( 655, 545 ), 1, textColor );



	switch( m_nCursor )
	{
	case 0:
		pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 20, 300 ) );
		pFont->Render( "Other", m_sSlot1Name.c_str(), SGD::Point( 50, 315 ), 1, textColor );
		break;
	case 1:
		pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 525, 300 ) );
		pFont->Render( "Other", m_sSlot2Name.c_str(), SGD::Point( 555, 315 ), 1, textColor );
		break;
	case 2:
		pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 285, 470 ) );
		pFont->Render( "Other", m_sSlot3Name.c_str(), SGD::Point( 315, 485 ), 1, textColor );
		break;
	case 3:
		pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 630, 530 ), {}, {}, {}, { .5f, 1 } );
		pFont->Render( "Other", "Exit", SGD::Point( 655, 545 ), 1, textColor );
		break;
	}

	if( m_bRename )
	{

		pGraphics->DrawTexture( m_hNameFrame, SGD::Point( 150, 190 ) );
		pFont->Render( "Other", "Do you want to rename the slot?", SGD::Point( 240, 240 ), .9f, SGD::Color( 0, 0, 0 ) );

		if( m_nRenameCursor == 0 )
			pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 250, 300 ), {}, {}, {}, { .5f, 1 } );
		else
			pGraphics->DrawTexture( m_hButton, SGD::Point( 250, 300 ), {}, {}, {}, { .5f, 1 } );

		if( m_nRenameCursor == 1 )
			pGraphics->DrawTexture( m_hButtonHighlighted, SGD::Point( 450, 300 ), {}, {}, {}, { .5f, 1 } );
		else
			pGraphics->DrawTexture( m_hButton, SGD::Point( 450, 300 ), {}, {}, {}, { .5f, 1 } );

		pFont->Render( "Other", "Yes", SGD::Point( 285, 315 ), 1, textColor );
		pFont->Render( "Other", "No", SGD::Point( 485, 315 ), 1, textColor );
	}
	if( m_bGetKey )
	{
		switch( m_nCursor )
		{
		case 0:
			pGraphics->DrawTexture( m_hNameFrame, SGD::Point( 150, 190 ) );
			pFont->Render( "Other", "Name;", SGD::Point( 230, 240 ), 1, SGD::Color( 0, 0, 0 ) );
			pFont->Render( "Other", m_sSlot1Name.c_str(), SGD::Point( 325, 310 ), 1, SGD::Color( 0, 0, 0 ) );
			break;
		case 1:
			pGraphics->DrawTexture( m_hNameFrame, SGD::Point( 150, 190 ) );
			pFont->Render( "Other", "Name;", SGD::Point( 230, 240 ), 1, SGD::Color( 0, 0, 0 ) );
			pFont->Render( "Other", m_sSlot2Name.c_str(), SGD::Point( 325, 310 ), 1, SGD::Color( 0, 0, 0 ) );
			break;
		case 2:
			pGraphics->DrawTexture( m_hNameFrame, SGD::Point( 150, 190 ) );
			pFont->Render( "Other", "Name;", SGD::Point( 230, 240 ), 1, SGD::Color( 0, 0, 0 ) );
			pFont->Render( "Other", m_sSlot3Name.c_str(), SGD::Point( 325, 310 ), 1, SGD::Color( 0, 0, 0 ) );
			break;
		}
	}

}

void SaveState::SlotName()
{
	fstream fout;
	fout.open( "resource/Save/Names.txt", ios_base::out | ios_base::binary );
	if( fout.is_open() )
	{
		int len = m_sSlot1Name.length() + 1;
		fout.write( (char*)&len, sizeof( len ) );
		fout.write( m_sSlot1Name.c_str(), len );

		len = m_sSlot2Name.length() + 1;
		fout.write( (char*)&len, sizeof( len ) );
		fout.write( m_sSlot2Name.c_str(), len );

		len = m_sSlot3Name.length() + 1;
		fout.write( (char*)&len, sizeof( len ) );
		fout.write( m_sSlot3Name.c_str(), len );

		fout.close();
	}

}

void SaveState::LoadNames()
{
	fstream fin;
	fin.open( "resource/Save/Names.txt", ios_base::in | ios_base::binary );
	char* name;
	int nameLength;
	if( fin.is_open() )
	{

		fin.read( (char*)&nameLength, sizeof( int ) );
		name = new char[nameLength];
		fin.read( name, nameLength );
		m_sSlot1Name = name;

		fin.read( (char*)&nameLength, sizeof( int ) );
		name = new char[nameLength];
		fin.read( name, nameLength );
		m_sSlot2Name = name;

		fin.read( (char*)&nameLength, sizeof( int ) );
		name = new char[nameLength];
		fin.read( name, nameLength );
		m_sSlot3Name = name;

		fin.close();
	}
}

void SaveState::Save()
{
	int health = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetHealth();
	float posx = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().x;
	float posy = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().y;
	int currLevel = GameplayState::GetInstance()->GetCurrentLevel();

	TiXmlDocument doc;

	TiXmlDeclaration* pDel = new TiXmlDeclaration{ "1.0", "utf-8", "" };

	doc.LinkEndChild( pDel );

	TiXmlElement* pRoot = new TiXmlElement{ "Save1" };

	doc.LinkEndChild( pRoot );

	TiXmlElement* pPlayer = new TiXmlElement{ "player_info" };

	pRoot->LinkEndChild( pPlayer );

	pPlayer->SetAttribute( "Health", health );
	pPlayer->SetDoubleAttribute( "PosX", posx );
	pPlayer->SetDoubleAttribute( "PosY", posy );
	pPlayer->SetAttribute( "CurrLevel", currLevel );

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vSword.size(); i++ )
	{
		TiXmlElement* pSword = new TiXmlElement{ "Sword" };

		pPlayer->LinkEndChild( pSword );

		pSword->SetAttribute( "Element", (int)( InventoryState::GetInstance()->m_vSword[i].GetElement() ) );
		pSword->SetAttribute( "Tier", InventoryState::GetInstance()->m_vSword[i].GetTier() );
	}

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vArmor.size(); i++ )
	{
		TiXmlElement* pArmor = new TiXmlElement{ "Armor" };

		pPlayer->LinkEndChild( pArmor );

		pArmor->SetAttribute( "Element", (int)( InventoryState::GetInstance()->m_vArmor[i].GetElement() ) );
		pArmor->SetAttribute( "Tier", InventoryState::GetInstance()->m_vArmor[i].GetTier() );
	}

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vRing.size(); i++ )
	{
		TiXmlElement* pRing = new TiXmlElement{ "Ring" };

		pPlayer->LinkEndChild( pRing );

		pRing->SetAttribute( "Element", (int)( InventoryState::GetInstance()->m_vRing[i].GetElement() ) );
		pRing->SetAttribute( "Tier", InventoryState::GetInstance()->m_vRing[i].GetTier() );
	}

	TiXmlElement* pInv = new TiXmlElement{ "Inventory" };
	pPlayer->LinkEndChild( pInv );
	pInv->SetAttribute( "Size", InventoryState::GetInstance()->m_vRunes.size() );

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vRunes.size(); i++ )
	{
		TiXmlElement* pInv1 = new TiXmlElement{ "Rune" };
		pInv->LinkEndChild( pInv1 );

		pInv1->SetAttribute( "Element", (int)( InventoryState::GetInstance()->m_vRunes[i].GetElement() ) );
		pInv1->SetAttribute( "Tier", InventoryState::GetInstance()->m_vRunes[i].GetTier() );
	}


	doc.SaveFile( "resource/Save/Save.xml" );

}

void SaveState::Save2()
{
	int health = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetHealth();
	float posx = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().x;
	float posy = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().y;
	int currLevel = GameplayState::GetInstance()->GetCurrentLevel();

	TiXmlDocument doc;

	TiXmlDeclaration* pDel = new TiXmlDeclaration{ "1.0", "utf-8", "" };

	doc.LinkEndChild( pDel );

	TiXmlElement* pRoot = new TiXmlElement{ m_sSlot2Name.c_str() };

	doc.LinkEndChild( pRoot );

	TiXmlElement* pPlayer = new TiXmlElement{ "player_info" };

	pRoot->LinkEndChild( pPlayer );

	pPlayer->SetAttribute( "Health", health );
	pPlayer->SetDoubleAttribute( "PosX", posx );
	pPlayer->SetDoubleAttribute( "PosY", posy );
	pPlayer->SetAttribute( "CurrLevel", currLevel );

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vSword.size(); i++ )
	{
		TiXmlElement* pSword = new TiXmlElement{ "Sword" };

		pPlayer->LinkEndChild( pSword );

		pSword->SetAttribute( "Element", InventoryState::GetInstance()->m_vSword[i].GetElement() );
		pSword->SetAttribute( "Tier", InventoryState::GetInstance()->m_vSword[i].GetTier() );
	}

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vArmor.size(); i++ )
	{
		TiXmlElement* pArmor = new TiXmlElement{ "Armor" };

		pPlayer->LinkEndChild( pArmor );

		pArmor->SetAttribute( "Element", InventoryState::GetInstance()->m_vArmor[i].GetElement() );
		pArmor->SetAttribute( "Tier", InventoryState::GetInstance()->m_vArmor[i].GetTier() );
	}

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vRing.size(); i++ )
	{
		TiXmlElement* pRing = new TiXmlElement{ "Ring" };

		pPlayer->LinkEndChild( pRing );

		pRing->SetAttribute( "Element", InventoryState::GetInstance()->m_vRing[i].GetElement() );
		pRing->SetAttribute( "Tier", InventoryState::GetInstance()->m_vRing[i].GetTier() );
	}

	TiXmlElement* pInv = new TiXmlElement{ "Inventory" };
	pPlayer->LinkEndChild( pInv );
	pInv->SetAttribute( "Size", InventoryState::GetInstance()->m_vRunes.size() );

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vRunes.size(); i++ )
	{
		TiXmlElement* pInv1 = new TiXmlElement{ "Rune" };
		pInv->LinkEndChild( pInv1 );

		pInv1->SetAttribute( "Element", InventoryState::GetInstance()->m_vRunes[i].GetElement() );
		pInv1->SetAttribute( "Tier", InventoryState::GetInstance()->m_vRunes[i].GetTier() );
	}


	doc.SaveFile( "resource/Save/Save2.xml" );

}

void SaveState::Save3()
{
	int health = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetHealth();
	float posx = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().x;
	float posy = ( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->GetPosition().y;
	int currLevel = GameplayState::GetInstance()->GetCurrentLevel();

	TiXmlDocument doc;

	TiXmlDeclaration* pDel = new TiXmlDeclaration{ "1.0", "utf-8", "" };

	doc.LinkEndChild( pDel );

	TiXmlElement* pRoot = new TiXmlElement{ m_sSlot3Name.c_str() };

	doc.LinkEndChild( pRoot );

	TiXmlElement* pPlayer = new TiXmlElement{ "player_info" };

	pRoot->LinkEndChild( pPlayer );

	pPlayer->SetAttribute( "Health", health );
	pPlayer->SetDoubleAttribute( "PosX", posx );
	pPlayer->SetDoubleAttribute( "PosY", posy );
	pPlayer->SetAttribute( "CurrLevel", currLevel );

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vSword.size(); i++ )
	{
		TiXmlElement* pSword = new TiXmlElement{ "Sword" };

		pPlayer->LinkEndChild( pSword );

		pSword->SetAttribute( "Element", InventoryState::GetInstance()->m_vSword[i].GetElement() );
		pSword->SetAttribute( "Tier", InventoryState::GetInstance()->m_vSword[i].GetTier() );
	}

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vArmor.size(); i++ )
	{
		TiXmlElement* pArmor = new TiXmlElement{ "Armor" };

		pPlayer->LinkEndChild( pArmor );

		pArmor->SetAttribute( "Element", InventoryState::GetInstance()->m_vArmor[i].GetElement() );
		pArmor->SetAttribute( "Tier", InventoryState::GetInstance()->m_vArmor[i].GetTier() );
	}

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vRing.size(); i++ )
	{
		TiXmlElement* pRing = new TiXmlElement{ "Ring" };

		pPlayer->LinkEndChild( pRing );

		pRing->SetAttribute( "Element", InventoryState::GetInstance()->m_vRing[i].GetElement() );
		pRing->SetAttribute( "Tier", InventoryState::GetInstance()->m_vRing[i].GetTier() );
	}

	TiXmlElement* pInv = new TiXmlElement{ "Inventory" };
	pPlayer->LinkEndChild( pInv );
	pInv->SetAttribute( "Size", InventoryState::GetInstance()->m_vRunes.size() );

	for( unsigned int i = 0; i < InventoryState::GetInstance()->m_vRunes.size(); i++ )
	{
		TiXmlElement* pInv1 = new TiXmlElement{ "Rune" };
		pInv->LinkEndChild( pInv1 );

		pInv1->SetAttribute( "Element", InventoryState::GetInstance()->m_vRunes[i].GetElement() );
		pInv1->SetAttribute( "Tier", InventoryState::GetInstance()->m_vRunes[i].GetTier() );
	}

	doc.SaveFile( "resource/Save/Save3.xml" );
}

void SaveState::Load( string path )
{
	int health, currLevel;
	//, size;
	double posx, posy;
	//	int element, tier;
	vector<Runes> tempS;
	vector<Runes> tempA;
	vector<Runes> tempG;
	vector<Runes> tempInv;

	TiXmlDocument doc;

	if( doc.LoadFile( path.c_str() ) == false )
	{
		return;
	}

	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
	{
		return;
	}

	TiXmlElement* pPlayer = pRoot->FirstChildElement();

	pPlayer->Attribute( "Health", &health );
	pPlayer->Attribute( "PosX", &posx );
	pPlayer->Attribute( "PosY", &posy );
	pPlayer->Attribute( "CurrLevel", &currLevel );


	////Sword
	TiXmlElement* pSword = pPlayer->FirstChildElement("Sword");

	Runes temp2;
	pSword->Attribute("Tier", &tier);
	temp2.SetTier(tier);
	pSword->Attribute("Element", &element);
	temp2.SetElement((Elements)element);
	

	tempS.push_back(temp2);

	pSword = pSword->NextSiblingElement( "Sword" );

	pSword->Attribute("Element", &element);
	temp2.SetElement((Elements)element);
	pSword->Attribute("Tier", &tier);
	temp2.SetTier(tier);

	tempS.push_back(temp2);

	pSword = pSword->NextSiblingElement( "Sword" );

	pSword->Attribute("Element", &element);
	temp2.SetElement((Elements)element);
	pSword->Attribute("Tier", &tier);
	temp2.SetTier(tier);

	tempS.push_back(temp2);

	//Armor
	TiXmlElement* pArmor = pSword->NextSiblingElement("Armor");

	for (int i = 0; i < 3; i++)
	{
		Runes temp3;

		pArmor->Attribute("Element", &element);
		temp3.SetElement((Elements)element);
		pArmor->Attribute("Tier", &tier);
		temp3.SetTier(tier);

		tempA.push_back(temp3);
		if( i < 2 )
		{
			pArmor = pArmor->NextSiblingElement( "Armor" );

		}
	}

	//Ring
	TiXmlElement* pRing = pArmor->NextSiblingElement(/*"Ring"*/);

	for (int i = 0; i < 3; i++)
	{
		Runes temp4;

		pRing->Attribute("Element", &element);
		temp4.SetElement((Elements)element);
		pRing->Attribute("Tier", &tier);
		temp4.SetTier(tier);

		tempG.push_back(temp4);
		if( i < 2 )
		{
			pRing = pRing->NextSiblingElement( "Ring" );

		}
	}

	//inventory
	TiXmlElement* pInv = pRing->NextSiblingElement("Inventory");
	pInv->Attribute("Size", &size);

	if (size != 0)
	{
		TiXmlElement* pRunes = pInv->FirstChildElement("Rune");

		while (pRunes != nullptr)
		{
			//Read in
			Runes temp5;

			pRunes->Attribute("Element", &element);
			temp5.SetElement((Elements)element);
			pRunes->Attribute("Tier", &tier);
			temp5.SetTier(tier);

			tempInv.push_back(temp5);

			pRunes = pRunes->NextSiblingElement();
		}
	}


	Game::GetInstance()->RemoveState();
	Game::GetInstance()->AddState( GameplayState::GetInstance() );

	GameplayState::GetInstance()->SetLevel( currLevel );
	GameplayState::GetInstance()->LoadNewLevel();

	( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetHealth( health );
	( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetPosition( SGD::Point{ (float)posx, (float)posy } );

	InventoryState* pInventory = InventoryState::GetInstance();

	pInventory->AddRunesToSword0fromInventory(tempS[0]);
	pInventory->AddRunesToSword1fromInventory(tempS[1]);
	pInventory->AddRunesToSword2fromInventory(tempS[2]);

	pInventory->AddRunesToArmor0fromInventory(tempA[0]);
	pInventory->AddRunesToArmor1fromInventory(tempA[1]);
	pInventory->AddRunesToArmor2fromInventory(tempA[2]);

	pInventory->AddRunesToRing0fromInventory(tempG[0]);
	pInventory->AddRunesToRing1fromInventory(tempG[1]);
	pInventory->AddRunesToRing2fromInventory(tempG[2]);

	for (unsigned int i = 0; i < tempInv.size(); i++)
	{
		pInventory->AddRunesToInventoryfromWorld(tempInv[i]);
	}

}

void SaveState::Load2( string path )
{
	/*fstream fin;
	fin.open("resource/Save/Save2.txt", ios_base::in | ios_base::binary);
	if (fin.is_open())
	{
	int health, currLevel;
	float posx, posy;

	fin.read((char*)&health, sizeof(int));
	fin.read((char*)&posx, sizeof(float));
	fin.read((char*)&posy, sizeof(float));
	fin.read((char*)&currLevel, sizeof(int));

	Game::GetInstance()->RemoveState();
	Game::GetInstance()->AddState(GameplayState::GetInstance());


	GameplayState::GetInstance()->SetLevel(currLevel);
	GameplayState::GetInstance()->LoadNewLevel();

	((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetHealth(health);
	((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetPosition(SGD::Point{ posx, posy });

	fin.close();
	}*/

	int health, currLevel;
	//, size;
	double posx, posy;
	//	int element, tier;
	vector<Runes> tempS;
	vector<Runes> tempA;
	vector<Runes> tempG;
	vector<Runes> tempInv;

	TiXmlDocument doc;

	if( doc.LoadFile( path.c_str() ) == false )
	{
		return;
	}

	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
	{
		return;
	}

	TiXmlElement* pPlayer = pRoot->FirstChildElement();

	pPlayer->Attribute( "Health", &health );
	pPlayer->Attribute( "PosX", &posx );
	pPlayer->Attribute( "PosY", &posy );
	pPlayer->Attribute( "CurrLevel", &currLevel );


	////Sword
	TiXmlElement* pSword = pPlayer->FirstChildElement("Sword");

	Runes temp2;
	pSword->Attribute("Tier", &tier);
	temp2.SetTier(tier);
	pSword->Attribute("Element", &element);
	temp2.SetElement((Elements)element);


	tempS.push_back(temp2);

	pSword = pSword->NextSiblingElement("Sword");

	pSword->Attribute("Element", &element);
	temp2.SetElement((Elements)element);
	pSword->Attribute("Tier", &tier);
	temp2.SetTier(tier);

	tempS.push_back(temp2);

	pSword = pSword->NextSiblingElement("Sword");

	pSword->Attribute("Element", &element);
	temp2.SetElement((Elements)element);
	pSword->Attribute("Tier", &tier);
	temp2.SetTier(tier);

	tempS.push_back(temp2);

	//Armor
	TiXmlElement* pArmor = pSword->NextSiblingElement("Armor");

	for (int i = 0; i < 3; i++)
	{
		Runes temp3;

		pArmor->Attribute("Element", &element);
		temp3.SetElement((Elements)element);
		pArmor->Attribute("Tier", &tier);
		temp3.SetTier(tier);

		tempA.push_back(temp3);
		if (i < 2)
		{
			pArmor = pArmor->NextSiblingElement("Armor");

		}
	}

	//Ring
	TiXmlElement* pRing = pArmor->NextSiblingElement(/*"Ring"*/);

	for (int i = 0; i < 3; i++)
	{
		Runes temp4;

		pRing->Attribute("Element", &element);
		temp4.SetElement((Elements)element);
		pRing->Attribute("Tier", &tier);
		temp4.SetTier(tier);

		tempG.push_back(temp4);
		if (i < 2)
		{
			pRing = pRing->NextSiblingElement("Ring");

		}
	}

	//inventory
	TiXmlElement* pInv = pRing->NextSiblingElement("Inventory");
	pInv->Attribute("Size", &size);

	if (size != 0)
	{
		TiXmlElement* pRunes = pInv->FirstChildElement("Rune");

		while (pRunes != nullptr)
		{
			//Read in
			Runes temp5;

			pRunes->Attribute("Element", &element);
			temp5.SetElement((Elements)element);
			pRunes->Attribute("Tier", &tier);
			temp5.SetTier(tier);

			tempInv.push_back(temp5);

			pRunes = pRunes->NextSiblingElement();
		}
	}


	Game::GetInstance()->RemoveState();
	Game::GetInstance()->AddState( GameplayState::GetInstance() );

	GameplayState::GetInstance()->SetLevel( currLevel );
	GameplayState::GetInstance()->LoadNewLevel();

	( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetHealth( health );
	( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetPosition( SGD::Point{ (float)posx, (float)posy } );

	InventoryState* pInventory = InventoryState::GetInstance();

	pInventory->AddRunesToSword0fromInventory(tempS[0]);
	pInventory->AddRunesToSword1fromInventory(tempS[1]);
	pInventory->AddRunesToSword2fromInventory(tempS[2]);

	pInventory->AddRunesToArmor0fromInventory(tempA[0]);
	pInventory->AddRunesToArmor1fromInventory(tempA[1]);
	pInventory->AddRunesToArmor2fromInventory(tempA[2]);

	pInventory->AddRunesToRing0fromInventory(tempG[0]);
	pInventory->AddRunesToRing1fromInventory(tempG[1]);
	pInventory->AddRunesToRing2fromInventory(tempG[2]);

	for (unsigned int i = 0; i < tempInv.size(); i++)
	{
		pInventory->AddRunesToInventoryfromWorld(tempInv[i]);
	}


}

void SaveState::Load3( string path )
{
	//fstream fin;
	//fin.open("resource/Save/Save3.txt", ios_base::in | ios_base::binary);
	//if (fin.is_open())
	//{
	//	int health, currLevel;
	//	float posx, posy;

	//	fin.read((char*)&health, sizeof(int));
	//	fin.read((char*)&posx, sizeof(float));
	//	fin.read((char*)&posy, sizeof(float));
	//	fin.read((char*)&currLevel, sizeof(int));

	//	Game::GetInstance()->RemoveState();
	//	Game::GetInstance()->AddState(GameplayState::GetInstance());


	//	GameplayState::GetInstance()->SetLevel(currLevel);
	//	GameplayState::GetInstance()->LoadNewLevel();

	//	((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetHealth(health);
	//	((Player*)(GameplayState::GetInstance()->GetPlayer()))->SetPosition(SGD::Point{ posx, posy });

	//	fin.close();
	//}

	int health, currLevel;
	//	, size;
	double posx, posy;
	//	int element, tier;
	vector<Runes> tempS;
	vector<Runes> tempA;
	vector<Runes> tempG;
	vector<Runes> tempInv;

	TiXmlDocument doc;

	if( doc.LoadFile( path.c_str() ) == false )
	{
		return;
	}

	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
	{
		return;
	}

	TiXmlElement* pPlayer = pRoot->FirstChildElement();

	pPlayer->Attribute( "Health", &health );
	pPlayer->Attribute( "PosX", &posx );
	pPlayer->Attribute( "PosY", &posy );
	pPlayer->Attribute( "CurrLevel", &currLevel );


	////Sword
	TiXmlElement* pSword = pPlayer->FirstChildElement("Sword");

	Runes temp2;
	pSword->Attribute("Tier", &tier);
	temp2.SetTier(tier);
	pSword->Attribute("Element", &element);
	temp2.SetElement((Elements)element);


	tempS.push_back(temp2);

	pSword = pSword->NextSiblingElement("Sword");

	pSword->Attribute("Element", &element);
	temp2.SetElement((Elements)element);
	pSword->Attribute("Tier", &tier);
	temp2.SetTier(tier);

	tempS.push_back(temp2);

	pSword = pSword->NextSiblingElement("Sword");

	pSword->Attribute("Element", &element);
	temp2.SetElement((Elements)element);
	pSword->Attribute("Tier", &tier);
	temp2.SetTier(tier);

	tempS.push_back(temp2);

	//Armor
	TiXmlElement* pArmor = pSword->NextSiblingElement("Armor");

	for (int i = 0; i < 3; i++)
	{
		Runes temp3;

		pArmor->Attribute("Element", &element);
		temp3.SetElement((Elements)element);
		pArmor->Attribute("Tier", &tier);
		temp3.SetTier(tier);

		tempA.push_back(temp3);
		if (i < 2)
		{
			pArmor = pArmor->NextSiblingElement("Armor");

		}
	}

	//Ring
	TiXmlElement* pRing = pArmor->NextSiblingElement(/*"Ring"*/);

	for (int i = 0; i < 3; i++)
	{
		Runes temp4;

		pRing->Attribute("Element", &element);
		temp4.SetElement((Elements)element);
		pRing->Attribute("Tier", &tier);
		temp4.SetTier(tier);

		tempG.push_back(temp4);
		if (i < 2)
		{
			pRing = pRing->NextSiblingElement("Ring");

		}
	}

	//inventory
	TiXmlElement* pInv = pRing->NextSiblingElement("Inventory");
	pInv->Attribute("Size", &size);

	if (size != 0)
	{
		TiXmlElement* pRunes = pInv->FirstChildElement("Rune");

		while (pRunes != nullptr)
		{
			//Read in
			Runes temp5;

			pRunes->Attribute("Element", &element);
			temp5.SetElement((Elements)element);
			pRunes->Attribute("Tier", &tier);
			temp5.SetTier(tier);

			tempInv.push_back(temp5);

			pRunes = pRunes->NextSiblingElement();
		}
	}


	Game::GetInstance()->RemoveState();
	Game::GetInstance()->AddState( GameplayState::GetInstance() );

	GameplayState::GetInstance()->SetLevel( currLevel );
	GameplayState::GetInstance()->LoadNewLevel();

	( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetHealth( health );
	( (Player*)( GameplayState::GetInstance()->GetPlayer() ) )->SetPosition( SGD::Point{ (float)posx, (float)posy } );

	InventoryState* pInventory = InventoryState::GetInstance();

	pInventory->AddRunesToSword0fromInventory(tempS[0]);
	pInventory->AddRunesToSword1fromInventory(tempS[1]);
	pInventory->AddRunesToSword2fromInventory(tempS[2]);

	pInventory->AddRunesToArmor0fromInventory(tempA[0]);
	pInventory->AddRunesToArmor1fromInventory(tempA[1]);
	pInventory->AddRunesToArmor2fromInventory(tempA[2]);

	pInventory->AddRunesToRing0fromInventory(tempG[0]);
	pInventory->AddRunesToRing1fromInventory(tempG[1]);
	pInventory->AddRunesToRing2fromInventory(tempG[2]);

	for (unsigned int i = 0; i < tempInv.size(); i++)
	{
		pInventory->AddRunesToInventoryfromWorld(tempInv[i]);
	}

}


