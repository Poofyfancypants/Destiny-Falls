#include "stdafx.h"
#include "DialogManager.h"



//***********************************************************************
// SINGLETON
//	- instantiate the static member
DialogManager* DialogManager::s_pInstance = nullptr;

// GetInstance
//	- allocate the singleton if necessary
//	- return the singleton
DialogManager* DialogManager::GetInstance()
{
	if( s_pInstance == nullptr )
	{
		s_pInstance = new DialogManager;
	}

	return s_pInstance;
}

// DeleteInstance
//	- deallocate the singleton
void DialogManager::DeleteInstance()
{

	//GetInstance()->Loaded.clear();
	auto iter = GetInstance()->Loaded.begin();

	for( ; iter != GetInstance()->Loaded.end(); ++iter )
	{
		//SGD::GraphicsManager::GetInstance()->UnloadTexture( GetInstance()->Loaded[ iter->first ]->GetImage() );

		// Do some stuff
		delete GetInstance()->Loaded[ iter->first ];
	}

	delete s_pInstance;
	s_pInstance = nullptr;
}

void DialogManager::Render()
{

}

void DialogManager::Update()
{

}

void DialogManager::Load( string fileName )
{
	assert( fileName.c_str() != nullptr && fileName[ 0 ] != '\0' && "AnimationManager:Load - Invalid filename" );
	
	//create the TinyXML Document
	TiXmlDocument doc;


	//Attempt to load the file
	//	(will allocate & set the Entire tree)
	if( doc.LoadFile( fileName.c_str() ) == false )
	{
		return;
	}

	//Access the root Element ("Dialogue")
	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
	{
		return;
	}

	//Access the root's first "Message" Element
	TiXmlElement* pMessage = pRoot->FirstChildElement();

	if( pMessage == nullptr )
	{
		return;
	}

	while( pMessage != nullptr )
	{
		Dialog * dialog = new Dialog;

		//Access the Messages first "Name" Element
		TiXmlElement* pName = pMessage->FirstChildElement("Name");

		//pAnimation = pAnimation->FirstChildElement();

		if( pName == nullptr )
		{
			return;
		}

		//Access the player element's Text
		string pText = pName->GetText();
		if( pText.c_str() != nullptr )
		{
			dialog->SetName( pText );
		}


		pText.clear();

		//Access the Messages first "Portrait" Element
		TiXmlElement* pPortrait = pName->NextSiblingElement( "Portrait" );

		pText = pPortrait->GetText();
		if( pText.c_str() != nullptr )
		{
			dialog->SetImageName( pText );
		}

		pText.clear();

		//Access the Messages first "Words" Element
		TiXmlElement* pWords = pPortrait->NextSiblingElement( "Words" );

		pText = pWords->GetText();
		if( pText.c_str() != nullptr )
		{
			dialog->SetWords( pText );
		}

		AddToDialogMap( dialog );

		//Move to the next "Message" Sibling Element
		pMessage = pMessage->NextSiblingElement( "Message" );
	}
}

void DialogManager::AddToDialogMap( Dialog* dialog )
{
	if( dialog != nullptr )
	{
		Loaded[ dialog->GetName() ] = dialog;
	}
}

int DialogManager::CheckSize()
{
	return Loaded.size();
}