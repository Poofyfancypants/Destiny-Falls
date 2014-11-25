#include "stdafx.h"
#include "BitmapFontManager.h"

#include <iterator>


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
	auto iter = GetInstance()->LoadedFonts.begin();

	for( ; iter != GetInstance()->LoadedFonts.end(); ++iter )
	{
		//SGD::GraphicsManager::GetInstance()->UnloadTexture( GetInstance()->Loaded[ iter->first ]->GetImage() );

		// Do some stuff
		delete GetInstance()->LoadedFonts[ iter->first ];
	}

	delete s_pInstance;
	s_pInstance = nullptr;
}

void BitmapFontManager::Render( string fontName, const char* output , SGD::Point position , float scale , SGD::Color color )
{
	LoadedFonts[ fontName ]->Draw( output , position , scale , color );
}

void BitmapFontManager::Load( string fontName, string fileName )
{
	BitmapFont* newFont = new BitmapFont;
	newFont->SetFontName( fontName );
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