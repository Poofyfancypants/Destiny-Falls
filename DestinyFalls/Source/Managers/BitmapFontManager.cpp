#include "stdafx.h"
#include "BitmapFontManager.h"

#include <iterator>
#include "../../SGD Wrappers/SGD_GraphicsManager.h"


//***********************************************************************
// SINGLETON
//	- instantiate the static member
BitmapFontManager* BitmapFontManager::s_pInstance = nullptr;

BitmapFontManager* BitmapFontManager::GetInstance()
{
	if( s_pInstance == nullptr )
	{
		s_pInstance = new BitmapFontManager;
	}

	return s_pInstance;
}

void BitmapFontManager::DeleteInstance()
{
	//Create an iterator to traverse the LoadedFonts map
	auto iter = GetInstance()->LoadedFonts.begin();

	//Kill off all the memory leaks
	for( ; iter != GetInstance()->LoadedFonts.end(); ++iter )
	{
		//Delete Font Images
		SGD::GraphicsManager::GetInstance()->UnloadTexture( GetInstance()->LoadedFonts[ iter->first ]->GetImage());

		// Delete fonts
		delete GetInstance()->LoadedFonts[ iter->first ];
	}

	//Delete the singleton and set it to null
	delete s_pInstance;
	s_pInstance = nullptr;
}

void BitmapFontManager::Render( string fontName, const char* output , SGD::Point position , float scale , SGD::Color color )
{
	LoadedFonts[ fontName ]->Draw( output , position , scale , color );
}

void BitmapFontManager::Load( string fontName ,  string imageName , string fileName )
{
	BitmapFont* newFont = new BitmapFont;

	newFont->SetFontName( fontName );
	newFont->Initialize( imageName );
	newFont->LoadFontFile( fileName );
	AddToBitmapFontMap( newFont );

}



void BitmapFontManager::AddToBitmapFontMap( BitmapFont* font )
{
	if( font != nullptr )
	{
		LoadedFonts[ font->GetFontName() ] = font;
	}
}

int BitmapFontManager::CheckSize()
{
	return LoadedFonts.size();
}