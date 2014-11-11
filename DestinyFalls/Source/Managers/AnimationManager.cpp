#include "stdafx.h"
#include "AnimationManager.h"
#include <fstream>
#include <cassert>
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
		int lastFrame = Loaded[ ts.GetCurrentAnimation() ]->GetFrameVector().size()-1;

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

		ts.SetTimeOnFrame( 0.0f );

	}
}

void AnimationManager::Load( string fileName )
{
	assert( fileName.c_str() != nullptr && fileName[ 0 ] != '\0' && "AnimationManager:Load - Invalid filename" );
	SGD::GraphicsManager*	pGraphics = SGD::GraphicsManager::GetInstance();

	//create the TinyXML Document
	TiXmlDocument doc;
	

	//Attempt to load the file
	//	(will allocate & set the Entire tree)
	if( doc.LoadFile( fileName.c_str() ) == false )
	{
		return;
	}

	//Access the root Element ("Root")
	TiXmlElement* pRoot = doc.RootElement();

	if( pRoot == nullptr )
	{
		return;
	}

	//Access the root's first "Root" Element
	//TiXmlElement* pAnimation = pRoot->FirstChildElement( "Root" );

	//Access the root's first "animation" Element
	TiXmlElement* pAnimation = pRoot->FirstChildElement(); 
	
	if( pAnimation == nullptr )
	{
		return;
	}

	//Access the root's first "animation_info" Element
	pAnimation = pAnimation->FirstChildElement( );

	if( pAnimation == nullptr )
	{
		return;
	}

	//Get all the animations
	while( pAnimation != nullptr )
	{
		Animation* a = new Animation;

		//Access the animation element's name
		string szText = "";
		szText = pAnimation->Attribute( "name" );

		if( szText != "" )
		{
			a->SetName( szText );
		}

		Loaded[ a->GetName() ] = a;

		//Get the looping bool
		bool bLoops;
		int temp;
		pAnimation->Attribute( "looping" , &temp );
		bLoops = temp;
		Loaded[ a->GetName() ]->SetLooping( bLoops );

		//Get the filepath for the image
		string  tName = "";
		tName = pAnimation->Attribute( "hTexture" );

		SGD::HTexture m_hImage = SGD::INVALID_HANDLE;
		m_hImage = pGraphics->LoadTexture( tName.c_str() );
		Loaded[ a->GetName() ]->SetImage( m_hImage );

		//Clear the frames vector
		Loaded[ a->GetName() ]->GetFrameVector().clear();

		//Get the number of frames in the animation
		int nFrames = 0;

		pAnimation->Attribute( "numFrames" , &nFrames );

		//Access the animations's first "frame" Element
		TiXmlElement* pFrame = pAnimation->FirstChildElement();

		//get each of the frames in the image
		while( pFrame != nullptr )
		{
			Frame f;
			/*<frame duration="0.5" damage="0" event="none" dLeft="4" dTop="520" dRight="47" dBottom="580" cLeft="4" cTop="520" cRight="47" cBottom="580" x="24" y="577"/>*/

			//Get the frame's duration
			double dur;
			pFrame->Attribute( "duration" , &dur );
			f.SetDuration( dur );

			//Get the frame's damage
			int dam;
			pFrame->Attribute( "damage" , &dam );
			f.SetDamage( dam );

			//Get the frame's event name
			string eve = "";
			eve = pFrame->Attribute( "event" );
			f.SetEventName( eve );

			//Get the drawRect
			SGD::Rectangle dRect;

				//Get the drawRect left
				int dleft;
				pFrame->Attribute( "dLeft" , &dleft );

				//Get the drawRect top
				int dtop;
				pFrame->Attribute( "dTop" , &dtop );

				//Get the drawRect right
				int drig;
				pFrame->Attribute( "dRight" , &drig );

				//Get the drawRect bottom
				int dbot;
				pFrame->Attribute( "dBottom" , &dbot );

				//set the drect left/top/bottom/right to the read in variables
				dRect.left = dleft;
				dRect.top = dtop;
				dRect.right = drig;
				dRect.bottom = dbot;

				//set the frame's draw rect to the drect
				f.SetDrawRect( dRect );


			//Get the collisionRect
			SGD::Rectangle cRect;

				//Get the collisionRect left
				int cleft;
				pFrame->Attribute( "cLeft" , &cleft );

				//Get the collisionRect top
				int ctop;
				pFrame->Attribute( "cTop" , &ctop );

				//Get the collisionRect right
				int crig;
				pFrame->Attribute( "cRight" , &crig );

				//Get the collisionRect bottom
				int cbot;
				pFrame->Attribute( "cBottom" , &cbot );
			
				//set the crect left/top/bottom/right to the read in variables
				cRect.left = cleft;
				cRect.top = ctop;
				cRect.right = crig;
				cRect.bottom = cbot;

				//add the crect to the frame collisionrects vector
				f.AddCollisionRect( cRect );

			//Get anchor point
				SGD::Point aP;
			//Get anchor point x
				int aX;
				pFrame->Attribute( "x" , &aX );

			//Get anchor point y
				int aY;
				pFrame->Attribute( "y" , &aY );

				aP.x = aX;
				aP.y = aY;

				f.SetAnchorPoint( aP );

			//Add the new frame to a's frame vector
			Loaded[ a->GetName() ]->AddFrame( f );

			
			//Move to the next "frame" Sibling Element if there are more frames
			pFrame = pFrame->NextSiblingElement( );
			
		}
		pAnimation = pAnimation->NextSiblingElement();
	}
}

void AnimationManager::AddToAnimationMap( Animation* animation )
{
	if( animation != nullptr )
	{
		Loaded[ animation->GetName() ] = animation;
	}
}