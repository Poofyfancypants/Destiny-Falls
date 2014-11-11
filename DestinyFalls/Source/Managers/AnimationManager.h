//***********************************************************************
//	File:		AnimationManager.h
//	Author:		Yvonne Neuland
//	Course:		SGP
//	Purpose:	
//***********************************************************************

#pragma once

#include "..\Engines\Frame.h"
#include "..\Engines\Animation.h"
#include "..\Engines\AnimationTimeStamp.h"

#include <string>
#include <map>
using namespace std;

class AnimationManager
{

private:
	map<string , Animation*> Loaded;

	//*******************************************************************
	// SINGLETON!
	//	- static member to hold the singleton object
	//	- prevent access to constructors / destructor / =op
	static AnimationManager* s_pInstance;

public:
	AnimationManager() = default;
	~AnimationManager() = default;

	//*******************************************************************
	// SINGLETON!
	//	- static accessor to get the singleton object
	static AnimationManager* GetInstance();
	static void DeleteInstance();

	void Render( AnimationTimeStamp& ts , int posX , int posY );
	void Update( AnimationTimeStamp& ts , float dt );
	void Load( string fileName );

	void AddToAnimationMap( Animation* animation );

};

