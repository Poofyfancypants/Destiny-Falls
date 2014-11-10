#include "stdafx.h"
#include "AnimationManager.h"
#include <fstream>

#include "..\..\SGD Wrappers\SGD_Geometry.h"
#include"..\..\SGD Wrappers\SGD_GraphicsManager.h"

//***********************************************************************
// SINGLETON
//	- instantiate the static member
AnimationManager* AnimationManager::s_pInstance = nullptr;

// GetInstance
//	- allocate the singleton if necessary
//	- return the singleton
AnimationManager* AnimationManager::GetInstance()
{
	if( s_pInstance == nullptr )
	{
		s_pInstance = new AnimationManager;
	}

	return s_pInstance;
}

// DeleteInstance
//	- deallocate the singleton
void AnimationManager::DeleteInstance()
{
	delete s_pInstance;
	s_pInstance = nullptr;
}

void AnimationManager::Render( AnimationTimeStamp& ts , int posX , int posY )
{
	//Draw the frame
	SGD::GraphicsManager::GetInstance()->DrawTextureSection(
		Loaded[ ts.GetCurrentAnimation() ]->GetImage() ,
		{ posX - Loaded[ ts.GetCurrentAnimation() ]->GetFrame( ts.GetCurrentFrame() ).GetAnchorPoint().x ,
		posY - Loaded[ ts.GetCurrentAnimation() ]->GetFrame( ts.GetCurrentFrame() ).GetAnchorPoint().y } ,
		Loaded[ ts.GetCurrentAnimation() ]->GetFrame( ts.GetCurrentFrame() ).GetDrawRect()
		);
}

void AnimationManager::Update( AnimationTimeStamp& ts , float dt )
{
	if( ts.GetTimeOnFrame() + dt < Loaded[ ts.GetCurrentAnimation() ]->GetFrame( ts.GetCurrentFrame() ).GetDuration() )
	{
		ts.SetTimeOnFrame( ts.GetTimeOnFrame() + dt );
	}
	else
	{
		//What is the last frame in the animation?
		int lastFrame = Loaded[ ts.GetCurrentAnimation() ]->GetFrameVector().size();

		//if we are not on the last frame in the animation
		if( ts.GetCurrentFrame() < lastFrame )
		{
			ts.SetCurrentFrame( ts.GetCurrentFrame() + 1 );
		}
		//else if we are on the last frame in the animation and the animation loops
		else if( ts.GetCurrentFrame() == lastFrame && Loaded[ ts.GetCurrentAnimation() ]->GetLooping() == true )
		{
			ts.SetCurrentFrame( 0 );
		}
		//else if we are on the last frame in the animation and the animation does not loop
		else
		{
			ts.SetCurrentFrame( lastFrame );
		}

	}
}

void AnimationManager::Load( string fileName )
{

	//create the TinyXML Document
	TiXmlDocument doc;

	//Attempt to load the file
	//	(will allocate & set the Entire tree)
	if( doc.LoadFile( fileName.c_str() ) == false )
	{
		return;
	}

	//Access the root Element ("Animation_List")
	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
	{
		return;
	}



}

void AnimationManager::AddToAnimationMap( Animation* animation )
{
	if( animation != nullptr )
	{
		Loaded[ animation->GetName() ] = animation;
	}
}