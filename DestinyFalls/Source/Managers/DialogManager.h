#pragma once

#include "..\Engines\Dialog.h"
#include "BitmapFontManager.h"

#include "../TinyXML/tinyxml.h"
#include "../TinyXML/tinystr.h"

#include <map>


class DialogManager
{
private:
	map<string , Dialog*> Loaded;

	//*******************************************************************
	// SINGLETON!
	//	- static member to hold the singleton object
	//	- prevent access to constructors / destructor / =op
	static DialogManager* s_pInstance;

public:
	DialogManager() = default;
	~DialogManager() = default;

	//*******************************************************************
	// SINGLETON!
	//	- static accessor to get the singleton object
	static DialogManager* GetInstance();
	static void DeleteInstance();

	void Render(  );
	void Update(  );
	void Load( string fileName );

	void AddToDialogMap( Dialog* dialog );

	int CheckSize();

};

