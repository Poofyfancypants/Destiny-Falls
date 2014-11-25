#pragma once

#include "../Bitmap Font/BitmapFont.h"
#include <string>
#include <map>
using namespace std;

class BitmapFontManager
{

	map<string , BitmapFont*> LoadedFonts;
	//*******************************************************************
	// SINGLETON!
	//	- static member to hold the singleton object
	//	- prevent access to constructors / destructor / =op
	static BitmapFontManager* s_pInstance;
public:
	BitmapFontManager() = default;
	~BitmapFontManager() = default;

	//*******************************************************************
	// SINGLETON!
	//	- static accessor to get the singleton object
	static BitmapFontManager* GetInstance();
	static void DeleteInstance();

	void Render(string fontName, const char* output , SGD::Point position, float scale, SGD::Color color );
	//void Initialize( string fontName, string path );
	void Load( string fontName, string imageName, string fileName );

	void AddToBitmapFontMap( BitmapFont* font );

	int CheckSize();
};

